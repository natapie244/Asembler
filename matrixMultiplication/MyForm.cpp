#include "MyForm.h"
#include <iostream>
#include <string>
#include <fstream>    
#include <vector>
#include <stdio.h>
#include <cstring>
#define _AFXDLL

//#include <afxwin.h>
#include <string>
#include <msclr\marshal_cppstd.h>
//#include <atlbase.h>
#include <cliext/list>
#include <chrono>



using namespace System;
using namespace System::Windows::Forms;
typedef int(*procCpp)(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
typedef int(*procMASM)(double*, double*, double*, int, int, int);
//typedef void(*procCpp)();


[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	matrixMultiplication::MyForm form;
	Application::Run(%form);
}

std::vector<std::vector<int>> loadFile(std::string fileName) {
	std::ofstream log;

	std::vector<std::vector<int>> v;
	const char* f = fileName.c_str();

	FILE* plik;

	plik = fopen(f, "r");
	char znak; 
	log.open("log.txt");

	std::string number;
	std::vector<int> tmp;

	std::string kamrol;

	do
	{
		znak = fgetc(plik); //zapisujê jeden znak z pliku
		if (znak == 32) { //32 = space in ASCII
			if (number != "") {
				tmp.push_back(stoi(number));
				number = "";
			}
			
		}
		else if(znak == 59) { //59 = ; in ASCII
			if (number != "") {
				tmp.push_back(stoi(number));
			}
			number = "";

			v.push_back(tmp);
			tmp.clear();
		}
		else if(isdigit(znak)){
			number += znak;
		}

	} while (znak != EOF); //End Of File - koniec pliku

	fclose(plik); 
	for (const auto &e : tmp) log << e << "\n";
	log << kamrol;
	log.close();

	return v;
}


matrixInfo getMatrixInfo(std::vector<std::vector<int>> matrix) {
	matrixInfo info;
	int columnPattern = -1;
	info.row = matrix.size();

	for (const auto &row : matrix) {
		if (columnPattern == -1) {
			columnPattern = row.size();
		}
		else {
			if (row.size() != columnPattern) {
				info.colums = 0;
				info.isValid = false;
				return info;
			}
		}
	}

	info.colums = columnPattern;
	info.isValid = true;
	return info;
}

void multiplyMatrix(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB) {
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
				tablica[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++) {
			for (int i = 0; i < n; i++) {
				tablica[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
}

void test(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB) {
	HINSTANCE cppDll = LoadLibraryA("DllCpp");

	procCpp multiplyCpp = (procCpp)GetProcAddress(cppDll, "multiplyMatrix");
	
	if (cppDll != NULL) {
		//multiplyCpp();
		int num = multiplyCpp(matrixA, matrixB);

		std::cout << num;
	}


}

void test_2() {
	HINSTANCE asmDll = LoadLibraryA("AsmDll");
	procMASM multiplyMASM = (procMASM)GetProcAddress(asmDll, "Multiply");

	double matrix_1[9] = { 2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0 };
	double matrix_2[9] = { 3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0 };
	double matrix_3[9] = { 0.0 };
	double* mat_1 = matrix_1;
	double* mat_2 = matrix_2;
	double* mat_3 = matrix_3;

	if (asmDll != NULL) {
		//multiplyCpp();
		multiplyMASM(mat_1, mat_2, mat_3,3,3,3);
		matrix_3[3] = 0;
	}

}