#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <Core/Core.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera();

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(GLFWwindow* window, float deltaTime);
    void ProcessMouseMovement(double xpos, double ypos, bool constrainPitch = true);
public:
    glm::vec3 Position = glm::vec3(0.0f, 1.0f, 2.0f);
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 Projection;
    float lastX;
    float lastY;

    float Yaw = -90.0f;
    float Pitch = 0.0f;

    float MovementSpeed = 1.5f;
    float MouseSensitivity = 0.08f;
    float FOV = 45.0f;
private:
    bool firstMouse = true;
    void updateCameraVectors();
};

#endif