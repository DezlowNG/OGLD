//
// Created by dezlow on 24.11.2021.
//

#include <stdexcept>
#include <iostream>
#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

ogld::Application::Application()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        std::runtime_error("OGLD: Failed to init glad!");
    }

    MainLoop();
}

bool ogld::Application::MainLoop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        glClearColor(1.0f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mWindow);
    }

    return true;
}

ogld::Application::~Application()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}
