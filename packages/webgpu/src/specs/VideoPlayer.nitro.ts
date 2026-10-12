import type { HybridObject } from "react-native-nitro-modules";

import type { NativeVideoFrame } from "./NativeVideoFrame.nitro";

export interface VideoPlayer extends HybridObject<{
  ios: "c++";
  android: "c++";
}> {
  copyLatestFrame(): NativeVideoFrame | null;
  play(): void;
  pause(): void;
  release(): void;
  readonly paused: boolean;
  currentTime: number;
  readonly duration: number;
  volume: number;
  loop: boolean;
  readonly videoWidth: number;
  readonly videoHeight: number;
  readonly rotation: number;
  readonly frameRate: number;
}
