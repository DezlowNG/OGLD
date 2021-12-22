//
// Created by Dezlow on 21.12.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef OGLD_LIBRARY_ENTRYPOINT_H
#define OGLD_LIBRARY_ENTRYPOINT_H

#include "Application.h"
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

#endif //OGLD_LIBRARY_ENTRYPOINT_H