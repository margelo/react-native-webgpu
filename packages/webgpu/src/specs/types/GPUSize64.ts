import type { CustomType } from "react-native-nitro-modules";

export type GPUSize64 = CustomType<
  number,
  "margelo::nitro::webgpu::GPUSize64",
  { include: "GPUSize64.hpp" }
>;
