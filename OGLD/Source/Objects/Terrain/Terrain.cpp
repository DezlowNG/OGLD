//
// Created by Dezlow on 02.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "Terrain.hpp"

void ogld::Terrain::Create(float x, float y, float z)
{
    float vertices[] = {
            x, -y,  z,  0.0f, y, 0.0f,  x, 0.0f,
           -x, -y,  z,  0.0f, y, 0.0f,  0.0f, 0.0f,
           -x, -y, -z,  0.0f, y, 0.0f,  0.0f, z,

            x, -y,  z,  0.0f, y, 0.0f,  x, 0.0f,
           -x, -y, -z,  0.0f, y, 0.0f,  0.0f, z,
            x, -y, -z,  0.0f, y, 0.0f,  x, z
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    VertexBuffer::PushLayoutFloat(0, 3, 8, 0);
    VertexBuffer::PushLayoutFloat(1, 3, 8, 3);
    VertexBuffer::PushLayoutFloat(2, 2, 8, 6);
    mVBO.UnBind();
    mVAO.UnBind();
}

void ogld::Terrain::Draw()
{
    mVAO.Bind();
    gl::DrawArrays(gl::TRIANGLES, 0, 6);
}


