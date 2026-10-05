#pragma once

#include <string>
#include <utility>

#include "HybridGPUErrorSpec.hpp"
#include "WebGPUObject.hpp"

namespace rnwgpu {

template <typename Spec> class GPUErrorImpl : public WebGPUObject<Spec> {
public:
  explicit GPUErrorImpl(std::string message)
      : HybridObject(Spec::TAG), _message(std::move(message)) {}

  std::string getMessage() override { return _message; }

private:
  std::string _message;
};

using GPUError = GPUErrorImpl<margelo::nitro::webgpu::HybridGPUErrorSpec>;

} // namespace rnwgpu
