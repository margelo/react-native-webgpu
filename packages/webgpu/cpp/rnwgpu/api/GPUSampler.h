#pragma once

#include <string>

#include <ReactNativeWebGPU/HybridGPUSamplerSpec.hpp>

#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUSampler
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUSamplerSpec> {
public:
  explicit GPUSampler(wgpu::Sampler instance, std::string label)
      : _instance(instance), _label(label) {}

public:
  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  inline const wgpu::Sampler get() { return _instance; }

private:
  wgpu::Sampler _instance;
  std::string _label;
};

} // namespace rnwgpu
