//
//  EnumMaps.h
//  Pods
//
//  Created by Ritesh Shukla on 05/10/26.
//

#pragma once

#include <stdexcept>

#include "GPUCompilationMessageType.hpp"
#include "GPUDeviceLostReason.hpp"
#include "GPUQueryType.hpp"
#include "GPUTextureAspect.hpp"
#include "GPUTextureDimension.hpp"
#include "GPUTextureFormat.hpp"
#include "GPUTextureViewDimension.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

inline margelo::nitro::webgpu::GPUCompilationMessageType
fromWGPU(wgpu::CompilationMessageType type) {
  using margelo::nitro::webgpu::GPUCompilationMessageType;
  switch (type) {
  case wgpu::CompilationMessageType::Error:
    return GPUCompilationMessageType::ERROR;
  case wgpu::CompilationMessageType::Warning:
    return GPUCompilationMessageType::WARNING;
  case wgpu::CompilationMessageType::Info:
    return GPUCompilationMessageType::INFO;
  }
  throw std::invalid_argument("Unknown wgpu::CompilationMessageType");
}

inline margelo::nitro::webgpu::GPUQueryType fromWGPU(wgpu::QueryType type) {
  using margelo::nitro::webgpu::GPUQueryType;
  switch (type) {
  case wgpu::QueryType::Occlusion:
    return GPUQueryType::OCCLUSION;
  case wgpu::QueryType::Timestamp:
    return GPUQueryType::TIMESTAMP;
  }
  throw std::invalid_argument("Unknown wgpu::QueryType");
}

inline margelo::nitro::webgpu::GPUDeviceLostReason
fromWGPU(wgpu::DeviceLostReason reason) {
  using margelo::nitro::webgpu::GPUDeviceLostReason;
  switch (reason) {
  case wgpu::DeviceLostReason::Destroyed:
    return GPUDeviceLostReason::DESTROYED;
  case wgpu::DeviceLostReason::Unknown:
  case wgpu::DeviceLostReason::CallbackCancelled:
  case wgpu::DeviceLostReason::FailedCreation:
    return GPUDeviceLostReason::UNKNOWN;
  }
  throw std::invalid_argument("Unknown wgpu::DeviceLostReason");
}

inline margelo::nitro::webgpu::GPUTextureDimension
fromWGPU(wgpu::TextureDimension value) {
  switch (value) {
  case wgpu::TextureDimension::e1D:
    return margelo::nitro::webgpu::GPUTextureDimension::_1D;
  case wgpu::TextureDimension::e2D:
    return margelo::nitro::webgpu::GPUTextureDimension::_2D;
  case wgpu::TextureDimension::e3D:
    return margelo::nitro::webgpu::GPUTextureDimension::_3D;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported wgpu::TextureDimension");
}

inline margelo::nitro::webgpu::GPUTextureFormat
fromWGPU(wgpu::TextureFormat value) {
  switch (value) {
  case wgpu::TextureFormat::Depth32FloatStencil8:
    return margelo::nitro::webgpu::GPUTextureFormat::DEPTH32FLOAT_STENCIL8;
  case wgpu::TextureFormat::R8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::R8UNORM;
  case wgpu::TextureFormat::R8Snorm:
    return margelo::nitro::webgpu::GPUTextureFormat::R8SNORM;
  case wgpu::TextureFormat::R8Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::R8UINT;
  case wgpu::TextureFormat::R8Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::R8SINT;
  case wgpu::TextureFormat::R16Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::R16UINT;
  case wgpu::TextureFormat::R16Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::R16SINT;
  case wgpu::TextureFormat::R16Float:
    return margelo::nitro::webgpu::GPUTextureFormat::R16FLOAT;
  case wgpu::TextureFormat::RG8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::RG8UNORM;
  case wgpu::TextureFormat::RG8Snorm:
    return margelo::nitro::webgpu::GPUTextureFormat::RG8SNORM;
  case wgpu::TextureFormat::RG8Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RG8UINT;
  case wgpu::TextureFormat::RG8Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::RG8SINT;
  case wgpu::TextureFormat::R32Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::R32UINT;
  case wgpu::TextureFormat::R32Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::R32SINT;
  case wgpu::TextureFormat::R32Float:
    return margelo::nitro::webgpu::GPUTextureFormat::R32FLOAT;
  case wgpu::TextureFormat::RG16Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RG16UINT;
  case wgpu::TextureFormat::RG16Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::RG16SINT;
  case wgpu::TextureFormat::RG16Float:
    return margelo::nitro::webgpu::GPUTextureFormat::RG16FLOAT;
  case wgpu::TextureFormat::RGBA8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA8UNORM;
  case wgpu::TextureFormat::RGBA8UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA8UNORM_SRGB;
  case wgpu::TextureFormat::RGBA8Snorm:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA8SNORM;
  case wgpu::TextureFormat::RGBA8Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA8UINT;
  case wgpu::TextureFormat::RGBA8Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA8SINT;
  case wgpu::TextureFormat::BGRA8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BGRA8UNORM;
  case wgpu::TextureFormat::BGRA8UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::BGRA8UNORM_SRGB;
  case wgpu::TextureFormat::RGB9E5Ufloat:
    return margelo::nitro::webgpu::GPUTextureFormat::RGB9E5UFLOAT;
  case wgpu::TextureFormat::RGB10A2Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGB10A2UINT;
  case wgpu::TextureFormat::RGB10A2Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::RGB10A2UNORM;
  case wgpu::TextureFormat::RG11B10Ufloat:
    return margelo::nitro::webgpu::GPUTextureFormat::RG11B10UFLOAT;
  case wgpu::TextureFormat::RG32Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RG32UINT;
  case wgpu::TextureFormat::RG32Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::RG32SINT;
  case wgpu::TextureFormat::RG32Float:
    return margelo::nitro::webgpu::GPUTextureFormat::RG32FLOAT;
  case wgpu::TextureFormat::RGBA16Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA16UINT;
  case wgpu::TextureFormat::RGBA16Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA16SINT;
  case wgpu::TextureFormat::RGBA16Float:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA16FLOAT;
  case wgpu::TextureFormat::RGBA32Uint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA32UINT;
  case wgpu::TextureFormat::RGBA32Sint:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA32SINT;
  case wgpu::TextureFormat::RGBA32Float:
    return margelo::nitro::webgpu::GPUTextureFormat::RGBA32FLOAT;
  case wgpu::TextureFormat::Stencil8:
    return margelo::nitro::webgpu::GPUTextureFormat::STENCIL8;
  case wgpu::TextureFormat::Depth16Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::DEPTH16UNORM;
  case wgpu::TextureFormat::Depth24Plus:
    return margelo::nitro::webgpu::GPUTextureFormat::DEPTH24PLUS;
  case wgpu::TextureFormat::Depth24PlusStencil8:
    return margelo::nitro::webgpu::GPUTextureFormat::DEPTH24PLUS_STENCIL8;
  case wgpu::TextureFormat::Depth32Float:
    return margelo::nitro::webgpu::GPUTextureFormat::DEPTH32FLOAT;
  case wgpu::TextureFormat::BC1RGBAUnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC1_RGBA_UNORM;
  case wgpu::TextureFormat::BC1RGBAUnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::BC1_RGBA_UNORM_SRGB;
  case wgpu::TextureFormat::BC2RGBAUnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC2_RGBA_UNORM;
  case wgpu::TextureFormat::BC2RGBAUnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::BC2_RGBA_UNORM_SRGB;
  case wgpu::TextureFormat::BC3RGBAUnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC3_RGBA_UNORM;
  case wgpu::TextureFormat::BC3RGBAUnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::BC3_RGBA_UNORM_SRGB;
  case wgpu::TextureFormat::BC4RUnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC4_R_UNORM;
  case wgpu::TextureFormat::BC4RSnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC4_R_SNORM;
  case wgpu::TextureFormat::BC5RGUnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC5_RG_UNORM;
  case wgpu::TextureFormat::BC5RGSnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC5_RG_SNORM;
  case wgpu::TextureFormat::BC6HRGBUfloat:
    return margelo::nitro::webgpu::GPUTextureFormat::BC6H_RGB_UFLOAT;
  case wgpu::TextureFormat::BC6HRGBFloat:
    return margelo::nitro::webgpu::GPUTextureFormat::BC6H_RGB_FLOAT;
  case wgpu::TextureFormat::BC7RGBAUnorm:
    return margelo::nitro::webgpu::GPUTextureFormat::BC7_RGBA_UNORM;
  case wgpu::TextureFormat::BC7RGBAUnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::BC7_RGBA_UNORM_SRGB;
  case wgpu::TextureFormat::ETC2RGB8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8UNORM;
  case wgpu::TextureFormat::ETC2RGB8UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8UNORM_SRGB;
  case wgpu::TextureFormat::ETC2RGB8A1Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8A1UNORM;
  case wgpu::TextureFormat::ETC2RGB8A1UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8A1UNORM_SRGB;
  case wgpu::TextureFormat::ETC2RGBA8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGBA8UNORM;
  case wgpu::TextureFormat::ETC2RGBA8UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGBA8UNORM_SRGB;
  case wgpu::TextureFormat::EACR11Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::EAC_R11UNORM;
  case wgpu::TextureFormat::EACR11Snorm:
    return margelo::nitro::webgpu::GPUTextureFormat::EAC_R11SNORM;
  case wgpu::TextureFormat::EACRG11Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::EAC_RG11UNORM;
  case wgpu::TextureFormat::EACRG11Snorm:
    return margelo::nitro::webgpu::GPUTextureFormat::EAC_RG11SNORM;
  case wgpu::TextureFormat::ASTC4x4Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_4X4_UNORM;
  case wgpu::TextureFormat::ASTC4x4UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_4X4_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC5x4Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X4_UNORM;
  case wgpu::TextureFormat::ASTC5x4UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X4_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC5x5Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X5_UNORM;
  case wgpu::TextureFormat::ASTC5x5UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X5_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC6x5Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X5_UNORM;
  case wgpu::TextureFormat::ASTC6x5UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X5_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC6x6Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X6_UNORM;
  case wgpu::TextureFormat::ASTC6x6UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X6_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC8x5Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X5_UNORM;
  case wgpu::TextureFormat::ASTC8x5UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X5_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC8x6Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X6_UNORM;
  case wgpu::TextureFormat::ASTC8x6UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X6_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC8x8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X8_UNORM;
  case wgpu::TextureFormat::ASTC8x8UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X8_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC10x5Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X5_UNORM;
  case wgpu::TextureFormat::ASTC10x5UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X5_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC10x6Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X6_UNORM;
  case wgpu::TextureFormat::ASTC10x6UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X6_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC10x8Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X8_UNORM;
  case wgpu::TextureFormat::ASTC10x8UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X8_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC10x10Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X10_UNORM;
  case wgpu::TextureFormat::ASTC10x10UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X10_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC12x10Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X10_UNORM;
  case wgpu::TextureFormat::ASTC12x10UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X10_UNORM_SRGB;
  case wgpu::TextureFormat::ASTC12x12Unorm:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X12_UNORM;
  case wgpu::TextureFormat::ASTC12x12UnormSrgb:
    return margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X12_UNORM_SRGB;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported wgpu::TextureFormat");
}

inline wgpu::TextureFormat
toWGPU(margelo::nitro::webgpu::GPUTextureFormat value) {
  switch (value) {
  case margelo::nitro::webgpu::GPUTextureFormat::R8UNORM:
    return wgpu::TextureFormat::R8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::R8SNORM:
    return wgpu::TextureFormat::R8Snorm;
  case margelo::nitro::webgpu::GPUTextureFormat::R8UINT:
    return wgpu::TextureFormat::R8Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::R8SINT:
    return wgpu::TextureFormat::R8Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::R16UINT:
    return wgpu::TextureFormat::R16Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::R16SINT:
    return wgpu::TextureFormat::R16Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::R16FLOAT:
    return wgpu::TextureFormat::R16Float;
  case margelo::nitro::webgpu::GPUTextureFormat::RG8UNORM:
    return wgpu::TextureFormat::RG8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::RG8SNORM:
    return wgpu::TextureFormat::RG8Snorm;
  case margelo::nitro::webgpu::GPUTextureFormat::RG8UINT:
    return wgpu::TextureFormat::RG8Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RG8SINT:
    return wgpu::TextureFormat::RG8Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::R32UINT:
    return wgpu::TextureFormat::R32Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::R32SINT:
    return wgpu::TextureFormat::R32Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::R32FLOAT:
    return wgpu::TextureFormat::R32Float;
  case margelo::nitro::webgpu::GPUTextureFormat::RG16UINT:
    return wgpu::TextureFormat::RG16Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RG16SINT:
    return wgpu::TextureFormat::RG16Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::RG16FLOAT:
    return wgpu::TextureFormat::RG16Float;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA8UNORM:
    return wgpu::TextureFormat::RGBA8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA8UNORM_SRGB:
    return wgpu::TextureFormat::RGBA8UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA8SNORM:
    return wgpu::TextureFormat::RGBA8Snorm;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA8UINT:
    return wgpu::TextureFormat::RGBA8Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA8SINT:
    return wgpu::TextureFormat::RGBA8Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::BGRA8UNORM:
    return wgpu::TextureFormat::BGRA8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BGRA8UNORM_SRGB:
    return wgpu::TextureFormat::BGRA8UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::RGB9E5UFLOAT:
    return wgpu::TextureFormat::RGB9E5Ufloat;
  case margelo::nitro::webgpu::GPUTextureFormat::RGB10A2UINT:
    return wgpu::TextureFormat::RGB10A2Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RGB10A2UNORM:
    return wgpu::TextureFormat::RGB10A2Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::RG11B10UFLOAT:
    return wgpu::TextureFormat::RG11B10Ufloat;
  case margelo::nitro::webgpu::GPUTextureFormat::RG32UINT:
    return wgpu::TextureFormat::RG32Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RG32SINT:
    return wgpu::TextureFormat::RG32Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::RG32FLOAT:
    return wgpu::TextureFormat::RG32Float;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA16UINT:
    return wgpu::TextureFormat::RGBA16Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA16SINT:
    return wgpu::TextureFormat::RGBA16Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA16FLOAT:
    return wgpu::TextureFormat::RGBA16Float;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA32UINT:
    return wgpu::TextureFormat::RGBA32Uint;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA32SINT:
    return wgpu::TextureFormat::RGBA32Sint;
  case margelo::nitro::webgpu::GPUTextureFormat::RGBA32FLOAT:
    return wgpu::TextureFormat::RGBA32Float;
  case margelo::nitro::webgpu::GPUTextureFormat::STENCIL8:
    return wgpu::TextureFormat::Stencil8;
  case margelo::nitro::webgpu::GPUTextureFormat::DEPTH16UNORM:
    return wgpu::TextureFormat::Depth16Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::DEPTH24PLUS:
    return wgpu::TextureFormat::Depth24Plus;
  case margelo::nitro::webgpu::GPUTextureFormat::DEPTH24PLUS_STENCIL8:
    return wgpu::TextureFormat::Depth24PlusStencil8;
  case margelo::nitro::webgpu::GPUTextureFormat::DEPTH32FLOAT:
    return wgpu::TextureFormat::Depth32Float;
  case margelo::nitro::webgpu::GPUTextureFormat::DEPTH32FLOAT_STENCIL8:
    return wgpu::TextureFormat::Depth32FloatStencil8;
  case margelo::nitro::webgpu::GPUTextureFormat::BC1_RGBA_UNORM:
    return wgpu::TextureFormat::BC1RGBAUnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC1_RGBA_UNORM_SRGB:
    return wgpu::TextureFormat::BC1RGBAUnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::BC2_RGBA_UNORM:
    return wgpu::TextureFormat::BC2RGBAUnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC2_RGBA_UNORM_SRGB:
    return wgpu::TextureFormat::BC2RGBAUnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::BC3_RGBA_UNORM:
    return wgpu::TextureFormat::BC3RGBAUnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC3_RGBA_UNORM_SRGB:
    return wgpu::TextureFormat::BC3RGBAUnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::BC4_R_UNORM:
    return wgpu::TextureFormat::BC4RUnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC4_R_SNORM:
    return wgpu::TextureFormat::BC4RSnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC5_RG_UNORM:
    return wgpu::TextureFormat::BC5RGUnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC5_RG_SNORM:
    return wgpu::TextureFormat::BC5RGSnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC6H_RGB_UFLOAT:
    return wgpu::TextureFormat::BC6HRGBUfloat;
  case margelo::nitro::webgpu::GPUTextureFormat::BC6H_RGB_FLOAT:
    return wgpu::TextureFormat::BC6HRGBFloat;
  case margelo::nitro::webgpu::GPUTextureFormat::BC7_RGBA_UNORM:
    return wgpu::TextureFormat::BC7RGBAUnorm;
  case margelo::nitro::webgpu::GPUTextureFormat::BC7_RGBA_UNORM_SRGB:
    return wgpu::TextureFormat::BC7RGBAUnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8UNORM:
    return wgpu::TextureFormat::ETC2RGB8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8UNORM_SRGB:
    return wgpu::TextureFormat::ETC2RGB8UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8A1UNORM:
    return wgpu::TextureFormat::ETC2RGB8A1Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGB8A1UNORM_SRGB:
    return wgpu::TextureFormat::ETC2RGB8A1UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGBA8UNORM:
    return wgpu::TextureFormat::ETC2RGBA8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ETC2_RGBA8UNORM_SRGB:
    return wgpu::TextureFormat::ETC2RGBA8UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::EAC_R11UNORM:
    return wgpu::TextureFormat::EACR11Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::EAC_R11SNORM:
    return wgpu::TextureFormat::EACR11Snorm;
  case margelo::nitro::webgpu::GPUTextureFormat::EAC_RG11UNORM:
    return wgpu::TextureFormat::EACRG11Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::EAC_RG11SNORM:
    return wgpu::TextureFormat::EACRG11Snorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_4X4_UNORM:
    return wgpu::TextureFormat::ASTC4x4Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_4X4_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC4x4UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X4_UNORM:
    return wgpu::TextureFormat::ASTC5x4Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X4_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC5x4UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X5_UNORM:
    return wgpu::TextureFormat::ASTC5x5Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_5X5_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC5x5UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X5_UNORM:
    return wgpu::TextureFormat::ASTC6x5Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X5_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC6x5UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X6_UNORM:
    return wgpu::TextureFormat::ASTC6x6Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_6X6_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC6x6UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X5_UNORM:
    return wgpu::TextureFormat::ASTC8x5Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X5_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC8x5UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X6_UNORM:
    return wgpu::TextureFormat::ASTC8x6Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X6_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC8x6UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X8_UNORM:
    return wgpu::TextureFormat::ASTC8x8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_8X8_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC8x8UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X5_UNORM:
    return wgpu::TextureFormat::ASTC10x5Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X5_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC10x5UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X6_UNORM:
    return wgpu::TextureFormat::ASTC10x6Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X6_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC10x6UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X8_UNORM:
    return wgpu::TextureFormat::ASTC10x8Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X8_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC10x8UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X10_UNORM:
    return wgpu::TextureFormat::ASTC10x10Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_10X10_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC10x10UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X10_UNORM:
    return wgpu::TextureFormat::ASTC12x10Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X10_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC12x10UnormSrgb;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X12_UNORM:
    return wgpu::TextureFormat::ASTC12x12Unorm;
  case margelo::nitro::webgpu::GPUTextureFormat::ASTC_12X12_UNORM_SRGB:
    return wgpu::TextureFormat::ASTC12x12UnormSrgb;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported GPUTextureFormat");
}

inline margelo::nitro::webgpu::GPUTextureViewDimension
fromWGPU(wgpu::TextureViewDimension value) {
  switch (value) {
  case wgpu::TextureViewDimension::e1D:
    return margelo::nitro::webgpu::GPUTextureViewDimension::_1D;
  case wgpu::TextureViewDimension::e2D:
    return margelo::nitro::webgpu::GPUTextureViewDimension::_2D;
  case wgpu::TextureViewDimension::e3D:
    return margelo::nitro::webgpu::GPUTextureViewDimension::_3D;
  case wgpu::TextureViewDimension::e2DArray:
    return margelo::nitro::webgpu::GPUTextureViewDimension::_2D_ARRAY;
  case wgpu::TextureViewDimension::Cube:
    return margelo::nitro::webgpu::GPUTextureViewDimension::CUBE;
  case wgpu::TextureViewDimension::CubeArray:
    return margelo::nitro::webgpu::GPUTextureViewDimension::CUBE_ARRAY;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported wgpu::TextureViewDimension");
}

inline wgpu::TextureViewDimension
toWGPU(margelo::nitro::webgpu::GPUTextureViewDimension value) {
  switch (value) {
  case margelo::nitro::webgpu::GPUTextureViewDimension::_1D:
    return wgpu::TextureViewDimension::e1D;
  case margelo::nitro::webgpu::GPUTextureViewDimension::_2D:
    return wgpu::TextureViewDimension::e2D;
  case margelo::nitro::webgpu::GPUTextureViewDimension::_2D_ARRAY:
    return wgpu::TextureViewDimension::e2DArray;
  case margelo::nitro::webgpu::GPUTextureViewDimension::CUBE:
    return wgpu::TextureViewDimension::Cube;
  case margelo::nitro::webgpu::GPUTextureViewDimension::CUBE_ARRAY:
    return wgpu::TextureViewDimension::CubeArray;
  case margelo::nitro::webgpu::GPUTextureViewDimension::_3D:
    return wgpu::TextureViewDimension::e3D;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported GPUTextureViewDimension");
}

inline margelo::nitro::webgpu::GPUTextureAspect
fromWGPU(wgpu::TextureAspect value) {
  switch (value) {
  case wgpu::TextureAspect::All:
    return margelo::nitro::webgpu::GPUTextureAspect::ALL;
  case wgpu::TextureAspect::StencilOnly:
    return margelo::nitro::webgpu::GPUTextureAspect::STENCIL_ONLY;
  case wgpu::TextureAspect::DepthOnly:
    return margelo::nitro::webgpu::GPUTextureAspect::DEPTH_ONLY;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported wgpu::TextureAspect");
}

inline wgpu::TextureAspect
toWGPU(margelo::nitro::webgpu::GPUTextureAspect value) {
  switch (value) {
  case margelo::nitro::webgpu::GPUTextureAspect::ALL:
    return wgpu::TextureAspect::All;
  case margelo::nitro::webgpu::GPUTextureAspect::STENCIL_ONLY:
    return wgpu::TextureAspect::StencilOnly;
  case margelo::nitro::webgpu::GPUTextureAspect::DEPTH_ONLY:
    return wgpu::TextureAspect::DepthOnly;
  default:
    break;
  }
  throw std::invalid_argument("Unsupported GPUTextureAspect");
}

} // namespace rnwgpu
