#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>

void Cube::Create(const char* texturePath)
{
	const char* vertexCubeShaderSrc = {
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoords;\n"
		"\n"
		"out vec3 FragPos;\n"
		"out vec3 Normal;\n"
		"out vec2 TexCoords;\n"
		"\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec4 pos = model * vec4(aPos, 1.0);\n"
		"	FragPos = pos.xyz;\n"
		"	Normal = aNormal;\n"
		"	TexCoords = aTexCoords;\n"
		"	gl_Position = projection * view * pos;\n"
		"}\0"
	};

	const char* fragmentCubeShaderSrc = {
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"in vec3 FragPos;\n"
		"in vec3 Normal;\n"
		"in vec2 TexCoords;\n"
		"\n"
		"uniform sampler2D cubeTexture;\n"
		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec3 color = texture(cubeTexture, TexCoords).rgb;\n"
		"\n"
		"	vec3 ambient = 0.05 * color;\n"
		"\n"
		"	vec3 lightDir = normalize(lightPos - FragPos);\n"
		"	vec3 normal = normalize(Normal);\n"
		"	float diff = max(dot(lightDir, normal), 0.0);\n"
		"	vec3 diffuse = diff * vec3(0.3);\n"
		"\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	float spec = 0.0;\n"
		"\n"
		"	float max_distance = 1.5;"
		"	float distance = length(lightPos - FragPos);"
		"	float attenuation = 1.0 / (distance * distance);"
		"	vec3 halfwayDir = normalize(lightDir + viewDir);\n"
		"	spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);\n"
		"\n"
		"	vec3 specular = vec3(0.3) * spec;\n"
		"	diffuse *= attenuation;\n"
		"   specular *= attenuation;\n"
		"   vec3 light = diffuse + specular;\n"
		"   color *= light;\n"
		"   color = pow(color, vec3(1.0/2.2));\n"
		"	FragColor = vec4(color, 1.0);\n"
		"}\0"
	};

	shader.LoadFromSource(vertexCubeShaderSrc, fragmentCubeShaderSrc);
	TextureID = loadTexture(texturePath);

	float cubeVertices[] = {
		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
	   -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	   -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
	   -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	shader.use();
	shader.setInt("cubeTexture", 0);
}

void Cube::Draw()
{
	shader.use();
	shader.setMat4("view", mLight->camera->GetViewMatrix());
	shader.setMat4("projection", mLight->camera->Projection);
	shader.setMat4("model", model);
	shader.setVec3("viewPos", mLight->camera->Position);
	shader.setVec3("lightPos", mLight->GetPosition());
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
