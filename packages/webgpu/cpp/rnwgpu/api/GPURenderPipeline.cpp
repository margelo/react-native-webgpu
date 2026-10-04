#include "GPURenderPipeline.h"

#include <memory>

namespace rnwgpu {

std::shared_ptr<margelo::nitro::webgpu::HybridGPUBindGroupLayoutSpec>
GPURenderPipeline::getBindGroupLayout(double index) {
  auto layout = _instance.GetBindGroupLayout(static_cast<uint32_t>(index));
  return std::make_shared<GPUBindGroupLayout>(layout, "");
}

} // namespace rnwgpu
