//
// Created by Dezlow on 20.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_LIBRARY_TEXTURE_H
#define OGLD_LIBRARY_TEXTURE_H

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
#endif //OGLD_LIBRARY_TEXTURE_H
