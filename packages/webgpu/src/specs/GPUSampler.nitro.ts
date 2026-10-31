import { Android, Apple } from "nitro-core";
import type { HybridObject } from "nitro-core";

import type { GPUObjectBase } from "./GPUObjectBase";

export * from "#nitro/GPUSampler";

@Apple({ language: "c++", allowMultipleImplementations: true })
@Android({ language: "c++", allowMultipleImplementations: true })
export declare class GPUSampler extends HybridObject implements GPUObjectBase {
  label: string;
}
