#pragma once

#include "GPUError.h"
#include "HybridGPUInternalErrorSpec.hpp"

namespace rnwgpu {

using GPUInternalError =
    GPUErrorImpl<margelo::nitro::webgpu::HybridGPUInternalErrorSpec>;

} // namespace rnwgpu
