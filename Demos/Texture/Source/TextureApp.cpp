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
    mSprite.Load("Textures/sprite.png", false, false);
    mBackground.Load("Textures/background.png", false, false);

    constexpr const float vertices[] = {
            1920.0f,  1080.0f, 0.0f,
            1920.0f, -1080.0f, 0.0f,
           -1920.0f,  1080.0f, 0.0f
    };

    constexpr const uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    ogld::VertexBuffer::PushLayout(0,3,3,0);
    mEBO.Init(indices, 6);
    gl::Enable(gl::DEPTH_TEST);
    gl::DepthFunc(gl::ALWAYS);
    gl::Enable(gl::BLEND);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

    return true;
}

bool DemoApp::AppUpdate()
{
#ifdef OGLD_DEBUG
    ogld::ErrorHandler::GLClearError();
#endif
    glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    glm::mat4 view{1.0f};
    glm::mat4 model{1.0f};

    mShader.Use();
    mShader.SetUniform("model", model);
    mShader.SetUniform("projection", projection);
    mShader.SetUniform("view", view);
    mShader.SetUniform("uTextureWidth", mBackground.GetData().width);
    mShader.SetUniform("uTextureHeight", mBackground.GetData().height);
    mBackground.Bind();
    mEBO.Bind();
    gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, nullptr);

    mShader.Use();
    mShader.SetUniform("uTextureWidth", mSprite.GetData().width);
    mShader.SetUniform("uTextureHeight", mSprite.GetData().height);
    model = glm::translate(model, glm::vec3(500.0f, 0.0f, 0.0f));
    mShader.SetUniform("model", model);
    mSprite.Bind();
    mEBO.Bind();
    gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, nullptr);
#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}
