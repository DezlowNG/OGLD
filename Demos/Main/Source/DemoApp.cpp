//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#include "DemoApp.hpp"

void DemoApp::renderScene(ogld::Shader& shader)
{
    mTerrainTexture.Bind();
    mTerrain.SetModel(glm::mat4(1.0f));
    shader.SetUniform("model", mTerrain.GetModel());
    mTerrain.Draw();
    mTerrainTexture.UnBind();

    mCubeDMap.Bind();
    mCubeSMap.Bind(1);

    mCube.SetModel(glm::mat4(1.0f));
    mCube.Translate(glm::vec3(0.0f, 1.5f, 0.0f));
    mCube.Scale(glm::vec3(0.5f));
    shader.SetUniform("model", mCube.GetModel());
    mCube.Draw();

    mCube.SetModel(glm::mat4(1.0f));
    mCube.Translate(glm::vec3(2.0f, 0.0f, 1.0f));
    mCube.Scale(glm::vec3(0.5f));
    shader.SetUniform("model", mCube.GetModel());
    mCube.Draw();

    mCube.SetModel(glm::mat4(1.0f));
    mCube.Translate(glm::vec3(-1.0f, 0.0f, 2.0f));
    mCube.Scale(glm::vec3(0.25f));
    mCube.Rotate(glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    shader.SetUniform("model", mCube.GetModel());
    mCube.Draw();
    mCubeSMap.UnBind();
    mCubeDMap.UnBind();
}

bool DemoApp::AppPreInit()
{
    properties.vsync = true;
    properties.title = "OGLD: Main Demo";

    return true;
}

bool DemoApp::AppInit()
{
    gl::Enable(gl::MULTISAMPLE);
    mShader.LoadFromFile("Shaders/shader.glsl");
    mDepthShader.LoadFromFile("Shaders/shadow_mapping.glsl");
    mCubeDMap.Load("Textures/box_wood_diffuse.png");
    mCubeSMap.Load("Textures/box_wood_specular.png");
    mTerrainTexture.Load("Textures/terrain_diffuse.jpg");
    mTerrain.Create(5.0f, 0.5f, 5.0f);
    mCube.Create(1.0f, 1.0f, 1.0f);
    mDepthMap.Create(4096);
    mDepthFBO.Create(mDepthMap.GetID());

    mShader.Use();
    mShader.SetUniform("material.diffuse", 0);
    mShader.SetUniform("material.specular", 1);
    mShader.SetUniform("shadowMap", 2);

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

    lightPos.x = sin(glfwGetTime()) * 3.0f;
    lightPos.z = cos(glfwGetTime()) * 2.0f;
    lightPos.y = 5.0 + cos(glfwGetTime()) * 1.0f;

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    mDepthShader.Use();
    mDepthShader.SetUniform("lightSpaceMatrix", lightSpaceMatrix);

    gl::Viewport(0, 0, 4096, 4096);
    mDepthFBO.Bind();
    gl::Clear(gl::DEPTH_BUFFER_BIT);
    renderScene(mDepthShader);
    mDepthFBO.UnBind();

    gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
    gl::Viewport(0, 0, properties.width, properties.height);

    mShader.Use();
    mShader.SetUniform("projection", projection);
    mShader.SetUniform("view", view);
    mShader.SetUniform("viewPos", GetCamera()->GetPosition());
    mShader.SetUniform("light.position", lightPos);
    mShader.SetUniform("lightSpaceMatrix", lightSpaceMatrix);
    mDepthMap.Bind(2);
    renderScene(mShader);

#ifdef OGLD_DEBUG
    ASSERT(ogld::ErrorHandler::GLLogCall());
#endif
    return true;
}
