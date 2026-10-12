#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "EnumMaps.h"
#include "HybridGPUCompilationInfoSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUCompilationInfo
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUCompilationInfoSpec> {
public:
  explicit GPUCompilationInfo(const wgpu::CompilationInfo &info)
      : HybridObject(TAG) {
    _messages.reserve(info.messageCount);
    for (size_t i = 0; i < info.messageCount; ++i) {
      const auto &message = info.messages[i];
      _messages.emplace_back(std::string(std::string_view(message.message)),
                             fromWGPU(message.type),
                             static_cast<double>(message.lineNum),
                             static_cast<double>(message.linePos),
                             static_cast<double>(message.offset),
                             static_cast<double>(message.length));
    }
  }

  std::vector<margelo::nitro::webgpu::GPUCompilationMessage>
  getMessages() override {
    return _messages;
  }

private:
  std::vector<margelo::nitro::webgpu::GPUCompilationMessage> _messages;
};

} // namespace rnwgpu
