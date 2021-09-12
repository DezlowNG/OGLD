#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>

#pragma comment ( lib, "opengl32.lib" )
#pragma comment ( lib, "glfw3.lib" )

unsigned int loadTexture(const char* texturePath);

#endif