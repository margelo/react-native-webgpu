#pragma once

#include <memory>
#include <string>
#include <utility>

#include "GPUBindGroupLayout.h"
#include "HybridGPUComputePipelineSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUComputePipeline
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUComputePipelineSpec> {
public:
  GPUComputePipeline(wgpu::ComputePipeline instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::shared_ptr<margelo::nitro::webgpu::HybridGPUBindGroupLayoutSpec>
  getBindGroupLayout(double index) override;

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::ComputePipeline get() { return _instance; }

protected:
  size_t getExternalMemorySize() noexcept override { return 16 * 1024; }

private:
  wgpu::ComputePipeline _instance;
  std::string _label;
  friend class GPUDevice;
};

} // namespace rnwgpu
