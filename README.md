# LearnOpenGL Workspace (CMake + MSVC + GLCore)

This repository is a Windows-focused C++20 workspace for learning OpenGL. It contains:
- A minimal reusable framework library `GLCore` (GLFW + glad + GLM) that provides a clean application loop and a RAII window.
- Example(s) under `LearnOpenGL/` demonstrating concepts, starting with a window creation sample.

If you are following the LearnOpenGL journey, use `GLCore` to keep samples small and focused while avoiding boilerplate.

---

## Repository Layout
```
LearnOpenGL/
├─ CMakeLists.txt            # Top-level CMake project (adds GLCore and examples)
├─ GLCore/                   # Reusable mini framework (GLFW, glad, GLM bundled)
│  ├─ include/GLCore/        # Public headers (App.h, Window.h)
│  ├─ src/                   # Implementation
│  ├─ lib/                   # Vendored third-party sources (glfw, glad, glm, imgui, stb, json)
│  └─ CMakeLists.txt
├─ LearnOpenGL/
│  └─ creating_a_window/     # First example executable
└─ .gitignore
```

See [GLCore/README.md](GLCore/README.md) for the detailed API and extension notes.

---

## Prerequisites
- Windows 10/11 x64
- Git (optional, if cloning)
- CMake ≥ 3.24
- MSVC (Visual Studio 2022) or CLion with Visual Studio toolchain
- GPU/driver supporting OpenGL 3.3+

All third-party libraries are bundled under [GLCore/lib](GLCore/lib) and built from source; no external package manager is required.

---

## Build (Command Line, Visual Studio toolchain)
Use a "x64 Native Tools Command Prompt for VS 2022" or PowerShell with VS dev environment loaded.

```powershell
# From the repository root
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

Run the example executable (Debug config shown):
```powershell
# One of the typical output locations created by the generator
./build/LearnOpenGL/creating_a_window/Debug/creating_a_window.exe
```

To build Release:
```powershell
cmake --build build --config Release
```

---

## Build and Run (CLion)
1. Open the repository root in CLion.
2. Let CLion generate a CMake profile (e.g., `Debug` with VS toolchain).
3. Select the `creating_a_window` run configuration.
4. Build and Run. A window titled "LearnOpenGL" (or as configured) should appear; press ESC to close.

---

## Using GLCore in New Examples
Create a new example under `LearnOpenGL/<topic>/` with its own `CMakeLists.txt` and link against `GLCore`:
```cmake
add_executable(my_example main.cpp)
target_link_libraries(my_example PRIVATE GLCore)
target_compile_features(my_example PRIVATE cxx_std_20)
```
`GLCore` exposes public includes and transitively links GLFW, glad, and GLM. In your `main.cpp`, derive from `GLCore::App` and implement the lifecycle methods; see `GLCore/README.md` for a quick-start snippet.

---

## Troubleshooting
- CMake generator isn't found: ensure Visual Studio 2022 with C++ Desktop workload is installed. Re-run from a VS Developer Prompt.
- Linker errors for OpenGL: the project uses GLFW + glad; make sure you are building x64 and the generator matches `-A x64`.
- Black window / GL errors: verify your GPU drivers support OpenGL 3.3+ and update drivers if needed.
- CLion cannot find a toolchain: configure a Visual Studio toolchain (File → Settings → Build, Execution, Deployment → Toolchains) and ensure CMake uses it.

---

## Third‑Party Components
Bundled sources under `GLCore/lib` include:
- GLFW (window/input)
- glad (OpenGL function loader)
- GLM (math)
- ImGui, stb, JSON (present; not all are currently wired into builds)

Each component retains its own license in its repository; consult their upstreaming if redistributing. Within this workspace they are used as source dependencies.

---

## License
This workspace is for learning and experimentation. If you plan to distribute binaries or the [GLCore](GLCore) library independently, review and include licenses for GLFW, glad, and GLM (and any other libraries you enable).

---

## Status
Last updated: 2025-11-04 12:54 (local).