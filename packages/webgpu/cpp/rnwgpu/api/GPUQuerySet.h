#pragma once

#include <string>
#include <utility>

#include "EnumMaps.h"
#include "HybridGPUQuerySetSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUQuerySet
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUQuerySetSpec> {
public:
  GPUQuerySet(wgpu::QuerySet instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  margelo::nitro::webgpu::GPUQueryType getType() override {
    return fromWGPU(_instance.GetType());
  }
  double getCount() override { return _instance.GetCount(); }
  void destroy() override { _instance.Destroy(); }

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::QuerySet get() { return _instance; }

protected:
  size_t getExternalMemorySize() noexcept override {
    return static_cast<size_t>(_instance.GetCount()) * 8;
  }

private:
  wgpu::QuerySet _instance;
  std::string _label;
};

} // namespace rnwgpu
