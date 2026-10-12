import type { HybridObject, UInt64 } from "react-native-nitro-modules";

export interface Canvas extends HybridObject<{ ios: "c++"; android: "c++" }> {
  readonly surface: UInt64;
  width: number;
  height: number;
  readonly clientWidth: number;
  readonly clientHeight: number;
}
