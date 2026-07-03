# BlockEngine

## Build

```bash
git submodule update --init --recursive   # first time only
xmake                                      # auto-installs packages on first run
xmake run                                  # launch the engine window
```

Binary output: `build/macosx/arm64/release/BlockEngine`

## Project Structure

Single-binary C++23 engine built with [xmake](https://xmake.io). Each functional
module is also a **C++20 named module** and an **xmake static library target**.

```
Source/
├── shared.lua          # modes, packages (imgui, stb, spdlog, glm), warnings, BE_DEBUG
├── xmake.lua           # includes shared.lua, then all modules + App in dep order
├── Core/
│   ├── xmake.lua       # target("Core")          — static lib, no deps
│   ├── Core.mpp        # export module be.core;  — re-exports partitions + Event
│   ├── Core-math.mpp   # export module be.core:math;  — glm aliases (Vec3=glm::vec3, Mat4=glm::mat4) + Ray
│   └── Core-ecs.mpp    # export module be.core:ecs;   — ECS (Registry, Ent)
├── Platform/
│   ├── xmake.lua       # target("Platform")      — static lib, deps Core
│   ├── Platform.mpp    # export module be.platform;
│   ├── SokolApp.cpp    # module be.platform;     — MU (SokolApp method impl)
│   └── SokolImpl.mm    # regular ObjC++          — SOKOL_IMPL + STB_IMAGE_IMPLEMENTATION
├── Render/
│   ├── xmake.lua       # target("Render")        — static lib, deps Core, Platform
│   └── Render.mpp      # export module be.render;
├── Input/
│   ├── xmake.lua       # target("Input")         — static lib, deps Core, Platform
│   └── Input.mpp       # export module be.input;
├── Audio/
│   ├── xmake.lua       # target("Audio")         — static lib, deps Core
│   └── Audio.mpp       # export module be.audio;
├── UI/
│   ├── xmake.lua       # target("UI")            — static lib, deps Core, Platform
│   └── UI.mpp          # export module be.ui;
├── Scene/
│   ├── xmake.lua       # target("Scene")         — static lib, deps Core, Platform, Render, Input, UI
│   └── Scene.mpp       # export module be.scene;
├── Engine/
│   ├── xmake.lua       # target("Engine")        — static lib, deps all above
│   └── Engine.mpp      # export module be.engine;
└── App/
    ├── xmake.lua       # target("BlockEngine")   — binary, deps Engine
    └── Main.cpp        # import be.engine; main()
```

### Module dependency graph

```
Core  ────────────────────────────────────────────┐
  │                                                │
  ├── Platform ──┬── Render ──┐                    │
  │              ├── Input ───┤                    │
  │              └── UI ──────┼── Scene ── Engine ── BlockEngine
  └── Audio ─────────────────┘
```

### Key conventions

- Module interface files use extension `.mpp` (xmake's default for C++ modules).
- `{public = true}` on `add_files("X.mpp", {public = true})` makes a module's
  interface visible to dependent targets via `add_deps(...)`.
- External C/C++ headers (sokol, imgui, soloud, stb, spdlog) are included via
  `#include` in the **global module fragment** (`module; ... #include ...`).
- Standard library is imported via `import std;` in the module purview (C++23).
  Direct use of `std::vector`, `std::unique_ptr` etc. — no wrapper aliases.
- Module names use dot-notation: `be.core`, `be.platform`, `be.render`, etc.
- Module partitions use colon-notation: `be.core:math`, `be.core:ecs`.
- All code in `namespace be`; ECS in `namespace be::ecs`.

## External Dependencies

| Dep   | Source              | Notes |
|-------|---------------------|-------|
| sokol | git submodule       | Header-only; included in global module fragment |
| soloud| git submodule       | Sources compiled in Audio target |
| stb   | xmake package `stb` | Implementation (`STB_IMAGE_IMPLEMENTATION`) in `SokolImpl.mm` |
| imgui | xmake package `imgui` | Included in global module fragment |
| spdlog| xmake package `spdlog` | Included in global module fragment |
| glm   | xmake package `glm` | Included in global module fragment (`Core-math.mpp` aliases `Vec3=glm::vec3`, `Mat4=glm::mat4`) |

Include paths (root `xmake.lua`):
- `$(projectdir)/Source`
- `external/sokol`, `external/sokol/util`, `external/soloud/include`

## Threading Architecture

Game and rendering run on separate threads:

```
Game Thread (worker, ~60Hz fixed timestep)     Render Thread (main, vsync)
┌──────────────────────────────────────┐     ┌─────────────────────────────┐
│ InputSystem::BeginFrame()            │     │ SokolApp::FrameCallback()    │
│ UpdateCam(dt)                        │     │   snapshot = bridge.Acquire()│
│ UpdateMovement(dt) — ECS Each<>      │     │   RenderSystem::BeginFrame() │
│ UpdatePicking()                      │     │   DrawSolidCube/WireCube/    │
│ PublishSnapshot()                    │     │     GroundGrid (from snapshot)│
│   → bridge.Publish(snapshot) ────────┼────→│   DrawDebugUI(snapshot)      │
│                                      │     │                             │
│ InputSystem reads (mutex-protected)  │     │ Input events → HandleEvent() │
└──────────────────────────────────────┘     └─────────────────────────────┘
```

### Data transfer

- `RenderBridge` in `Render.mpp`: `shared_ptr<FrameSnapshot>` swap via `std::mutex`
- Game thread calls `Publish()`, render thread calls `Acquire()` — zero-copy
- `FrameSnapshot` contains: `commands[]` (solid), `wireCommands[]`, camera state, debug UI data

### Synchronization

- `InputSystem`: `std::mutex` on all reads/writes — render thread writes events, game thread reads state
- `RenderBridge`: `std::mutex` on `shared_ptr` swap — minimal lock contention
- Game loop uses `std::chrono::steady_clock` for fixed timestep (60Hz), sleeps between ticks
- `mRunning` is `std::atomic<bool>` for clean shutdown

`.clang-format` (based on Microsoft CCF) — key rules:
- C++23, 2-space indent, 80-column limit
- **Allman braces** (braces on new line after every control statement, class, function, namespace)
- **Left pointer alignment** (`int* p` not `int *p`)
- `NamespaceIndentation: All`
- `SortIncludes: true`, `IncludeBlocks: Regroup`

All code in `namespace be`; ECS in `namespace be::ecs`.

## Gotchas

- **SokolImpl.mm**: On macOS sokol_app.h includes AppKit headers. The file MUST be
  `.mm` (Objective-C++). Never rename to `.cpp`. It is a **regular (non-module)**
  translation unit that defines `SOKOL_IMPL`, `SOKOL_GL_IMPL`, and
  `STB_IMAGE_IMPLEMENTATION`. SokolApp method implementations live in the
  separate `SokolApp.cpp` module implementation unit.
- **SOKOL_NO_ENTRY**: Defined in `SokolImpl.mm` to prevent sokol from generating its own `main`.
- **C++20 Modules**: Each functional module is a C++20 named module. The `.mpp` files
  are **module interface units** (`export module be.xxx;`). Module implementation units
  (`module be.xxx;`) use `.cpp` extension. Module partitions use `export module be.core:sub;`.
- **Global module fragment**: External headers (sokol, imgui, spdlog, stb) that are
  not module-aware must be `#include`d in the global module fragment (`module;` block
  before the `export module` declaration).
- **`import std;`**: Standard library is imported as a module (C++23), not `#include`d.
  Use `std::vector` directly — no `DynArray<T>` wrappers.
- **`import std;` + third-party C++ headers**: Modules that include C++ headers (glm, spdlog)
  which internally `#include` STL cannot also `import std;` due to ODR conflicts. These
  modules use the global module fragment for all includes. See `Core-math.mpp`, `Render.mpp`,
  `Engine.mpp`.
- **xmake module detection**: xmake auto-detects `.mpp` files as module interfaces.
  For cross-target module visibility, `.mpp` files must be added with
  `{public = true}`.
- **SoLoud backends**: `WITH_COREAUDIO` (macOS), `WITH_WASAPI` (Windows), `WITH_MINIAUDIO` (Linux).
- **Platform defines**: `SOKOL_METAL` (macOS), `SOKOL_D3D11` (Windows), `SOKOL_GLCORE33` (Linux).
- **macOS frameworks**: Metal, MetalKit, QuartzCore, Cocoa (Platform target);
  AudioToolbox, CoreAudio, CoreFoundation (Audio target).
- **C++23 only**: Uses `<format>`, `<ranges>`, concepts. README says C++17 but code requires C++23.
- **ECS**: Sparse-set storage in `Core-ecs.mpp`. `Registry::Each<A,B,C>(fn)` supports 1–3 component
  types via `if constexpr` dispatch. Entity access uses `Ent{i, generation}` with generational indexing.
- **No tests, no CI**: The repository has no test framework, CI workflows, or pre-commit hooks.
- **Build config**: `BE_DEBUG` defined in debug mode (`Source/shared.lua`). Release mode uses `-O fastest`.
