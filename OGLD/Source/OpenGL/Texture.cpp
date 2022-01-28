//
// Created by Dezlow on 20.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "Texture.hpp"
#include "OpenGL/gl_core_4_5.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <iostream>

ogld::Texture::Texture()
{
    stbi_set_flip_vertically_on_load(1);
}

void ogld::Texture::Load(const std::string& path)
{
    gl::GenTextures(1, &mID);

    int width, height, nrChannels;
    uint8_t* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        Bind();
        gl::TexImage2D(gl::TEXTURE_2D, 0, nrChannels == 4 ? gl::SRGB_ALPHA : gl::SRGB,
                       width, height, 0, nrChannels == 4 ? gl::RGBA : gl::RGB, gl::UNSIGNED_BYTE, data);
        gl::GenerateMipmap(gl::TEXTURE_2D);

        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);

        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
    }
    else
    {
        std::cerr << "[OGLD]: Failed to load texture at " << path << " path!\n";
    }
    stbi_image_free(data);
}

void ogld::Texture::Bind() const
{
    gl::ActiveTexture(gl::TEXTURE0);
    gl::BindTexture(gl::TEXTURE_2D, mID);
}

void ogld::Texture::UnBind() const
{
    gl::BindTexture(gl::TEXTURE_2D, 0);
}

void ogld::Texture::Bind(size_t index) const
{
    gl::ActiveTexture(gl::TEXTURE0 + index);
    gl::BindTexture(gl::TEXTURE_2D, mID);
}

ogld::Texture::~Texture()
{
    gl::DeleteTextures(1, &mID);
}
