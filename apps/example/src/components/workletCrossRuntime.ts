import { scheduleOnRN, scheduleOnUI } from "react-native-worklets";

export interface CrossRuntimeResult {
  portedBrand: string;
  portedLabel: string;
  legacyBrand: string;
  legacySize: number;
}

export const workletCrossRuntime = (
  device: GPUDevice,
): Promise<CrossRuntimeResult> => {
  const ported = device.createSampler();
  const legacy = device.createBuffer({
    size: 4,
    usage: GPUBufferUsage.COPY_DST,
  });
  return new Promise((resolve) => {
    scheduleOnUI(
      (sampler: GPUSampler, buffer: GPUBuffer) => {
        "worklet";
        sampler.label = "crossed";
        scheduleOnRN(resolve, {
          portedBrand: (sampler as unknown as { __brand: string }).__brand,
          portedLabel: sampler.label,
          legacyBrand: (buffer as unknown as { __brand: string }).__brand,
          legacySize: buffer.size,
        });
      },
      ported,
      legacy,
    );
  });
};
