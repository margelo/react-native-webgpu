import type { HybridObject, UInt64 } from "react-native-nitro-modules";

import type { GPUObjectBase } from "./GPUObjectBase";
import type { GPUSharedFence } from "./GPUSharedFence.nitro";
import type { GPUTexture } from "./GPUTexture.nitro";
import type { GPUTextureDescriptor } from "./GPUTextureDescriptor";

export interface GPUSharedFenceState {
  fence: GPUSharedFence;
  signaledValue: UInt64;
}

export interface GPUSharedTextureMemoryEndAccessState {
  initialized: boolean;
  fences: GPUSharedFenceState[];
}

export interface GPUSharedTextureMemory
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {
  createTexture(descriptor?: GPUTextureDescriptor): GPUTexture;
  beginAccess(
    texture: GPUTexture,
    initialized: boolean,
    fences?: GPUSharedFenceState[],
  ): void;
  endAccess(texture: GPUTexture): GPUSharedTextureMemoryEndAccessState;
}
