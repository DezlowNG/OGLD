//
// Created by dezlow on 21.12.2021.
//

#include <iostream>
#include "CameraComponent.h"

ogld::Camera::Camera()
{
    mPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mWorldUp = mUp;
    mYaw = -90.0f;
    mPitch = 0.0f;
    mFront = glm::vec3(0.0f, 0.0f, -1.0f);
    mMovementSpeed = 2.5f;
    mMouseSensitivity = 0.12f;

    updateCameraVectors();
}

void ogld::Camera::keyboard_callback(GLFWwindow* window, float deltaTime)
{
    float velocity = mMovementSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mPosition += velocity * mFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mPosition -= velocity * mFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mPosition -= glm::normalize(glm::cross(mFront, mUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mPosition += glm::normalize(glm::cross(mFront, mUp)) * velocity;
}

void ogld::Camera::mouse_callback(float xpos, float ypos)
{
    if (mFirstMouse)
    {
        mLastX = xpos;
        mLastY = ypos;
        mFirstMouse = false;
    }

    float xoffset = xpos - mLastX;
    float yoffset = mLastY - ypos;

    mLastX = xpos;
    mLastY = ypos;

    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    if (mPitch > 89.0f)
        mPitch = 89.0f;
    if (mPitch < -89.0f)
        mPitch = -89.0f;

    updateCameraVectors();
}

void ogld::Camera::updateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mFront = glm::normalize(front);
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}