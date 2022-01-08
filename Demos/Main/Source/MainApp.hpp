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
#include <Core/Entity.hpp>

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
    void renderScene(ogld::Shader& shader);
    ogld::Shader mShader{};
    ogld::Shader mDepthShader{};
    ogld::DepthFBO mDepthFBO{};
    ogld::DepthMap mDepthMap{};
    CubeEntity mCube{};
    TerrainEntity mTerrain{};

    glm::vec3 mLightPos{-2.0f, 4.0f, -1.0f};
};

std::shared_ptr<ogld::Application> ogld::CreateApplication()
{
    return std::make_shared<DemoApp>();
}

#endif //OGLD_MAINAPP_HPP