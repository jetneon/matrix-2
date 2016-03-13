#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Matrix::Matrix(unsigned int _string, unsigned int _column) : a(new double *[_string]), string(_string), column(_column) {
	for (int i = 0; i < string; i++) {
		a[i] = new double[column];
		for (int j = 0; j < column; j++) {
			a[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix & x) : a(new double *[x.string]), column(x.column), string(x.string) {
	for (int i = 0; i < string; i++) {
		a[i] = new double[column];
		for (int j = 0; j < column; j++) {
			a[i][j] = x.a[i][j];
		}
	}
}

Matrix::Matrix(double **matr, unsigned int _string, unsigned int _column) : a(new double *[_string]), string(_string), column(_column) {
	for (int i = 0; i < string; i++) {
		a[i] = new double[column];
		for (int j = 0; j < column; j++) {
			a[i][j] = matr[i][j];
		}
	}
}

void Matrix::writeToConsole() const {
	if (this->a == nullptr || this->string == 0 || this->column == 0) {
		cout << "Пустая матрица\n";
	}
	for (int i = 0; i < this->string; i++) {
		for (int j = 0; j < this->column; j++) {
			cout.width(4);
			cout << (int)this->a[i][j];
		}
		cout << endl;
	}
}

void Matrix::readFromFile(char* path) {
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

unsigned int Matrix::rowsNumber() const {
	return string;
}

unsigned int Matrix::columnsNumber() const {
	return column;
}

Matrix& Matrix::operator =(const Matrix& m2) {
	if (this != &m2) {
		(Matrix(m2)).swap(*this);
	}
	return *this;
}

Matrix Matrix::operator +(const Matrix &m2) {
	if (m2.column != this->column || m2.string != this->string) {
		throw "Неверные размеры матриц при сложении\n";
	}
	Matrix temp(this->string, this->column);
	for (int i = 0; i < this->string; i++) {
		for (int j = 0; j < this->column; j++) {
			temp[i][j] = m2.a[i][j] + this->a[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator -(const Matrix &m2) {
	if (m2.column != this->column || m2.string != this->string)
		throw "Неверные размеры матриц при вычитании\n";
	Matrix temp(this->string, this->column);
	for (int i = 0; i < this->string; i++) {
		for (int j = 0; j < this->column; j++) {
			temp.a[i][j] = m2.a[i][j] - a[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator *(double num) {
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

Matrix Matrix::operator *(const Matrix &m2) {
	if (this->column != m2.string) {
		throw "Неверные размеры матриц при умножении\n";
	}
	Matrix temp(this->string, m2.column);

	double t = 0;

	for (int row = 0; row < this->string; row++) {
		for (int col = 0; col < m2.column; col++) {
			t = 0;
			for (int inner = 0; inner < this->column; inner++) {
				t = t + this->a[row][inner] * m2.a[inner][col];
			}
			temp.a[row][col] = t;
		}
	}
	return temp;
}


double* Matrix::operator[](unsigned int index) {
	return this->a[index];
}

void Matrix::swap(Matrix & x) {
	std::swap(x.a, a);
	std::swap(x.column, column);
	std::swap(x.string, string);
}

Matrix::~Matrix() {
	string = 0;
	column = 0;
	if (a != nullptr) {
		for (int i = 0; i < string; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
}