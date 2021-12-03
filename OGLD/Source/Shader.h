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

using vec3cr = const glm::vec3&;
using mat4cr = const glm::mat4&;

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

        template<class T>
        inline void SetUniform(const char* uname, const T uvalue);
#ifdef _MSC_VER
		template<>
        inline void SetUniform<float>(const char* uname, float uvalue)
        {
            gl::Uniform1f(GetUniformLocation(uname), uvalue);
        }

        template<>
        inline void SetUniform(const char* uname, vec3cr uvalue)
        {
            gl::Uniform3fv(GetUniformLocation(uname), 1, &uvalue[0]);
        }

        template<>
        inline void SetUniform(const char* uname, mat4cr uvalue)
        {
            gl::UniformMatrix4fv(GetUniformLocation(uname), 1, gl::FALSE_, &uvalue[0][0]);
        }
#endif
    private:
        mutable std::unordered_map<const char*, GLint> mUniformLocationCache;
        uint32_t mID{};

        GLint GetUniformLocation(const char* name) const;
    };
}

#endif //OGLD_MAIN_SHADER_H
