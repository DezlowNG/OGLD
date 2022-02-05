//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "3DCubeApp.hpp"

bool DemoApp::AppPreInit()
{
    properties.vsync = 0;
    properties.title = "OGLD: Main Demo";
    properties.msaa.enabled = true;
    properties.msaa.level = 2;
    properties.camera.enabled = true;

    return true;
}

bool DemoApp::AppInit()
{
    gl::Enable(gl::CULL_FACE);
    gl::CullFace(gl::BACK);
    gl::FrontFace(gl::CCW);

    mShader.LoadFromFile("Shaders/shader.glsl");
    mCube.Init();
    UBO.Init(2 * sizeof(glm::mat4));
    UBO.PushBufferRange(0, 0, 2 * sizeof(glm::mat4));
    mShader.BindUniformBlock("Matrices");
    return true;
}

bool DemoApp::AppUpdate()
{
#ifdef OGLD_DEBUG
    ogld::ErrorHandler::GLClearError();
#endif
    mShader.Use();
    UBO.Bind();
    UBO.PushData(0, sizeof(glm::mat4), glm::perspective(glm::radians(90.0f),
                                                        (float)properties.width / (float)properties.height,
                                                        0.1f, 100.0f));
    UBO.PushData(sizeof(glm::mat4), sizeof(glm::mat4), GetCamera()->GetViewMatrix());
    glm::mat4 model{1.0f};
    mShader.SetUniform("model", mCube.SetUpModel(model));
    mCube.Draw();

#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}

void CubeEntity::Init()
{
    constexpr const float vertices[] = {
           -1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,

            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,

           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,

           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f , 1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    ogld::VertexBuffer::PushLayout(0,3,3,0);
    mVBO.UnBind();
    mVAO.UnBind();
}

void CubeEntity::Draw()
{
    mVAO.Bind();
    gl::DrawArrays(gl::TRIANGLES, 0, 36);
}