#pragma once

#include <memory>
#include <string>
#include <utility>

#include "HybridGPUShaderModuleSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUShaderModule
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUShaderModuleSpec> {
public:
  GPUShaderModule(wgpu::ShaderModule instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::shared_ptr<margelo::nitro::Promise<
      std::shared_ptr<margelo::nitro::webgpu::HybridGPUCompilationInfoSpec>>>
  getCompilationInfo() override;

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::ShaderModule get() { return _instance; }

protected:
  size_t getExternalMemorySize() noexcept override { return 12 * 1024; }

private:
  wgpu::ShaderModule _instance;
  std::string _label;
};

} // namespace rnwgpu
