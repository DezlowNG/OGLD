//
// Created by Dezlow on 03.02.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//

#ifndef OGLD_INDEXBUFFER_HPP
#define OGLD_INDEXBUFFER_HPP

#include "OpenGL/gl_core_4_5.hpp"

namespace ogld
{
    class IndexBuffer
    {
    public:
        IndexBuffer() = default;
        ~IndexBuffer()
        {
            gl::DeleteBuffers(1, &mID);
        }

        void Init(const uint32_t* data, size_t count)
        {
            gl::GenBuffers(1, &mID);
            Bind();
            gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, count, data, gl::STATIC_DRAW);
            SetElementCount(count);
        }

        void Bind() const
        {
            gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, mID);
        }

        void UnBind() const
        {
            gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);
        }

        [[nodiscard]] inline constexpr size_t GetElementCount() const { return mElementCount; }
    private:
        constexpr void SetElementCount(size_t count) { mElementCount = count / sizeof(uint32_t); }

        size_t mElementCount{};
        uint32_t mID{};
    };
}

#endif //OGLD_INDEXBUFFER_HPP
