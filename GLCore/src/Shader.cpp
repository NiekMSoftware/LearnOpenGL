//
// Created by niek on 11/6/2025.
//

#include "GLCore/Shader.h"
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <gtc/type_ptr.hpp>

namespace GLCore {

    // Static helpers
    std::string Shader::ReadTextFile(const char* path) {
        const std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << path << std::endl;
            return {};
        }
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    unsigned int Shader::Compile(const unsigned int type, const char* src) {
        const unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return shader;
    }

    unsigned int Shader::LinkProgram(const unsigned int vertex, const unsigned int fragment) {
        const unsigned int program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        int success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        return program;
    }

    Shader::Shader(const char* vertexPath, const char* fragmentPath) {
        const std::string vertexCode = ReadTextFile(vertexPath);
        const std::string fragmentCode = ReadTextFile(fragmentPath);
        const char* vsrc = vertexCode.c_str();
        const char* fsrc = fragmentCode.c_str();

        const unsigned int vs = Compile(GL_VERTEX_SHADER, vsrc);
        const unsigned int fs = Compile(GL_FRAGMENT_SHADER, fsrc);
        mID = LinkProgram(vs, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader() {
        if (mID) {
            glDeleteProgram(mID);
            mID = 0;
        }
    }

    // Binding
    void Shader::Bind() const {
        glUseProgram(mID);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    // Scalar setters
    void Shader::SetBool(const std::string &name, const bool value) const {
        glUniform1i(glGetUniformLocation(mID, name.c_str()), static_cast<int>(value));
    }

    void Shader::SetInt(const std::string &name, const int value) const {
        glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string &name, const float value) const {
        glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
    }

    // Matrix setter (common case)
    void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const {
        glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

}
