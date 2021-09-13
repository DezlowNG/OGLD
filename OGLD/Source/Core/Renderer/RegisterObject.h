#pragma once

#include <Core/Core.h>

#include <Components/Camera/Camera.h>
#include <Components/PointLight/PointLight.h>
#include <Components/Mesh/Mesh.h>
#include <Components/SkyBox/SkyBox.h>
#include <Components/Objects/Cube/Cube.h>

namespace Renderer
{
	template<class T>
	void RegisterObject(T object);

	template<>
	void RegisterObject<Camera&>(Camera& camera);

	template<>
	void RegisterObject<PointLight&>(PointLight& light);

	template<>
	void RegisterObject<Cube&>(Cube& cube);

	template<>
	void RegisterObject<Mesh&>(Mesh& mesh);
	
	template<>
	void RegisterObject<SkyBox&>(SkyBox& skybox);
}