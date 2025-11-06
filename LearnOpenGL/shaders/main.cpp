//
// Created by niek on 11/6/2025.
//

#include <iostream>
#include <GLcore/App.h>
#include <GLCore/Shader.h>
using namespace GLCore;

class ShaderApp final : public App {
public:
    using App::App;

protected:
    void OnInit() override {
        // Generate buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shader = new Shader("assets/vert.glsl", "assets/frag.glsl");
    }

    void OnShutdown() override {
        delete shader;
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void OnUpdate() override { }

    void OnRender() override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        shader->Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    float vertices[18] = {
        // positions        // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    unsigned int VAO, VBO;

    Shader* shader;
};

int main() {
    constexpr AppProperties props{ "Shaders", 800, 600 };
    const std::unique_ptr<ShaderApp> shaderApp = std::make_unique<ShaderApp>(props);
    shaderApp->Run();

    return 0;
}