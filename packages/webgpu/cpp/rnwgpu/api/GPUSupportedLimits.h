#pragma once

#include "HybridGPUSupportedLimitsSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUSupportedLimits
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUSupportedLimitsSpec> {
public:
  explicit GPUSupportedLimits(wgpu::Limits instance)
      : HybridObject(TAG), _instance(instance) {}

  double getMaxTextureDimension1D() override;
  double getMaxTextureDimension2D() override;
  double getMaxTextureDimension3D() override;
  double getMaxTextureArrayLayers() override;
  double getMaxBindGroups() override;
  double getMaxBindGroupsPlusVertexBuffers() override;
  double getMaxBindingsPerBindGroup() override;
  double getMaxDynamicUniformBuffersPerPipelineLayout() override;
  double getMaxDynamicStorageBuffersPerPipelineLayout() override;
  double getMaxSampledTexturesPerShaderStage() override;
  double getMaxSamplersPerShaderStage() override;
  double getMaxStorageBuffersPerShaderStage() override;
  double getMaxStorageTexturesPerShaderStage() override;
  double getMaxUniformBuffersPerShaderStage() override;
  double getMaxUniformBufferBindingSize() override;
  double getMaxStorageBufferBindingSize() override;
  double getMinUniformBufferOffsetAlignment() override;
  double getMinStorageBufferOffsetAlignment() override;
  double getMaxVertexBuffers() override;
  double getMaxBufferSize() override;
  double getMaxVertexAttributes() override;
  double getMaxVertexBufferArrayStride() override;
  double getMaxInterStageShaderVariables() override;
  double getMaxColorAttachments() override;
  double getMaxColorAttachmentBytesPerSample() override;
  double getMaxComputeWorkgroupStorageSize() override;
  double getMaxComputeInvocationsPerWorkgroup() override;
  double getMaxComputeWorkgroupSizeX() override;
  double getMaxComputeWorkgroupSizeY() override;
  double getMaxComputeWorkgroupSizeZ() override;
  double getMaxComputeWorkgroupsPerDimension() override;

  const wgpu::Limits get() { return _instance; }

private:
  wgpu::Limits _instance;
};

} // namespace rnwgpu
