//
// Created by Dezlow on 01.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include <OpenGL/gl_core_4_5.hpp>
#include "DepthMap.hpp"

void ogld::DepthMap::Create(uint32_t size)
{
    gl::GenTextures(1, &mID);
    gl::BindTexture(gl::TEXTURE_2D, mID);
    gl::TexImage2D(gl::TEXTURE_2D, 0, gl::DEPTH_COMPONENT, size, size, 0, gl::DEPTH_COMPONENT, gl::FLOAT, nullptr);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_BORDER);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    gl::TexParameterfv(gl::TEXTURE_2D, gl::TEXTURE_BORDER_COLOR, borderColor);
}

void ogld::DepthMap::Bind(size_t index) const
{
    gl::ActiveTexture(gl::TEXTURE0 + index);
    gl::BindTexture(gl::TEXTURE_2D, mID);
}

void ogld::DepthMap::UnBind() const
{
    gl::BindTexture(gl::TEXTURE_2D, 0);
}

void ogld::DepthMap::Bind() const
{
    gl::ActiveTexture(gl::TEXTURE0);
    gl::BindTexture(gl::TEXTURE_2D, mID);
}
