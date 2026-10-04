import React, { useState } from "react";
import { ScrollView, StyleSheet, Text, View } from "react-native";
import { Canvas } from "react-native-webgpu";

import { useWebGPU } from "../components/useWebGPU";
import { fetchAsset } from "../components/useAssets";

import { checkerboardWGSL, quadsWGSL } from "./shaders";

interface Check {
  name: string;
  nitro: boolean;
}

const isNitro = (value: object) => {
  const candidate = value as { dispose?: unknown; equals?: unknown };
  return (
    typeof candidate.dispose === "function" &&
    typeof candidate.equals === "function"
  );
};

const describe = (name: string, value: object): Check => ({
  name,
  nitro: isNitro(value),
});

const CHECKERBOARD_SIZE = 64;

export const NitroPort = () => {
  const [checks, setChecks] = useState<Check[]>([]);
  const [compilationMessages, setCompilationMessages] = useState<number>();

  const ref = useWebGPU(async ({ context, device, presentationFormat }) => {
    const asset = await fetchAsset(require("../assets/Di-3d.png"));
    const imageBitmap = await createImageBitmap(await asset.arrayBuffer());
    const photo = device.createTexture({
      size: [imageBitmap.width, imageBitmap.height],
      format: "rgba8unorm",
      usage:
        GPUTextureUsage.TEXTURE_BINDING |
        GPUTextureUsage.COPY_DST |
        GPUTextureUsage.RENDER_ATTACHMENT,
    });
    device.queue.copyExternalImageToTexture(
      { source: imageBitmap },
      { texture: photo },
      [imageBitmap.width, imageBitmap.height],
    );

    const checkerboard = device.createTexture({
      size: [CHECKERBOARD_SIZE, CHECKERBOARD_SIZE],
      format: "rgba8unorm",
      usage: GPUTextureUsage.STORAGE_BINDING | GPUTextureUsage.TEXTURE_BINDING,
    });
    const computePipeline = device.createComputePipeline({
      layout: "auto",
      compute: {
        module: device.createShaderModule({ code: checkerboardWGSL }),
      },
    });
    const computeBindGroup = device.createBindGroup({
      layout: computePipeline.getBindGroupLayout(0),
      entries: [{ binding: 0, resource: checkerboard.createView() }],
    });
    const computeEncoder = device.createCommandEncoder();
    const computePass = computeEncoder.beginComputePass();
    computePass.setPipeline(computePipeline);
    computePass.setBindGroup(0, computeBindGroup);
    computePass.dispatchWorkgroups(
      CHECKERBOARD_SIZE / 8,
      CHECKERBOARD_SIZE / 8,
    );
    computePass.end();
    device.queue.submit([computeEncoder.finish()]);

    const shaderModule = device.createShaderModule({ code: quadsWGSL });
    const compilationInfo = await shaderModule.getCompilationInfo();
    const bindGroupLayout = device.createBindGroupLayout({
      entries: [
        {
          binding: 0,
          visibility: GPUShaderStage.FRAGMENT,
          sampler: { type: "filtering" },
        },
        {
          binding: 1,
          visibility: GPUShaderStage.FRAGMENT,
          texture: { sampleType: "float" },
        },
        {
          binding: 2,
          visibility: GPUShaderStage.FRAGMENT,
          texture: { sampleType: "float" },
        },
      ],
    });
    const pipelineLayout = device.createPipelineLayout({
      bindGroupLayouts: [bindGroupLayout],
    });
    const renderPipeline = device.createRenderPipeline({
      layout: pipelineLayout,
      vertex: { module: shaderModule, entryPoint: "vs" },
      fragment: {
        module: shaderModule,
        entryPoint: "fs",
        targets: [{ format: presentationFormat }],
      },
    });
    const sampler = device.createSampler({
      magFilter: "nearest",
      minFilter: "linear",
    });
    const bindGroup = device.createBindGroup({
      layout: bindGroupLayout,
      entries: [
        { binding: 0, resource: sampler },
        { binding: 1, resource: checkerboard.createView() },
        { binding: 2, resource: photo.createView() },
      ],
    });
    const bundleEncoder = device.createRenderBundleEncoder({
      colorFormats: [presentationFormat],
    });
    bundleEncoder.setPipeline(renderPipeline);
    bundleEncoder.setBindGroup(0, bindGroup);
    bundleEncoder.draw(6, 2);
    const renderBundle = bundleEncoder.finish();
    const querySet = device.createQuerySet({ type: "occlusion", count: 1 });

    let reported = false;
    return () => {
      const view = context.getCurrentTexture().createView();
      const encoder = device.createCommandEncoder();
      const pass = encoder.beginRenderPass({
        colorAttachments: [
          {
            view,
            clearValue: [0.05, 0.05, 0.08, 1],
            loadOp: "clear",
            storeOp: "store",
          },
        ],
        occlusionQuerySet: querySet,
      });
      pass.beginOcclusionQuery(0);
      pass.executeBundles([renderBundle]);
      pass.endOcclusionQuery();
      pass.end();
      const commandBuffer = encoder.finish();
      device.queue.submit([commandBuffer]);
      if (!reported) {
        reported = true;
        setCompilationMessages(compilationInfo.messages.length);
        setChecks([
          describe("GPUShaderModule", shaderModule),
          describe("GPUCompilationInfo", compilationInfo),
          describe("GPUBindGroupLayout", bindGroupLayout),
          describe("GPUPipelineLayout", pipelineLayout),
          describe("GPURenderPipeline", renderPipeline),
          describe("GPUComputePipeline", computePipeline),
          describe("GPUSampler", sampler),
          describe("GPUBindGroup", bindGroup),
          describe("GPURenderBundle", renderBundle),
          describe("GPUQuerySet", querySet),
          describe("GPUTextureView", view),
          describe("GPUCommandBuffer", commandBuffer),
          describe("ImageBitmap", imageBitmap),
          describe("Canvas", context.canvas),
          describe("GPUDevice (still legacy)", device),
        ]);
      }
    };
  });

  return (
    <View style={style.container}>
      <Canvas ref={ref} style={style.canvas} />
      <ScrollView style={style.list}>
        <Text style={style.heading}>
          Compilation messages: {compilationMessages ?? "…"}
        </Text>
        {checks.map((check) => (
          <Text key={check.name} style={style.row}>
            {check.nitro ? "✅" : "⬜️"} {check.name}{" "}
            {check.nitro ? "Nitro" : "legacy"}
          </Text>
        ))}
      </ScrollView>
    </View>
  );
};

const style = StyleSheet.create({
  container: {
    flex: 1,
  },
  canvas: {
    width: "100%",
    aspectRatio: 2,
  },
  list: {
    flex: 1,
    padding: 16,
  },
  heading: {
    fontSize: 16,
    fontWeight: "600",
    marginBottom: 8,
  },
  row: {
    fontSize: 16,
    paddingVertical: 2,
  },
});
