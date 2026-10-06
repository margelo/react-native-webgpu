import type { CustomType } from "react-native-nitro-modules";

export interface GPUExtent3DDict {
  width: number;
  height?: number;
  depthOrArrayLayers?: number;
}

export type GPUExtent3D = CustomType<
  number[] | GPUExtent3DDict,
  "GPUExtent3D",
  { include: "GPUExtent3D.hpp" }
>;
