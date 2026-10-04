import type { HybridObject } from "react-native-nitro-modules";

import type { GPUBindGroupLayout } from "./GPUBindGroupLayout.nitro";
import type { GPUObjectBase } from "./GPUObjectBase";

export interface GPURenderPipeline
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {
  getBindGroupLayout(index: number): GPUBindGroupLayout;
}
