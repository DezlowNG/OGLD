//
// Created by dezlow on 24.11.2021.
//

#include <stdexcept>
#include <sstream>
#include <iostream>
#include "Application.h"

ogld::Application::ApplicationProperties ogld::Application::properties{};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    gl::Viewport(0, 0, width, height);
}

bool ogld::Application::MainLoop()
{
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

        mAppCamera.keyboard_callback(mWindow, mDeltaTime.delta);

        gl::ClearColor(properties.bg[0], properties.bg[1], properties.bg[2], properties.bg[3]);
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

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
        throw std::runtime_error("OGLD: Failed to call AppPreInit function! Please, check your code for errors!");

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

    gl::Enable(gl::DEPTH_TEST);

    if (!AppInit())
        throw std::runtime_error("OGLD: Failed to call AppInit function! Please, check your code for errors!");

    GLint GLVerMajor, GLVerMinor;
    gl::GetIntegerv(gl::MAJOR_VERSION, &GLVerMajor);
    gl::GetIntegerv(gl::MINOR_VERSION, &GLVerMinor);

    std::cout << "GPU: " << gl::GetString(gl::RENDERER) << '\n';
    std::cout << "OpenGL Version: " << GLVerMajor << "." << GLVerMinor << '\n';
    std::cout << "GLSL Version: " << gl::GetString(gl::SHADING_LANGUAGE_VERSION) << '\n';

    glfwSetWindowUserPointer(mWindow, this);

    glfwSetKeyCallback(mWindow, Application::KeyCallback);
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(mWindow, Application::MouseCallback);

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

void ogld::Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void ogld::Application::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* app = reinterpret_cast<ogld::Application*>(glfwGetWindowUserPointer(window));

    app->mAppCamera.mouse_callback(xpos, ypos);
}
