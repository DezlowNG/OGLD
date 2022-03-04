//
// Created by Dezlow on 04.03.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_MAIN_SKYBOX_HPP
#define OGLD_MAIN_SKYBOX_HPP

#include <utility>

#include "CubeMap.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Components/Component.hpp"

namespace ogld
{
    class SkyBox : public Component
    {
    public:
        void Load(std::vector<const char*> faces)
        {
            mCubeMap.Load(std::move(faces));
            constexpr const float skyboxVertices[] = {
                   -1.0f,  1.0f, -1.0f,
                   -1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f,  1.0f, -1.0f,
                   -1.0f,  1.0f, -1.0f,

                   -1.0f, -1.0f,  1.0f,
                   -1.0f, -1.0f, -1.0f,
                   -1.0f,  1.0f, -1.0f,
                   -1.0f,  1.0f, -1.0f,
                   -1.0f,  1.0f,  1.0f,
                   -1.0f, -1.0f,  1.0f,

                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,

                   -1.0f, -1.0f,  1.0f,
                   -1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f, -1.0f,  1.0f,
                   -1.0f, -1.0f,  1.0f,

                   -1.0f,  1.0f, -1.0f,
                    1.0f,  1.0f, -1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                   -1.0f,  1.0f,  1.0f,
                   -1.0f,  1.0f, -1.0f,

                   -1.0f, -1.0f, -1.0f,
                   -1.0f, -1.0f,  1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                   -1.0f, -1.0f,  1.0f,
                    1.0f, -1.0f,  1.0f
            };

            mVAO.Init();
            mVAO.Bind();
            mVBO.Create(sizeof(skyboxVertices), skyboxVertices);
            ogld::VertexBuffer::PushLayout(0, 3, 3, 0);
        }

        void Draw()
        {
            mVAO.Bind();
            mCubeMap.Bind();
            gl::DrawArrays(gl::TRIANGLES, 0, 36);
        }
    private:
        VertexArray mVAO;
        VertexBuffer mVBO;
        CubeMap mCubeMap;
    };
}

#endif //OGLD_MAIN_SKYBOX_HPP
