#pragma once

#ifndef CUBE_H
#define CUBE_H

#include <Core/Shader/Shader.h>
#include <Core/Core.h>
#include <Components/PointLight/PointLight.h>

class Cube
{
public:
	Cube() {}
	~Cube() {}

	void Create(const char* texturePath);

	void Draw();
	void RegisterLight(PointLight& light) { mLight = &light; }
	glm::mat4 model = glm::mat4(1.0f);
private:
	Shader shader;
	PointLight* mLight = nullptr;

	unsigned int TextureID, VAO, VBO, EBO;
};

#endif