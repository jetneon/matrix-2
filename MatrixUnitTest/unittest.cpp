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
int **A = (int**)malloc(N * sizeof(int*));
int **B = (int**)malloc(N * sizeof(int*));
int **C = (int**)malloc(N * sizeof(int*));
int **D = (int**)malloc(M * sizeof(int*));

namespace MatrixUnitTest
{
	// Инициализация начальных данных
	void Init()
	{
		for (int i = 0; i < N; i++)
		{
			A[i] = (int*)malloc(M * sizeof(int));
			B[i] = (int*)malloc(M * sizeof(int));
			C[i] = (int*)malloc(M * sizeof(int));
		}

		for (int i = 0; i < M; i++)
		{
			D[i] = (int*)malloc(N * sizeof(int*));
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
		
		// Тест получения количества строк
		TEST_METHOD(GetStringNumber)
		{
			Init();
			/* ТЕСТЫ
			Matrix M1(A, N, M), M2(B, N, M), M3(N, M), M4(D, M, N), M5(N, N), M6;
			M1.consoleWrite();

			double *str = new double[5];
			str = M1[1];
			for (i = 0; i < 5; i++)
			printf_s("%3d ", (int)str[i]);
			printf_s("\n");
			M2.consoleWrite();

			getchar();
			M3 = M1 + M2;
			M3.consoleWrite();

			M5.consoleWrite();
			M5 = M1 * M4;
			M5.consoleWrite();
			M5 = M1 + M6;
			M5.consoleWrite();
			*/
			CMatrixDLL M1(A, N, M), M2;
			int k = M1.getStringNumber(M1);
		};

		// Тест получения количества столбцов
		TEST_METHOD(GetColumnNumber)
		{
			Init();
			CMatrixDLL M2;
			int k = M2.getColumnNumber(M2);
		}
		
		// Тест сложения матриц
		TEST_METHOD(Addition)
		{
			Init();
			CMatrixDLL M1(A, N, M), M2(D, M, N), M3, M4(B, N, M);
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
		
		// Тест умножения матриц
		TEST_METHOD(Multiplication)
		{
			Init();
			CMatrixDLL M1(A, N, M), M2(D, M, N), M3, M4(B, N, N);
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

		// Тест получения строки матрицы
		// (перегрузка оператора [])
		TEST_METHOD(GetString)
		{
			Init();
			CMatrixDLL M1(A, N, M);
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