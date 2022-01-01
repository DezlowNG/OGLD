//
// Created by Dezlow on 01.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_DEPTHMAP_HPP
#define OGLD_DEPTHMAP_HPP

#include <cstdint>

namespace ogld
{
    class DepthMap
    {
    public:
        void Create(uint32_t size);
        void Bind() const;
        void Bind(size_t index) const;
        void UnBind() const;
        uint32_t GetID() const { return mID; }
    private:
        uint32_t mID;
    };
}


#endif //OGLD_DEPTHMAP_HPP
