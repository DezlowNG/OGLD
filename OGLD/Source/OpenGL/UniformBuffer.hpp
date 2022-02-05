//
// Created by Dezlow on 05.02.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#ifndef OGLD_UNIFORMBUFFER_HPP
#define OGLD_UNIFORMBUFFER_HPP

#include "OpenGL/gl_core_4_5.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace ogld
{
    class UniformBuffer
    {
    public:
        void Init(int size)
        {
            gl::GenBuffers(1, &mID);
            Bind();
            gl::BufferData(gl::UNIFORM_BUFFER, size, nullptr, gl::STATIC_DRAW);
            UnBind();
        }

        void PushBufferRange(int index, int offset, int size) {
            gl::BindBufferRange(gl::UNIFORM_BUFFER, index, mID, offset, size);
        }

        void PushData(int offset, int size, const glm::mat4& matrix) {
            gl::BufferSubData(gl::UNIFORM_BUFFER, offset, size, glm::value_ptr(matrix));
        }

        void PushData(int offset, int size, const glm::vec3& vec) {
            gl::BufferSubData(gl::UNIFORM_BUFFER, offset, size, glm::value_ptr(vec));
        }

        void Bind() const { gl::BindBuffer(gl::UNIFORM_BUFFER, mID); }
        void UnBind() const { gl::BindBuffer(gl::UNIFORM_BUFFER, 0); }
    private:
        uint32_t mID{};
    };
}


#endif //OGLD_UNIFORMBUFFER_HPP
