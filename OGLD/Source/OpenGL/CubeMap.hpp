//
// Created by Dezlow on 04.03.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_CUBEMAP_HPP
#define OGLD_CUBEMAP_HPP

#include "OpenGL/gl_core_4_5.hpp"
#include <vector>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <iostream>

namespace ogld
{
    class CubeMap
    {
    public:
        void Load(std::vector<const char*> faces)
        {
            stbi_set_flip_vertically_on_load(0);

            gl::GenTextures(1, &mID);
            Bind();

            int width, height, nrChannels;
            uint8_t* data;
            for(GLuint i = 0; i < faces.size(); i++)
            {
                data = stbi_load(faces[i], &width, &height, &nrChannels, 0);
                if (data)
                {
                    gl::TexImage2D(
                            gl::TEXTURE_CUBE_MAP_POSITIVE_X + i,
                            0, gl::RGB, width, height, 0, gl::RGB, gl::UNSIGNED_BYTE, data
                    );
                } else {
                    std::cerr << std::string("Failed to load cubemap texture at ") + faces[i] + "path";
                }
                stbi_image_free(data);
            }
            gl::GenerateMipmap(gl::TEXTURE_CUBE_MAP);

            gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::NEAREST_MIPMAP_NEAREST);
            gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::NEAREST_MIPMAP_NEAREST);
            gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
            gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
            gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);

            stbi_set_flip_vertically_on_load(1);
        }

        void Bind() const { gl::BindTexture(gl::TEXTURE_CUBE_MAP, mID); }
        void Bind(uint8_t index) const { gl::ActiveTexture(gl::TEXTURE0 + index); gl::BindTexture(gl::TEXTURE_CUBE_MAP, mID); }
        void UnBind() const { gl::BindTexture(gl::TEXTURE_CUBE_MAP, 0); }
    private:
        uint32_t mID{};
    };
}

#endif //OGLD_CUBEMAP_HPP
