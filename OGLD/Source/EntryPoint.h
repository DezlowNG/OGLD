#pragma once

#include "Application.h"

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