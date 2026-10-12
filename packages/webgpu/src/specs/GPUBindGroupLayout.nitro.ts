import type { HybridObject } from "react-native-nitro-modules";

import type { GPUObjectBase } from "./GPUObjectBase";

export interface GPUBindGroupLayout
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {}
