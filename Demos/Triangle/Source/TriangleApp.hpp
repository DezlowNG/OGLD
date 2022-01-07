//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_TRIANGLEAPP_HPP
#define OGLD_TRIANGLEAPP_HPP

//If u want debug project then uncomment next lines:
//#define OGLD_DEBUG
//#define OGLD_TRACK_MEMORY
#define OGLD_INCLUDE_CORE
#include "OGLD.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"

class DemoApp : public ogld::Application
{
protected:
    bool AppPreInit() override;
    bool AppInit() override;
    bool AppUpdate() override;
#ifdef OGLD_TRACK_MEMORY
    bool AppClosed() override
    {
        std::cout << "Total alloc: " << allocMemory << '\n';
        return true;
    }
#else
    bool AppClosed() override { return true; }
#endif

private:
    ogld::Shader mShader{};
    ogld::VertexArray mVAO{};
    ogld::VertexBuffer mVBO{};
};

std::shared_ptr<ogld::Application> ogld::CreateApplication()
{
    return std::make_shared<DemoApp>();
}

#endif //OGLD_TRIANGLEAPP_HPP
