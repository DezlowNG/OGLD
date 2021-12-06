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

#include "EntryPoint.h"

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
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
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
        double deltaTime = GetDelta();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, cos((float)glfwGetTime() * glm::radians(50.0f)), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(90.0f), (float)properties.width / (float)properties.height, 0.1f, 100.0f);

		glm::mat4 MVP = projection * view * model;

        mShader.Use();
        mShader.SetUniformMat4("MVP", MVP);
		mShader.SetUniformVec3("color", glm::vec3(glm::max(glm::sin(0.75f * glfwGetTime()), 0.35),
													  glm::max(glm::sin(0.75f * glfwGetTime()), 0.2),
													  glm::max(glm::cos(glm::sin(0.59f * glfwGetTime())), 0.25)));

		mVAO.Bind();
        gl::DrawArrays(gl::TRIANGLES, 0, 36);

        return true;
    }
private:
    ogld::Shader mShader{};
    ogld::VertexArray mVAO{};
    ogld::VertexBuffer mVBO{};
};

std::shared_ptr<ogld::Application> ogld::CreateApplication()
{
	return std::make_shared<DemoApplication>();
}