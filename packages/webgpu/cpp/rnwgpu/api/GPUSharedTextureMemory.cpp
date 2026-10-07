#include "GPUSharedTextureMemory.h"

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "BytesPerPixel.h"
#include "EnforceRange.h"
#include "EnumMaps.h"
#include "GPUSharedFence.h"
#include "GPUTexture.h"

namespace rnwgpu {

using margelo::nitro::webgpu::GPUSharedFenceState;
using margelo::nitro::webgpu::GPUSharedTextureMemoryEndAccessState;
using margelo::nitro::webgpu::GPUTextureDescriptor;
using margelo::nitro::webgpu::HybridGPUSharedFenceSpec;
using margelo::nitro::webgpu::HybridGPUTextureSpec;

namespace {

wgpu::Texture
unwrapTexture(const std::shared_ptr<HybridGPUTextureSpec> &texture) {
  auto gpuTexture = std::dynamic_pointer_cast<GPUTexture>(texture);
  if (gpuTexture == nullptr) [[unlikely]] {
    throw std::runtime_error(
        "The given `GPUTexture` instance is not of type `rnwgpu::GPUTexture`!");
  }
  return gpuTexture->get();
}

wgpu::SharedFence
unwrapSharedFence(const std::shared_ptr<HybridGPUSharedFenceSpec> &fence) {
  auto gpuSharedFence = std::dynamic_pointer_cast<GPUSharedFence>(fence);
  if (gpuSharedFence == nullptr) [[unlikely]] {
    throw std::runtime_error("The given `GPUSharedFence` instance is not of "
                             "type `rnwgpu::GPUSharedFence`!");
  }
  return gpuSharedFence->get();
}

} // namespace

std::shared_ptr<HybridGPUTextureSpec> GPUSharedTextureMemory::createTexture(
    const std::optional<GPUTextureDescriptor> &descriptor) {
  if (!descriptor.has_value()) {
    return std::make_shared<GPUTexture>(_instance.CreateTexture(), "");
  }

  wgpu::TextureDescriptor desc;
  std::string label = descriptor->label.value_or("");
  desc.label = label.c_str();
  desc.size.width = enforceRange<uint32_t>(descriptor->size.width, "width");
  desc.size.height = enforceRange<uint32_t>(descriptor->size.height, "height");
  desc.size.depthOrArrayLayers = enforceRange<uint32_t>(
      descriptor->size.depthOrArrayLayers, "depthOrArrayLayers");
  if (descriptor->mipLevelCount) {
    desc.mipLevelCount =
        enforceRange<uint32_t>(*descriptor->mipLevelCount, "mipLevelCount");
  }
  if (descriptor->sampleCount) {
    desc.sampleCount =
        enforceRange<uint32_t>(*descriptor->sampleCount, "sampleCount");
  }
  if (descriptor->dimension) {
    desc.dimension = toWGPU(*descriptor->dimension);
  }
  desc.format = toWGPU(descriptor->format);
  desc.usage = static_cast<wgpu::TextureUsage>(
      enforceRange<uint32_t>(descriptor->usage, "usage"));
  std::vector<wgpu::TextureFormat> viewFormats;
  if (descriptor->viewFormats) {
    for (auto format : *descriptor->viewFormats) {
      viewFormats.push_back(toWGPU(format));
    }
    desc.viewFormatCount = viewFormats.size();
    desc.viewFormats = viewFormats.data();
  }
  return std::make_shared<GPUTexture>(_instance.CreateTexture(&desc), label);
}

void GPUSharedTextureMemory::beginAccess(
    const std::shared_ptr<HybridGPUTextureSpec> &texture, bool initialized,
    const std::optional<std::vector<GPUSharedFenceState>> &fences) {
  wgpu::SharedTextureMemoryBeginAccessDescriptor desc{};
  desc.initialized = initialized;
  desc.concurrentRead = false;

  // Built in lockstep so fenceCount covers both arrays, and kept in locals so
  // the raw pointers outlive the synchronous BeginAccess() below.
  std::vector<wgpu::SharedFence> rawFences;
  std::vector<uint64_t> values;
  if (fences.has_value()) {
    for (const auto &state : *fences) {
      rawFences.push_back(unwrapSharedFence(state.fence));
      values.push_back(state.signaledValue);
    }
    desc.fenceCount = rawFences.size();
    desc.fences = rawFences.data();
    desc.signaledValues = values.data();
  }

#if defined(__ANDROID__)
  // Dawn's Vulkan backend (AHardwareBuffer) validates that the begin-access
  // descriptor chains a SharedTextureMemoryVkImageLayoutBeginState specifying
  // the VkImageLayout to acquire the image into. UNDEFINED (= 0) on both ends
  // is the canonical "no prior GPU producer" pattern: Dawn performs an
  // external-queue acquire from VK_QUEUE_FAMILY_EXTERNAL which preserves the
  // AHB contents, then transitions to whatever layout the texture's actual
  // usage requires.
  wgpu::SharedTextureMemoryVkImageLayoutBeginState vkLayout{};
  vkLayout.oldLayout = 0;
  vkLayout.newLayout = 0;
  desc.nextInChain = &vkLayout;
#endif

  auto status = _instance.BeginAccess(unwrapTexture(texture), &desc);
  if (status != wgpu::Status::Success) {
    throw std::runtime_error("GPUSharedTextureMemory::beginAccess() failed");
  }
}

GPUSharedTextureMemoryEndAccessState GPUSharedTextureMemory::endAccess(
    const std::shared_ptr<HybridGPUTextureSpec> &texture) {
  wgpu::SharedTextureMemoryEndAccessState state{};

#if defined(__ANDROID__)
  // Dawn's Vulkan backend writes the released old/new VkImageLayouts back into
  // a chained SharedTextureMemoryVkImageLayoutEndState; validation requires
  // the chain even when the caller doesn't read the values.
  wgpu::SharedTextureMemoryVkImageLayoutEndState vkLayout{};
  state.nextInChain = &vkLayout;
#endif

  auto status = _instance.EndAccess(unwrapTexture(texture), &state);
  if (status != wgpu::Status::Success) {
    throw std::runtime_error("GPUSharedTextureMemory::endAccess() failed");
  }

  // Copy each wgpu::SharedFence (ref-counted) into its own GPUSharedFence
  // wrapper before `state` is destroyed.
  std::vector<GPUSharedFenceState> fences;
  fences.reserve(state.fenceCount);
  for (size_t i = 0; i < state.fenceCount; i++) {
    fences.emplace_back(std::make_shared<GPUSharedFence>(state.fences[i], ""),
                        state.signaledValues[i]);
  }
  return GPUSharedTextureMemoryEndAccessState(
      static_cast<bool>(state.initialized), std::move(fences));
}

size_t GPUSharedTextureMemory::getExternalMemorySize() noexcept {
  wgpu::SharedTextureMemoryProperties properties{};
  _instance.GetProperties(&properties);
  size_t width = properties.size.width;
  size_t height = properties.size.height;
  size_t layers = properties.size.depthOrArrayLayers;
  return width * height * layers * bytesPerPixel(properties.format);
}

} // namespace rnwgpu
