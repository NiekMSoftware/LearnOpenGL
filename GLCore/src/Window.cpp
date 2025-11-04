//
// Created by niek on 11/3/2025.
//

#include "GLCore/Window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <atomic>
#include <stdexcept>

namespace GLCore {

    struct Window::Impl {
        GLFWwindow* handle{nullptr};
        WindowProperties props{};

        static std::atomic<int> sWindowCount;
        static std::atomic<bool> sGLFWInitialized;
        static std::atomic<bool> sGLADLoaded;

        explicit Impl(const WindowProperties& p) : props(p) {
            InitializeGLFWOnce();

            // Set for OpenGL 3.3
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            handle = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);
            if (!handle) {
                TerminateGLFWIfLast();
                throw std::runtime_error("Failed to create GLFW window");
            }

            ++sWindowCount;
            glfwMakeContextCurrent(handle);
            glfwSetWindowUserPointer(handle, this);

            // Load GLAD once per process (after a context is current)
            if (!sGLADLoaded.load()) {
                if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
                    glfwDestroyWindow(handle);
                    handle = nullptr;
                    TerminateGLFWIfLast();
                    throw std::runtime_error("Failed to load GLAD");
                }
                sGLADLoaded = true;
            }

            // Initial viewport and resize callback
            glViewport(0, 0, props.width, props.height);
            glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* win, const int w, const int h) {
                if (Impl* self = static_cast<Impl*>(glfwGetWindowUserPointer(win))) {
                    self->props.width = w;
                    self->props.height = h;
                }
                glViewport(0, 0, w, h);
            });
        }

        ~Impl() {
            if (handle) {
                glfwDestroyWindow(handle);
                handle = nullptr;
                --sWindowCount;
            }
            TerminateGLFWIfLast();
        }

        static void InitializeGLFWOnce() {
            bool expected = false;
            if (sGLFWInitialized.compare_exchange_strong(expected, true)) {
                if (!glfwInit()) {
                    sGLFWInitialized = false;
                    throw std::runtime_error("Failed to initialize GLFW");
                }
            }
        }

        static void TerminateGLFWIfLast() {
            if (sGLFWInitialized.load() && sWindowCount.load() == 0) {
                glfwTerminate();
                sGLFWInitialized = false;
                sGLADLoaded = false; // GLAD function pointers are invalid without a context
            }
        }
    };

    std::atomic<int> Window::Impl::sWindowCount{0};
    std::atomic<bool> Window::Impl::sGLFWInitialized{false};
    std::atomic<bool> Window::Impl::sGLADLoaded{false};

    Window::Window() = default;

    Window::Window(const WindowProperties& props)
        : mImpl(std::make_unique<Impl>(props)) {}

    Window::~Window() = default;

    Window::Window(Window&&) noexcept = default;
    Window& Window::operator=(Window&&) noexcept = default;

    bool Window::ShouldClose() const {
        return mImpl ? glfwWindowShouldClose(mImpl->handle) != 0 : true;
    }

    void Window::SwapBuffers() const {
        if (mImpl && mImpl->handle) glfwSwapBuffers(mImpl->handle);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    int Window::Width() const { return mImpl ? mImpl->props.width : 0; }
    int Window::Height() const { return mImpl ? mImpl->props.height : 0; }
    const char* Window::Title() const { return mImpl ? mImpl->props.title : ""; }

    void* Window::GetNativeHandle() const { return mImpl ? static_cast<void*>(mImpl->handle) : nullptr; }

}  // GLCore