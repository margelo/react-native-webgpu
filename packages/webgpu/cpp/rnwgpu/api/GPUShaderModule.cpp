#include "GPUShaderModule.h"

#include <memory>
#include <stdexcept>

#include "GPUCompilationInfo.h"
#include "SettleOnce.hpp"

namespace rnwgpu {

using CompilationInfo =
    std::shared_ptr<margelo::nitro::webgpu::HybridGPUCompilationInfoSpec>;

std::shared_ptr<margelo::nitro::Promise<CompilationInfo>>
GPUShaderModule::getCompilationInfo() {
  auto operation =
      SettleOnce<CompilationInfo>::create("GPUShaderModule.getCompilationInfo");
  _instance.GetCompilationInfo(
      wgpu::CallbackMode::AllowSpontaneous,
      [operation](wgpu::CompilationInfoRequestStatus status,
                  const wgpu::CompilationInfo *info) {
        operation->settle([&]() -> CompilationInfo {
          if (status != wgpu::CompilationInfoRequestStatus::Success ||
              info == nullptr) {
            throw std::runtime_error("Failed to get compilation info");
          }
          return std::make_shared<GPUCompilationInfo>(*info);
        });
      });
  return operation->promise();
}

} // namespace rnwgpu
