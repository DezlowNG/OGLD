#pragma once

#ifndef SKYBOX_H
#define SKYBOX_H

#include <Core/Shader/Shader.h>
#include <Core/Core.h>
#include <vector>

static unsigned int loadCubemap(std::vector<std::string> faces);

class SkyBox
{
public:
	SkyBox() {}
	SkyBox(std::vector<std::string> faces);

	void Draw(glm::mat4 view, glm::mat4 proj);

	unsigned int GetTextureID() { return texture; }

private:
	Shader shader;
	unsigned int texture;
	unsigned int VAO, VBO;
};

#endif