# GLCore — Minimal OpenGL App Framework (C++20)

`GLCore` is a tiny reusable library within this workspace that sets up a GLFW window and OpenGL context, loads GL function pointers (glad), and drives a simple application loop via an `App` base class. It’s designed to keep examples clean and focused on LearnOpenGL concepts.

---

## Key Features
- C++20, header-only API surface with Pimpl-backed implementation
- RAII-managed window and GL context
- Built-in main loop with overridable lifecycle hooks
- vendored deps: GLFW, glad, GLM (available transitively)

---

## Directory
```
GLCore/
├─ include/GLCore/
│  ├─ App.h     # Abstract app API (OnInit/OnUpdate/OnRender/OnShutdown)
│  └─ Window.h  # RAII wrapper around GLFWwindow
├─ src/
│  ├─ App.cpp
│  └─ Window.cpp
└─ lib/         # vendored third‑party source (glfw, glad, glm, imgui, stb, json)
```

---

## CMake integration (inside this repo)
`GLCore` is added as a CMake library by the top-level project. Any executable in this repo can link it:
```cmake
add_executable(my_example main.cpp)
target_link_libraries(my_example PRIVATE GLCore)
target_compile_features(my_example PRIVATE cxx_std_20)
```
Public include directories and transitive link to `glfw`, `glad`, and `glm` are already configured by `GLCore`'s `CMakeLists.txt`.

No external package manager is required; all third-party libraries are built from source bundled under `GLCore/lib`.

---

## Quick Start
A minimal app using `GLCore::App`:
```cpp
#include <GLCore/App.h>

class MyApp : public GLCore::App {
protected:
    void OnInit() override {
        // Load resources, initialize state, set GL state
    }
    void OnShutdown() override {
        // Free resources
    }
    void OnUpdate() override {
        // Update logic, input, timing, etc.
    }
    void OnRender() override {
        // Issue GL draws. glad is included via App.h, so you can call GL directly.
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};

int main() {
    constexpr GLCore::AppProperties props{"My App", 1280, 720};
    auto app = std::make_unique<MyApp>(props);
    app->Run();
}
```

Run loop and buffer/event management are handled by `GLCore::App`.

---

## API Reference

### Namespaces
- `GLCore`

### Struct: `AppProperties`
Parameters used to construct an `App`:
- `const char* title`
- `int width`
- `int height`

### Class: `App`
Header: `include/GLCore/App.h`

Purpose: Base class providing an application loop and lifecycle callbacks.

Key members:
- Constructors: `App()`, `explicit App(AppProperties)`
- Move-only semantics (non-copyable)
- `void Run()` — starts the app loop
- `const char* GetAppName() const`
- `int GetAppWidth() const`
- `int GetAppHeight() const`

Lifecycle (override in derived class):
- `void OnInit()` — called once before the loop
- `void OnShutdown()` — called once after the loop ends
- `void OnUpdate()` — called once per frame before rendering
- `void OnRender()` — called once per frame for rendering

Notes:
- `App.h` includes `glad/glad.h`, so GL symbols are available in overrides.
- Input: Escape key closes the window by default (handled internally with GLFW).
- The internal implementation (`Impl`) creates and owns a `Window`.

### Struct: `WindowProperties`
- `const char* title`
- `int width`
- `int height`

### Class: `Window`
Header: `include/GLCore/Window.h`

Purpose: RAII wrapper over `GLFWwindow` with a pimpl.

Key members:
- Constructors: `Window()`, `explicit Window(const WindowProperties&)`
- Move-only semantics (non-copyable)
- `bool ShouldClose() const`
- `void SwapBuffers() const`
- `static void PollEvents()`
- Introspection: `int Width() const`, `int Height() const`, `const char* Title() const`
- `void* GetNativeHandle() const` — returns `GLFWwindow*` as a `void*`

---

## Rendering and Loop Order
Within `App::Run()` the internal loop performs roughly:
1. Process input (ESC to close)
2. `OnUpdate()`
3. `OnRender()`
4. Clear and present frame:
   - `glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`
   - `SwapBuffers()`
   - `Window::PollEvents()`

You can additionally clear in `OnRender()` if desired; the library performs a default clear after your render to guarantee a presentable frame.

---

## Requirements
- Windows 10/11 x64
- OpenGL 3.3+ capable GPU/driver
- Built with MSVC via CMake (see root `README.md` for detailed build steps)

---

## Common Questions
- How do I access GLFW directly?
  - Use `static_cast<GLFWwindow*>(window.GetNativeHandle())` if you have a `Window`. From an `App`, GLCore uses an internal `Window`; expose or augment as needed for advanced scenarios.
- Where do I include GL headers?
  - `App.h` already includes `glad/glad.h` for your overrides; you can include it directly in other files as needed.
- Input handling?
  - The template only implements ESC-to-close. Add your own input handling via GLFW callbacks or polling.

---

## License
This library is part of the project in the repository root. See the root `README.md` for license guidance. Include third‑party notices if distributing `GLCore` separately.

---

## Status
Last updated: 2025-11-04 11:06 (local).
