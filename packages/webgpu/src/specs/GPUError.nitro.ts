import type { HybridObject } from "react-native-nitro-modules";

export interface GPUError extends HybridObject<{ ios: "c++"; android: "c++" }> {
  readonly message: string;
}

export interface GPUValidationError extends GPUError {}

export interface GPUOutOfMemoryError extends GPUError {}

export interface GPUInternalError extends GPUError {}
