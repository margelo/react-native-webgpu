import type { HybridObject } from "react-native-nitro-modules";

import type { GPUObjectBase } from "./GPUObjectBase";

export interface GPUExternalTexture
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {
  readonly yuvToRgbMatrix: number[];
  destroy(): void;
}
