# Build and run Godot for Orta

This builds Godot with Orta's initial native two-pane workspace. Model connectivity and agent tools are not implemented yet.

## Apple Silicon Mac

Prerequisites: Xcode with its command-line tools, Python and SCons. Xcode and SCons were present on this machine when checked on 2026-09-23.

From the repository root:

```sh
scons -C engine platform=macos arch=arm64 target=editor \
  metal=yes vulkan=no angle=no accesskit=no module_mono_enabled=no \
  generate_bundle=yes
```

This configuration includes native Metal, leaves GDScript available, and excludes C#. It disables Vulkan/MoltenVK, ANGLE and AccessKit to avoid additional SDK dependencies for this first local build. Screen-reader support through AccessKit is therefore absent from this build.

After the build succeeds:

```sh
open engine/bin/godot_macos_editor.app
```

Opening the app without arguments launches the Orta workspace and its embedded empty game. On first launch, the bundled starter project is copied to `~/Library/Application Support/Orta/Workspace`. You can also open the `.app` directly from Finder. The starter currently uses the Compatibility renderer. Explicit command-line arguments retain the normal Godot behavior, including `--project-manager`.

Run the same build command after source changes; SCons performs incremental builds. This builds the editor only, not game export templates.

## Current build

Initial compilation succeeded on 2026-09-23 in 8 minutes 50 seconds. The executable reports `4.7.2.stable.custom_build`. Headless Project Manager startup and exit succeeded, the app's code signature verified, and the packaged app was opened on this Mac. This is a startup check, not a gameplay or rendering benchmark.

Build output is in `/private/tmp/orta-godot-build.log` on this machine.

The workspace changes also compiled and launched successfully. The current UI remains a prototype with layout issues; submitting a message only reports that no model is connected.
