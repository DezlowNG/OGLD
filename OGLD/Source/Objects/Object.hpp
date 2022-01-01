//
// Created by Dezlow on 02.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_OBJECT_HPP
#define OGLD_OBJECT_HPP

#include <glm/gtx/transform.hpp>

namespace ogld
{
    class Object
    {
    public:
        Object() = default;
        ~Object() = default;

        virtual void Draw() = 0;

        void SetModel(const glm::mat4& newModel) { model = newModel; }
        void Rotate(float radians, const glm::vec3& pos) { model = glm::rotate(model, radians, pos); }
        void Translate(const glm::vec3& pos) { model = glm::translate(model, pos); }
        void Scale(const glm::vec3 scale) { model = glm::scale(model, scale); }
        const glm::mat4& GetModel() { return model; }
    protected:
        glm::mat4 model{};
    };
}


#endif //OGLD_OBJECT_HPP
