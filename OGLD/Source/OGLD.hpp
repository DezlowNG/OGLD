//
// Created by Dezlow on 31.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

// HAPPY NEW YEAR

#ifndef OGLD_HPP
#define OGLD_HPP

#ifdef OGLD_INCLUDE_CORE
    #include <memory>
    #include "Core/EntryPoint.hpp"
#endif

#ifdef OGLD_DEBUG
    #include "OpenGL/ErrorHandler.hpp"
#endif

#ifdef OGLD_TRACK_MEMORY
static int64_t allocMemory{};
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes\n";
    allocMemory += size;
    return malloc(size);
}
void operator delete(void* memory, size_t size)
{
    std::cout << "Freeing " << size << " bytes\n";
    allocMemory -= size;
    return free(memory);
}
#endif

#endif //OGLD_HPP
