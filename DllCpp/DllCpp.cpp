// DllCpp.cpp : Definiuje eksportowane funkcje dla aplikacji DLL.
//

#include "stdafx.h"

// MathLibrary.cpp : Defines the exported functions for the DLL.
#include <utility>
#include <limits.h>
#include "DllCpp.h"
#include <vector>
#include <iostream>

int multiplyMatrix(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB) {



	int n = matrixA.size();
	int m = matrixA[0].size();
	int p = matrixB[0].size();

	int ** tablica = new int *[n];

	for (int i = 0; i < p; i++)
		tablica[i] = new int[p];

	std::vector<std::vector<int>> c(n, std::vector<int>(p, 0));

	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++) {
			for (int i = 0; i < n; i++) {
				c[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	return 5;
}

void multiply() {
	std::cout << "hello";
}