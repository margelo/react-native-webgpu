#include "GPUTexture.h"

#include <memory>
#include <string>

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

  size_t bytesPerPixel = 4; // Default to RGBA8 format
  wgpu::TextureFormat format = _instance.GetFormat();
  switch (format) {
  case wgpu::TextureFormat::R8Unorm:
  case wgpu::TextureFormat::R8Snorm:
  case wgpu::TextureFormat::R8Uint:
  case wgpu::TextureFormat::R8Sint:
  case wgpu::TextureFormat::Stencil8:
    bytesPerPixel = 1;
    break;
  case wgpu::TextureFormat::R16Uint:
  case wgpu::TextureFormat::R16Sint:
  case wgpu::TextureFormat::R16Float:
  case wgpu::TextureFormat::RG8Unorm:
  case wgpu::TextureFormat::RG8Snorm:
  case wgpu::TextureFormat::RG8Uint:
  case wgpu::TextureFormat::RG8Sint:
  case wgpu::TextureFormat::Depth16Unorm:
    bytesPerPixel = 2;
    break;
  case wgpu::TextureFormat::RGBA8Unorm:
  case wgpu::TextureFormat::RGBA8UnormSrgb:
  case wgpu::TextureFormat::RGBA8Snorm:
  case wgpu::TextureFormat::RGBA8Uint:
  case wgpu::TextureFormat::RGBA8Sint:
  case wgpu::TextureFormat::BGRA8Unorm:
  case wgpu::TextureFormat::BGRA8UnormSrgb:
  case wgpu::TextureFormat::RGB10A2Unorm:
  case wgpu::TextureFormat::R32Float:
  case wgpu::TextureFormat::R32Uint:
  case wgpu::TextureFormat::R32Sint:
  case wgpu::TextureFormat::RG16Uint:
  case wgpu::TextureFormat::RG16Sint:
  case wgpu::TextureFormat::RG16Float:
  case wgpu::TextureFormat::Depth24Plus:
  case wgpu::TextureFormat::Depth24PlusStencil8:
  case wgpu::TextureFormat::Depth32Float:
    bytesPerPixel = 4;
    break;
  case wgpu::TextureFormat::RG32Float:
  case wgpu::TextureFormat::RG32Uint:
  case wgpu::TextureFormat::RG32Sint:
  case wgpu::TextureFormat::RGBA16Uint:
  case wgpu::TextureFormat::RGBA16Sint:
  case wgpu::TextureFormat::RGBA16Float:
  case wgpu::TextureFormat::Depth32FloatStencil8:
    bytesPerPixel = 8;
    break;
  case wgpu::TextureFormat::RGBA32Float:
  case wgpu::TextureFormat::RGBA32Uint:
  case wgpu::TextureFormat::RGBA32Sint:
    bytesPerPixel = 16;
    break;
  default:
    bytesPerPixel = 4; // Safe default
    break;
  }

  size_t totalMemory = 0;
  for (uint32_t mip = 0; mip < mipLevelCount; ++mip) {
    uint32_t mipWidth = std::max(1u, width >> mip);
    uint32_t mipHeight = std::max(1u, height >> mip);
    totalMemory += static_cast<size_t>(mipWidth) * mipHeight *
                   depthOrArrayLayers * bytesPerPixel * sampleCount;
  }

  return totalMemory;
}

} // namespace rnwgpu
