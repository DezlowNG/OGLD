//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_SHADER_H
#define OGLD_MAIN_SHADER_H

#include <unordered_map>
#include "../OpenGL/gl_core_4_5.hpp"

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
private:
    mutable std::unordered_map<const char*, GLint> mUniformLocationCache;
    uint32_t mID;

    GLint GetUniformLocation(const char* name) const;
};


#endif //OGLD_MAIN_SHADER_H
