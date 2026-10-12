#pragma once

#include <string>

#include "HybridGPUAdapterInfoSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUAdapterInfo
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUAdapterInfoSpec> {
public:
  explicit GPUAdapterInfo(wgpu::AdapterInfo &info)
      : HybridObject(TAG), _vendor(info.vendor),
        _architecture(info.architecture), _device(info.device),
        _description(info.description),
        _isFallbackAdapter(info.adapterType == wgpu::AdapterType::CPU) {}

  std::string getVendor() override { return _vendor; }
  std::string getArchitecture() override { return _architecture; }
  std::string getDevice() override { return _device; }
  std::string getDescription() override { return _description; }
  bool getIsFallbackAdapter() override { return _isFallbackAdapter; }

private:
  std::string _vendor;
  std::string _architecture;
  std::string _device;
  std::string _description;
  bool _isFallbackAdapter;
};

} // namespace rnwgpu
