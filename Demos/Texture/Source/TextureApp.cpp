//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "TextureApp.hpp"

bool DemoApp::AppPreInit()
{
    properties.vsync = 0;
    properties.title = "OGLD: Texture Demo";
    properties.msaa.enabled = false;
    properties.msaa.level = 4;
    properties.camera.enabled = false;

    return true;
}

bool DemoApp::AppInit()
{
    mShader.LoadFromFile("Shaders/shader.glsl");

    constexpr const float vertices[] = {
           -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };

    constexpr const uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    ogld::VertexBuffer::PushLayout(0,3,5,0);
    ogld::VertexBuffer::PushLayout(1,2,5,3);
    mEBO.Init(indices, 5);

    mTexture.Load("Textures/texture.png", false);

    return true;
}

bool DemoApp::AppUpdate()
{
#ifdef OGLD_DEBUG
    ogld::ErrorHandler::GLClearError();
#endif
    mShader.Use();
    mTexture.Bind();
    mEBO.Bind();
    gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, nullptr);
#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}
