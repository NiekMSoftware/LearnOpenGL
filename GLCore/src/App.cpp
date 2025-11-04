//
// Created by niek on 11/3/2025.
//

#include "GLCore/App.h"
#include "GLCore/Window.h"

#include <GLFW/glfw3.h>

namespace GLCore {

    struct App::Impl {
        AppProperties props{};
        Window window;

        explicit Impl(const AppProperties& p)
            : props(p), window(WindowProperties{p.title, p.width, p.height}) {}

        static void ProcessInput(GLFWwindow* win) {
            if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(win, GLFW_TRUE);
        }
    };

    App::App() = default;

    App::App(const AppProperties properties)
        : mImpl(std::make_unique<Impl>(properties)) {}

    App::~App() = default;

    App::App(App&&) noexcept = default;
    App& App::operator=(App&&) noexcept = default;

    void App::Run() {
        if (!mImpl) return;
        auto* native = static_cast<GLFWwindow*>(mImpl->window.GetNativeHandle());

        OnInit();
        while (!mImpl->window.ShouldClose()) {
            Impl::ProcessInput(native);
            OnUpdate();

            // Rendering events
            OnRender();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            mImpl->window.SwapBuffers();
            Window::PollEvents();
        }
        OnShutdown();
    }

    const char* App::GetAppName() const { return mImpl ? mImpl->props.title : ""; }
    int App::GetAppWidth() const { return mImpl ? mImpl->props.width : 0; }
    int App::GetAppHeight() const { return mImpl ? mImpl->props.height : 0; }

}  // GLCore