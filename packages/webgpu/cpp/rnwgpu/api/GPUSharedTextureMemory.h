#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "HybridGPUSharedTextureMemorySpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUSharedTextureMemory
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUSharedTextureMemorySpec> {
public:
  GPUSharedTextureMemory(wgpu::SharedTextureMemory instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::shared_ptr<margelo::nitro::webgpu::HybridGPUTextureSpec> createTexture(
      const std::optional<margelo::nitro::webgpu::GPUTextureDescriptor>
          &descriptor) override;
  void beginAccess(
      const std::shared_ptr<margelo::nitro::webgpu::HybridGPUTextureSpec>
          &texture,
      bool initialized,
      const std::optional<
          std::vector<margelo::nitro::webgpu::GPUSharedFenceState>> &fences)
      override;
  margelo::nitro::webgpu::GPUSharedTextureMemoryEndAccessState
  endAccess(const std::shared_ptr<margelo::nitro::webgpu::HybridGPUTextureSpec>
                &texture) override;

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

private:
  wgpu::SharedTextureMemory _instance;
  std::string _label;
};

} // namespace rnwgpu
