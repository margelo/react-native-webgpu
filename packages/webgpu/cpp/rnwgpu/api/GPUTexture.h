#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "EnumMaps.h"
#include "GPUTextureView.h"
#include "HybridGPUTextureSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUTexture
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUTextureSpec> {
public:
  GPUTexture(wgpu::Texture instance, std::string label,
             bool reportsMemoryPressure = true)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)),
        _reportsMemoryPressure(reportsMemoryPressure) {}

  std::shared_ptr<margelo::nitro::webgpu::HybridGPUTextureViewSpec> createView(
      const std::optional<margelo::nitro::webgpu::GPUTextureViewDescriptor>
          &descriptor) override;
  void destroy() override { _instance.Destroy(); }

  double getWidth() override { return _instance.GetWidth(); }
  double getHeight() override { return _instance.GetHeight(); }
  double getDepthOrArrayLayers() override {
    return _instance.GetDepthOrArrayLayers();
  }
  double getMipLevelCount() override { return _instance.GetMipLevelCount(); }
  double getSampleCount() override { return _instance.GetSampleCount(); }
  margelo::nitro::webgpu::GPUTextureDimension getDimension() override {
    return fromWGPU(_instance.GetDimension());
  }
  margelo::nitro::webgpu::GPUTextureFormat getFormat() override {
    return fromWGPU(_instance.GetFormat());
  }
  double getUsage() override {
    return static_cast<double>(_instance.GetUsage());
  }
  uint64_t getNativePointer() override {
    return reinterpret_cast<uint64_t>(_instance.Get());
  }

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::Texture get() { return _instance; }

protected:
  size_t getExternalMemorySize() noexcept override;

private:
  wgpu::Texture _instance;
  std::string _label;
  bool _reportsMemoryPressure;
};

} // namespace rnwgpu
