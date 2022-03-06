//
// Created by Dezlow on 03.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_MAINAPP_HPP
#define OGLD_MAINAPP_HPP

//If u want debug project then uncomment next lines:
//#define OGLD_DEBUG
//#define OGLD_TRACK_MEMORY
#define OGLD_INCLUDE_CORE
#include "OGLD.hpp"
#include <OpenGL/DepthMap.hpp>
#include <OpenGL/DepthFBO.hpp>
#include <OpenGL/Shader.hpp>
#include <OpenGL/UniformBuffer.hpp>
#include <Core/Entity.hpp>
#include "OpenGL/Model.hpp"
#include "OpenGL/SkyBox.hpp"

class CubeEntity : public ogld::Entity
{
public:
    void Init(const std::string& difPath, const std::string& specPath);
    void Draw() override;
};

class TerrainEntity : public ogld::Entity
{
public:
    void Init(const std::string& difPath);
    void Draw() override;
};

class DemoApp : public ogld::Application
{
protected:
    bool AppPreInit() override;
    bool AppInit() override;
    bool AppUpdate() override;
    void AppInput(int key, int action) override;

#ifdef OGLD_TRACK_MEMORY
    bool AppClosed() override
    {
        std::cout << "Total alloc: " << allocMemory << '\n';
        return true;
    }
#else
    bool AppClosed() override { return true; }
#endif
#if OGLD_USE_IMGUI
    void ImInit() override;
    void ImUpdate() override;
    void ImClosed() override;
#endif
private:
    struct Light
    {
        glm::vec3 position{-2.0f, 4.0f, -1.0f};
        float dt{};
        bool move{true};
    };

    struct Fog
    {
        float maxDist = 20.0f;
        float minDist = 2.0f;
        bool draw{true};
        bool set = !draw;
    };

    struct Shadows
    {
        int16_t size{1024};
        bool draw{false};
    };

    void renderScene(ogld::Shader& shader, bool cullface);
    ogld::Model mBackpack;
    ogld::SkyBox mSkyBox;
    CubeEntity mCube{};
    TerrainEntity mTerrain{};
    ogld::Shader mShader{};
    ogld::Shader mDepthShader{};
    ogld::Shader mSkyShader{};
    ogld::DepthFBO mDepthFBO{};
    ogld::DepthMap mDepthMap{};
    ogld::UniformBuffer mUBO{};
    Light mLight;
    Fog mFog;
    Shadows mShadows;
    bool DrawEditor{false};
};

std::shared_ptr<ogld::Application> ogld::CreateApplication()
{
    return std::make_shared<DemoApp>();
}

#endif //OGLD_MAINAPP_HPP
