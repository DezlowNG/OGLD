//
// Created by Dezlow on 21.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_ENTRYPOINT_HPP
#define OGLD_ENTRYPOINT_HPP

#include "Application.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	auto app = ogld::CreateApplication();

	try {
		app->Run();
	} catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}

	return 0;
}

#endif //OGLD_ENTRYPOINT_HPP