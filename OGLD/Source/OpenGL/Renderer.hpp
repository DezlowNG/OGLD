//
// Created by Dezlow on 06.03.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#ifndef OGLD_RENDERER_HPP
#define OGLD_RENDERER_HPP

#include "OpenGL/gl_core_4_5.hpp"

namespace ogld::Renderer
{
    enum DrawMode
    {
        TRIANGLES = gl::TRIANGLES
    };

    enum ElementsType
    {
        UNSIGNED_INT = gl::UNSIGNED_INT,
        UNSIGNED_BYTE = gl::UNSIGNED_BYTE
    };

    enum ClearType
    {
        COLOR_BUFFER = gl::COLOR_BUFFER_BIT,
        DEPTH_BUFFER = gl::DEPTH_BUFFER_BIT
    };

    void DrawArrays(DrawMode mode, GLsizei arraysCount);
    void DrawElements(DrawMode mode, GLsizei elementsCount, ElementsType type);
    void DrawArraysInstanced(DrawMode mode, GLsizei arraysCount, GLsizei instanceCount);
    void DrawElementsInstanced(DrawMode mode, GLsizei count, ElementsType type, GLsizei instanceCount);
    void Clear(ClearType type);
    void ClearColor(float r, float g, float b, float a);
}

#endif //OGLD_RENDERER_HPP
