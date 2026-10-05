import type { HybridObject, UInt64 } from "react-native-nitro-modules";

export type NativeVideoPixelFormat = "bgra8" | "nv12";

export interface NativeVideoFrame extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  readonly handle: UInt64;
  readonly width: number;
  readonly height: number;
  readonly pixelFormat: NativeVideoPixelFormat;
  release(): void;
}
