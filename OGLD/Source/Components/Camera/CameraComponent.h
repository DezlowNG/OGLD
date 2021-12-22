//
// Created by Dezlow on 21.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_LIBRARY_CAMERA_H
#define OGLD_LIBRARY_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include <GLFW/glfw3.h>

namespace ogld
{
    class Camera
    {
    public:
        Camera();
        const glm::mat4& GetViewMatrix() { return glm::lookAt(mPosition, mPosition + mFront, mUp); }

        void keyboard_callback(GLFWwindow* window, float deltaTime);
        void mouse_callback(float xpos, float ypos);
    private:
        glm::vec3 mPosition{};
        glm::vec3 mFront{};
        glm::vec3 mUp{};
        glm::vec3 mRight{};
        glm::vec3 mWorldUp{};

        float mMovementSpeed{};
        float mMouseSensitivity{};
        float mYaw{};
        float mPitch{};
        float mLastX{};
        float mLastY{};
        bool mFirstMouse = true;

        void updateCameraVectors();
    };
}
#endif //OGLD_LIBRARY_CAMERA_H