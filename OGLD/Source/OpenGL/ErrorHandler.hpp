//
// Created by Dezlow on 21.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_ERRORHANDLER_HPP
#define OGLD_ERRORHANDLER_HPP

#include "OpenGL/gl_core_4_5.hpp"
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

namespace ogld
{
    namespace ErrorHandler
    {
        void GLClearError()
        {
            while (gl::GetError() != gl::NO_ERROR_);
        }

        bool GLLogCall()
        {
            while (GLenum error = gl::GetError())
            {
                std::cout << "[OGLD] OpenGL Error: (" << error << " )\n";
                return false;
            }
            return true;
        }
    }
}


#endif //OGLD_ERRORHANDLER_HPP
