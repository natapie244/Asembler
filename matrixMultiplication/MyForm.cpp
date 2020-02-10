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
typedef void(*procCpp)(std::vector<std::vector<double>> *, std::vector<std::vector<double>> *, std::vector<std::vector<double>> *);
typedef int(*procMASM)(double*, double*, double*, int, int, int);
//typedef void(*procCpp)();


[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	matrixMultiplication::MyForm form;
	Application::Run(%form);
}

std::vector<std::vector<double>> loadFile(std::string fileName) {
	std::ofstream log;

	std::vector<std::vector<double>> v;
	const char* f = fileName.c_str();

	FILE* plik;

	plik = fopen(f, "r");
	char znak; 
	log.open("log.txt");

	std::string number;
	std::vector<double> tmp;


	do
	{
		znak = fgetc(plik); //zapisujê jeden znak z pliku
		if (znak == 32) { //32 = space in ASCII
			if (number != "") {
				tmp.push_back(stod(number));
				number = "";
			}
			
		}
		else if(znak == 59) { //59 = ; in ASCII
			if (number != "") {
				tmp.push_back(stod(number));
			}
			number = "";

			v.push_back(tmp);
			tmp.clear();
		}
		else if(isdigit(znak) || znak == 46){ //46 = . in ASCII
			number += znak;
		}

	} while (znak != EOF); //End Of File - koniec pliku

	fclose(plik); 


	for (const auto &row : v) {
		for (const auto &e : row) {
			log << e << " ";
		}

		log << "; ";
	}
	log.close();

	return v;
}


matrixInfo getMatrixInfo(std::vector<std::vector<double>> matrix) {
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



void cppMatrixMultiplication(std::vector<std::vector<double>> matrixA, std::vector<std::vector<double>> matrixB) {
	HINSTANCE cppDll = LoadLibraryA("DllCpp");
	procCpp multiplyCpp = (procCpp)GetProcAddress(cppDll, "multiplyMatrix");

	int n = matrixA.size();
	int p = matrixB[0].size();

	std::vector<std::vector<double>> matrixC(n, std::vector<double>(p, 0));

	if (cppDll != NULL) {
		multiplyCpp(&matrixA, &matrixB, &matrixC);
	}

	std::ofstream wynik;

	wynik.open("wynik.txt");
	for (const auto &row : matrixC) { 
		for (const auto &e : row) {
			wynik << e << " "; 
		}

		wynik << "; ";
	}

	wynik.close();



}

void asmMatrixMultiplication(std::vector<std::vector<double>> matrixA, std::vector<std::vector<double>> matrixB) {
	HINSTANCE asmDll = LoadLibraryA("AsmDll");
	procMASM multiplyMASM = (procMASM)GetProcAddress(asmDll, "Multiply");

	int n = matrixA.size();
	int m = matrixA[0].size();
	int p = matrixB[0].size();

	//double matrix_1[9] = { 2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0 };
	//double matrix_2[9] = { 3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0 };

	//double matrix_3[9] = { 0.0 };  //n * p
	double * matrixC = new double[n*p];

	for (int i = 0; i < n*p; i++) {
		matrixC[i] = 0;
	}

	double* mat_1 = vectorToArray(matrixA);
	double* mat_2 = vectorToArray(matrixB);
	double* mat_3 = matrixC;

	if (asmDll != NULL) {
		//multiplyCpp();
		multiplyMASM(mat_1, mat_2, mat_3,n,m,p);

		//matrixC[0] = 5;

		std::ofstream wynik;

		wynik.open("wynikasm.txt");

		//wynik << *matrixC;

		for (int i = 0; i < n*p; i++) {
			wynik << matrixC[i] << " ";
			if(!((i + 1) % p)) {
				wynik << "; ";
			}
		}

		wynik.close();
	}



}

double * vectorToArray(std::vector<std::vector<double>> matrixA) {
	//std::vector<std::vector<int>> v = { {1,2},{3,4},{5,6} };
	int n = matrixA.size();
	int m = matrixA[0].size();

	double *arr = (double*)malloc((n * m) * sizeof(double));
	for (int i = 0; i < n; i++)
		memcpy(arr + matrixA[i].size() * i, &(matrixA[i][0]), matrixA[i].size() * sizeof(double));

	return arr;

}