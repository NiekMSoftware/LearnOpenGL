//
// Created by niek on 11/6/2025.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <string>
#include <glm.hpp>

namespace GLCore {

    /**
     * A tiny OpenGL shader program wrapper
     * - Construct from vertex/fragment file paths.
     * - Bind/Unbind and set a few common uniforms.
     * - RAII: program deleted in destructor.
     */
    class Shader {
    public:
        // Construct and link a shader program from vertex/fragment file paths.
        explicit Shader(const char* vertexPath, const char* fragmentPath);

        ~Shader();

        // Non-copyable (owning handle)
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        // Binding
        void Bind() const;
        static void Unbind();

        // Program accessor
        unsigned int ID() const { return mID; }

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;

    private:
        // Helper: read a text-file to string
        static std::string ReadTextFile(const char* path);

        // Helper: compile & link
        static unsigned int Compile(unsigned int type, const char* src);
        static unsigned int LinkProgram(unsigned int vertex, unsigned int fragment);

    private:
        unsigned int mID = 0;
    };

}

#endif //LEARNOPENGL_SHADER_H