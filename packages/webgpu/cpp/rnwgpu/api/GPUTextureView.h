#pragma once

#include <string>
#include <utility>

#include "HybridGPUTextureViewSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUTextureView
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUTextureViewSpec> {
public:
  GPUTextureView(wgpu::TextureView instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::TextureView get() { return _instance; }

private:
  wgpu::TextureView _instance;
  std::string _label;
};

} // namespace rnwgpu
