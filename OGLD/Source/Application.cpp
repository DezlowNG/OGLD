//
// Created by dezlow on 24.11.2021.
//

#include <stdexcept>
#include <sstream>
#include <iostream>
#include "Application.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    gl::Viewport(0, 0, width, height);
}

bool ogld::Application::MainLoop()
{
    uint32_t clearFlags = gl::COLOR_BUFFER_BIT | (properties.renderer.depth ? gl::DEPTH_BUFFER_BIT : 0);

    mFPS.prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        mDeltaTime.currentFrame = glfwGetTime();
        mDeltaTime.delta = mDeltaTime.currentFrame - mDeltaTime.lastFrame;
        mDeltaTime.lastFrame = mDeltaTime.currentFrame;

        mFPS.frames++;
        if (mDeltaTime.currentFrame - mFPS.prevTime >= 1.0)
            CalculateFPS();

        gl::ClearColor(properties.bg[0], properties.bg[1], properties.bg[2], properties.bg[3]);
        gl::Clear(clearFlags);

        if (!AppUpdate()) return false;

        glfwSwapBuffers(mWindow);
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
        std::runtime_error("OGLD: Failed to call AppPreInit function! Please, check your code for errors!");

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    mWindow = glfwCreateWindow(properties.width, properties.height, std::string(properties.title + std::string(" | FPS: 0")).c_str(), nullptr, nullptr);

    if (mWindow == nullptr)
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        throw std::runtime_error("OGLD: Failed to create window!");
    }

    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

    if (properties.vsync)
        glfwSwapInterval(1);

    if (properties.renderer.depth)
        gl::Enable(gl::DEPTH_TEST);

    if (!AppInit())
        throw std::runtime_error("OGLD: Failed to call AppInit function! Please, check your code for errors!");

    GLint GLVerMajor, GLVerMinor;
    gl::GetIntegerv(gl::MAJOR_VERSION, &GLVerMajor);
    gl::GetIntegerv(gl::MINOR_VERSION, &GLVerMinor);

    std::cout << "GPU: " << gl::GetString(gl::RENDERER) << '\n';
    std::cout << "OpenGL Version: " << GLVerMajor << "." << GLVerMinor << '\n';
    std::cout << "GLSL Version: " << gl::GetString(gl::SHADING_LANGUAGE_VERSION) << '\n';

    if (!MainLoop())
        throw std::runtime_error("OGLD: Failed to call AppUpdate function! Please, check your code for errors!");
}

void ogld::Application::CalculateFPS()
{
    std::ostringstream oss;
    oss << properties.title << " | FPS: " << mFPS.frames;

    glfwSetWindowTitle(mWindow, oss.str().c_str());

    mFPS.frames = 0;
    mFPS.prevTime = mDeltaTime.currentFrame;
}