//
// Created by dezlow on 21.11.2021.
//

#include <memory>
#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec3 color;"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(color.xyz, 1.0f);\n"
                                   "}\n\0";

#include "glm/vec3.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/mat4x4.hpp"

class DemoApplication : public ogld::Application
{
protected:
    bool AppInit() override
    {
        mShader.LoadFromFile("Shaders/vertex.glsl", "Shaders/fragment.glsl");
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f
        };

        VAO.Init();
        VAO.Bind();
        VBO.Create(sizeof(vertices), vertices);
        VertexBuffer::PushLayout<float>(0, 3, 3, 0);
        VBO.UnBind();
        VAO.UnBind();

        gl::DepthFunc(gl::ALWAYS);
        gl::Enable(gl::BLEND);
        gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

        return true;
    }

    bool AppUpdate() override
    {
        double deltaTime = GetDelta();
        mShader.Use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)tan(sin(glfwGetTime())), glm::vec3(1.0f, 0.0f, 0.0f));
        mShader.SetUniform<glm::mat4>("MVP", model);
        mShader.SetUniform<glm::vec3>("color", glm::vec3(glm::max(glm::sin(0.75f * glfwGetTime()), 0.35), glm::max(glm::sin(0.75f * glfwGetTime()), 0.2),  glm::max(glm::sin(0.59f * glfwGetTime()), 0.25)));
        VAO.Bind();
        gl::DrawArrays(gl::TRIANGLES, 0, 3);

        return true;
    }
private:
    Shader mShader;
    VertexArray VAO;
    VertexBuffer VBO;
};

int main()
{
    try
    {
        DemoApplication* demo_app = new DemoApplication;
        demo_app->Run();
        delete demo_app;
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }
    return 0;
}