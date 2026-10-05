import type { HybridObject } from "react-native-nitro-modules";

import type { GPUError } from "./GPUError.nitro";

export interface GPUUncapturedErrorEvent extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  readonly type: string;
  readonly error: GPUError;
}
