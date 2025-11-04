//
// Created by niek on 11/3/2025.
//

#ifndef LEARNOPENGL_APP_H
#define LEARNOPENGL_APP_H

// Keep glad available to users of App API so they can call GL functions in overrides.
#include "glad/glad.h"
#include <memory>

namespace GLCore {

    struct AppProperties {
        const char* title;
        int width;
        int height;
    };

    /** @brief Abstract base application using RAII + Pimpl. */
    class App {
    public:
        App();
        explicit App(AppProperties properties);
        virtual ~App();

        // Non-copyable, movable
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        App(App&&) noexcept;
        App& operator=(App&&) noexcept;

        /** @brief Application runtime. */
        void Run();

        const char* GetAppName() const;
        int GetAppWidth() const;
        int GetAppHeight() const;

    protected:
        /** @brief Called at the start of the application */
        virtual void OnInit() = 0;

        /** @brief Called at the end of the application */
        virtual void OnShutdown() = 0;

        /** @brief Called every frame to update the state of the application. */
        virtual void OnUpdate() = 0;

        /** @brief Called every frame to render out the application's shaders. */
        virtual void OnRender() = 0;

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };

}  // GLCore

#endif //LEARNOPENGL_APP_H