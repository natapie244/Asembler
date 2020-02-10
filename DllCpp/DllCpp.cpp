// DllCpp.cpp : Definiuje eksportowane funkcje dla aplikacji DLL.
//

#include "stdafx.h"

// MathLibrary.cpp : Defines the exported functions for the DLL.
#include <utility>
#include <limits.h>
#include "DllCpp.h"
#include <vector>
#include <iostream>

void multiplyMatrix(std::vector<std::vector<double>> * matrixA, std::vector<std::vector<double>> * matrixB, std::vector<std::vector<double>> * matrixC) {


	int n = (*matrixA).size();
	int m = (*matrixA)[0].size();
	int p = (*matrixB)[0].size();


	//std::vector<std::vector<int>> c(n, std::vector<int>(p, 0));

	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++) {
			for (int i = 0; i < n; i++) {
				(*matrixC)[i][j] += (*matrixA)[i][k] * (*matrixB)[k][j];
			}
		}
	}
}

void multiply() {
	std::cout << "hello";
}