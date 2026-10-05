import type { HybridObject } from "react-native-nitro-modules";

export interface GPUAdapterInfo extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  readonly vendor: string;
  readonly architecture: string;
  readonly device: string;
  readonly description: string;
  readonly isFallbackAdapter: boolean;
}
