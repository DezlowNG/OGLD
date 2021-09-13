#pragma once

#ifndef SKYBOX_H
#define SKYBOX_H

#include <Core/Shader/Shader.h>
#include <Core/Core.h>
#include <vector>

#include <Components/PointLIght/PointLight.h>

static unsigned int loadCubemap(std::vector<std::string> faces);

class SkyBox
{
public:
	SkyBox() {}
	SkyBox(std::vector<std::string> faces);

	void RegisterLight(PointLight& light) { this->light = &light; }

	void Draw();

	unsigned int GetTextureID() { return texture; }

private:
	Shader shader;
	PointLight* light;
	unsigned int texture;
	unsigned int VAO, VBO;
};

#endif