//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_SHADER_H
#define OGLD_MAIN_SHADER_H

#include <unordered_map>
#include "OpenGL/gl_core_4_5.hpp"

#ifdef _MSC_VER
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#endif

namespace ogld
{
    class Shader
    {
    public:
        Shader() = default;

		~Shader()
    	{
            gl::DeleteShader(mID);
			mUniformLocationCache.clear();
        }

        inline void Use() const { gl::UseProgram(mID); }

        void LoadFromFile(const char* shaderPath);

        inline void SetUniformFloat(const char* uname, float uvalue)
        {
            gl::Uniform1f(GetUniformLocation(uname), uvalue);
        }

        inline void SetUniformVec3(const char* uname, const glm::vec3& uvalue)
        {
            gl::Uniform3fv(GetUniformLocation(uname), 1, &uvalue[0]);
        }

        inline void SetUniformMat4(const char* uname, const glm::mat4& uvalue)
        {
            gl::UniformMatrix4fv(GetUniformLocation(uname), 1, gl::FALSE_, &uvalue[0][0]);
        }
    private:
        mutable std::unordered_map<const char*, GLint> mUniformLocationCache;
        uint32_t mID{};

        GLint GetUniformLocation(const char* name) const;
    };
}

#endif //OGLD_MAIN_SHADER_H
