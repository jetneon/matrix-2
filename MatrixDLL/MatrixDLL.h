// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа MATRIXDLL_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции MATRIXDLL_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef MATRIXDLL_EXPORTS
#define MATRIXDLL_API __declspec(dllexport)
#else
#define MATRIXDLL_API __declspec(dllimport)
#endif

// Этот класс экспортирован из MatrixDLL.dll

class MATRIXDLL_API Matrix {
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
