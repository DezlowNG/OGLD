//
// Created by dezlow on 21.11.2021.
//

#include <memory>

#include "glm/gtx/vector_angle.hpp"

#include "Core/Application.h"
#include "Core/EntryPoint.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/Texture.h"
#include "OpenGL/ErrorHandler.h"

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
        mShader.LoadFromFile("Shaders/shader.glsl");

        float vertices[] = {
               -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
               -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

               -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
               -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
               -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

               -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
               -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
               -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

               -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
               -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
               -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

               -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
               -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
               -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        mVAO.Init();
        mVAO.Bind();
        mVBO.Create(sizeof(vertices), vertices);
        ogld::VertexBuffer::PushLayout<float>(0, 3, 5, 0);
        ogld::VertexBuffer::PushLayout<float>(1, 2, 5, 3);
        mVBO.UnBind();
        mVAO.UnBind();

        mTexture.Load("Textures/woodbox.jpg");

        return true;
    }

    bool AppUpdate() override
    {
        ogld::ErrorHandler::GLClearError();

        glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                                      cos((float)glfwGetTime() * glm::radians(50.0f)),
                                      glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = GetCameraView();
        glm::mat4 projection = glm::perspective(glm::radians(90.0f),
                                                (float)properties.width / (float)properties.height,
                                                0.1f, 100.0f);

        glm::mat4 MVP = projection * view * model;

        mTexture.Bind();

        mShader.Use();
        mShader.SetUniform("MVP", MVP);

        mVAO.Bind();
        gl::DrawArrays(gl::TRIANGLES, 0, 36);

        ASSERT(ogld::ErrorHandler::GLLogCall());

        return true;
    }

private:
    ogld::Shader mShader{};
    ogld::VertexArray mVAO{};
    ogld::VertexBuffer mVBO{};

    ogld::Texture mTexture;
};

std::shared_ptr<ogld::Application> ogld::CreateApplication()
{
	return std::make_shared<DemoApplication>();
}