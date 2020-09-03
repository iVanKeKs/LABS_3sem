
#include "TimeTests.h"

void TEST(int countOfTests)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::system_clock::now();
	for (int i = 0; i < countOfTests; ++i)
	{
		SquareMatrix A("A", 3, 2., 2., 3., 4., 5., 6., 7., 8., 9.);
		Determinant(A);
	}
	end = std::chrono::system_clock::now();
	std::cout << "Вермя нахождения оперделителя" << countOfTests << " раз/a" << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " секунд\n";

	start = std::chrono::system_clock::now();
	for (int i = 0; i < countOfTests; ++i)
	{
		SquareMatrix A("A", 3, 2., 2., 3., 4., 5., 6., 7., 8., 9.);
		TransposeMatrix(A);
	}
	end = std::chrono::system_clock::now();
	std::cout << "Транспонирование матрицы " << countOfTests << " раз/a" << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " секунд\n";

	start = std::chrono::system_clock::now();
	for (int i = 0; i < countOfTests; ++i)
	{
		SquareMatrix A("A", 3, 2., 2., 3., 4., 5., 6., 7., 8., 9.);
		MultiplicativeInverse(A);
	}
	end = std::chrono::system_clock::now();
	std::cout << "Нахождение обратной матрицы " << countOfTests << " раз/a" << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " секунд\n";

	start = std::chrono::system_clock::now();
	for (int i = 0; i < countOfTests; ++i)
	{
		SquareMatrix A("A", 3, 2., 2., 3., 4., 5., 6., 7., 8., 9.);
		ExponentOfMatrix(A);
	}
	end = std::chrono::system_clock::now();
    std::cout << "Нахождение экспонента матрицы " << countOfTests << " раз/a" << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s\n";

	start = std::chrono::system_clock::now();
	for (int i = 0; i < countOfTests; ++i)
	{
		SquareMatrix A("A", 3, 2., 2., 3., 4., 5., 6., 7., 8., 9.);
		TraceOfMatrix(A);
	}
	end = std::chrono::system_clock::now();
    std::cout << "Нахождение следа матрицы " << countOfTests << " раз/a" << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s\n";
}