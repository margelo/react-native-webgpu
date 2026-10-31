// WebGPU's GPUObjectBase mixin. Specs implement it and declare its members,
// so nitrogen generates them on every GPU object.
export interface GPUObjectBase {
  label: string;
}
