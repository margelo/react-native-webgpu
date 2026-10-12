import type { CustomType } from "react-native-nitro-modules";

export interface GPUColorDict {
  r: number;
  g: number;
  b: number;
  a: number;
}

export type GPUColor = CustomType<
  number[] | GPUColorDict,
  "GPUColor",
  { include: "GPUColor.hpp" }
>;
