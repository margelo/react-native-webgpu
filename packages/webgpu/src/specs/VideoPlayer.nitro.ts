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
}
