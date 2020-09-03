#include<iostream>

#include "SquareMatrix.h"
#include "TimeTests.h"

using namespace std;

int main()
{
	SquareMatrix a("test1", 3, 23., 5., 6., 9., 8., 6., 45., 60., 58.);
	SquareMatrix b;
	SquareMatrix c(1);
	SquareMatrix d("test2");
	SquareMatrix e(a);

	cout << a << endl << b << endl << c << endl << d << e << endl;

	cout << "\tОПЕРАТОРЫ" << endl;
	SquareMatrix a1("TEST", 2, 1., 2., 3., 4.);
	SquareMatrix a2("TESTLOL", 2, 1., 2., 3., 4.);

	cout << a1 + a2 << endl;
	cout << a1 - a2 << endl;
	cout << a1 * 2 << endl;
    cout << a1 * a2 << endl;
    cout << a1 / 2 << endl;
    cout << a1 / a2;

    cout << "Детерминант: " << Determinant(a1) << endl;
    cout << "Транспонированная матрица: " << TransposeMatrix(a1) << endl;
    cout << "Обратная матрица: " << MultiplicativeInverse(a1) << endl;
    cout << "След матрицы: " << TraceOfMatrix(a1) << endl;
    cout << "Экспонент матрицы: " << ExponentOfMatrix(a1) << endl;
	
	std::cout << "\tМЕТОД ГАУСА" << std::endl;
	SquareMatrix a3("Gaussian", 3, 2., 2., 3., 4., 5., 6., 7., 8., 9.);
	cout << a3 << endl;

	int numberOfSolutions;
	double *res = a3.GaussianMethod(numberOfSolutions);

	cout << "Решение: ";
	for (int i = 0; i < numberOfSolutions; ++i)
    {
	    cout << res[i] << ' ';
    }
	cout << endl;

    delete[] res;

	return 0;
}