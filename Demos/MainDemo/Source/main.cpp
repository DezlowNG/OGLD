#include <Core/Application/Application.h>

#include <Core/Shader/Shader.h>
#include <Components/Camera/Camera.h>
#include <Components/Mesh/Mesh.h>
#include <Components/SkyBox/SkyBox.h>

#include <Components/Objects/Cube/Cube.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Components/PointLight/PointLight.h>

const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 900;

bool DrawImGui = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class DemoApplication : public Application
{
public:
	void ApplicationPreInit() override
	{

	}
	
	void ApplicationInit() override
	{
		glfwWindowHint(GLFW_SAMPLES, 4);

		glfwSetKeyCallback(GetWindow(), key_callback);
		glfwSetInputMode(GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(GetWindow(), mouse_callback);

		mesh = Mesh::Mesh("../Assets/Objects/nanosuit/nanosuit.obj");

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_SAMPLES);

		mesh.Scale(glm::vec3(0.1f, 0.1f, 0.1f));
		mesh.Translate(glm::vec3(0.0f, -10.0f, -25.0f));

		std::vector<std::string> sbfaces = {
			"../Assets/Textures/SkyBox/right.jpg",
			"../Assets/Textures/SkyBox/left.jpg",
			"../Assets/Textures/SkyBox/top.jpg",
			"../Assets/Textures/SkyBox/bottom.jpg",
			"../Assets/Textures/SkyBox/front.jpg",
			"../Assets/Textures/SkyBox/back.jpg"
		};

		skybox = SkyBox::SkyBox(sbfaces);

		cube.Create("../Assets/Textures/wood.png");

		light.SetPosition(glm::vec3(0.0f, 0.5f, -1.25f));

		RegisterObject<PointLight&>(light);
		RegisterObject<Cube&>(cube);
		RegisterObject<Mesh&>(mesh);
	}

	void ApplicationInput(float delta) override
	{
		if (!DrawImGui)
		{
			camera.ProcessKeyboard(GetWindow(), delta);
		}
	}

	void ApplicationUpdate(float delta) override
	{
		skybox.Draw(glm::mat4(glm::mat3(camera.GetViewMatrix())), camera.Projection);

		mesh.Draw();

		glDisable(GL_CULL_FACE);
		cube.Draw();
		glEnable(GL_CULL_FACE);
	}

	void ApplicationClose() override
	{

	}

	void ImGuiPreInit() override
	{

	}

	void ImGuiInit() override
	{

	}

	void ImGuiUpdate(float delta) override
	{
		if (DrawImGui)
		{
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			if (ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
			{
				ImGui::DragFloat("Camera speed", &camera.MovementSpeed, 0.005f, 0.0f, 100.0f);
				glm::vec3 lightPos = light.GetPosition();
				if (ImGui::DragFloat3("Light Position", &lightPos[0], 0.01f, -5000.0f, 5000.0f))
					light.SetPosition(lightPos);

				ImGui::End();
			}
		}
	}

	void ImGuiClose() override
	{

	}
private:
	Shader shader;
	Mesh mesh;
	SkyBox skybox;

	Cube cube;

	PointLight light;

	glm::mat4 view;
	glm::mat4 proj;
};

int main()
{
	try
	{
		DemoApplication* DemoApp = new DemoApplication;

		DemoApp->Run(WINDOW_WIDTH, WINDOW_HEIGHT, "Main Demo");

		delete DemoApp;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << '\n';
	}

	return 0;
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
	app->camera.ProcessMouseMovement(xpos, ypos);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		break;
	case GLFW_KEY_F:
		if (action == GLFW_PRESS)
		{
			if (!DrawImGui)
			{
				DrawImGui = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetCursorPosCallback(window, nullptr);
				break;
			}
			DrawImGui = false;
			glfwSetKeyCallback(window, key_callback);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, mouse_callback);
		}
	default:
		break;
	}
}