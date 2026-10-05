#pragma once

#include <cstdint>
#include <utility>

#include "HybridNativeVideoFrameSpec.hpp"
#include "PlatformContext.h"
#include "WebGPUObject.hpp"

namespace rnwgpu {

// VideoFrame is a small RAII wrapper around a platform-specific native handle
// (IOSurfaceRef-backed CVPixelBuffer on Apple, AHardwareBuffer on Android).
// It surfaces the raw handle as a BigInt to JS so callers can hand it to
// GPUDevice.importSharedTextureMemory, and owns a deleter so the underlying
// object stays alive until the JS object is GC'd (or release() is called).
class VideoFrame
    : public WebGPUObject<margelo::nitro::webgpu::HybridNativeVideoFrameSpec> {
public:
  explicit VideoFrame(VideoFrameHandle handle)
      : HybridObject(TAG), _handle(std::move(handle)) {}

  ~VideoFrame() override { release(); }

  uint64_t getHandle() override {
    return reinterpret_cast<uint64_t>(_handle.handle);
  }
  double getWidth() override { return _handle.width; }
  double getHeight() override { return _handle.height; }
  margelo::nitro::webgpu::NativeVideoPixelFormat getPixelFormat() override {
    return _handle.pixelFormat == VideoPixelFormat::NV12
               ? margelo::nitro::webgpu::NativeVideoPixelFormat::NV12
               : margelo::nitro::webgpu::NativeVideoPixelFormat::BGRA8;
  }
  void release() override {
    if (_handle.deleter) {
      _handle.deleter();
      _handle.deleter = nullptr;
    }
    _handle.handle = nullptr;
  }

  const VideoFrameHandle &handle() const { return _handle; }

private:
  VideoFrameHandle _handle;
};

} // namespace rnwgpu
