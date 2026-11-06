import type { CustomType } from "react-native-nitro-modules";

export type GPUColor = CustomType<
  object,
  "margelo::nitro::webgpu::GPUColor",
  { include: "GPUColor.hpp" }
>;
