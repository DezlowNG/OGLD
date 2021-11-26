//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_APPLICATION_H
#define OGLD_MAIN_APPLICATION_H

#include "../OpenGL/gl_core_4_5.hpp"
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
protected:
    virtual bool AppInit() = 0;
    virtual bool AppUpdate() = 0;

    double GetDelta()
    {
        return mAppDelta;
    }
public:
    ApplicationProperties properties;
    Application() = default;
    ~Application();

    void Run();
private:
    GLFWwindow* mWindow;
    double mAppDelta;

    bool MainLoop();
};
}


#endif //OGLD_MAIN_APPLICATION_H
