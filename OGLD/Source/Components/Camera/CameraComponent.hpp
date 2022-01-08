//
// Created by Dezlow on 21.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_CAMERA_HPP
#define OGLD_CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include <GLFW/glfw3.h>
#include <Components/Component.hpp>

namespace ogld
{
    class Camera : public Component
    {
    public:
        Camera();
        void keyboard_callback(GLFWwindow* window, float deltaTime);
        void mouse_callback(float xpos, float ypos);
        glm::mat4 GetViewMatrix() const { return glm::lookAt(mPosition, mPosition + mFront, mUp); }
    private:
        glm::vec3 mFront{};
        glm::vec3 mUp{};
        glm::vec3 mRight{};
        glm::vec3 mWorldUp{};
        bool mFirstMouse = 1;
        float mLastX{};
        float mLastY{};

        float mYaw{};
        float mPitch{};

        float mMovementSpeed{};
        float mMouseSensitivity{};

        void updateCameraVectors();
    };
}
#endif //OGLD_CAMERA_HPP