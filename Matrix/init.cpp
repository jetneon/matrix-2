#include "stdafx.h"
#include "Matrix.h"
#include <catch.hpp>

SCENARIO("Matrix init", "[init]") {
	GIVEN("The number of rows and columns") {
		auto rows = 3;
		auto columns = 3;
		WHEN("Create instansce of Matrix") {
			CMatrix<int> m(rows, columns);
			THEN("The number of rows and columns must be preserved") {
				REQUIRE(m.rowsNumber() == rows);
				REQUIRE(m.columnsNumber() == columns);
			}
		}
	}
}

SCENARIO("Matrix: readFromFile()", "[fill]") {
	CMatrix<double> A;
	REQUIRE(A.readFromFile("A2x2.txt"));
}

SCENARIO("Matrix: operator +", "[addition]") {
	CMatrix<int> A, B, expected;
	A.readFromFile("A2x2.txt");
	B.readFromFile("B2x2.txt");
	expected.readFromFile("A+B.txt");

	CMatrix<int> result = A + B;
	REQUIRE(result == expected);
}

SCENARIO("Matrix: operator -", "[subtraction]") {
	CMatrix<int> A, B, expected;
	A.readFromFile("A2x2.txt");
	B.readFromFile("B2x2.txt");
	expected.readFromFile("A-B.txt");

	CMatrix<int> result = A - B;
	REQUIRE(result == expected);
}

SCENARIO("Matrix: operator *(matix, number)", "[multiplication]") {
	CMatrix<int> A, expected;
	A.readFromFile("A2x2.txt");
	expected.readFromFile("A2x2mult2.txt");

	CMatrix<int> result = A * 2;
	REQUIRE(result == expected);
}

SCENARIO("Matrix: operator *(matix, matrix)", "[multiplication]") {
	CMatrix<int> A, B, expected;
	A.readFromFile("A2x2.txt");
	B.readFromFile("B2x2.txt");
	expected.readFromFile("AxB.txt");

	CMatrix<int> result = A * B;
	REQUIRE(result == expected);
}

SCENARIO("Matrix: operator [](index)", "[get row]") {
	CMatrix<int> A;
	int* a = new int[2]; a[0] = 1; a[1] = 2;
	A.readFromFile("A2x2.txt");

	bool flag = true;
	int* res = A[0];
	for (int i = 0; i < 2; i++) {
		if (a[i] != res[i]) {
			flag = false;
		}
	}
	REQUIRE(flag);
}

SCENARIO("Matrix: rowsNumber()", "[rows number]") {
	CMatrix<int> A(3, 3);

	REQUIRE(A.rowsNumber() == 3);
}

SCENARIO("Matrix: columnsNumber()", "[columns number]") {
	CMatrix<int> A(3, 3);

	REQUIRE(A.columnsNumber() == 3);
}