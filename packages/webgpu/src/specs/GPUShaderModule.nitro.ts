import type { HybridObject } from "react-native-nitro-modules";

import type { GPUCompilationInfo } from "./GPUCompilationInfo.nitro";
import type { GPUObjectBase } from "./GPUObjectBase";

export interface GPUShaderModule
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {
  getCompilationInfo(): Promise<GPUCompilationInfo>;
}
