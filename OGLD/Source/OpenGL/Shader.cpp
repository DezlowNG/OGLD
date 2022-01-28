//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

#include "Shader.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "OpenGL/gl_core_4_5.hpp"

uint32_t CreateVertexShader(const char* shaderSrc);
uint32_t CreateFragmentShader(const char* shaderSrc);
uint32_t CreateProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID);
void CheckCompileErrors(uint32_t shader, const char* type);

enum ShaderType
{
    VERTEX,
    FRAGMENT
};

void ogld::Shader::LoadFromFile(const char* shaderPath)
{
    std::string vertexShaderSrc{};
    std::string fragmentShaderSrc{};

    std::ifstream shaderFile{};
    
    try
    {
        shaderFile.open(shaderPath);

        std::stringstream ss[2];
        std::string line{};
        ShaderType type{};

        while (std::getline(shaderFile, line))
        {
            if (line.find("// TYPE=") != std::string::npos)
            {
                if (line.find("VERTEX") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("FRAGMENT") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[(int)type] << line << '\n';
            }
        }

        shaderFile.close();

        vertexShaderSrc = ss[(int)ShaderType::VERTEX].str();
        fragmentShaderSrc = ss[(int)ShaderType::FRAGMENT].str();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "[OGLD]: Failed to load shader file! Error: " << ex.what() << '\n';
    }

    uint32_t vertexShader = CreateVertexShader(vertexShaderSrc.c_str());
    uint32_t fragmentShader = CreateFragmentShader(fragmentShaderSrc.c_str());

    mID = CreateProgram(vertexShader, fragmentShader);

    gl::DeleteShader(vertexShader);
    gl::DeleteShader(fragmentShader);
}

GLint ogld::Shader::GetUniformLocation(const char* name) const
{
    if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
        return mUniformLocationCache[name];

    GLint location = gl::GetUniformLocation(mID, name);
    mUniformLocationCache[name] = location;
    return location;
}

void ogld::Shader::Use() const
{
    gl::UseProgram(mID);
}

void ogld::Shader::SetUniform(const char* uname, float uvalue)
{
    gl::Uniform1f(GetUniformLocation(uname), uvalue);
}

void ogld::Shader::SetUniform(const char* uname, int uvalue)
{
    gl::Uniform1i(GetUniformLocation(uname), uvalue);
}

void ogld::Shader::SetUniform(const char* uname, const glm::vec3& uvalue)
{
    gl::Uniform3fv(GetUniformLocation(uname), 1, &uvalue[0]);
}

void ogld::Shader::SetUniform(const char* uname, const glm::mat4& uvalue)
{
    gl::UniformMatrix4fv(GetUniformLocation(uname), 1, gl::FALSE_, &uvalue[0][0]);
}

ogld::Shader::~Shader()
{
    gl::DeleteShader(mID);
    mUniformLocationCache.clear();
}

uint32_t CreateVertexShader(const char* shaderSrc)
{
    uint32_t shaderID = gl::CreateShader(gl::VERTEX_SHADER);

    gl::ShaderSource(shaderID, 1, &shaderSrc, nullptr);
    gl::CompileShader(shaderID);
    CheckCompileErrors(shaderID, "VERTEX");

    return shaderID;
}

uint32_t CreateFragmentShader(const char* shaderSrc)
{
    uint32_t shaderID = gl::CreateShader(gl::FRAGMENT_SHADER);

    gl::ShaderSource(shaderID, 1, &shaderSrc, nullptr);
    gl::CompileShader(shaderID);
    CheckCompileErrors(shaderID, "FRAGMENT");

    return shaderID;
}

uint32_t CreateProgram(uint32_t vertexShaderID, uint32_t fragmentShaderID)
{
    uint32_t programID = gl::CreateProgram();

    gl::AttachShader(programID, vertexShaderID);
    gl::AttachShader(programID, fragmentShaderID);
    gl::LinkProgram(programID);
    CheckCompileErrors(programID, "PROGRAM");

    return programID;
}

void CheckCompileErrors(uint32_t shader, const char* type)
{
    int succes;
    char infoLog[512];

    if (std::strcmp(type, "PROGRAM") != 0)
    {
        gl::GetShaderiv(shader, gl::COMPILE_STATUS, &succes);
        if (!succes)
        {
            gl::GetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
    else
    {
        gl::GetProgramiv(shader, gl::LINK_STATUS, &succes);
        if (!succes)
        {
            gl::GetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
}