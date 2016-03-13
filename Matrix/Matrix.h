#pragma once

class Matrix {
private:
	void swap(Matrix & x);
	double **matrix;
	int m_columns;
	int m_rows;

public:
	Matrix() : m_rows(0), m_columns(0), matrix(nullptr) {};
	Matrix(unsigned int n, unsigned int m);
	Matrix(double **matr, unsigned int _n, unsigned int _m);
	Matrix(Matrix const & x);
	~Matrix();

	unsigned int rowsNumber() const;
	unsigned int columnsNumber() const;
	void readFromFile(char *path);
	void writeToConsole() const;

	Matrix &operator =(const Matrix& m2);
	Matrix operator +(const Matrix& m2);
	Matrix operator -(const Matrix& m2);
	Matrix operator *(double num);
	Matrix operator *(const Matrix& m2);
	double* operator [](unsigned int index);
};