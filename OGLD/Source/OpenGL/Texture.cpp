//
// Created by dezlo on 20.12.2021.
//

#include <iostream>

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "OpenGL/gl_core_4_5.hpp"

ogld::Texture::Texture()
{
    stbi_set_flip_vertically_on_load(1);
}

void ogld::Texture::Load(const std::string& path)
{
    GenerateSampler();

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, width, height, 0, gl::RGB, gl::UNSIGNED_BYTE, data);
        gl::GenerateMipmap(gl::TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void ogld::Texture::Bind()
{
    gl::BindTexture(gl::TEXTURE_2D, mTextureID);
}

void ogld::Texture::UnBind()
{
    gl::BindTexture(gl::TEXTURE_2D, 0);
}

bool ogld::Texture::GenerateSampler()
{
    gl::GenTextures(1, &mTextureID);
    Bind();

    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);

    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

    return true;
}
