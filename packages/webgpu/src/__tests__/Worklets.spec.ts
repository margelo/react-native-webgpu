import { client } from "./setup";

interface CrossRuntimeResult {
  portedBrand: string;
  portedLabel: string;
  legacyBrand: string;
  legacySize: number;
}

describe("Worklets", () => {
  it("passes ported and legacy objects to the UI runtime", async () => {
    if (client.OS === "web") {
      return;
    }
    const result = await client.eval<
      Record<string, unknown>,
      CrossRuntimeResult | "unsupported"
    >(({ gpu, workletCrossRuntime }) => {
      if (!workletCrossRuntime) {
        return "unsupported" as const;
      }
      return gpu
        .requestAdapter()
        .then((adapter) => adapter!.requestDevice())
        .then((device) => workletCrossRuntime(device));
    });
    if (result === "unsupported") {
      return;
    }
    expect(result).toEqual({
      portedBrand: "GPUSampler",
      portedLabel: "crossed",
      legacyBrand: "GPUBuffer",
      legacySize: 4,
    });
  });
});
