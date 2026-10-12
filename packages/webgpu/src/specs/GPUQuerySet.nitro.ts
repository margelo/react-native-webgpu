import type { HybridObject } from "react-native-nitro-modules";

import type { GPUObjectBase } from "./GPUObjectBase";
import type { GPUQueryType } from "./types/enums";

export interface GPUQuerySet
  extends HybridObject<{ ios: "c++"; android: "c++" }>, GPUObjectBase {
  readonly type: GPUQueryType;
  readonly count: number;
  destroy(): void;
}
