#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <Core/Core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <Components/Camera/Camera.h>

class Application
{
public:
	Application() {}
	~Application() {}

	virtual void ApplicationPreInit() = 0;
	virtual void ApplicationInit() = 0;
	virtual void ApplicationInput(float delta) = 0;
	virtual void ApplicationUpdate(float delta) = 0;
	virtual void ApplicationClose() = 0;

	virtual void ImGuiPreInit() = 0;
	virtual void ImGuiInit() = 0;
	virtual void ImGuiUpdate(float delta) = 0;
	virtual void ImGuiClose() = 0;

	Camera camera;

	void Run(const unsigned int width, const unsigned int height, const char* Title);
protected:
	GLFWwindow* GetWindow() { return mWindow; }

private:
	void InitImGui();
	void DestroyImGui();

	GLFWwindow* mWindow = nullptr;
};

#endif