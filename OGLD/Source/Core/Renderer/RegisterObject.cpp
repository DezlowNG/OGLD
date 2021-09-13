#include "RegisterObject.h"

namespace
{
	PointLight* pLight;
	Camera* pCamera;
}

template<class T>
void Renderer::RegisterObject(T object)
{
	static_assert("Failed to register object!");
}

template<>
void Renderer::RegisterObject(Camera& camera)
{
	pCamera = &camera;
}

template<>
void Renderer::RegisterObject(PointLight& light)
{
	pLight = &light;
	pLight->RegisterCamera(*pCamera);
}

template<>
void Renderer::RegisterObject(Cube& cube)
{
	cube.RegisterLight(*pLight);
}

template<>
void Renderer::RegisterObject(Mesh& mesh)
{
	mesh.RegisterLight(*pLight);
}

template<>
void Renderer::RegisterObject(SkyBox& skybox)
{
	skybox.RegisterLight(*pLight);
}
