#pragma once

class Matrix
{
private:
	void swap(Matrix & x);
	double **a;     // Массив (сама матрица)
	int column;     // Столбцы
	int string;     // Строки

public:
	Matrix();
	Matrix(unsigned int n, unsigned int m); // Конструктор, принимающий размеры массива
	Matrix(int **matr, int _n, int _m);     // Только внутри программы
	Matrix(Matrix const & x);
	static Matrix &readFromFile(char* path);            // Чтение массива из консоли
	~Matrix();

	void writeToConsole() const;                          // Вывод массива на консоль
	int getStringNumber(Matrix) const;
	int getColumnNumber(Matrix) const;

	// Перегрузка опрераторов
	Matrix operator =(Matrix& m2);
	Matrix operator +(Matrix& m2);
	Matrix operator -(Matrix& m2);
	Matrix operator *(double num);
	Matrix operator *(Matrix& m2);
	double* operator [](int index);

	Matrix error(Matrix) const;
};