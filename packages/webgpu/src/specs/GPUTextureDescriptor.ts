import type { GPUTextureDimension, GPUTextureFormat } from "./types/enums";
import type { GPUExtent3D } from "./types/GPUExtent3D";

export interface GPUTextureDescriptor {
  label?: string;
  size: GPUExtent3D;
  mipLevelCount?: number;
  sampleCount?: number;
  dimension?: GPUTextureDimension;
  format: GPUTextureFormat;
  usage: number;
  viewFormats?: GPUTextureFormat[];
}
