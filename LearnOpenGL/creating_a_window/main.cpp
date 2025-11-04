//
// Created by niek on 11/3/2025.
//

#include <GLCore/App.h>

class WindowApp final : public GLCore::App {
public:
    WindowApp() = default;

    explicit WindowApp(const GLCore::AppProperties &properties)
        : App(properties) { }

protected:
    void OnInit() override { }

    void OnShutdown() override { }

    void OnUpdate() override { }

    void OnRender() override {

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    }
};

int main() {
    constexpr GLCore::AppProperties props{ "Creating a Window", 800, 600 };
    const std::unique_ptr<WindowApp> windowApp = std::make_unique<WindowApp>(props);
    windowApp->Run();
    return 0;
}