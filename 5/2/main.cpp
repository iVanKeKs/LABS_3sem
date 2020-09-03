#pragma warning(disable:4996)

#include<cstdio>
#include<iostream>
#include<cctype>
#include<cmath>
#include<ctime>

using namespace std;

#include"Polynomial.h"
#include "TechnicalMethods.h"

//3x^5+3x^4+3x^3+3x^2+3x+3
//2x^5+2x^4+2x^3+2x^2+2x+2

/*
0 Add - сложение
1 Sub - вычитание
2 Mult - умножение
3 Div Ц целочисленное деление
4 Mod Ц остаток от делени€
5 Eval Ц вычисление многочлена в заданной точке
6 Diff - дифференцирование
*/

int main(int argc, char **argv)
{
    if(argc == 0)
    {
        cout << "Ќе был получен входной файл" << endl;
        exit(-1);
    }

	Polynomial polynom;

	cin >> polynom;

	cout << polynom << endl;

	FILE *fileInput;
	if (!(fileInput = fopen("test.txt", "r")))
	{
		cout << "‘айл \"" << argv[1] << "\" не существует" << endl;
		exit(-1);
	}

	char buff[BUFSIZ],
	     command[BUFSIZ],
	     firstNode[BUFSIZ],
	     secondNode[BUFSIZ];

	Polynomial resultPolynomial;
	double tmp_double;

	while (!feof(fileInput))
	{
        readFromFile(fileInput, buff);

		if (strlen(buff) > 0)
		{
            parseInputString(buff, command, firstNode, secondNode);

			cout << endl << "Command: " << command << endl;
			cout << "First argument: " << firstNode << endl;
			cout << "Second argument: " << secondNode << endl;

			int lenOfFirst = strlen(firstNode);
			int lenOfSecond = strlen(secondNode);

			try
			{
				if (!strcmp("add", command))
				{
					if (lenOfSecond != 0)
					{
						Polynomial left(firstNode);
						Polynomial right(secondNode);

                        resultPolynomial = left + right;
						cout << "RESULT = " << resultPolynomial << endl;
					}
					else
					{
                        cout << "Need two arguments in command: " << buff;
					}
				}
				else if (!strcmp("sub", command))
				{
					if (lenOfSecond != 0)
					{
						Polynomial left(firstNode);
						Polynomial right(secondNode);

                        resultPolynomial = left - right;
						cout << "RESULT = " << resultPolynomial << endl;
					}
					else
					{
                        cout << "Need two arguments in command: " << buff;
					}
				}
				else if (!strcmp("mult", command))
				{
					if (lenOfSecond != 0)
					{
						Polynomial left(firstNode);
						Polynomial right(secondNode);

                        resultPolynomial = left * right;
						cout << "RESULT = " << resultPolynomial << endl;
					}
					else
					{
                        cout << "Need two arguments in command: " << buff;
					}
				}
				else if (!strcmp("div", command))
				{
					if (lenOfSecond != 0)
					{
						Polynomial left(firstNode);
						Polynomial right(secondNode);

                        resultPolynomial = left / right;
						cout << "RESULT = " << resultPolynomial << endl;
					}
					else
					{
                        cout << "Need two arguments in command: " << buff;
					}
				}
				else if (!strcmp("mod", command))
				{
					if (lenOfSecond != 0)
					{
						Polynomial left(firstNode);
						Polynomial right(secondNode);

                        resultPolynomial = left % right;
						cout << "RESULT = " << resultPolynomial << endl;
					}
					else
					{
					    cout << "Need two arguments in command: " << buff;
					}
				}
				else if (!strcmp("eval", command))
				{
					if (lenOfSecond != 0)
					{
						Polynomial left(firstNode);
						int x = atoi(secondNode);

						tmp_double = left.SolvePolynomial(x);
						cout << "RESULT = " << tmp_double << endl;
					}
					else
					{
					    continue;
					}
				}
				else if (!strcmp("diff", command))
				{
					if (lenOfFirst)
					{
						Polynomial left(firstNode);

                        resultPolynomial = left.Derivative();
						cout << "RESULT = " << resultPolynomial << endl;
					}
					else
					{
                        cout << "Need argument in command: " << buff;
					}
				}
				else
				{
					cout << "Bad command! : " << buff << endl;
				}
			}
			catch (PolynomialException &exception)
			{
				cout << exception.WhatException() << endl;
			}
			catch (ListException &exception)
			{
				cout << exception.WhatException() << endl;
			}
		}

	}

	return 0;
}