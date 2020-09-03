#include <cmath>

class SquareMatrix
{

private:

    constexpr static double Epsilon = 0.00000000000000001;

	double **data;
	char *name;
	int size;

	SquareMatrix CreateMinor(int, int) const;
	double AlgebraicComplement(int, int) const;

	void addNewColumn();
	void removeRightColumn();

    void RenameMatrix(const char *);
    double **ResizeMatrix(int);

public:

	explicit SquareMatrix(double);
    explicit SquareMatrix(const char * = nullptr);
	SquareMatrix(const char *, int, ...);

	SquareMatrix(const SquareMatrix &);
	SquareMatrix(SquareMatrix &&);

	~SquareMatrix();

    double *GaussianMethod(int &);

    friend double Determinant(const SquareMatrix &);
    friend SquareMatrix MultiplicativeInverse(const SquareMatrix &);
    friend SquareMatrix TransposeMatrix(const SquareMatrix &);
    friend double TraceOfMatrix(const SquareMatrix &);
    friend SquareMatrix ExponentOfMatrix(const SquareMatrix &);

	SquareMatrix & operator =(const SquareMatrix &);
	SquareMatrix & operator =(SquareMatrix &&);
	SquareMatrix & operator +=(const SquareMatrix &);
	SquareMatrix & operator -=(const SquareMatrix &);
	SquareMatrix & operator *=(const SquareMatrix &);
	SquareMatrix & operator *=(double);
	SquareMatrix & operator /=(const SquareMatrix &);
    SquareMatrix & operator /=(double);
    friend std::ostream & operator <<(std::ostream &, const SquareMatrix &);
    friend std::istream & operator >>(std::istream &, SquareMatrix &);
};

SquareMatrix operator +(const SquareMatrix &, const SquareMatrix &);
SquareMatrix operator -(const SquareMatrix &, const SquareMatrix &);
SquareMatrix operator *(const SquareMatrix &, const SquareMatrix &);
SquareMatrix operator *(const SquareMatrix &, double);
SquareMatrix operator /(const SquareMatrix &, const SquareMatrix &);
SquareMatrix operator /(const SquareMatrix &, double);

class MatrixException
{

private:
    char* error;
    MatrixException();


public:
    MatrixException(const char*);
    MatrixException(const MatrixException &);
    ~MatrixException();

    const char *WhatException() const;
};