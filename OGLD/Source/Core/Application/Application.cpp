#include "Application.h"

double currentFrame = 0.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX, lastY;

static inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	lastX = width / 2.0f;
	lastY = height / 2.0f;
}

void Application::Run(const unsigned int width, const unsigned int height, const char* Title)
{
	ApplicationPreInit();
	ImGuiPreInit();

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(width, height, Title, nullptr, nullptr);

	if (mWindow == nullptr) {
		std::runtime_error("Failed to create window!"); 
		return;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::runtime_error("Failed to init GLAD!");
		return;
	}

	ApplicationInit();
	InitImGui();
	ImGuiInit();

	camera.lastX = lastX;
	camera.lastY = lastY;

	glfwSetWindowUserPointer(GetWindow(), this);

	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		ApplicationInput(deltaTime);
		ApplicationUpdate(deltaTime);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiUpdate(deltaTime);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}

	ApplicationClose();
	ImGuiClose();
	DestroyImGui();

	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Application::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Application::DestroyImGui()
{
}
