#pragma once

#include <string>
#include <utility>

#include "HybridGPURenderBundleSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPURenderBundle
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPURenderBundleSpec> {
public:
  GPURenderBundle(wgpu::RenderBundle instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::RenderBundle get() { return _instance; }

private:
  wgpu::RenderBundle _instance;
  std::string _label;
};

} // namespace rnwgpu
