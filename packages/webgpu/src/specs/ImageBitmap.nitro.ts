import type { HybridObject } from "react-native-nitro-modules";

export interface ImageBitmap extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  readonly width: number;
  readonly height: number;
  close(): void;
}
