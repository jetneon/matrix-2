#include "stdafx.h"

#include <time.h>
#include <fstream>

using namespace std;

#define N 3
#define M 5

int main() {
	setlocale(LC_CTYPE, "Russian_Russia.1251");
	char* path = new char[256];
	printf_s("Enter path to input file:\n");
	cin >> path;
	CMatrix<int> M1;
	try {
		M1.readFromFile(path);
		printf_s("Matrix M1:\n");
		cout << M1;
	}
	catch (const char* msg) {
		cout << msg;
	}
	delete[] path;
	double **A = (double**)malloc(N * sizeof(double*));
	double **B = (double**)malloc(N * sizeof(double*));
	int **C = (int**)malloc(N * sizeof(int*));
	double **D = (double**)malloc(M * sizeof(double*));

	for (int i = 0; i < N; i++) {
		A[i] = (double*)malloc(M * sizeof(double));
		B[i] = (double*)malloc(M * sizeof(double));
		C[i] = (int*)malloc(M * sizeof(int));
	}

	for (int i = 0; i < M; i++) {
		D[i] = (double*)malloc(N * sizeof(double*));
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
			C[i][j] = rand() % 10;
		}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			D[i][j] = rand() % 10;

	CMatrix<double> M2(A, N, M), M3(B, N, M), M4(A, N, M), M5, M6(D, M, N), M7, M8, M9 = M8, M10;
	printf_s("Matrix M2:\n");
	cout << M2;
	printf_s("Matrix M3:\n");
	cout << M3;
	printf_s("Matrix M4 = M2 + M3:\n");
	M4 = M2 + M3;
	cout << M4;
	printf_s("Matrix M5 = 2 * M3:\n");
	M5 = M3 * 2;
	cout << M5;
	printf_s("Matrix M6:\n");
	cout << M6;
	printf_s("Matrix M7 = M2 * M6:\n");
	M7 = M2 * M6;
	cout << M7;
	printf_s("Matrix M8 = M2 + M6:\n");
	try {
		M8 = M6 + M2;
		cout << M8;
	}
	catch (const char *msg) {
		cout << msg;
	}
	printf_s("Matrix M9 (empty):\n");
	cout << M9;
	printf_s("Matrix M10 (empty => M2 + M2):\n");
	M10 = M2 + M2;
	cout << M10;
	printf_s("Matrix M11 (int test):\n");
	CMatrix<int> M11(C, N, M);
	cout << M11;

	printf_s("Operator << test:\n");
	cout << M2;
	printf_s("Operator >> test:\n");
	CMatrix<int> M12(2, 2);
	try {
		cin >> M12;
		cout << M12;
	}
	catch (const char *msg) {
		cout << msg;
	}
	for (int i = 0; i < N; i++) {
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
	for (int i = 0; i < M; i++) {
		delete[] D[i];
	}
	delete[] D;
	system("pause");

	return 0;
}