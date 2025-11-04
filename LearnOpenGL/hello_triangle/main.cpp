//
// Created by niek on 11/4/2025.
//

#include <iostream>
#include <GLCore/App.h>
using namespace GLCore;

class TriangleApp final : public App {
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Create shaders
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Compile vertex shader
        int success;
        char infoLog[512];
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

        // Link program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void OnShutdown() override {
        glDeleteProgram(shaderProgram);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void OnUpdate() override {  }

    void OnRender() override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    unsigned int VBO;
    unsigned int VAO;

    // shaders
    unsigned int vertexShader, fragmentShader;
    unsigned int shaderProgram;

    float vertices[9] {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    const char* vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(vec3(aPos), 1.0);
    })";
    const char* fragmentShaderSource = R"(#version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    })";
};

class RectangleApp final : public App {
public:
    using App::App;

protected:
    void OnInit() override {
        // Generate buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Set input
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Create shaders
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Compile vertex shader
        int success;
        char infoLog[512];
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

        // Link program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void OnShutdown() override {
        glDeleteProgram(shaderProgram);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void OnUpdate() override {

    }

    void OnRender() override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

private:
    float vertices[12] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
   };
    unsigned int indices[9] = {
        0, 1, 3,
        1, 2, 3
    };

    // buffer
    unsigned int VBO, VAO, EBO;

    // shader
    unsigned int shaderProgram;
    unsigned int vertexShader, fragmentShader;

    const char* vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(vec3(aPos), 1.0);
    })";
    const char* fragmentShaderSource = R"(#version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    })";
};

class ExerciseApp final : public App {
public:
    using App::App;

void OnInit() override {
        // Generate buffers
        glGenVertexArrays(2, VAO);
        glGenBuffers(2, VBO);

        // first triangle
        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // second triangle
        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Create shaders
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        orangeShaderProgram = glCreateProgram();
        yellowShaderProgram = glCreateProgram();

        // init shaders
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, nullptr);
        glCompileShader(orangeFragmentShader);
        glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource2, nullptr);
        glCompileShader(yellowFragmentShader);

        glAttachShader(orangeShaderProgram, vertexShader);
        glAttachShader(orangeShaderProgram, orangeFragmentShader);
        glLinkProgram(orangeShaderProgram);

        glAttachShader(yellowShaderProgram, vertexShader);
        glAttachShader(yellowShaderProgram, yellowFragmentShader);
        glLinkProgram(yellowShaderProgram);

        // Compile shaders
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glGetShaderiv(orangeFragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(orangeFragmentShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(yellowFragmentShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Link program
        glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(orangeShaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(yellowShaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Cleanup
        glDeleteShader(orangeFragmentShader);
        glDeleteShader(yellowFragmentShader);
        glDeleteShader(vertexShader);
    }

    void OnShutdown() override {
        glDeleteProgram(orangeShaderProgram);
        glDeleteProgram(yellowShaderProgram);

        glDeleteBuffers(1, &VBO[0]);
        glDeleteVertexArrays(1, &VAO[0]);
        glDeleteBuffers(1, &VBO[1]);
        glDeleteVertexArrays(1, &VAO[1]);
    }

    void OnUpdate() override {  }

    void OnRender() override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        glUseProgram(orangeShaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    unsigned int VBO[2];
    unsigned int VAO[2];

    // shaders
    unsigned int vertexShader, orangeFragmentShader, yellowFragmentShader;
    unsigned int orangeShaderProgram, yellowShaderProgram;

    // vertices for triangle 1
    float firstTriangle[9] {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f
    };

    // vertices for triangle 2
    float secondTriangle[9] {
        0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f
    };

    const char* vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(vec3(aPos), 1.0);
    })";
    const char* orangeFragmentShaderSource = R"(#version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    })";
    const char* yellowFragmentShaderSource2 = R"(#version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    })";
};

int main() {
    // change value to toggle between exercises or regular showcase
#if 0
    // change value to toggle between apps
    #if 0
    constexpr AppProperties props{ "Hello Triangle", 800, 600 };
    const std::unique_ptr<TriangleApp> triangleApp = std::make_unique<TriangleApp>(props);
    triangleApp->Run();
    #else
    constexpr AppProperties props { "Hello Rectangle", 800, 600 };
    const std::unique_ptr<RectangleApp> rectangleApp = std::make_unique<RectangleApp>(props);
    rectangleApp->Run();
    #endif
#else

    constexpr AppProperties props { "Exercises", 800, 600 };
    const std::unique_ptr<ExerciseApp> exerciseApp = std::make_unique<ExerciseApp>(props);
    exerciseApp->Run();

#endif

    return 0;
}