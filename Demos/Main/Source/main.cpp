//
// Created by dezlow on 21.11.2021.
//

#include <memory>
#include <iostream>
#include "Application.h"

int main()
{
    try
    {
        auto demo_app = std::make_shared<ogld::Application>();
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }
    return 0;
}