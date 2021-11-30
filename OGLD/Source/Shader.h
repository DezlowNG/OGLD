//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_SHADER_H
#define OGLD_MAIN_SHADER_H

#include <unordered_map>
#include "OpenGL/gl_core_4_5.hpp"

namespace ogld
{
    class Shader
    {
    public:
        Shader() = default;

        ~Shader() { gl::DeleteShader(mID); }

        inline void Use() const { gl::UseProgram(mID); }

        void LoadFromFile(const char* vertexPath, const char* fragmentPath);

        void LoadFromSource(const char* vertexSource, const char* fragmentSource);

        template<class T>
        void SetUniform(const char* uniformName, const T& value) {}
#ifdef _MSC_VER
        template<>
        void SetUniform<float>(const char* uniformName, const float& value) {
            gl::Uniform1f(GetUniformLocation(uniformName), value);
        }

        template<>
        void SetUniform<glm::vec3>(const char* uniformName, const glm::vec3& value) {
            gl::Uniform3fv(GetUniformLocation(uniformName), 1, &value[0]);
        }

        template<>
        void SetUniform<glm::mat4>(const char* uniformName, const glm::mat4& value) {
            gl::UniformMatrix4fv(GetUniformLocation(uniformName), 1, gl::FALSE_, &value[0][0]);
        }
#endif
    private:
        mutable std::unordered_map<const char*, GLint> mUniformLocationCache;
        uint32_t mID;

        GLint GetUniformLocation(const char* name) const;
    };
}

#endif //OGLD_MAIN_SHADER_H
