//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "TriangleApp.hpp"

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
    mShader.LoadFromFile("Shaders/shader.glsl");

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

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
    mShader.SetUniform("uColor", glm::vec3(1.0f, 0.5f, 1.0f));
    mVAO.Bind();
    gl::DrawArrays(gl::TRIANGLES, 0, 3);
#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}