#pragma once


#include <Core/Core.h>
#include <glm/glm.hpp>

#include <Components/Camera/Camera.h>

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

class PointLight
{
public:
	PointLight() {}
	void RegisterCamera(Camera& camera) { this->camera = &camera; }

	inline void SetPosition(glm::vec3 position) { mPosition = position; }
	inline glm::vec3 GetPosition() { return mPosition; }
	
	Camera* camera = nullptr;
private:
	glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
};

#endif