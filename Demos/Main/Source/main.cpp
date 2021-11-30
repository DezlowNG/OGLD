//
// Created by dezlow on 21.11.2021.
//

#include <memory>
#include <iostream>

#include "Application.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include "glm/gtx/vector_angle.hpp"
#include "glm/mat4x4.hpp"

class DemoApplication : public ogld::Application
{
protected:
    bool AppPreInit() override
    {
        properties.vsync = false;
        properties.title = "OGLD: Main Demo";

        return true;
    }

    bool AppInit() override
    {
        mShader.LoadFromFile("Shaders/vertex.glsl", "Shaders/fragment.glsl");

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f
        };

        mVAO.Init();
        mVAO.Bind();
        mVBO.Create(sizeof(vertices), vertices);
        ogld::VertexBuffer::PushLayout<float>(0, 3, 3, 0);
        mVBO.UnBind();
        mVAO.UnBind();

        return true;
    }

    bool AppUpdate() override
    {
        glm::mat4 model = glm::mat4(1.0f);
        double deltaTime = GetDelta();

        model = glm::rotate(model, (float)sin(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));

        mShader.Use();
        mShader.SetUniform<glm::mat4>("MVP", model);
        mShader.SetUniform<glm::vec3>("color", glm::vec3(glm::max(glm::sin(0.75f * glfwGetTime()), 0.35),
                                                         glm::max(glm::sin(0.75f * glfwGetTime()), 0.2),
                                                         glm::max(glm::cos(glm::sin(0.59f * glfwGetTime())), 0.25)));

        mVAO.Bind();
        gl::DrawArrays(gl::TRIANGLES, 0, 3);

        return true;
    }
private:
    ogld::Shader mShader;
    ogld::VertexArray mVAO;
    ogld::VertexBuffer mVBO;
};

int main()
{
    auto demo_app = std::make_shared<DemoApplication>();

    try {
        demo_app->Run();
    } catch (std::exception& ex) {
        std::cout << ex.what() << '\n';
    }

    return 0;
}