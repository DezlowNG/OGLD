//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_VERTEXARRAY_H
#define OGLD_VERTEXARRAY_H

#include "OpenGL/gl_core_4_5.hpp"

namespace ogld
{
    class VertexArray
    {
    public:
        VertexArray() = default;

        ~VertexArray() { gl::DeleteVertexArrays(1, &mID); }

        void Init() { gl::GenVertexArrays(1, &mID); }

        void Bind() const { gl::BindVertexArray(mID); }

        void UnBind() const { gl::BindVertexArray(0); }

    private:
        uint32_t mID;
    };
}


#endif //OGLD_VERTEXARRAY_H
