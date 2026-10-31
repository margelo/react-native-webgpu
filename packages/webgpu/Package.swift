// swift-tools-version: 6.2
//
// SwiftPM manifest for react-native-webgpu. iOS only.
//
// React Native 0.87+ references a library that ships its own Package.swift
// through a symlink at <app>/ios/build/generated/autolinking/libs/<name>, and
// resolves the relative paths below against that symlink. They are the same
// for every standard app, because the symlink location is. Earlier React
// Native releases have no SwiftPM autolinking: keep CocoaPods there.

import Foundation
import PackageDescription

// Absolute location of this package. Xcode passes the autolinking symlink as
// the package directory, so resolve it before deriving sibling paths.
let packageRoot = URL(fileURLWithPath: Context.packageDirectory)
  .resolvingSymlinksInPath().path
let sibling = { (relative: String) -> String in
  URL(fileURLWithPath: "\(packageRoot)/\(relative)").standardized.path
}
// A node package next to this one: a sibling in the consumer's node_modules,
// or under this monorepo's root.
let nodePackage = { (name: String) -> String? in
  ["../\(name)", "../../node_modules/\(name)"]
    .map(sibling)
    .first { FileManager.default.fileExists(atPath: "\($0)/package.json") }
}
let readJSON = { (path: String) -> [String: Any]? in
  guard let data = FileManager.default.contents(atPath: path) else { return nil }
  return try? JSONSerialization.jsonObject(with: data) as? [String: Any]
}

// Dawn, the WebGPU implementation, comes from the react-native-webgpu-dawn npm
// package this package depends on: an xcframework with the `webgpu/` and
// `dawn/` headers embedded in every slice, which SwiftPM exposes to dependents
// without any search path. react-native-skia's Graphite backend links the
// same package, so an app installing both contains exactly one Dawn.
guard let dawnPath = nodePackage("react-native-webgpu-dawn") else {
  // Reached when the dependency was skipped at install time, which SwiftPM
  // would otherwise report as an unresolvable dependency path.
  fatalError(
    """
    react-native-webgpu-dawn was not found next to react-native-webgpu. It ships \
    the Dawn binaries this package links against. Reinstall dependencies.
    """)
}
let ownPackage = readJSON("\(packageRoot)/package.json") ?? [:]
let dawnVersion =
  (readJSON("\(dawnPath)/package.json")?["version"] as? String) ?? "unknown"

// Skia Graphite and WebGPU must link the exact same Dawn, or the pair links
// fine and crashes at runtime. react-native-skia's podspec enforces this at
// `pod install` time; a Swift package has no install hook, so the same check
// runs here, at manifest evaluation. SwiftPM caches evaluations, so after
// changing either package's Dawn reset the package caches (File > Packages >
// Reset Package Caches) if this does not re-run.
//
// A react-native-skia that depends on react-native-webgpu-dawn itself must pin
// the same version as this package. Older Graphite builds (react-native-skia
// 3.0.x) vendor their own Dawn and record its release tag at
// libs/.dawn-version in their binary packages; this package's `dawn` field
// names the release that Dawn is interchangeable with.
if let skiaPath = nodePackage("react-native-skia"),
  let skiaPackage = readJSON("\(skiaPath)/package.json"),
  let skiaDawn = (skiaPackage["dependencies"] as? [String: String])?["react-native-webgpu-dawn"]
{
  if skiaDawn != dawnVersion {
    fatalError(
      """
      react-native-webgpu: Dawn version mismatch. This package links \
      react-native-webgpu-dawn \(dawnVersion) but react-native-skia depends on \
      \(skiaDawn). Align the two packages so the app contains exactly one Dawn.
      """)
  }
} else {
  let dawnReleaseTag =
    "dawn-\((ownPackage["dawn"] as? String ?? "").replacingOccurrences(of: "/", with: "-"))"
  // The graphite packages are normally hoisted next to this package, but may
  // be nested under react-native-skia when the package manager cannot hoist
  // them. The v2 Graphite previews (e.g. @shopify/react-native-skia@2.12.0-next.1)
  // keep the marker in their own libs/. Every marker found is checked.
  let skiaDawnMarkers = [
    "react-native-skia-graphite-apple-ios/libs/.dawn-version",
    "react-native-skia-graphite-apple-macos/libs/.dawn-version",
    "react-native-skia/node_modules/react-native-skia-graphite-apple-ios/libs/.dawn-version",
    "react-native-skia/node_modules/react-native-skia-graphite-apple-macos/libs/.dawn-version",
    "@shopify/react-native-skia/libs/.dawn-version",
  ].flatMap { marker in
    [
      sibling("../\(marker)"), // consumer: sibling in node_modules
      sibling("../../node_modules/\(marker)"), // this monorepo
    ]
  }
  for marker in skiaDawnMarkers {
    guard let data = FileManager.default.contents(atPath: marker),
      let skiaDawn = String(data: data, encoding: .utf8)?
        .trimmingCharacters(in: .whitespacesAndNewlines)
    else { continue }
    if skiaDawn != dawnReleaseTag {
      fatalError(
        """
        react-native-webgpu: Dawn version mismatch. This package links \
        react-native-webgpu-dawn \(dawnVersion) (\(dawnReleaseTag)) but the \
        react-native-skia Graphite binaries (\(marker)) link \(skiaDawn). Align \
        the two packages so the app contains exactly one Dawn.
        """)
    }
  }
}

// Unlike a native Xcode target, SwiftPM doesn't generate an implicit
// per-target header map, so quoted includes only resolve within the
// including file's own directory. The sources use bare cross-directory
// includes (e.g. apple/WebGPUModule.h includes "RNWebGPUManager.h" from
// cpp/rnwgpu), so every directory that's the target of one of those bare
// includes has to be listed explicitly here. The "webgpu/..." and "dawn/..."
// includes resolve through the Dawn xcframework's embedded headers.
let internalHeaderDirs = [
  "apple",
  "cpp",
  "cpp/jsi",
  "cpp/rnwgpu",
  "cpp/rnwgpu/api",
  "cpp/rnwgpu/api/descriptors",
  "cpp/rnwgpu/async",
]

let package = Package(
  name: "ReactNativeWebGPU",
  // Minimum iOS version for Nitro.
  platforms: [.iOS(.v16)],
  dependencies: [
    .package(name: "React-GeneratedCode", path: "../../../ios"),
    .package(path: dawnPath),
  ]
)

// The sources compile in nitrogen's ReactNativeWebGPUCxx target, next to the
// generated specs they implement; apple/ is Objective-C++, not Swift.
addNitrogenTargets(
  to: package,
  swiftSources: [],
  cxxSources: ["apple", "cpp/jsi", "cpp/rnwgpu"],
  dependencies: [
    .product(name: "ReactHeaders", package: "ReactNative"),
    // RNWgpuViewSpec, generated by the app's codegen run.
    .product(name: "ReactAppHeaders", package: "React-GeneratedCode"),
    .product(name: "react-native-webgpu-dawn", package: "react-native-webgpu-dawn"),
  ],
  cxxSettings: internalHeaderDirs.map { CXXSetting.headerSearchPath($0) } + [
    // CocoaPods forces both project-wide; the SwiftPM path defines neither.
    // React Native's headers gate on them, and the prebuilt React.framework
    // was built with both, so the module must see the same declarations.
    .define("RCT_NEW_ARCH_ENABLED", to: "1"),
    .define("RCT_REMOVE_LEGACY_ARCH", to: "1"),
  ]
)

// VideoPlayer uses AVFoundation / CoreMedia, shared-texture surfaces use
// CoreVideo (CVPixelBuffer), and ImageIO provides CGImageSource, the image
// decoder behind createImageBitmap. addNitrogenTargets takes no linker settings.
package.targets.first { $0.name == "ReactNativeWebGPUCxx" }!.linkerSettings = [
  .linkedFramework("AVFoundation"),
  .linkedFramework("CoreMedia"),
  .linkedFramework("CoreVideo"),
  .linkedFramework("ImageIO"),
]

// nitrogen:begin
//
// This section was generated by nitrogen. DO NOT MODIFY THIS SECTION.
// Running nitrogen replaces everything between "nitrogen:begin" and "nitrogen:end".
// https://github.com/margelo/nitro
// Copyright © Marc Rousavy @ Margelo
//

// swift-format-ignore
import Foundation

/// Adds the `ReactNativeWebGPU` library and its targets to `package`:
///
/// - `ReactNativeWebGPUCxx`: The generated cross-platform C++ specs, and your C++ sources.
/// - `ReactNativeWebGPUAppleCxx`: The generated C++ bridge declarations that Swift imports.
/// - `ReactNativeWebGPU`: Your Swift sources and the generated Swift specs.
/// - `ReactNativeWebGPUSwiftBridge`: The generated C++ wrappers that call into Swift, and autolinking.
///
/// It also adds the packages these targets depend on: React Native's `ReactNative` package,
/// `NitroModules`, and the Nitro modules whose types the specs use.
/// React Native's autolinking references every library through `build/generated/autolinking/libs/<SwiftName>`,
/// and SwiftPM resolves the relative package paths against that location.
/// List every Nitro module this library depends on in `swiftpmConfig.dependencies` in package.json,
/// so React Native's autolinking links it too.
/// Packages without a C++ language standard use C++20.
///
/// - Parameters:
///   - package: The package to add the library and its targets to.
///   - swiftSources: Directories or files containing your Swift sources, relative to the package root.
///     Paths that don't exist are skipped.
///   - cxxSources: Directories or files containing your C++ sources, relative to the package root.
///     Paths that don't exist are skipped. Their directories are also added to the header search paths.
///   - dependencies: Additional dependencies of all targets.
///   - swiftSettings: Additional Swift settings of the `ReactNativeWebGPU` Swift target.
///   - cxxSettings: Additional C++ settings of the `ReactNativeWebGPUCxx` and `ReactNativeWebGPUSwiftBridge` targets.
// swift-format-ignore
func addNitrogenTargets(
    to package: Package,
    swiftSources: [String] = ["apple"],
    cxxSources: [String] = ["cpp"],
    dependencies: [Target.Dependency] = [],
    swiftSettings: [SwiftSetting] = [],
    cxxSettings: [CXXSetting] = []
) {
    package.dependencies += [
        .package(name: "ReactNative", path: "../../../../xcframeworks"),
        .package(name: "NitroModules", path: "../NitroModules"),
    ]
    let nitroModuleDependencies: [Target.Dependency] = [
        .product(name: "NitroModules", package: "NitroModules"),
    ] + dependencies

    let packageDirectory = URL(fileURLWithPath: Context.packageDirectory)
    func exists(_ path: String) -> Bool {
        return FileManager.default.fileExists(atPath: packageDirectory.appendingPathComponent(path).path)
    }
    let userSwiftSources = swiftSources.filter(exists)
    let userCxxSources = cxxSources.filter(exists)
    func userHeaderSearchPaths(relativeTo targetPath: String) -> [CXXSetting] {
        let targetComponents = packageDirectory.appendingPathComponent(targetPath).standardizedFileURL.pathComponents
        return userCxxSources.map { source in
            let sourceURL = packageDirectory.appendingPathComponent(source)
            var isDirectory: ObjCBool = false
            FileManager.default.fileExists(atPath: sourceURL.path, isDirectory: &isDirectory)
            let directory = isDirectory.boolValue ? sourceURL : sourceURL.deletingLastPathComponent()
            let headerComponents = directory.standardizedFileURL.pathComponents
            let commonCount = zip(targetComponents, headerComponents).prefix { $0.0 == $0.1 }.count
            let relativeComponents = Array(repeating: "..", count: targetComponents.count - commonCount)
                + headerComponents.dropFirst(commonCount)
            return .headerSearchPath(relativeComponents.isEmpty ? "." : relativeComponents.joined(separator: "/"))
        }
    }

    // React Native's prebuilt React.framework is either Debug or Release, keep the C++ ABI in sync.
    let releaseSettings: [CXXSetting] = [
        .define("DEBUG", .when(configuration: .debug)),
        .define("NDEBUG", .when(configuration: .release)),
    ]
    let commonCxxSettings: [CXXSetting] = releaseSettings + [
        .disableWarning("nullability-extension"),
    ]
    let reactNativeDependencies: [Target.Dependency] = [
        .product(name: "ReactNativeHeaders", package: "ReactNative"),
        .product(name: "ReactNativeDependenciesHeaders", package: "ReactNative"),
    ]

    let cxxSourcesInTarget = ["nitrogen/generated/shared/c++"] + userCxxSources
    let cxxTarget: Target = .target(
        name: "ReactNativeWebGPUCxx",
        dependencies: nitroModuleDependencies + reactNativeDependencies,
        path: ".",
        exclude: nitrogenExcludes(in: ".", keeping: cxxSourcesInTarget)
            + ["nitrogen/generated/shared/c++/include"],
        sources: cxxSourcesInTarget,
        publicHeadersPath: "nitrogen/generated/shared/c++/include",
        cxxSettings: commonCxxSettings + userHeaderSearchPaths(relativeTo: ".") + cxxSettings
    )

    let appleCxxTarget: Target = .target(
        name: "ReactNativeWebGPUAppleCxx",
        dependencies: ["ReactNativeWebGPUCxx"] + nitroModuleDependencies,
        path: "nitrogen/generated/apple/ReactNativeWebGPUAppleCxx",
        cxxSettings: commonCxxSettings + userHeaderSearchPaths(relativeTo: "nitrogen/generated/apple/ReactNativeWebGPUAppleCxx")
    )

    let swiftSourcesInTarget = userSwiftSources + [
        "nitrogen/generated/apple/swift",
    ]
    let swiftDependencies: [Target.Dependency] = ["ReactNativeWebGPUAppleCxx"] + nitroModuleDependencies
    let generatedSwiftSettings: [SwiftSetting] = [
        .swiftLanguageMode(.v6),
        .enableUpcomingFeature("InternalImportsByDefault"),
        .interoperabilityMode(.Cxx),
        .unsafeFlags(["-Xfrontend", "-clang-header-expose-decls=has-expose-attr-or-stdlib"]),
        // Swift leaves declarations that use another module's Swift types, like AnyJSON,
        // out of the generated header unless that module's header is exposed to it.
        .unsafeFlags([
            "-Xfrontend", "-clang-header-expose-module", "-Xfrontend", "NitroModules=NitroModules-Swift.h",
        ]),
    ]
    let swiftTarget: Target = .target(
        name: "ReactNativeWebGPU",
        dependencies: swiftDependencies,
        path: ".",
        exclude: nitrogenExcludes(in: ".", keeping: swiftSourcesInTarget),
        sources: swiftSourcesInTarget,
        cxxSettings: releaseSettings,
        swiftSettings: generatedSwiftSettings + swiftSettings
    )

    let swiftBridgeSources = [
        "c++",
        "ReactNativeWebGPU-Swift-Cxx-Bridge.cpp",
        "ReactNativeWebGPUAutolinking.cpp",
        "ReactNativeWebGPUAutolinking.mm",
    ].filter { exists("nitrogen/generated/apple/" + $0) }
    let swiftBridgeSettings: [CXXSetting] = [
        // Include Swift's generated header textually after the C++ declarations it uses.
        // Swift Build and Xcode provide the generated header directory.
        .unsafeFlags(["-I${GENERATED_MODULEMAP_DIR}", "-fno-modules"]),
    ]
    let swiftBridgeTarget: Target = .target(
        name: "ReactNativeWebGPUSwiftBridge",
        dependencies: [
            "ReactNativeWebGPU",
            "ReactNativeWebGPUAppleCxx",
        ] + nitroModuleDependencies + reactNativeDependencies,
        path: "nitrogen/generated/apple",
        exclude: nitrogenExcludes(in: "nitrogen/generated/apple", keeping: swiftBridgeSources)
            + ["c++/include"],
        sources: swiftBridgeSources,
        publicHeadersPath: "c++/include",
        cxxSettings: commonCxxSettings + userHeaderSearchPaths(relativeTo: "nitrogen/generated/apple") + swiftBridgeSettings + cxxSettings
    )

    package.products.append(
        .library(name: "ReactNativeWebGPU", targets: ["ReactNativeWebGPUCxx", "ReactNativeWebGPU", "ReactNativeWebGPUSwiftBridge"])
    )
    package.targets += [cxxTarget, appleCxxTarget, swiftTarget, swiftBridgeTarget]
    if package.cxxLanguageStandard == nil {
        package.cxxLanguageStandard = .cxx20
    }
}

/// Returns the files and directories in `path` that are neither `sources` nor contain them.
/// Excluding them stops SwiftPM from scanning unrelated files, like `node_modules`.
// swift-format-ignore
func nitrogenExcludes(in path: String, keeping sources: [String]) -> [String] {
    var parents: Set<String> = [""]
    for source in sources {
        var components = source.split(separator: "/").dropLast()
        while !components.isEmpty {
            parents.insert(components.joined(separator: "/"))
            components = components.dropLast()
        }
    }

    let targetURL = URL(fileURLWithPath: Context.packageDirectory).appendingPathComponent(path)
    var excludes: [String] = []
    for parent in parents.sorted() {
        let parentURL = targetURL.appendingPathComponent(parent)
        let entries = (try? FileManager.default.contentsOfDirectory(atPath: parentURL.path)) ?? []
        for entry in entries.sorted() where !entry.hasPrefix(".") {
            let entryPath = parent.isEmpty ? entry : "\(parent)/\(entry)"
            if !sources.contains(entryPath) && !parents.contains(entryPath) {
                excludes.append(entryPath)
            }
        }
    }
    return excludes
}
// nitrogen:end
