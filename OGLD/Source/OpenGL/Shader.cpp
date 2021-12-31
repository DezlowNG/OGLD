//
// Created by dezlow on 24.11.2021.
//

#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

#include "Shader.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

uint32_t CreateVertexShader(const char* shaderSrc);
uint32_t CreateFragmentShader(const char* shaderSrc);
uint32_t CreateProgram(const uint32_t& vertexShaderID, const uint32_t& fragmentShaderID);
void CheckCompileErrors(const uint32_t& shader, const char* type);

enum ShaderType
{
    VERTEX,
    FRAGMENT,
};

void ogld::Shader::LoadFromFile(const char* shaderPath)
{
    std::string vertexShaderSrc;
    std::string fragmentShaderSrc;

    std::ifstream shaderFile;
    
    try
    {
        shaderFile.open(shaderPath);

        std::stringstream ss[2];
        std::string line;
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
        std::cerr << ex.what() << std::endl;
    }

    unsigned int vertexShader = CreateVertexShader(vertexShaderSrc.c_str()),
            fragmentShader = CreateFragmentShader(fragmentShaderSrc.c_str());

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

uint32_t CreateProgram(const uint32_t& vertexShaderID, const uint32_t& fragmentShaderID)
{
    uint32_t programID = gl::CreateProgram();

    gl::AttachShader(programID, vertexShaderID);
    gl::AttachShader(programID, fragmentShaderID);
    gl::LinkProgram(programID);
    CheckCompileErrors(programID, "PROGRAM");

    return programID;
}

void CheckCompileErrors(const uint32_t& shader, const char* type)
{
    int succes;
    char infoLog[512];

    /*
     * DONT WRITE:
     * if (type == "PROGRAM")
     * because result will ALWAYS TRUE
     */
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