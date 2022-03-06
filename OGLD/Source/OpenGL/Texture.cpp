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

void ogld::Texture::Load(const std::string& path, bool srgb, bool repeat)
{
    gl::GenTextures(1, &mID);

    uint8_t* data = stbi_load(path.c_str(), &mData.width, &mData.height, &mData.nrChannels, 0);
    if (data)
    {
        Bind();
        if (srgb)
        {
            gl::TexImage2D(gl::TEXTURE_2D, 0, mData.nrChannels == 4 ? gl::SRGB_ALPHA : gl::SRGB,
                           mData.width, mData.height, 0, mData.nrChannels == 4 ? gl::RGBA : gl::RGB, gl::UNSIGNED_BYTE, data);
        }
        else
        {
            gl::TexImage2D(gl::TEXTURE_2D, 0, mData.nrChannels == 4 ? gl::RGBA : gl::RGB,
                           mData.width, mData.height, 0, mData.nrChannels == 4 ? gl::RGBA : gl::RGB, gl::UNSIGNED_BYTE, data);
        }
        gl::GenerateMipmap(gl::TEXTURE_2D);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, repeat ? gl::REPEAT : gl::CLAMP_TO_BORDER);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, repeat ? gl::REPEAT : gl::CLAMP_TO_BORDER);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST_MIPMAP_NEAREST);
        gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST_MIPMAP_NEAREST);
        isLoaded = true;
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
