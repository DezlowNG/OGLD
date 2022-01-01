//
// Created by Dezlow on 02.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "Cube.hpp"

void ogld::Cube::Create(float x, float y, float z)
{
    float vertices[] = {
            -x, -y, -z,  0.0f,  0.0f, -x, 0.0f, 0.0f,
            x,  y, -z,  0.0f,  0.0f, -x, y, z,
            x, -y, -z,  0.0f,  0.0f, -x, y, 0.0f,
            x,  y, -z,  0.0f,  0.0f, -x, y, z,
            -x, -y, -z,  0.0f,  0.0f, -x, 0.0f, 0.0f,
            -x,  y, -z,  0.0f,  0.0f, -x, 0.0f, z,

            -x, -y,  z,  0.0f,  0.0f,  x, 0.0f, 0.0f,
            x, -y,  z,  0.0f,  0.0f,  x, y, 0.0f,
            x,  y,  z,  0.0f,  0.0f,  x, y, z,
            x,  y,  z,  0.0f,  0.0f,  x, y, z,
            -x,  y,  z,  0.0f,  0.0f,  x, 0.0f, z,
            -x, -y,  z,  0.0f,  0.0f,  x, 0.0f, 0.0f,

            -x,  y,  z, -x,  0.0f,  0.0f, y, 0.0f,
            -x,  y, -z, -x,  0.0f,  0.0f, y, z,
            -x, -y, -z, -x,  0.0f,  0.0f, 0.0f, z,
            -x, -y, -z, -x,  0.0f,  0.0f, 0.0f, z,
            -x, -y,  z, -x,  0.0f,  0.0f, 0.0f, 0.0f,
            -x,  y,  z, -x,  0.0f,  0.0f, y, 0.0f,

            x,  y,  z,  x,  0.0f,  0.0f, y, 0.0f,
            x, -y, -z,  x,  0.0f,  0.0f, 0.0f, z,
            x,  y, -z,  x,  0.0f,  0.0f, y, z,
            x, -y, -z,  x,  0.0f,  0.0f, 0.0f, z,
            x,  y,  z,  x,  0.0f,  0.0f, y, 0.0f,
            x, -y,  z,  x,  0.0f,  0.0f, 0.0f, 0.0f,

            -x, -y, -z,  0.0f, -z,  0.0f, 0.0f, z,
            x, -y, -z,  0.0f, -z,  0.0f, y, z,
            x, -y,  z,  0.0f, -z,  0.0f, y, 0.0f,
            x, -y,  z,  0.0f, -z,  0.0f, y, 0.0f,
            -x, -y,  z,  0.0f, -z,  0.0f, 0.0f, 0.0f,
            -x, -y, -z,  0.0f, -z,  0.0f, 0.0f, z,

            -x,  y, -z,  0.0f,  z,  0.0f, 0.0f, z,
            x,  y , z,  0.0f,  z,  0.0f, y, 0.0f,
            x,  y, -z,  0.0f,  z,  0.0f, y, z,
            x,  y,  z,  0.0f,  z,  0.0f, y, 0.0f,
            -x,  y, -z,  0.0f,  z,  0.0f, 0.0f, z,
            -x,  y,  z,  0.0f,  z,  0.0f, 0.0f, 0.0f
    };
    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    VertexBuffer::PushLayout<float>(0,3,8,0);
    VertexBuffer::PushLayout<float>(1,3,8,3);
    VertexBuffer::PushLayout<float>(2,3,8,6);
    mVBO.UnBind();
    mVAO.UnBind();
}

void ogld::Cube::Draw()
{
    mVAO.Bind();
    gl::DrawArrays(gl::TRIANGLES, 0, 36);
}
