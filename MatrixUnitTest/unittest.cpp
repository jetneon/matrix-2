#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\MatrixDLL\MatrixDLL.h"
#include <stdlib.h>
#include <time.h>
#include <locale>
#include <stdio.h>
#include <tchar.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define N 3
#define M 5
wchar_t message[200];
double **A = (double**)malloc(N * sizeof(double*));
double **B = (double**)malloc(N * sizeof(double*));
double **C = (double**)malloc(N * sizeof(double*));
double **D = (double**)malloc(M * sizeof(double*));

namespace MatrixUnitTest
{
	// Инициализация начальных данных
	void Init()
	{
		for (int i = 0; i < N; i++)
		{
			A[i] = (double*)malloc(M * sizeof(double));
			B[i] = (double*)malloc(M * sizeof(double));
			C[i] = (double*)malloc(M * sizeof(double));
		}

		for (int i = 0; i < M; i++)
		{
			D[i] = (double*)malloc(N * sizeof(double*));
		}

		srand(time(NULL));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				A[i][j] = rand() % 10;
				B[i][j] = rand() % 10;
			}
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				D[i][j] = rand() % 10;
	}
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(GetStringNumber)
		{
			Init();
			Matrix M1(A, N, M), M2;
			int k = M1.rowsNumber();
		};

		TEST_METHOD(GetColumnNumber)
		{
			Init();
			Matrix M2;
			int k = M2.columnsNumber();
		}
		
		TEST_METHOD(Addition)
		{
			Init();
			Matrix M1(A, N, M), M2(D, M, N), M3, M4(B, N, M);
			try
			{
				M3 = M1 + M2;
			}
			catch (std::out_of_range ex)
			{
				Assert::Fail(message, LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception");
				Assert::Fail(message, LINE_INFO());
			}

			try 
			{
				M3 = M1 + M4;
			}
			catch (std::out_of_range ex)
			{
				Assert::Fail(message, LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception");
				Assert::Fail(message, LINE_INFO());
			}
		};
		
		TEST_METHOD(Multiplication)
		{
			Init();
			Matrix M1(A, N, M), M2(D, M, N), M3, M4(B, N, N);
			try
			{
				M3 = M1 * M2;
			}
			catch (std::out_of_range ex)
			{
				Assert::Fail(message, LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception");
				Assert::Fail(message, LINE_INFO());
			}

			try
			{
				M4 = M1 * M2;
			}
			catch (std::out_of_range ex)
			{
				Assert::Fail(message, LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception");
				Assert::Fail(message, LINE_INFO());
			}
			try
			{
				M4 = M1 * 2;
			}
			catch (std::out_of_range ex)
			{
				Assert::Fail(message, LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception");
				Assert::Fail(message, LINE_INFO());
			}
		}

		TEST_METHOD(GetString)
		{
			Init();
			Matrix M1(A, N, M);
			try
			{
				double *s = M1[1];
			}
			catch (std::out_of_range ex)
			{
				Assert::Fail(message, LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception");
				Assert::Fail(message, LINE_INFO());
			}
		}
	};
}