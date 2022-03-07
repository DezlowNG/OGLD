//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "TriangleApp.hpp"
#include "OpenGL/Renderer.hpp"

bool DemoApp::AppPreInit()
{
    properties.vsync = 0;
    properties.title = "OGLD: Triangle Demo";
    properties.msaa.enabled = true;
    properties.msaa.level = 8;
    properties.camera.enabled = false;

    return true;
}

bool DemoApp::AppInit()
{
    constexpr const float vertices[] = {
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    mShader.LoadFromFile("Shaders/shader.glsl");

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    ogld::VertexBuffer::PushLayout(0,3,3,0);

    return true;
}

bool DemoApp::AppUpdate()
{
#ifdef OGLD_DEBUG
    ogld::ErrorHandler::GLClearError();
#endif
    mShader.Use();
    mShader.SetUniform("uColor", mTriangleColor);
    mVAO.Bind();
    ogld::Renderer::DrawArrays(ogld::Renderer::DrawMode::TRIANGLES, 3);
#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}
