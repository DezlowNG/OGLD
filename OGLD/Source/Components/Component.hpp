//
// Created by Dezlow on 12.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_COMPONENT_HPP
#define OGLD_COMPONENT_HPP

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ogld
{
    class Component
    {
    public:
        Component() : mRotationAngle(0), mRotation(0.0f), mPosition(0.0f), mScale(1.0f) {}
        void SetPosition(const glm::vec3& position) { mPosition = position; }
        void SetRotation(float angle, const glm::vec3& rotation) { mRotationAngle = angle; mRotation = rotation; }
        void SetScale(const glm::vec3& scale) { mScale = scale; }

        const glm::mat4& SetUpModel(glm::mat4& model, bool makeRotate = false)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, GetPosition());
            model = glm::scale(model, GetScale());
            if (makeRotate)
                model = glm::rotate(model, mRotationAngle, GetRotation());
            return model;
        }

        [[nodiscard]] const glm::vec3& GetPosition() const { return mPosition; }
        [[nodiscard]] const glm::vec3& GetRotation() const { return mRotation; }
        [[nodiscard]] const glm::vec3& GetScale() const { return mScale; }
    protected:
        glm::vec3 mPosition{1.0f};
        glm::vec3 mRotation{0.0f};
        float mRotationAngle{0.0f};
        glm::vec3 mScale{1.0f};
    };
}

#endif //OGLD_COMPONENT_HPP
