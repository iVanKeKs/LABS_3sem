#include<iostream>
#include<stdarg.h>
#include<cstring>

#include "SquareMatrix.h"

#define TESTa

SquareMatrix::SquareMatrix(const double newValue)
{
	name = nullptr;
	size = 1;
	data = new double* [1];
	*data = new double [1];
	**data = newValue;
}

SquareMatrix::SquareMatrix(const char *newName)
{
    if(newName != nullptr)
    {
        name = new char [strlen(newName) + 1];
        strcpy(name, newName);
    }
    else
    {
        name = nullptr;
    }

    size = 0;

    data = nullptr;
}

SquareMatrix::SquareMatrix(const char *newName, int newSize, ...)
{
	if (newName != NULL)
	{
		name = new char[strlen(newName) + 1];
		strcpy(name, newName);
	}
	else
	{
		name = nullptr;
	}

	size = newSize;

	data = new double*[newSize];

	va_list args;
	va_start(args, newSize);

	for (int i = 0; i < newSize; i++)
	{
	    data[i] = new double[newSize];
		for (int j = 0; j < newSize; ++j)
		{
			data[i][j] = va_arg(args, double);
		}
	}

	va_end(args);
}

SquareMatrix::SquareMatrix(const SquareMatrix &sourceMatrix)
{
	if (sourceMatrix.name != nullptr)
	{
		name = new char[strlen(sourceMatrix.name) + 1];
		strcpy(name, sourceMatrix.name);
	}
	else
	{
		name = nullptr;
	}

	size = sourceMatrix.size;
	if(size != 0)
	{
		data = new double* [size];
		for (int i = 0; i < size; ++i)
        {
		    data[i] = new double[size];
		    for(int j = 0; j < size; ++j)
            {
                data[i][j] = sourceMatrix.data[i][j];
            }
        }
	}
	else
	{
		data = nullptr;
	}
}

SquareMatrix::SquareMatrix(SquareMatrix &&oldMatrix)
{
	name = oldMatrix.name;
	data = oldMatrix.data;
	size = oldMatrix.size;

    oldMatrix.name = nullptr;
    oldMatrix.data = nullptr;
    oldMatrix.size = 0;
}

SquareMatrix::~SquareMatrix()
{
    delete[] name;

	if(size != 0)
	{
		for (int i = 0; i < size; i++)
		{
		    delete[] data[i];
		}

		delete[] data;
	}
}

////////////////////////////////////////////////////////
//		���������
////////////////////////////////////////////////////////
SquareMatrix& SquareMatrix::operator =(const SquareMatrix &sourceMatrix)
{
	if (this == &sourceMatrix)
	{
		return *this;
	}

	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
		    delete[] data[i];
		}

		delete[] data;
	}

	size = sourceMatrix.size;

	if (sourceMatrix.size != 0)
	{
		data = new double* [size];
		for (int i = 0; i < size; ++i)
        {
		    data[i] = new double [size];

            for (int j = 0; j < size; ++j)
            {
                data[i][j] = sourceMatrix.data[i][j];
            }
        }
	}
	else
	{
		data = nullptr;
	}

	return *this;
}

SquareMatrix& SquareMatrix::operator =(SquareMatrix &&oldMatrix)
{
	if (this == &oldMatrix)
	{
		return *this;
	}

	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
            delete[] data[i];
		}

		delete[] data;
	}

	name = oldMatrix.name;
	data = oldMatrix.data;
	size = oldMatrix.size;

    oldMatrix.name = nullptr;
    oldMatrix.data = nullptr;
    oldMatrix.size = 0;

	return *this;
}

SquareMatrix& SquareMatrix::operator +=(const SquareMatrix &secondMatrix)
{
	if (size != secondMatrix.size)
	{
		throw MatrixException("Matrix dimension varies!");
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			data[i][j] += secondMatrix.data[i][j];
		}
	}

	return *this;
}

SquareMatrix& SquareMatrix::operator -=(const SquareMatrix &secondMatrix)
{
	if (size != secondMatrix.size)
	{
		throw MatrixException("Matrix dimension varies!");
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			data[i][j] -= secondMatrix.data[i][j];
		}
	}

	return *this;
}

SquareMatrix& SquareMatrix::operator *=(const SquareMatrix &secondMatrix)
{
	if (size != secondMatrix.size)
	{
		throw MatrixException("Matrix dimension varies!");
	}

	double** newData = new double*[size];

	for (int i = 0; i < size; ++i)
	{
	    newData[i] = new double[size];

		for (int j = 0; j < size; ++j)
		{
			double buff = 0;
			for (int k = 0; k < size; ++k)
			{
                buff += data[i][k]*secondMatrix.data[k][j];
			}

            newData[i][j] = buff;
		}
	}

	for (int i = 0; i < size; ++i)
	{
        delete[] data[i];
	}

	delete[] data;

	data = newData;
	
	return *this;
}

SquareMatrix& SquareMatrix::operator *=(const double number)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			data[i][j] *= number;
		}
	}

	return *this;
}

SquareMatrix& SquareMatrix::operator /=(const SquareMatrix &secondMatrix)
{
    *this *= MultiplicativeInverse(secondMatrix);

    return *this;
}

SquareMatrix& SquareMatrix::operator /=(const double number)
{
	if (std::abs(number) < Epsilon)
	{
		throw MatrixException("Division by zero!");
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; ++j)
		{
			data[i][j] /= number;
		}
	}

	return *this;
}

std::ostream& operator <<(std::ostream &outputStream, const SquareMatrix &outputMatrix)
{
	outputStream << "Matrix name: ";

	if (outputMatrix.name != nullptr)
	{
		outputStream << outputMatrix.name << std::endl;
	}
	else
	{
		outputStream << "<matrix name>" << std::endl;
	}

	if (outputMatrix.size != 0)
	{
		for (int i = 0; i < outputMatrix.size; ++i)
		{
			for (int j = 0; j < outputMatrix.size; ++j)
			{
				outputStream << outputMatrix.data[i][j] << " ";
			}

			outputStream << std::endl;
		}
	}
	else
	{
		outputStream << "<matrix elements>" << std::endl;
	}

	return outputStream;
}

std::istream& operator >>(std::istream &inputStream, SquareMatrix &newMatrix)
{
	char newName[BUFSIZ];
    int newSize;

	std::cout << "Matrix name: ";
	inputStream >> newName;

	std::cout << "Matrix size: ";
	inputStream >> newSize;

    newMatrix.RenameMatrix(newName);
	double **data = newMatrix.ResizeMatrix(newSize);

	std::cout << "Matrix elements:" << std::endl;
	for (int i = 0; i < newSize; ++i)
	{
		for (int j = 0; j < newSize; ++j)
		{
			inputStream >> data[i][j];
		}
	}

	return inputStream;
}


SquareMatrix operator +(const SquareMatrix &leftMatrix, const SquareMatrix &rightMatrix)
{
	SquareMatrix newMatrix(leftMatrix);
    newMatrix += rightMatrix;
	return newMatrix;
}

SquareMatrix operator -(const SquareMatrix &leftMatrix, const SquareMatrix &rightMatrix)
{
	SquareMatrix newMatrix(leftMatrix);
    newMatrix -= rightMatrix;
	return newMatrix;
}

SquareMatrix operator *(const SquareMatrix &leftMatrix, const SquareMatrix &rightMatrix)
{
	SquareMatrix newMatrix(leftMatrix);
    newMatrix *= rightMatrix;
	return newMatrix;
}

SquareMatrix operator *(const SquareMatrix &leftMatrix, const double rightNumber)
{
	SquareMatrix newMatrix(leftMatrix);
    newMatrix *= rightNumber;
	return newMatrix;
}

SquareMatrix operator /(const SquareMatrix &leftMatrix, const SquareMatrix &rightMatrix)
{
    SquareMatrix newMatrix(leftMatrix);
    newMatrix /= rightMatrix;
    return newMatrix;
}

SquareMatrix operator /(const SquareMatrix &leftMatrix, const double rightNumber)
{
    SquareMatrix newMatrix(leftMatrix);
    newMatrix /= rightNumber;
    return newMatrix;
}


void SquareMatrix::RenameMatrix(const char* newName)
{
    delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

double **SquareMatrix::ResizeMatrix(const int newSize)
{
	if (size == newSize)
    {
	    return data;
    }

	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
            delete[] data[i];
		}

		delete[] data;
	}

	size = newSize;

	data = new double*[newSize];
	for (int i = 0; i < newSize; ++i)
    {
	    data[i] = new double[newSize];
    }

	return data;
}

SquareMatrix SquareMatrix::CreateMinor(int numberOfColumn, int numberOfString) const
{
	if (size < 2)
	{
		throw MatrixException("Error in CreateSmallerMatrix(...)! (Matrix.size < 2)");
	}
	if (numberOfString > size)
	{
		throw MatrixException("Error in CreateSmallerMatrix(...)! (numberOfString > Matrix.size)");
	}
	if (numberOfColumn > size)
	{
		throw MatrixException("Error in CreateSmallerMatrix(...)! (numberOfColumn > Matrix.size)");
	}

	SquareMatrix minor;
    minor.size = size - 1;
    minor.data = new double*[minor.size];

	for (int i = 0, minorCurrentColumn = 0; i < size; ++i)
	{
		if (i != numberOfColumn)
		{
		    minor.data[minorCurrentColumn] = new double[minor.size];
			for (int j = 0, minorCurrentString = 0; j < size; ++j)
			{
				if (j != numberOfString)
				{
                    minor.data[minorCurrentColumn][minorCurrentString] = data[i][j];
					++minorCurrentString;
				}
			}
			
			++minorCurrentColumn;
		}
	}

	return minor;
}

double SquareMatrix::AlgebraicComplement(int numberOfColumn, int numberOfString) const
{
	SquareMatrix currentMinor = CreateMinor(numberOfColumn, numberOfString);

	if ((numberOfColumn + numberOfString) % 2)
	{
		return -1 * Determinant(currentMinor);
	}
	else
	{
		return Determinant(currentMinor);
	}
}


double *SquareMatrix::GaussianMethod(int &numberOfSolutions)
{
	double* result = NULL;

	if (std::abs(Determinant(*this)) < SquareMatrix::Epsilon)
	{
        numberOfSolutions = 0;
		return NULL;
	}

	int strings = size,
	    columns = size + 1;
    addNewColumn();

	for (int i = 0; i < strings; ++i)
	{
		std::cout << "������ �����" << i + 1 << " xyz: ";

		std::cin >> data[i][size];
	}

	double  buff;
	result = new double[columns];

	for (int i = 0; i < strings; ++i)
	{
        buff = data[i][i];
		for (int j = strings; j >= i; --j)
        {
		    data[i][j] /= buff;
        }

		for (int j = i + 1; j < strings; ++j)
		{
            buff = data[j][i];
			for (int k = strings; k >= i; --k)
            {
			    data[j][k] -= buff * data[i][k];
            }
		}
	}

	result[strings - 1] = data[strings - 1][strings];

	for (int i = strings - 2; i >= 0; --i)
	{
		result[i] = data[i][strings];
		for (int j = i + 1; j < strings; ++j)
        {
		    result[i] -= data[i][j] * result[j];
        }
	}

    removeRightColumn();

    numberOfSolutions = size;
	return result;
}

void SquareMatrix::addNewColumn()
{
	double **tmp = data;
	data = NULL;

	data = new double*[size];
	for (int i = 0; i < size; ++i)
    {
	    data[i] = new double[size + 1];
    }


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; ++j)
		{
			if (j != size)
				data[i][j] = tmp[i][j];
			else
				data[i][j] = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (tmp[i])
		{
			delete[] tmp[i];
		}
	}

	delete[] tmp;
}

void SquareMatrix::removeRightColumn()
{
	double **buffData = data;
	data = nullptr;

	data = new double*[size];

	for (int i = 0; i < size; ++i)
	{
	    data[i] = new double[size];
		for (int j = 0; j < size; ++j)
		{
			data[i][j] = buffData[i][j];
		}
        delete[] buffData[i];
	}
}


double Determinant(const SquareMatrix &Matrix)
{
	if (Matrix.size == 0)
    {
	    throw MatrixException("Empty matirx!");
    }

	if (Matrix.size == 1)
    {
	    return Matrix.data[0][0];
    }

	if (Matrix.size == 2)
    {
	    return Matrix.data[0][0] * Matrix.data[1][1] - Matrix.data[1][0] * Matrix.data[0][1];
    }

	double determinant = 0;

	for (int i = 0; i < Matrix.size; ++i)
	{
		int sign;
		if (i % 2)
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}

		SquareMatrix minor = Matrix.CreateMinor(0, i);

        determinant += sign * Matrix.data[0][i] * Determinant(minor);
	}

	return determinant;
}

SquareMatrix MultiplicativeInverse(const SquareMatrix &sourceMatrix)
{
	double determinant = Determinant(sourceMatrix);

	if (std::abs(determinant) < SquareMatrix::Epsilon)
	{
		throw MatrixException("Determinant is 0!");
	}

	SquareMatrix inverseMatrix(sourceMatrix.name);
	inverseMatrix.size = sourceMatrix.size;

    inverseMatrix.data = new double*[inverseMatrix.size];
	for (int i = 0; i < inverseMatrix.size; ++i)
	{
	    inverseMatrix.data[i] = new double[inverseMatrix.size];
		for (int j = 0; j < inverseMatrix.size; ++j)
		{
            inverseMatrix.data[i][j] = sourceMatrix.AlgebraicComplement(i, j) / determinant;
		}
	}

	return TransposeMatrix(inverseMatrix);
}

SquareMatrix TransposeMatrix(const SquareMatrix &sourceMatrix)
{
	SquareMatrix transposeMatrix(sourceMatrix.name);
    transposeMatrix.size = sourceMatrix.size;

    transposeMatrix.data = new double*[transposeMatrix.size];
	for (int i = 0; i < transposeMatrix.size; ++i)
	{
	    transposeMatrix.data[i] = new double[transposeMatrix.size];
		for (int j = 0; j < transposeMatrix.size; ++j)
		{
            transposeMatrix.data[i][j] = sourceMatrix.data[j][i];
		}
	}

	return transposeMatrix;
}

double TraceOfMatrix(const SquareMatrix &currentMatrix)
{
	double trace = 0;

	for (int i = 0; i < currentMatrix.size; ++i)
	{
		trace += currentMatrix.data[i][i];
	}

	return trace;
}

SquareMatrix ExponentOfMatrix(const SquareMatrix &sourceMatrix)
{
	SquareMatrix matrixExponent(sourceMatrix);

	for (int i = 0; i < matrixExponent.size; ++i)
    {
        for (int j = 0; j < matrixExponent.size; ++j)
        {
            if (i == j)
            {
                matrixExponent.data[i][j] = 1;
            }
            else
            {
                matrixExponent.data[i][j] = 0;
            }
        }
    }

	double factorial = 1;
	SquareMatrix A(sourceMatrix);

	for (double i = 1; 1 / factorial > SquareMatrix::Epsilon; ++i)
	{
        factorial *= i;

        matrixExponent += (A * (1 / factorial));

		A *= sourceMatrix;
	}

	return matrixExponent;
}

MatrixException::MatrixException()
        :error(NULL)
{}

MatrixException::MatrixException(const char* errorName)
{
    if (errorName != nullptr)
    {
        error = new char[strlen(exception) + 1];
        strcpy(error, errorName);
    }
    else
    {
        error = nullptr;
    }
}

MatrixException::MatrixException(const MatrixException& exception)
{
    if (exception.error != nullptr)
    {
        error = new char[strlen(exception.error) + 1];
        strcpy(error, exception.error);
    }
    else
    {
        error = nullptr;
    }
}

MatrixException::~MatrixException()
{
    delete[] error;
}

const char *MatrixException::WhatException() const
{
    return error;
}