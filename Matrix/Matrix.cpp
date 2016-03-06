#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Была ли ошибшка при выполнении операции
int flag = 0;
string s;

// Пустой конструктор
Matrix::Matrix()
{
	string = 0;
	column = 0;
	a = nullptr;
}

// Конструктор с заданным количеством строк и столбцов (нулевая матрица)
Matrix::Matrix(unsigned int _string, unsigned int _column)
{
	this->string = _string;
	this->column = _column;

	a = new double *[string];
	for (int i = 0; i < string; i++)
		a[i] = new double[column];

	for (int i = 0; i < string; i++)
		for (int j = 0; j < column; j++)
			a[i][j] = 0;
}

// Ошибка при выполнении какой-либо операции с матрицами
Matrix Matrix::error(Matrix M) const
{
	printf_s("Operation error!\n");
	flag = 1;
	return M;
}

// Копирование матрицы
Matrix::Matrix(Matrix const & x) : a(new double *[x.column]), column(x.column), string(x.string)
{
	for (int i = 0; i < string; i++)
	{
		a[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			a[i][j] = x.a[i][j];
		}
	}
}

// Ввод из массива заданной размерности
Matrix::Matrix(int **matr, int _string, int _column)
{
	string = _string;
	column = _column;
	a = new double*[string];
	for (int i = 0; i < string; i++)
		a[i] = new double[column];
	for (int i = 0; i < string; i++)
		for (int j = 0; j < column; j++)
			a[i][j] = matr[i][j];
}


// Вывод
void Matrix::writeToConsole() const
{
	for (int i = 0; i < this->string; i++)
	{
		for (int j = 0; j < this->column; j++)
			printf_s("%3d ", (int)this->a[i][j]);
		cout << endl;
	}
}


Matrix &Matrix::readFromFile(char* path)
{
	ifstream stream;
	stream.open(path);

	if (stream.fail())
	{
		cout << "Incorrect filename";
		return Matrix();
	}

	int string, column;

	stream >> string >> column;
	int **mass = new int*[string];
	for (int i = 0; i < string; i++)
	{
		mass[i] = new int[column];
		for (int j = 0; j < column; j++)
			stream >> mass[i][j];
	}

	Matrix *temp = new Matrix(mass, string, column);
	stream.close();
	return *temp;
}

// Получение количесва строк матрицы
int Matrix::getStringNumber(Matrix m) const
{
	return m.string;
}

// Поулчение количества строк матрицы
int Matrix::getColumnNumber(Matrix m) const
{
	return m.column;
}

// Присваивание
Matrix Matrix::operator =(Matrix& m2)
{
	if (flag != 1)
		if (this != &m2)
			(Matrix(m2)).swap(*this);
	return *this;
}

// Сложение двух матриц
Matrix Matrix::operator +(Matrix &m2)
{
	flag = 0;
	if ((m2.string != this->string) || (m2.column != this->column))
	{
		Matrix temp = *this;
		return error(temp);
	}
	else
	{
		Matrix temp(this->string, this->column); // Создаем временную матрицу, в которой будет храниться результатирующая матрица

		for (int i = 0; i < string; i++)
			for (int j = 0; j < column; j++)
				temp.a[i][j] = this->a[i][j] + m2.a[i][j];

		return temp;
	}
}

// Вычитание двух матриц
Matrix Matrix::operator -(Matrix &m2)
{
	flag = 0;
	if ((m2.string != this->string) || (m2.column != this->column))
	{
		Matrix temp = *this;
		return error(temp);
	}
	else
	{
		Matrix temp(this->string, this->column); // Создаем временную матрицу, в которой будет храниться результатирующая матрица

		for (int i = 0; i < string; i++)
			for (int j = 0; j < column; j++)
				temp.a[i][j] = this->a[i][j] - m2.a[i][j];

		return temp;
	}
}

// Умножение матрицы на число
Matrix Matrix::operator *(double num) 
{
	Matrix temp(this->string, this->column); //В данном случае неважно - использовать m1 или m2, т. к. при корректном использовании, размеры матриц равны

	for (int i = 0; i < this->string; i++)
		for (int j = 0; j < this->column; j++)
			temp.a[i][j] = this->a[i][j] * num;

	return temp;
}

// Умножение двух матриц
Matrix Matrix::operator *(Matrix &m2) 
{
	flag = 0;
	if (this->column != m2.string)
	{
		Matrix temp = *this;
		return error(temp);
	}
	else
	{
		Matrix temp(this->string, m2.column); // В данном случае неважно - использовать m1 или m2, т. к. при корректном использовании, размеры матриц равны

		for (int row = 0; row < this->string; row++)
			for (int col = 0; col < m2.column; col++)
				for (int inner = 0; inner < m2.string; inner++)
					temp.a[row][col] += this->a[row][inner] * m2.a[inner][col];

		return temp;
	}
}

double* Matrix::operator[](int index) 
{
	return this->a[index];
}

// Функция для operator =
void Matrix::swap(Matrix & x)
{
	std::swap(x.a, a);
	std::swap(x.column, column);
	std::swap(x.string, string);
}

//Деструктор
Matrix::~Matrix()
{
	for (int i = 0; i < string; i++)
		delete[] a[i];
	delete[] a;
}