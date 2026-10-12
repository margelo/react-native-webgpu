import type { CustomType } from "react-native-nitro-modules";

export interface GPUOrigin3DDict {
  x?: number;
  y?: number;
  z?: number;
}

export type GPUOrigin3D = CustomType<
  number[] | GPUOrigin3DDict,
  "GPUOrigin3D",
  { include: "GPUOrigin3D.hpp" }
>;
