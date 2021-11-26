//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_VERTEXBUFFER_H
#define OGLD_MAIN_VERTEXBUFFER_H

#include <cstdint>
#include "../OpenGL/gl_core_4_5.hpp"

class VertexBuffer
{
public:
    VertexBuffer() = default;
    void Create(const uint32_t size, const float* pVertices)
    {
        gl::GenBuffers(1, &mID);
        Bind();
        gl::BufferData(gl::ARRAY_BUFFER, size, pVertices, gl::STATIC_DRAW);
    }
    ~VertexBuffer() { gl::DeleteBuffers(1, &mID); }

    void Bind() const { gl::BindBuffer(gl::ARRAY_BUFFER, mID); }
    void UnBind() const { gl::BindBuffer(gl::ARRAY_BUFFER, 0); }

    template<class T>
    static void PushLayout(const uint32_t& id, const uint32_t& size, const uint32_t& stride, const uint32_t& pointer) {}
private:
    uint32_t mID;
};

template<>
void VertexBuffer::PushLayout<float>(const uint32_t& id, const uint32_t& size, const uint32_t& stride, const uint32_t& pointer)
{
    gl::EnableVertexAttribArray(id);
    gl::VertexAttribPointer(id, (int)size, gl::FLOAT, gl::FALSE_, stride * sizeof(float), (void*)pointer);
}

#endif //OGLD_MAIN_VERTEXBUFFER_H
