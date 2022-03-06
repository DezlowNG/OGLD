//
// Created by Dezlow on 01.03.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_MODEL_HPP
#define OGLD_MODEL_HPP

#include "OpenGL/VertexBuffer.hpp"
#include "OpenGL/VertexArray.hpp"
#include "OpenGL/IndexBuffer.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

struct Vertex
{
    glm::vec3 pos{};
    glm::vec3 normal{};
    glm::vec2 texCoord{};

    bool operator==(const Vertex& other) const {
        return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

namespace ogld
{
    class Model
    {
    public:
        void Load(const std::string& path);
        void Draw() const;
    private:
        struct ModelTextures
        {
            ogld::Texture diffuse{};
            ogld::Texture specular{};
        };
        ogld::IndexBuffer mEBO{};
        ModelTextures mTextures;
        ogld::VertexArray mVAO{};
        ogld::VertexBuffer mVBO{};
    };
}

#endif //OGLD_MODEL_HPP
