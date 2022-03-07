//
// Created by Dezlow on 04.03.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <unordered_map>
#include <vector>

#include <iostream>

#include "Renderer.hpp"

void ogld::Model::Load(const std::string& path)
{
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;
    std::string absoluteDir{};

    int pos = path.size();
    while (path[pos] != '/')
        pos--;

    pos++;

    for (uint32_t i = 0; i < pos; ++i)
        absoluteDir.push_back(path[i]);

    if (!reader.ParseFromFile(path, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    for (auto& material : reader.GetMaterials())
    {
        if (!material.diffuse_texname.empty())
            mTextures.diffuse.Load(absoluteDir + material.diffuse_texname);

        if (!material.specular_texname.empty())
            mTextures.specular.Load(absoluteDir + material.specular_texname);
    }

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes)
    {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            auto fv = size_t(shape.mesh.num_face_vertices[f]);

            for (size_t v = 0; v < fv; v++)
            {
                Vertex vertex{};
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                vertex.pos.x = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                vertex.pos.y = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                vertex.pos.z = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                vertex.normal.x = attrib.normals[3*size_t(idx.normal_index)+0];
                vertex.normal.y = attrib.normals[3*size_t(idx.normal_index)+1];
                vertex.normal.z = attrib.normals[3*size_t(idx.normal_index)+2];

                vertex.texCoord.x = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                vertex.texCoord.y = 1.0f - attrib.texcoords[2 * idx.texcoord_index + 1];

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }
            index_offset += fv;

            shape.mesh.material_ids[f];
        }
    }

    mVAO.Init();
    mVAO.Bind();
    mVBO.Bind();
    mVBO.Create(vertices.size() * sizeof(Vertex), vertices.data());

    mEBO.Init(indices.data(), indices.size() * sizeof(uint32_t));

    ogld::VertexBuffer::PushLayout(0, 3, 8, 0);
    ogld::VertexBuffer::PushLayout(1, 3, 8, 3);
    ogld::VertexBuffer::PushLayout(2, 2, 8, 6);
}

void ogld::Model::Draw() const
{
    mVAO.Bind();
    mEBO.Bind();
    mTextures.diffuse.Bind(1);
    mTextures.specular.Bind(2);
    Renderer::DrawElements(Renderer::TRIANGLES, mEBO.GetElementCount(), Renderer::UNSIGNED_INT);
    mTextures.diffuse.UnBind();
    mTextures.specular.UnBind();
}
