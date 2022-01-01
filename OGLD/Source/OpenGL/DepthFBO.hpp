//
// Created by Dezlow on 01.01.2022.
// Copyright (c) 2022 Oneiro Games. All rights reserved.
//


#pragma once

#ifndef OGLD_DEPTHFBO_HPP
#define OGLD_DEPTHFBO_HPP

#include <cstdint>

namespace ogld
{
    class DepthFBO
    {
    public:
        void Create(uint32_t depthID);
        void Bind() const;
        void UnBind() const;
        uint32_t GetID() const { return mID; }
    private:
        uint32_t mID;
    };
}

#endif //OGLD_DEPTHFBO_HPP
