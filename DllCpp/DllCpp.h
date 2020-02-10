
#pragma once
#include <vector>

#ifdef DLLCPP_EXPORTS
#define DLLCPP __declspec(dllexport)
#else
#define DLLCPP __declspec(dllimport)
#endif


extern "C" DLLCPP void multiplyMatrix(
	std::vector<std::vector<double>> *, std::vector<std::vector<double>> *, std::vector<std::vector<double>> *);

extern "C" DLLCPP void multiply();