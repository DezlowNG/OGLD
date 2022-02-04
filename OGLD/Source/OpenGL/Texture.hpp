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
        struct TextureData
        {
            int width{};
            int height{};
            int nrChannels{};
        };
    public:
        Texture();
        ~Texture();

        void Load(const std::string& path, bool srgb = true, bool repeat = true);
        void Bind() const;
        void Bind(size_t index) const;
        void UnBind() const;

        [[nodiscard]] const TextureData& GetData() const { return mData; }
    private:
        TextureData mData{};
        uint32_t mID{};
    };
}

#endif //OGLD_TEXTURE_HPP
