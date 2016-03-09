#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Matrix::Matrix(unsigned int _string, unsigned int _column)
{
	this->string = _string;
	this->column = _column;

	a = new double *[string];
	for (int i = 0; i < string; i++) {
		a[i] = new double[column];
	}
	for (int i = 0; i < string; i++) {
		for (int j = 0; j < column; j++) {
			a[i][j] = 0;
		}
	}
}

Matrix::Matrix(Matrix const & x) : a(new double *[x.column]), column(x.column), string(x.string)
{
	try {
		//if (x.a == nullptr || string == 0 || column == 0 || this->a == nullptr) {
		//	throw "Отсутствие матрицы\n";
		//}
		for (int i = 0; i < string; i++) {
			a[i] = new double[column];
			for (int j = 0; j < column; j++) {
				a[i][j] = x.a[i][j];
			}
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}

Matrix::Matrix(double **matr, int _string, int _column)
{
	string = _string;
	column = _column;
	a = new double*[string];
	for (int i = 0; i < string; i++) {
		a[i] = new double[column];
	}
	for (int i = 0; i < string; i++) {
		for (int j = 0; j < column; j++) {
			a[i][j] = matr[i][j];
		}
	}
}


void Matrix::writeToConsole() const
{
	try {
		if (a == nullptr || string == 0 || column == 0) {
			throw "Пустая матрица\n";
		}
		for (int i = 0; i < this->string; i++) {
			for (int j = 0; j < this->column; j++) {
				cout.width(4);
				cout << (int)this->a[i][j];
			}
			cout << endl;
		}
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}


void Matrix::readFromFile(char* path)
{
	ifstream stream;
	try {
		stream.open(path);

		int string, column;

		stream >> string >> column;
		double **mass = new double*[string];
		for (int i = 0; i < string; i++) {
			mass[i] = new double[column];
			for (int j = 0; j < column; j++) {
				stream >> mass[i][j];
			}
		}

		this->a = mass;
		this->string = string;
		this->column = column;
		stream.close();
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return;
	}
}

int Matrix::rowsNumber() const
{
	return string;
}

int Matrix::columnsNumber() const
{
	return column;
}

Matrix Matrix::operator =(Matrix& m2)
{
	try {
		if (this != &m2) {
			(Matrix(m2)).swap(*this);
		}
		return *this;
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return m2;
	}
}

Matrix Matrix::operator +(Matrix &m2)
{
	try {
		if (m2.column != this->column || m2.string != this->string)
			throw "Неверные размеры матриц при сложении\n";
		Matrix temp(this->string, this->column);

		for (int i = 0; i < string; i++) {
			for (int j = 0; j < column; j++) {
				temp.a[i][j] = this->a[i][j] + m2.a[i][j];
			}
		}
		return temp;
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return Matrix();
	}
	catch (const char* msg) {
		std::cout << msg;
		return Matrix();
	}
}

Matrix Matrix::operator -(Matrix &m2)
{
	try {
		if (m2.column != this->column || m2.string != this->string)
			throw "Неверные размеры матриц при вычитании\n";
		Matrix temp(this->string, this->column);

		for (int i = 0; i < string; i++) {
			for (int j = 0; j < column; j++) {
				temp.a[i][j] = this->a[i][j] - m2.a[i][j];
			}
		}
		return temp;
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return Matrix();
	}
	catch (const char* msg) {
		std::cout << msg;
		return Matrix();
	}
}

Matrix Matrix::operator *(double num)
{
	try {
		if (this->a == nullptr || this->string == 0 || this->column == 0) {
			throw "Ошибка. Матрица пуста\n";
		}
		Matrix temp(this->string, this->column);

		for (int i = 0; i < this->string; i++) {
			for (int j = 0; j < this->column; j++) {
				temp.a[i][j] = this->a[i][j] * num;
			}
		}
		return temp;
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return *this;
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}

Matrix Matrix::operator *(Matrix &m2)
{
	try {
		if (this->column != m2.string) {
			throw "Неверные размеры матриц при умножении\n";
		}
		Matrix temp(this->string, m2.column);

		double t = 0;

		for (int row = 0; row < this->string; row++) {
			for (int col = 0; col < m2.column; col++) {
				t = 0;
				for (int inner = 0; inner < m2.string; inner++) {
					t += this->a[row][inner] * m2.a[inner][col];
				}
				temp.a[row][col] = t;
			}
		}
		return temp;
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
	}
	catch (const char* msg) {
		cout << msg;
	}
}

double* Matrix::operator[](int index)
{
	try {
		if (this->a == nullptr || this->column == 0 || this->string == 0) {
			throw "Невозможно получить строку. Матрица пуста\n";
		}
		return this->a[index];
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}

void Matrix::swap(Matrix & x)
{
	std::swap(x.a, a);
	std::swap(x.column, column);
	std::swap(x.string, string);
}

Matrix::~Matrix()
{
	if (a != nullptr) {
		for (int i = 0; i < string; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
}