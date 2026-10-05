#pragma once

#include "GPUError.h"
#include "HybridGPUOutOfMemoryErrorSpec.hpp"

namespace rnwgpu {

using GPUOutOfMemoryError =
    GPUErrorImpl<margelo::nitro::webgpu::HybridGPUOutOfMemoryErrorSpec>;

} // namespace rnwgpu
