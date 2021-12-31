//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_SHADER_HPP
#define OGLD_SHADER_HPP

#include <unordered_map>
#include "OpenGL/gl_core_4_5.hpp"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

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

        inline void SetUniform(const char* uname, float uvalue) {
            gl::Uniform1f(GetUniformLocation(uname), uvalue);
        }

        inline void SetUniform(const char* uname, const glm::vec3& uvalue) {
            gl::Uniform3fv(GetUniformLocation(uname), 1, &uvalue[0]);
        }

        inline void SetUniform(const char* uname, const glm::mat4& uvalue) {
            gl::UniformMatrix4fv(GetUniformLocation(uname), 1, gl::FALSE_, &uvalue[0][0]);
        }
    private:
        mutable std::unordered_map<const char*, GLint> mUniformLocationCache;
        uint32_t mID{};

        GLint GetUniformLocation(const char* name) const;
    };
}

#endif //OGLD_SHADER_HPP
