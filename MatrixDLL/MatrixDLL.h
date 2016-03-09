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

class MATRIXDLL_API CMatrixDLL 
{

	void swap(CMatrixDLL & x);
	double **a;		// Массив (сама матрица)
	int column;		// Столбцы
	int string;		// Строки
public:
	CMatrixDLL(void);
	CMatrixDLL(int **matr, int _n, int _m);		// Вспомогательный метод. Только внутри программы
	CMatrixDLL(int, int);						// Конструктор, принимающий размеры массива
	CMatrixDLL(CMatrixDLL const & x);
	~CMatrixDLL();

	void read(char *path);						// Чтение массива из консоли
	void write();								// Вывод массива на консоль
	int getStringNumber(CMatrixDLL);
	int getColumnNumber(CMatrixDLL);

	// Перегрузка опреторов
	CMatrixDLL& operator =(const CMatrixDLL& m2);
	CMatrixDLL operator +(const CMatrixDLL& m2);
	CMatrixDLL operator -(const CMatrixDLL& m2);
	CMatrixDLL operator *(double num);
	CMatrixDLL operator *(const CMatrixDLL& m2);
	double*& operator [](int index);

	CMatrixDLL error(CMatrixDLL);
};

extern MATRIXDLL_API int nMatrixDLL;

MATRIXDLL_API int fnMatrixDLL(void);
