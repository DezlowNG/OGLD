//
// Created by Dezlow on 24.11.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include <stdexcept>
#include <sstream>
#include <iostream>
#include "Application.hpp"

#if OGLD_USE_IMGUI
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#endif

ogld::Application::AppProps ogld::Application::properties{};

bool ogld::Application::MainLoop()
{
    if (properties.framerate.show)
        mFPS.prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        gl::ClearColor(properties.bg[0], properties.bg[1], properties.bg[2], properties.bg[3]);
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        mDeltaTime.currentFrame = glfwGetTime();
        mDeltaTime.delta = mDeltaTime.currentFrame - mDeltaTime.lastFrame;
        mDeltaTime.lastFrame = mDeltaTime.currentFrame;

        if (properties.framerate.show)
        {
            mFPS.frames++;
            if (mDeltaTime.currentFrame - mFPS.prevTime >= 1.0)
                CalculateFPS();
        }

        mAppCamera.keyboard_callback(mWindow, mDeltaTime.delta);

        if (!AppUpdate()) return false;

#if OGLD_USE_IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImUpdate();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
        glfwSwapBuffers(mWindow);

        input.active = false;
    }

    return true;
}

ogld::Application::~Application()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void ogld::Application::Run()
{
    if (!AppPreInit())
        throw std::runtime_error("[OGLD]: Failed to call AppPreInit function! Please, check your code for errors!");

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OGLD_GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OGLD_GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (properties.msaa.enabled)
        glfwWindowHint(GLFW_SAMPLES, properties.msaa.level);

    if (properties.framerate.show) {
        mWindow = glfwCreateWindow(properties.width, properties.height, (std::string(properties.title) + std::string(" | FPS: 0")).c_str(), nullptr, nullptr);
    } else {
        mWindow = glfwCreateWindow(properties.width, properties.height, properties.title, nullptr, nullptr);
    }

    if (mWindow == nullptr)
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        throw std::runtime_error("[OGLD]: Failed to create window!");
    }

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(properties.vsync);

    gl::Enable(gl::DEPTH_TEST);
    if (properties.msaa.enabled) gl::Enable(gl::MULTISAMPLE);

    if (!AppInit())
        throw std::runtime_error("[OGLD]: Failed to call AppInit function! Please, check your code for errors!");
#ifdef OGLD_DEBUG
    GLint GLVerMajor, GLVerMinor;
    gl::GetIntegerv(gl::MAJOR_VERSION, &GLVerMajor);
    gl::GetIntegerv(gl::MINOR_VERSION, &GLVerMinor);

    std::cout << "GPU: " << gl::GetString(gl::RENDERER) << '\n';
    std::cout << "OpenGL Version: " << GLVerMajor << "." << GLVerMinor << '\n';
    std::cout << "GLSL Version: " << gl::GetString(gl::SHADING_LANGUAGE_VERSION) << '\n';
#endif

#if OGLD_USE_IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    std::string glVersion = "#version " + std::to_string(OGLD_GL_VERSION_MAJOR) + std::to_string(OGLD_GL_VERSION_MINOR) + "0";
    ImGui_ImplOpenGL3_Init(glVersion.c_str());
    ImInit();
    glVersion.clear();
#endif

    if (properties.camera.enabled)
    {
        glfwSetWindowUserPointer(mWindow, this);
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(mWindow, Application::MouseCallback);
    }
    glfwSetFramebufferSizeCallback(mWindow, Application::framebuffer_size_callback);
    glfwSetKeyCallback(mWindow, Application::KeyCallback);

    if (!MainLoop())
        throw std::runtime_error("[OGLD]: Failed to call AppUpdate function! Please, check your code for errors!");

    AppClosed();
#if OGLD_USE_IMGUI
    ImClosed();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif
}

void ogld::Application::CalculateFPS()
{
    std::ostringstream oss;
    oss << properties.title << " | FPS: " << mFPS.frames;

    glfwSetWindowTitle(mWindow, oss.str().c_str());

    mFPS.frames = 0;
    mFPS.prevTime = mDeltaTime.currentFrame;
}

void ogld::Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* app = reinterpret_cast<ogld::Application*>(glfwGetWindowUserPointer(window));
    app->AppInput(key, action);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, nullptr);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, Application::MouseCallback);
        }
    }
}

void ogld::Application::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* app = reinterpret_cast<ogld::Application*>(glfwGetWindowUserPointer(window));
    app->mAppCamera.mouse_callback(xpos, ypos);
}

void ogld::Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    auto* app = reinterpret_cast<ogld::Application*>(glfwGetWindowUserPointer(window));
    app->properties.width = width;
    app->properties.height = height;
    gl::Viewport(0, 0, width, height);
}
