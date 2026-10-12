#pragma once

#include <cstdint>

#include "HybridCanvasSpec.hpp"
#include "WebGPUObject.hpp"

namespace rnwgpu {

class Canvas
    : public WebGPUObject<margelo::nitro::webgpu::HybridCanvasSpec, false> {
public:
  Canvas(void *surface, int width, int height)
      : HybridObject(TAG), _surface(surface), _width(width), _height(height),
        _clientWidth(width), _clientHeight(height) {}

  uint64_t getSurface() override {
    return reinterpret_cast<uint64_t>(_surface);
  }

  double getWidth() override { return _width; }
  void setWidth(double width) override { _width = static_cast<int>(width); }
  double getHeight() override { return _height; }
  void setHeight(double height) override { _height = static_cast<int>(height); }

  double getClientWidth() override { return _clientWidth; }
  double getClientHeight() override { return _clientHeight; }
  void setClientWidth(int width) { _clientWidth = width; }
  void setClientHeight(int height) { _clientHeight = height; }

protected:
  void loadHybridMethods() override {
    WebGPUObject::loadHybridMethods();
    registerHybrids(this, [](Prototype &prototype) {
      for (const char *name :
           {"addEventListener", "removeEventListener", "dispatchEvent",
            "setPointerCapture", "releasePointerCapture"}) {
        prototype.registerRawHybridMethod(name, 0, &Canvas::ignoreDomCall);
      }
    });
  }

private:
  jsi::Value ignoreDomCall(jsi::Runtime & /*runtime*/,
                           const jsi::Value & /*thisValue*/,
                           const jsi::Value * /*args*/, size_t /*count*/) {
    return jsi::Value::undefined();
  }

  void *_surface;
  int _width;
  int _height;
  int _clientWidth;
  int _clientHeight;
};

} // namespace rnwgpu
