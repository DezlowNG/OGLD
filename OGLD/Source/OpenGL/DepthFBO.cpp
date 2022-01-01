//
// Created by Dezlow on 01.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include <OpenGL/gl_core_4_5.hpp>
#include "DepthFBO.hpp"

void ogld::DepthFBO::Create(uint32_t depthID)
{
    gl::GenFramebuffers(1, &mID);

    gl::BindFramebuffer(gl::FRAMEBUFFER, mID);
    gl::FramebufferTexture2D(gl::FRAMEBUFFER, gl::DEPTH_ATTACHMENT, gl::TEXTURE_2D, depthID, 0);
    gl::DrawBuffer(gl::NONE);
    gl::ReadBuffer(gl::NONE);
    gl::BindFramebuffer(gl::FRAMEBUFFER, 0);
}

void ogld::DepthFBO::Bind() const
{
    gl::BindFramebuffer(gl::FRAMEBUFFER, mID);
}

void ogld::DepthFBO::UnBind() const
{
    gl::BindFramebuffer(gl::FRAMEBUFFER, 0);
}
