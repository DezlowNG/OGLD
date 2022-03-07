//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "MainApp.hpp"
#include "OpenGL/Renderer.hpp"
#if OGLD_USE_IMGUI
#include "ImGui/imgui.h"
#endif

bool DemoApp::AppPreInit()
{
    properties.vsync = 0;
    properties.title = "OGLD: Main Demo";
    properties.msaa.enabled = false;
    properties.msaa.level = 4;
    properties.camera.enabled = true;
    properties.framerate.show = false;
    mShadows.size = 1024;

    return true;
}

bool DemoApp::AppInit()
{
    gl::CullFace(gl::BACK);
    gl::FrontFace(gl::CCW);

    mShader.LoadFromFile("Shaders/shader.glsl");
    mDepthShader.LoadFromFile("Shaders/shadow_mapping.glsl");

    mCube.Init("Textures/box/wood_diffuse.png", "Textures/box/wood_specular.png");
    mTerrain.Init("Textures/terrain/diffuse.jpg");

    mDepthMap.Create(mShadows.size);
    mDepthFBO.Create(mDepthMap.GetID());

    mShader.Use();
    mShader.SetUniform("uShadowsMap", 0);
    mShader.SetUniform("uMaterial.diffuse", 1);
    mShader.SetUniform("uMaterial.specular", 2);

    mUBO.Init(3 * sizeof(glm::mat4));
    mUBO.PushBufferRange(0, 0, 3 * sizeof(glm::mat4));
    mShader.BindUniformBlock("Matrices");

    mBackpack.Load("Models/backpack/backpack.obj");

    std::vector<const char*> faces
    {
        "Textures/skybox/right.jpg",
        "Textures/skybox/left.jpg",
        "Textures/skybox/top.jpg",
        "Textures/skybox/bottom.jpg",
        "Textures/skybox/front.jpg",
        "Textures/skybox/back.jpg"
    };

    mSkyBox.Load(faces);
    mSkyShader.LoadFromFile("Shaders/skybox.glsl");

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
                                            0.1f, mFog.draw ? mFog.maxDist : 100.0f);

    if (mLight.move)
    {
        mLight.dt += GetDelta();
        mLight.position.x = sin(mLight.dt) * 3.0f;
        mLight.position.z = cos(mLight.dt) * 2.0f;
        mLight.position.y = 5.0 + cos(mLight.dt) * 1.0f;
    }

    glm::mat4 lightProjection{}, lightView{};
    glm::mat4 lightSpaceMatrix{};

    if (mShadows.draw)
    {
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 10.0f);
        lightView = glm::lookAt(mLight.position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
    }

    mShader.Use();
    mShader.SetUniform("uViewPos", GetCamera()->GetPosition());
    mShader.SetUniform("uLight.position", mLight.position);
    mShader.SetUniform("uShadowsDraw", mShadows.draw);
    mShader.SetUniform("uFog.draw", mFog.draw);
    mShader.SetUniform("uFog.minDist", mFog.minDist);
    mShader.SetUniform("uFog.maxDist", mFog.maxDist);

    mUBO.Bind();
    mUBO.PushData(0, sizeof(glm::mat4), projection);
    mUBO.PushData(sizeof(glm::mat4), sizeof(glm::mat4), view);
    if (mShadows.draw)
    {
        mUBO.PushData(2 * sizeof(glm::mat4), sizeof(glm::mat4), lightSpaceMatrix);
        mDepthShader.Use();
        mDepthShader.SetUniform("lightSpaceMatrix", lightSpaceMatrix);
        gl::Viewport(0, 0, mShadows.size, mShadows.size);
        mDepthFBO.Bind();
        gl::Clear(gl::DEPTH_BUFFER_BIT);
        renderScene(mDepthShader, false);
        mDepthFBO.UnBind();
        gl::Viewport(0, 0, properties.width, properties.height);
    }

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

    if (mShadows.draw)
    {
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        mDepthMap.Bind();
    }

    if (!mFog.draw)
    {
        gl::DepthFunc(gl::LEQUAL);

        mSkyShader.Use();
        mSkyShader.SetUniform("projection", projection);
        mSkyShader.SetUniform("view", glm::mat4(glm::mat3(view)));
        mSkyBox.Draw();

        gl::DepthFunc(gl::LESS);
    }
    renderScene(mShader, true);

#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}

void DemoApp::renderScene(ogld::Shader& shader, bool cullface)
{
    shader.Use();
    glm::mat4 model{1.0f};
    shader.SetUniform("model", mTerrain.SetUpModel(model));
    mTerrain.Draw();

    if (cullface) gl::Enable(gl::CULL_FACE);

    model = glm::scale(model, glm::vec3(0.45f));
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetUniform("model", model);
    mBackpack.Draw();

    mCube.SetScale(glm::vec3(0.5f));
    mCube.SetPosition(glm::vec3(1.0f, 0.25f, 2.0f));
    shader.SetUniform("model", mCube.SetUpModel(model));
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

    ImGui::SetWindowSize(ImVec2(350, 150));
    ImGui::SetWindowPos(ImVec2(0, 0));

    ImGui::Text("FPS: %.ffps", ImGui::GetIO().Framerate);
    ImGui::Text("Frame time: %.2fms", GetDelta() * 1000.0f);

    ImGui::Text("Press T to enable/disable fog; Enabled: %i", mFog.draw);
    ImGui::Text("Press Y to enable/disable shadows; Enabled: %i", mShadows.draw);
    ImGui::Text("Press H to disable moving light; Enabled: %i", mLight.move);
    ImGui::Text("Press R to reload shaders;");

    ImGui::End();

    if (DrawEditor)
    {
        ImGui::Begin("Editor");
        if (ImGui::CollapsingHeader("Fog"))
        {
            ImGui::DragFloat("Minimum distance", &mFog.minDist, 0.05f, -5.0f, 100.0f);
            ImGui::DragFloat("Maximum distance", &mFog.maxDist, 0.05f, -100.0f, 1000.0f);
        }
        ImGui::End();
    }
}
void DemoApp::ImInit() {}
void DemoApp::ImClosed() {}
#endif

void DemoApp::AppInput(int key, int action)
{
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        mFog.set = false; mFog.draw = !mFog.draw;
    }

    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        mShadows.draw = !mShadows.draw;

    if (key == GLFW_KEY_H && action == GLFW_PRESS)
        mLight.move = !mLight.move;

    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        DrawEditor = !DrawEditor;

    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        mShader.Destroy();
        mShader.LoadFromFile("Shaders/shader.glsl");

        mShader.Use();
        mShader.SetUniform("uShadowsMap", 0);
        mShader.SetUniform("uMaterial.diffuse", 1);
        mShader.SetUniform("uMaterial.specular", 2);

        mUBO.Bind();
        mShader.BindUniformBlock("Matrices");
        mUBO.UnBind();
    }

    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        if (isMouseInputEnabled())
            DisableMouseInput();
        else {
            DrawEditor = false;
            EnableMouseInput();
        }
    }
}

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
    ogld::Renderer::DrawArrays(ogld::Renderer::TRIANGLES, 36);
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
    ogld::Renderer::DrawArrays(ogld::Renderer::TRIANGLES, 6);
    mTextures.diffuse.UnBind();
}