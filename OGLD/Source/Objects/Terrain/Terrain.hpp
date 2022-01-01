//
// Created by Dezlow on 01.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_TERRAIN_HPP
#define OGLD_TERRAIN_HPP

#include "Objects/Object.hpp"
#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"

namespace ogld
{
    class Terrain : public Object
    {
    public:
        Terrain() = default;

        void Create(float x, float y, float z);
        void Draw() override;
    private:
        VertexArray mVAO{};
        VertexBuffer mVBO{};
    };
}


#endif //OGLD_TERRAIN_HPP
