import type { HybridObject } from "react-native-nitro-modules";

import type { GPUDeviceLostReason } from "./types/enums";

export interface GPUDeviceLostInfo extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  readonly reason: GPUDeviceLostReason;
  readonly message: string;
}
