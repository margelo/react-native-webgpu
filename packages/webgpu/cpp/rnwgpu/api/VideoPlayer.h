#pragma once

#include <memory>
#include <utility>
#include <variant>

#include "HybridVideoPlayerSpec.hpp"
#include "PlatformContext.h"
#include "VideoFrame.h"
#include "WebGPUObject.hpp"

namespace rnwgpu {

class VideoPlayer
    : public WebGPUObject<margelo::nitro::webgpu::HybridVideoPlayerSpec> {
public:
  explicit VideoPlayer(std::unique_ptr<IVideoPlayer> impl)
      : HybridObject(TAG), _impl(std::move(impl)) {}

  std::variant<
      std::shared_ptr<margelo::nitro::webgpu::HybridNativeVideoFrameSpec>,
      margelo::nitro::NullType>
  copyLatestFrame() override {
    if (!_impl) {
      return margelo::nitro::null;
    }
    auto handle = _impl->copyLatestFrame();
    if (handle.handle == nullptr) {
      return margelo::nitro::null;
    }
    return std::make_shared<VideoFrame>(std::move(handle));
  }

  void play() override {
    if (_impl) {
      _impl->play();
    }
  }

  void pause() override {
    if (_impl) {
      _impl->pause();
    }
  }

  bool getPaused() override { return _impl ? _impl->paused() : true; }

  double getCurrentTime() override { return _impl ? _impl->currentTime() : 0; }
  void setCurrentTime(double seconds) override {
    if (_impl) {
      _impl->seek(seconds);
    }
  }

  double getDuration() override { return _impl ? _impl->duration() : 0; }

  double getVolume() override { return _impl ? _impl->volume() : 0; }
  void setVolume(double volume) override {
    if (_impl) {
      _impl->setVolume(volume);
    }
  }

  bool getLoop() override { return _impl ? _impl->loop() : false; }
  void setLoop(bool loop) override {
    if (_impl) {
      _impl->setLoop(loop);
    }
  }

  double getVideoWidth() override { return _impl ? _impl->videoWidth() : 0; }
  double getVideoHeight() override { return _impl ? _impl->videoHeight() : 0; }
  double getRotation() override { return _impl ? _impl->rotation() : 0; }
  double getFrameRate() override { return _impl ? _impl->frameRate() : 0; }

  void release() override { _impl.reset(); }

private:
  std::unique_ptr<IVideoPlayer> _impl;
};

} // namespace rnwgpu
