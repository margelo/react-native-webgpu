export const checkerboardWGSL = /* wgsl */ `
@group(0) @binding(0) var output: texture_storage_2d<rgba8unorm, write>;

@compute @workgroup_size(8, 8)
fn main(@builtin(global_invocation_id) id: vec3u) {
  let isEven = ((id.x / 8u) + (id.y / 8u)) % 2u == 0u;
  let color = select(vec4f(0.1, 0.2, 0.9, 1.0), vec4f(1.0, 0.8, 0.1, 1.0), isEven);
  textureStore(output, id.xy, color);
}
`;

export const quadsWGSL = /* wgsl */ `
@group(0) @binding(0) var linearSampler: sampler;
@group(0) @binding(1) var checkerboard: texture_2d<f32>;
@group(0) @binding(2) var photo: texture_2d<f32>;

struct VertexOut {
  @builtin(position) position: vec4f,
  @location(0) uv: vec2f,
  @location(1) @interpolate(flat) quad: u32,
}

@vertex
fn vs(@builtin(vertex_index) vertex: u32, @builtin(instance_index) quad: u32) -> VertexOut {
  var corners = array<vec2f, 6>(
    vec2f(0.0, 0.0), vec2f(1.0, 0.0), vec2f(0.0, 1.0),
    vec2f(0.0, 1.0), vec2f(1.0, 0.0), vec2f(1.0, 1.0),
  );
  let corner = corners[vertex];
  var out: VertexOut;
  out.position = vec4f(-0.95 + f32(quad) + corner.x * 0.9, -0.9 + corner.y * 1.8, 0.0, 1.0);
  out.uv = vec2f(corner.x, 1.0 - corner.y);
  out.quad = quad;
  return out;
}

@fragment
fn fs(in: VertexOut) -> @location(0) vec4f {
  let checker = textureSample(checkerboard, linearSampler, in.uv);
  let image = textureSample(photo, linearSampler, in.uv);
  return select(checker, image, in.quad == 1u);
}
`;
