//
// Created by Dezlow on 06.03.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "Renderer.hpp"

namespace ogld::Renderer
{
    void DrawArraysInstanced(DrawMode mode, int arraysCount, int instanceCount)
    {
        gl::DrawArraysInstanced(mode, 0, arraysCount, instanceCount);
    }

    void DrawArrays(DrawMode mode, GLsizei arraysCount)
    {
        gl::DrawArrays(mode, 0, arraysCount);
    }

    void DrawElementsInstanced(DrawMode mode, GLsizei count, ElementsType type, GLsizei instanceCount)
    {
        gl::DrawElementsInstanced(mode, count, type, nullptr, instanceCount);
    }

    void Clear(ClearType type)
    {
        gl::Clear(type);
    }

    void ClearColor(float r, float g, float b, float a)
    {
        gl::ClearColor(r, g, b, a);
    }

    void DrawElements(DrawMode mode, GLsizei elementsCount, ElementsType type)
    {
        gl::DrawElements(mode, elementsCount, type, nullptr);
    }
}