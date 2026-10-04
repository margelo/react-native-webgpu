#pragma once

#include <string>
#include <utility>

#include "HybridGPUSharedFenceSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

namespace jsi = facebook::jsi;

// Wraps a wgpu::SharedFence: a native GPU sync primitive (id<MTLSharedEvent> on
// Apple, sync-fd / VkSemaphore on Android).
class GPUSharedFence
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUSharedFenceSpec> {
public:
  GPUSharedFence(wgpu::SharedFence instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  jsi::Value exportInfo(jsi::Runtime &runtime, const jsi::Value &thisVal,
                        const jsi::Value *args, size_t count);

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  wgpu::SharedFence get() { return _instance; }

protected:
  void loadHybridMethods() override {
    WebGPUObject::loadHybridMethods();
    registerHybrids(this, [](Prototype &prototype) {
      prototype.registerRawHybridMethod("export", 0,
                                        &GPUSharedFence::exportInfo);
    });
  }

private:
  wgpu::SharedFence _instance;
  std::string _label;
};

} // namespace rnwgpu
