//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_APPLICATION_HPP
#define OGLD_APPLICATION_HPP

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "OpenGL/gl_core_4_5.hpp"

#include "Components/Camera/CameraComponent.hpp"

namespace ogld
{
    class Application
    {
        struct ApplicationProperties
        {
            const char* title = "OGLD";
            uint16_t width = 1280;
            uint16_t height = 720;
            float bg[4]{ 0.1f, 0.1f, 0.1f, 1.0f };
            bool vsync = true;
        };

        struct DTSturct
        {
            double lastFrame = 0.0;
            double currentFrame = 0.0;
            double delta = 0.0;
        };

        struct FPSStruct
        {
            double fps = 0.0;
            double prevTime = 0.0;
            uint32_t frames = 0;
        };
    public:
        Application() = default;
        ~Application();

        void Run();
    protected:
        virtual bool AppPreInit() = 0;
        virtual bool AppInit() = 0;
        virtual bool AppUpdate() = 0;
        virtual bool AppClosed() = 0;

        static ApplicationProperties properties;

        double GetDelta() const { return mDeltaTime.delta; }
        GLFWwindow* GetWindow() { return mWindow; }
        const Camera* GetCamera() { return &mAppCamera; }
    private:
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

        GLFWwindow* mWindow{};
        DTSturct mDeltaTime;
        FPSStruct mFPS;

        Camera mAppCamera;

        void CalculateFPS();

        bool MainLoop();
    };

    std::shared_ptr<Application> CreateApplication();
}


#endif //OGLD_APPLICATION_HPP
