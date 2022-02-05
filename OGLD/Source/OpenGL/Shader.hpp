//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_SHADER_HPP
#define OGLD_SHADER_HPP

#include <unordered_map>

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace ogld
{
    class Shader
    {
    public:
        Shader() = default;
		~Shader();
        void Use() const;
        void LoadFromFile(const char* shaderPath);

        void BindUniformBlock(const char* name) const;

        void SetUniform(const char* uname, float uvalue);
        void SetUniform(const char* uname, int uvalue);
        void SetUniform(const char* uname, const glm::vec3& uvalue);
        void SetUniform(const char* uname, const glm::mat4& uvalue);
    private:
        mutable std::unordered_map<const char*, int> mUniformLocationCache;
        uint32_t mID{};

        int GetUniformLocation(const char* name) const;
    };
}

#endif //OGLD_SHADER_HPP
