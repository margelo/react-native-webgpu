#include "GPUShaderModule.h"

#include <memory>
#include <utility>

#include "JSIConverter.h"

namespace rnwgpu {

async::AsyncTaskHandle
GPUShaderModule::getCompilationInfo(jsi::Runtime &runtime) {
  auto module = _instance;

  // Post to the CALLING runtime's context so the promise settles on the
  // thread that requested it (see GPUBuffer::mapAsync).
  auto context =
      async::RuntimeContext::getOrCreate(runtime, _async->instance());
  return context->postTask(
      [module](const async::AsyncTaskHandle::ResolveFunction &resolve,
               const async::AsyncTaskHandle::RejectFunction &reject) {
        module.GetCompilationInfo(
            wgpu::CallbackMode::AllowProcessEvents,
            [resolve, reject](wgpu::CompilationInfoRequestStatus status,
                              const wgpu::CompilationInfo *compilationInfo) {
              if (status != wgpu::CompilationInfoRequestStatus::Success ||
                  compilationInfo == nullptr) {
                reject("Failed to get compilation info");
                return;
              }

              auto result =
                  std::make_shared<GPUCompilationInfo>(*compilationInfo);
              resolve([result](jsi::Runtime &runtime) mutable {
                return JSIConverter<std::shared_ptr<GPUCompilationInfo>>::toJSI(
                    runtime, result);
              });
            });
      });
}

} // namespace rnwgpu
