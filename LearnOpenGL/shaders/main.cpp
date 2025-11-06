//
// Created by niek on 11/6/2025.
//

#include <iostream>
#include <math.h>
#include <GLcore/App.h>
#include <GLFW/glfw3.h>
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

        int success;
        char infoLog[512];

        // Create shaders
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void OnShutdown() override {
        glDeleteProgram(shaderProgram);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void OnUpdate() override { }

    void OnRender() override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        glUseProgram(shaderProgram);

        // update uniform color
        const float timeValue = glfwGetTime();
        const float greenValue = sin(timeValue) / 2.0f + 0.5f;
        const int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
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

    unsigned int shaderProgram;
    unsigned int vertexShader, fragmentShader;

    const char* vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 ourColor;

    void main() {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
    })";
    const char* fragmentShaderSource = R"(#version 330 core
    out vec4 FragColor;
    in vec3 ourColor;
    void main() {
        FragColor = vec4(ourColor, 1.0);
    })";
};

int main() {
    constexpr AppProperties props{ "Shaders", 800, 600 };
    const std::unique_ptr<ShaderApp> shaderApp = std::make_unique<ShaderApp>(props);
    shaderApp->Run();

    return 0;
}