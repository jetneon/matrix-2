#pragma once

class Matrix {
private:
	void swap(Matrix & x);
	double **a;
	int column;
	int string;

public:
	Matrix() : string(0), column(0), a(nullptr) {};
	Matrix(unsigned int n, unsigned int m);
	Matrix(double **matr, unsigned int _n, unsigned int _m);
	Matrix(Matrix const & x);
	~Matrix();

	void writeToConsole() const;
	unsigned int rowsNumber() const;
	unsigned int columnsNumber() const;
	void readFromFile(char *path);

	Matrix &operator =(const Matrix& m2);
	Matrix operator +(const Matrix& m2);
	Matrix operator -(const Matrix& m2);
	Matrix operator *(double num);
	Matrix operator *(const Matrix& m2);
	double* operator [](unsigned int index);
};