//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_APPLICATION_H
#define OGLD_MAIN_APPLICATION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace ogld
{
class Application
{
private:
    struct ApplicationProperties
    {
        uint16_t width = 1280;
        uint16_t height = 720;
        const char* title = "OGLD";
    };
public:
    ApplicationProperties properties;
    Application();
    ~Application();
private:
    GLFWwindow* mWindow;

    bool MainLoop();
};
}


#endif //OGLD_MAIN_APPLICATION_H
