//
// Created by dezlow on 24.11.2021.
//

#ifndef OGLD_MAIN_APPLICATION_H
#define OGLD_MAIN_APPLICATION_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "OpenGL/gl_core_4_5.hpp"

namespace ogld
{
    class Application
    {
        struct ApplicationProperties
        {
            const char* title = "OGLD";
            uint16_t width = 1280;
            uint16_t height = 720;
            float bg[4]{0.1f, 0.1f, 0.1f, 1.0f};
            struct rendererProps
            {
                bool depth = true;
            };
            rendererProps renderer;
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
        ApplicationProperties properties{};
        Application() = default;
        ~Application();

        void Run();
    protected:
        virtual bool AppPreInit() = 0;
        virtual bool AppInit() = 0;
        virtual bool AppUpdate() = 0;

        double GetDelta() const { return mDeltaTime.delta; }
    private:
        GLFWwindow* mWindow{};
        DTSturct mDeltaTime;
        FPSStruct mFPS;

        void CalculateFPS();

        bool MainLoop();
    };
}


#endif //OGLD_MAIN_APPLICATION_H
