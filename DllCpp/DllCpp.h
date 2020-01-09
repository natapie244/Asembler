
#pragma once
#include <vector>

#ifdef DLLCPP_EXPORTS
#define DLLCPP __declspec(dllexport)
#else
#define DLLCPP __declspec(dllimport)
#endif


extern "C" DLLCPP int multiplyMatrix(
	std::vector<std::vector<int>>, std::vector<std::vector<int>>);

extern "C" DLLCPP void multiply();