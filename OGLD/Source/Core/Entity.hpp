//
// Created by Dezlow on 13.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_ENTITY_HPP
#define OGLD_ENTITY_HPP

#include <Components/Component.hpp>
#include <OpenGL/VertexArray.hpp>
#include <OpenGL/VertexBuffer.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <OpenGL/Texture.hpp>

namespace ogld
{
    class Entity : public Component
    {
    private:
        struct TexturesStruct
        {
            Texture diffuse{};
            Texture specular{};
            Texture ambient{};
        };
    public:
        virtual void Draw() = 0;
    protected:
        VertexArray mVAO{};
        VertexBuffer mVBO{};
        TexturesStruct mTextures{};
    };
}

#endif //OGLD_ENTITY_HPP
