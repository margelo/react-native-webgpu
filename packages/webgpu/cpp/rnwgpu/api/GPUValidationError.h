#pragma once

#include "GPUError.h"
#include "HybridGPUValidationErrorSpec.hpp"

namespace rnwgpu {

using GPUValidationError =
    GPUErrorImpl<margelo::nitro::webgpu::HybridGPUValidationErrorSpec>;

} // namespace rnwgpu
