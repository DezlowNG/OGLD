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

#include <memory>

#include "Core/Config.hpp"

namespace ogld
{
    class Application
    {
        struct AppProps
        {
            struct CameraProps
            {
                bool enabled = false;
            };
            struct MSAAProps
            {
                bool enabled = true;
                uint8_t level = 8;
            };
            struct FPSProps
            {
                bool show = true;
            };
            const char* title = "OGLD";
            uint16_t width = 1280;
            uint16_t height = 720;
            uint8_t vsync = 1;
            MSAAProps msaa;
            CameraProps camera;
            FPSProps framerate;
        };

        struct DTSturct
        {
            double lastFrame = 0.0;
            double currentFrame = 0.0;
            float delta = 0.0;
        };

        struct FPSStruct
        {
            float fps = 0.0;
            double prevTime = 0.0;
            size_t frames = 0;
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
#if OGLD_USE_IMGUI
        virtual void ImInit() = 0;
        virtual void ImUpdate() = 0;
        virtual void ImClosed() = 0;
#endif
        [[nodiscard]] float GetDelta() const { return mDeltaTime.delta; }
        GLFWwindow* GetWindow() { return mWindow; }
        const Camera* GetCamera() { return &mAppCamera; }
    private:
        bool MainLoop();
        void CalculateFPS();
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        Camera mAppCamera{}; // 116 bytes
        DTSturct mDeltaTime{}; // 24 bytes
        FPSStruct mFPS{}; // 24 bytes
    protected:
        static AppProps properties; // 16 bytes
    private:
        GLFWwindow* mWindow{}; // 8 bytes
    };

    std::shared_ptr<Application> CreateApplication();
}


#endif //OGLD_APPLICATION_HPP
