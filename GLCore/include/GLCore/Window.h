//
// Created by niek on 11/3/2025.
//

#ifndef LEARNOPENGL_WINDOW_H
#define LEARNOPENGL_WINDOW_H

#include <memory>

namespace GLCore {

    struct WindowProperties {
        const char* title;
        int width;
        int height;
    };

    class Window {
    public:
        Window();
        explicit Window(const WindowProperties& props);
        ~Window();

        // Non-copyable, movable
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) noexcept;
        Window& operator=(Window&&) noexcept;

        // Basic operations
        bool ShouldClose() const;
        void SwapBuffers() const;
        static void PollEvents();

        // Introspection
        int Width() const;
        int Height() const;
        const char* Title() const;

        // Native handle (GLFW)
        void* GetNativeHandle() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };

}

#endif //LEARNOPENGL_WINDOW_H