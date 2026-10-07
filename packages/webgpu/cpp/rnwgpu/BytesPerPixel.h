//
//  BytesPerPixel.h
//  Pods
//
//  Created by Dave Mkpa-Eke on 07/10/26.
//

#pragma once

#include <cstddef>

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

inline size_t bytesPerPixel(wgpu::TextureFormat format) {
  switch (format) {
  case wgpu::TextureFormat::R8Unorm:
  case wgpu::TextureFormat::R8Snorm:
  case wgpu::TextureFormat::R8Uint:
  case wgpu::TextureFormat::R8Sint:
  case wgpu::TextureFormat::Stencil8:
    return 1;
  case wgpu::TextureFormat::R16Uint:
  case wgpu::TextureFormat::R16Sint:
  case wgpu::TextureFormat::R16Float:
  case wgpu::TextureFormat::RG8Unorm:
  case wgpu::TextureFormat::RG8Snorm:
  case wgpu::TextureFormat::RG8Uint:
  case wgpu::TextureFormat::RG8Sint:
  case wgpu::TextureFormat::Depth16Unorm:
    return 2;
  case wgpu::TextureFormat::RGBA8Unorm:
  case wgpu::TextureFormat::RGBA8UnormSrgb:
  case wgpu::TextureFormat::RGBA8Snorm:
  case wgpu::TextureFormat::RGBA8Uint:
  case wgpu::TextureFormat::RGBA8Sint:
  case wgpu::TextureFormat::BGRA8Unorm:
  case wgpu::TextureFormat::BGRA8UnormSrgb:
  case wgpu::TextureFormat::RGB10A2Unorm:
  case wgpu::TextureFormat::R32Float:
  case wgpu::TextureFormat::R32Uint:
  case wgpu::TextureFormat::R32Sint:
  case wgpu::TextureFormat::RG16Uint:
  case wgpu::TextureFormat::RG16Sint:
  case wgpu::TextureFormat::RG16Float:
  case wgpu::TextureFormat::Depth24Plus:
  case wgpu::TextureFormat::Depth24PlusStencil8:
  case wgpu::TextureFormat::Depth32Float:
    return 4;
  case wgpu::TextureFormat::RG32Float:
  case wgpu::TextureFormat::RG32Uint:
  case wgpu::TextureFormat::RG32Sint:
  case wgpu::TextureFormat::RGBA16Uint:
  case wgpu::TextureFormat::RGBA16Sint:
  case wgpu::TextureFormat::RGBA16Float:
  case wgpu::TextureFormat::Depth32FloatStencil8:
    return 8;
  case wgpu::TextureFormat::RGBA32Float:
  case wgpu::TextureFormat::RGBA32Uint:
  case wgpu::TextureFormat::RGBA32Sint:
    return 16;
  default:
    return 4; // Safe default
  }
}

} // namespace rnwgpu
