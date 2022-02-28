//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "MainApp.hpp"
#if OGLD_USE_IMGUI
#include "ImGui/imgui.h"
#endif

bool DemoApp::AppPreInit()
{
    properties.vsync = 0;
    properties.title = "OGLD: Main Demo";
    properties.msaa.enabled = true;
    properties.msaa.level = 2;
    properties.camera.enabled = true;
    properties.framerate.show = false;

    return true;
}

bool DemoApp::AppInit()
{
    gl::CullFace(gl::BACK);
    gl::FrontFace(gl::CCW);

    mShader.LoadFromFile("Shaders/shader.glsl");
    mDepthShader.LoadFromFile("Shaders/shadow_mapping.glsl");

    mCube.Init("Textures/box_wood_diffuse.png", "Textures/box_wood_specular.png");
    mTerrain.Init("Textures/terrain_diffuse.jpg");

    mDepthMap.Create(1024);
    mDepthFBO.Create(mDepthMap.GetID());

    mShader.Use();
    mShader.SetUniform("shadowMap", 0);
    mShader.SetUniform("material.diffuse", 1);
    mShader.SetUniform("material.specular", 2);

    mUBO.Init(3 * sizeof(glm::mat4));
    mUBO.PushBufferRange(0, 0, 3 * sizeof(glm::mat4));
    mShader.BindUniformBlock("Matrices");

    return true;
}

bool DemoApp::AppUpdate()
{
#ifdef OGLD_DEBUG
    ogld::ErrorHandler::GLClearError();
#endif
    glm::mat4 view = GetCamera()->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(90.0f),
                                            (float)properties.width / (float)properties.height,
                                            0.1f, 100.0f);

    mLightPos.x = sin(glfwGetTime()) * 3.0f;
    mLightPos.z = cos(glfwGetTime()) * 2.0f;
    mLightPos.y = 5.0 + cos(glfwGetTime()) * 1.0f;

    glm::mat4 lightProjection{}, lightView{};
    glm::mat4 lightSpaceMatrix{};

    if (DrawShadows)
    {
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 10.0f);
        lightView = glm::lookAt(mLightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
    }

    mShader.Use();
    mShader.SetUniform("viewPos", GetCamera()->GetPosition());
    mShader.SetUniform("light.position", mLightPos);
    mShader.SetUniform("uDrawShadows", DrawShadows);
    mShader.SetUniform("uDrawFog", mFog.draw);

    mUBO.Bind();
    mUBO.PushData(0, sizeof(glm::mat4), projection);
    mUBO.PushData(sizeof(glm::mat4), sizeof(glm::mat4), view);
    if (DrawShadows)
    {
        mUBO.PushData(2 * sizeof(glm::mat4), sizeof(glm::mat4), lightSpaceMatrix);
        mDepthShader.Use();
        mDepthShader.SetUniform("lightSpaceMatrix", lightSpaceMatrix);
        gl::Viewport(0, 0, 1024, 1024);
        mDepthFBO.Bind();
        gl::Clear(gl::DEPTH_BUFFER_BIT);
        renderScene(mDepthShader, false);
        mDepthFBO.UnBind();
        gl::Viewport(0, 0, properties.width, properties.height);
    }

    mShader.Use();

    if (mFog.draw && !mFog.set)
    {
        properties.bg = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
        mFog.set = true;
    }
    else if (!mFog.draw && !mFog.set)
    {
        properties.bg = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        mFog.set = true;
    }

    if (DrawShadows)
    {
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        mDepthMap.Bind();
    }

    renderScene(mShader, true);

#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}

void DemoApp::renderScene(ogld::Shader& shader, bool cullface)
{
    glm::mat4 model{1.0f};
    shader.SetUniform("model", mTerrain.SetUpModel(model));
    mTerrain.Draw();

    if (cullface) gl::Enable(gl::CULL_FACE);
    mCube.SetPosition(glm::vec3(0.0f, 1.5f, 0.0f));
    mCube.SetScale(glm::vec3(0.5f));
    shader.SetUniform("model", mCube.SetUpModel(model));
    mCube.Draw();

    mCube.SetPosition(glm::vec3(2.0f, 0.0f, 1.0f));
    mCube.SetScale(glm::vec3(0.5f));
    shader.SetUniform("model", mCube.SetUpModel(model));
    mCube.Draw();

    mCube.SetPosition(glm::vec3(-1.0f, 0.0f, 2.0f));
    mCube.SetScale(glm::vec3(0.25f));
    mCube.SetRotation(glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    shader.SetUniform("model", mCube.SetUpModel(model, true));
    mCube.Draw();
    if (cullface) gl::Disable(gl::CULL_FACE);
}

#if OGLD_USE_IMGUI
void DemoApp::ImUpdate()
{
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar
    );

    ImGui::SetWindowSize(ImVec2(350, 50));
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::Text("FPS: %.ffps", ImGui::GetIO().Framerate);
    ImGui::Text("Delta: %.2fms", GetDelta() * 1000.0f);
    ImGui::End();
}
void DemoApp::ImInit() {}
void DemoApp::ImClosed() {}

void DemoApp::AppInput(int key, int action)
{
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        mFog.set = false;
        mFog.draw = !mFog.draw;
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        DrawShadows = !DrawShadows;
}

#endif

void CubeEntity::Init(const std::string& difPath, const std::string& specPath)
{
    constexpr const float vertices[] = {
           -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
           -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
           -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

           -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
            1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
           -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
           -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

           -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
           -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
           -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
           -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

           -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
           -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
           -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

           -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
            1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
           -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
           -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    ogld::VertexBuffer::PushLayout(0,3,8,0);
    ogld::VertexBuffer::PushLayout(1,3,8,3);
    ogld::VertexBuffer::PushLayout(2,3,8,6);
    mVBO.UnBind();
    mVAO.UnBind();

    mTextures.diffuse.Load(difPath);
    mTextures.specular.Load(specPath);
}

void CubeEntity::Draw()
{
    mVAO.Bind();
    mTextures.diffuse.Bind(1);
    mTextures.specular.Bind(2);
    gl::DrawArrays(gl::TRIANGLES, 0, 36);
    mTextures.diffuse.UnBind();
    mTextures.specular.UnBind();
}

void TerrainEntity::Init(const std::string& difPath)
{
    constexpr const float vertices[] = {
            25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
           -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
           -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

            25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
           -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
            25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
    };

    mVAO.Init();
    mVAO.Bind();
    mVBO.Create(sizeof(vertices), vertices);
    ogld::VertexBuffer::PushLayout(0, 3, 8, 0);
    ogld::VertexBuffer::PushLayout(1, 3, 8, 3);
    ogld::VertexBuffer::PushLayout(2, 2, 8, 6);
    mVBO.UnBind();
    mVAO.UnBind();

    mTextures.diffuse.Load(difPath);
}

void TerrainEntity::Draw()
{
    mTextures.diffuse.Bind(1);
    mVAO.Bind();
    gl::DrawArrays(gl::TRIANGLES, 0, 6);
    mTextures.diffuse.UnBind();
}
