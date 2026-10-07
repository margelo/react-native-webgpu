#include "GPUTexture.h"

#include <memory>
#include <string>

#include "BytesPerPixel.h"
#include "EnforceRange.h"

namespace rnwgpu {

std::shared_ptr<margelo::nitro::webgpu::HybridGPUTextureViewSpec>
GPUTexture::createView(
    const std::optional<margelo::nitro::webgpu::GPUTextureViewDescriptor>
        &descriptor) {
  wgpu::TextureViewDescriptor desc;
  std::string label;
  if (descriptor.has_value()) {
    label = descriptor->label.value_or("");
    desc.label = label.c_str();
    if (descriptor->format) {
      desc.format = toWGPU(*descriptor->format);
    }
    if (descriptor->dimension) {
      desc.dimension = toWGPU(*descriptor->dimension);
    }
    if (descriptor->usage) {
      desc.usage = static_cast<wgpu::TextureUsage>(
          enforceRange<uint32_t>(*descriptor->usage, "usage"));
    }
    if (descriptor->aspect) {
      desc.aspect = toWGPU(*descriptor->aspect);
    }
    if (descriptor->baseMipLevel) {
      desc.baseMipLevel =
          enforceRange<uint32_t>(*descriptor->baseMipLevel, "baseMipLevel");
    }
    if (descriptor->mipLevelCount) {
      desc.mipLevelCount =
          enforceRange<uint32_t>(*descriptor->mipLevelCount, "mipLevelCount");
    }
    if (descriptor->baseArrayLayer) {
      desc.baseArrayLayer =
          enforceRange<uint32_t>(*descriptor->baseArrayLayer, "baseArrayLayer");
    }
    if (descriptor->arrayLayerCount) {
      desc.arrayLayerCount = enforceRange<uint32_t>(
          *descriptor->arrayLayerCount, "arrayLayerCount");
    }
  }
  return std::make_shared<GPUTextureView>(_instance.CreateView(&desc), label);
}

size_t GPUTexture::getExternalMemorySize() noexcept {
  if (!_reportsMemoryPressure) {
    return sizeof(GPUTexture);
  }
  uint32_t width = _instance.GetWidth();
  uint32_t height = _instance.GetHeight();
  uint32_t depthOrArrayLayers = _instance.GetDepthOrArrayLayers();
  uint32_t mipLevelCount = _instance.GetMipLevelCount();
  uint32_t sampleCount = _instance.GetSampleCount();

  size_t pixelSize = bytesPerPixel(_instance.GetFormat());

  size_t totalMemory = 0;
  for (uint32_t mip = 0; mip < mipLevelCount; ++mip) {
    uint32_t mipWidth = std::max(1u, width >> mip);
    uint32_t mipHeight = std::max(1u, height >> mip);
    totalMemory += static_cast<size_t>(mipWidth) * mipHeight *
                   depthOrArrayLayers * pixelSize * sampleCount;
  }

  return totalMemory;
}

} // namespace rnwgpu
