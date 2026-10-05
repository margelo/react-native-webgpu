import type { HybridObject, UInt64 } from "react-native-nitro-modules";

import type { GPUObjectBase } from "./GPUObjectBase";
import type { GPUTextureView } from "./GPUTextureView.nitro";
import type {
  GPUTextureAspect,
  GPUTextureDimension,
  GPUTextureFormat,
  GPUTextureViewDimension,
} from "./types/enums";

export interface GPUTextureViewDescriptor {
  label?: string;
  format?: GPUTextureFormat;
  dimension?: GPUTextureViewDimension;
  usage?: number;
  aspect?: GPUTextureAspect;
  baseMipLevel?: number;
  mipLevelCount?: number;
  baseArrayLayer?: number;
  arrayLayerCount?: number;
}

export interface GPUTexture
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {
  createView(descriptor?: GPUTextureViewDescriptor): GPUTextureView;
  destroy(): void;
  readonly width: number;
  readonly height: number;
  readonly depthOrArrayLayers: number;
  readonly mipLevelCount: number;
  readonly sampleCount: number;
  readonly dimension: GPUTextureDimension;
  readonly format: GPUTextureFormat;
  readonly usage: number;
  readonly nativePointer: UInt64;
}
