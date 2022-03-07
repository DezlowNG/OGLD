//
// Created by Dezlow on 31.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

/* HAPPY NEW YEAR
                           88
                          6¶¶8
                     06668¶¶0¶¶¶¶¶0
                     08¶¶¶8 0 8¶¶6
                        8¶¶8¶¶¶¶¶
                        ¶¶¶¶8068¶6
                        008¶¶0
                        0¶¶8¶8
                       8¶¶6 6¶6
                    08¶¶¶0   8¶8
                 06¶¶¶¶6      8¶¶6
              08¶¶¶¶60         08¶¶80
              08¶¶¶¶¶¶¶¶¶¶¶80     6¶¶¶0
                 0¶¶¶0            6¶¶¶
               6¶¶¶0             8¶¶¶0
           08¶¶¶80                06¶¶¶¶80
         ¶¶¶¶80                     08¶¶¶¶6
         6¶¶¶60          6¶¶¶¶¶¶¶¶¶¶¶¶¶860
           6¶¶¶¶860        06666666¶¶
            6¶¶88860               0¶¶60
         68¶¶6                       08¶¶¶660
     6¶¶¶¶80                            06¶¶¶¶¶0
     6¶¶¶¶86666668880                     8¶¶¶8
       06¶¶¶¶¶¶¶86                   068¶¶¶¶6
       6¶¶6        60           6¶¶¶¶¶¶8860
   068¶¶¶0         6¶¶60             8¶¶800
 8¶¶¶¶60            0¶¶¶¶¶800          68¶¶¶¶¶¶8
 0¶¶¶¶¶¶86666666688¶¶¶¶¶¶¶¶¶¶¶¶¶¶888666688¶¶¶¶80
    6¶¶¶¶¶¶¶¶¶¶¶¶¶860 8¶0  ¶¶88¶¶¶¶¶¶¶¶¶¶¶866
        0066600       ¶8   6¶
                     6¶6   8¶6
                     8¶¶¶¶¶¶¶0
                      688860
*/

#pragma once

#ifndef OGLD_HPP
#define OGLD_HPP

#ifdef OGLD_INCLUDE_CORE
    #include <memory>
    #include "Core/EntryPoint.hpp"
#endif

#if defined(OGLD_DEBUG)
    #include "OpenGL/ErrorHandler.hpp"
#endif

#if defined(OGLD_TRACK_MEMORY)
static uint32_t allocMemory{};
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
