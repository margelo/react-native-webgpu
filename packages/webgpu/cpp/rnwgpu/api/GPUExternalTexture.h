#pragma once

#include <array>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "HybridGPUExternalTextureSpec.hpp"
#include "VideoFrame.h"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

struct GPUExternalTextureDescriptor;

class GPUExternalTexture
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUExternalTextureSpec> {
public:
  static std::shared_ptr<GPUExternalTexture>
  Create(wgpu::Device device,
         std::shared_ptr<GPUExternalTextureDescriptor> descriptor);

  GPUExternalTexture(wgpu::ExternalTexture instance,
                     wgpu::SharedTextureMemory memory, wgpu::Texture texture,
                     std::shared_ptr<VideoFrame> source, std::string label,
                     std::array<float, 12> yuvToRgbMatrix)
      : HybridObject(TAG), _instance(std::move(instance)),
        _memory(std::move(memory)), _texture(std::move(texture)),
        _source(std::move(source)), _label(std::move(label)),
        _yuvToRgbMatrix(yuvToRgbMatrix) {}

  ~GPUExternalTexture() override { destroy(); }

  void destroy() override {
    if (_memory && _texture) {
      endAccess(_memory, _texture);
    }
    if (_texture) {
      _texture.Destroy();
    }
    if (_instance) {
      _instance.Destroy();
    }
    _texture = nullptr;
    _memory = nullptr;
    _instance = nullptr;
    _source = nullptr;
  }

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    if (_instance) {
      _instance.SetLabel(_label.c_str());
    }
  }

  std::vector<double> getYuvToRgbMatrix() override {
    return std::vector<double>(_yuvToRgbMatrix.begin(), _yuvToRgbMatrix.end());
  }

  const wgpu::ExternalTexture get() { return _instance; }

  static void endAccess(const wgpu::SharedTextureMemory &memory,
                        const wgpu::Texture &texture) {
    wgpu::SharedTextureMemoryEndAccessState state{};
#if defined(__ANDROID__)
    // Dawn's Vulkan backend rejects EndAccess without a layout end state.
    wgpu::SharedTextureMemoryVkImageLayoutEndState vkLayout{};
    state.nextInChain = &vkLayout;
#endif
    (void)memory.EndAccess(texture, &state);
  }

private:
  wgpu::ExternalTexture _instance;
  wgpu::SharedTextureMemory _memory;
  wgpu::Texture _texture;
  std::shared_ptr<VideoFrame> _source;
  std::string _label;
  std::array<float, 12> _yuvToRgbMatrix;
};

} // namespace rnwgpu
