import type { CustomType } from "react-native-nitro-modules";

export interface GPUOrigin2DDict {
  x?: number;
  y?: number;
}

export type GPUOrigin2D = CustomType<
  number[] | GPUOrigin2DDict,
  "GPUOrigin2D",
  { include: "GPUOrigin2D.hpp" }
>;
