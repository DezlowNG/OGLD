//
// Created by Dezlow on 01.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_CUBE_HPP
#define OGLD_CUBE_HPP

#include "Objects/Object.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "OpenGL/VertexArray.hpp"

namespace ogld
{
    class Cube : public Object
    {
    public:
        void Create(float x, float y, float z);
        void Draw() override;
    private:
        VertexArray mVAO{};
        VertexBuffer mVBO{};
    };
}

#endif //OGLD_CUBE_HPP
