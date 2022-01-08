//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_VERTEXBUFFER_HPP
#define OGLD_VERTEXBUFFER_HPP

#include <cstdint>
#include "OpenGL/gl_core_4_5.hpp"

namespace ogld
{
    class VertexBuffer
    {
    public:
        VertexBuffer() = default;
        ~VertexBuffer() { gl::DeleteBuffers(1, &mID); }

        void Create(uint32_t size, const float* pVertices)
        {
            gl::GenBuffers(1, &mID);
            Bind();
            gl::BufferData(gl::ARRAY_BUFFER, size, pVertices, gl::STATIC_DRAW);
        }

        void Bind() const { gl::BindBuffer(gl::ARRAY_BUFFER, mID); }
        void UnBind() const { gl::BindBuffer(gl::ARRAY_BUFFER, 0); }

        static void PushLayout(uint32_t id, uint32_t size, uint32_t stride, uint32_t pointer)
        {
            gl::EnableVertexAttribArray(id);
            gl::VertexAttribPointer(id, size, gl::FLOAT, gl::FALSE_, stride * sizeof(float), (void*)(pointer == 0 ? 0 : (pointer * sizeof(float))));
        }

    private:
        uint32_t mID;
    };
}

#endif //OGLD_VERTEXBUFFER_HPP
