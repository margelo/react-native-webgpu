#include "GPURenderPipeline.h"

#include <memory>

#include "EnforceRange.h"

namespace rnwgpu {

std::shared_ptr<margelo::nitro::webgpu::HybridGPUBindGroupLayoutSpec>
GPURenderPipeline::getBindGroupLayout(double index) {
  auto layout =
      _instance.GetBindGroupLayout(enforceRange<uint32_t>(index, "index"));
  return std::make_shared<GPUBindGroupLayout>(layout, "");
}

} // namespace rnwgpu
