//
// Created by dezlow on 24.11.2021.
//

#include <stdexcept>
#include <iostream>
#include "Application.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    gl::Viewport(0, 0, width, height);
}

bool ogld::Application::MainLoop()
{
    AppInit();

    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

    double lastFrame = 0.0f;

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        double currentFrame = glfwGetTime();
        mAppDelta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        gl::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        if (!AppUpdate())
        {
            return false;
        }

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
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    mWindow = glfwCreateWindow(properties.width, properties.height, properties.title, nullptr, nullptr);

    if (mWindow == nullptr)
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        std::runtime_error("OGLD: Failed to create window!");
    }

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);

    gl::Enable(gl::DEPTH_TEST);

    MainLoop();
}
