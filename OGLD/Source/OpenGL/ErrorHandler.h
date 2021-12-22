//
// Created by Dezlow on 21.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_LIBRARY_ERRORHANDLER_H
#define OGLD_LIBRARY_ERRORHANDLER_H

#include "OpenGL/gl_core_4_5.hpp"

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
                std::cout << "[OGL ERROR] (" << error << " )\n";
                return false;
            }
            return true;
        }
    }
}


#endif //OGLD_LIBRARY_ERRORHANDLER_H
