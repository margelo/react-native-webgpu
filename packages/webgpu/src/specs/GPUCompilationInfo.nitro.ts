import type { HybridObject } from "react-native-nitro-modules";

import type { GPUCompilationMessageType } from "./types/enums";

export interface GPUCompilationMessage {
  readonly message: string;
  readonly type: GPUCompilationMessageType;
  readonly lineNum: number;
  readonly linePos: number;
  readonly offset: number;
  readonly length: number;
}

export interface GPUCompilationInfo extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  readonly messages: GPUCompilationMessage[];
}
