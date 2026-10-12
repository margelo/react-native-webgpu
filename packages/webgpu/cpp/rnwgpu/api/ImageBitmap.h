#pragma once

#include <cstdint>
#include <utility>

#include "HybridImageBitmapSpec.hpp"
#include "PlatformContext.h"
#include "WebGPUObject.hpp"

namespace rnwgpu {

// Convert RGBA8 pixel data in place between straight and premultiplied alpha.
// Uses the same integer rounding as the web reference polyfill in the test
// harness (setup.ts, convertAlpha) so the native result is bit-exact with the
// dawn.node client. A no-op when the source and destination representations
// already match.
inline void convertAlpha(uint8_t *data, size_t byteLength,
                         bool sourcePremultiplied,
                         bool destinationPremultiplied) {
  if (sourcePremultiplied == destinationPremultiplied) {
    return;
  }
  for (size_t i = 0; i + 3 < byteLength; i += 4) {
    const uint32_t alpha = data[i + 3];
    for (size_t channel = 0; channel < 3; channel++) {
      const uint32_t value = data[i + channel];
      if (destinationPremultiplied) {
        data[i + channel] = static_cast<uint8_t>((value * alpha + 127) / 255);
      } else if (alpha == 0) {
        data[i + channel] = 0;
      } else {
        const uint32_t straight = (value * 255 + (alpha >> 1)) / alpha;
        data[i + channel] = static_cast<uint8_t>(straight > 255 ? 255 : straight);
      }
    }
  }
}

class ImageBitmap
    : public WebGPUObject<margelo::nitro::webgpu::HybridImageBitmapSpec,
                          false> {
public:
  explicit ImageBitmap(ImageData imageData)
      : HybridObject(TAG), _imageData(std::move(imageData)) {}

  double getWidth() override { return _imageData.width; }
  double getHeight() override { return _imageData.height; }
  void close() override {
    _imageData.data.clear();
    _imageData.data.shrink_to_fit();
    _imageData.width = 0;
    _imageData.height = 0;
  }

  void *getData() { return _imageData.data.data(); }
  size_t getSize() { return _imageData.data.size(); }
  bool getPremultiplied() { return _imageData.premultiplied; }

protected:
  size_t getExternalMemorySize() noexcept override {
    return _imageData.data.size();
  }

private:
  ImageData _imageData;
};

} // namespace rnwgpu
