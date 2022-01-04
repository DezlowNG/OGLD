//
// Created by Dezlow on 20.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_TEXTURE_HPP
#define OGLD_TEXTURE_HPP

#include <string>

namespace ogld
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void Load(const std::string& path);
        void Bind() const;
        void Bind(size_t index) const;
        void UnBind() const;
        uint32_t GetID() const { return mTextureID; }
    private:
        uint32_t mTextureID{};
    };
}

#endif //OGLD_TEXTURE_HPP
