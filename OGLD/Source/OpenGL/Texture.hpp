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

        void Load(const std::string& path);

        void Bind();

        void UnBind();
    private:
        bool GenerateSampler();

        uint32_t mTextureID;
    };
}

#endif //OGLD_TEXTURE_HPP
