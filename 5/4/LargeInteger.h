
#ifndef INC_4_LARGEINTEGER_H
#define INC_4_LARGEINTEGER_H

#include<iostream>
#include<cctype>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>

class LargeIntegerException
{
private:

	char *error;
	LargeIntegerException();

public:

	LargeIntegerException(const char*);
	LargeIntegerException(const LargeIntegerException&);
	~LargeIntegerException();

	const char *WhatExceptions();
};


class LargeInteger
{
private:

	int *data;
	int size;
	int base;
	bool isPlus;

	LargeInteger(const LargeInteger&, bool);
	LargeInteger(const LargeInteger&, int, int);

	void AddNodesWhileNotEven();
	void AddNewNumeralInStart(int);
	void AddNewNumeralInEnd(int);
	void NumberNormalization();

	void Swap(LargeInteger&);

	LargeInteger MultSimpleLargeInteger(const LargeInteger&) const;

public:

	LargeInteger MulInt(int);

	LargeInteger();
	LargeInteger(int);
	explicit LargeInteger(const char*, int = 10);

	LargeInteger(const LargeInteger&);
	LargeInteger(LargeInteger&&);

	~LargeInteger();

	LargeInteger& operator =(const LargeInteger&);
	LargeInteger& operator =(LargeInteger&&);

	LargeInteger& operator +=(const LargeInteger&);
	LargeInteger& operator -=(const LargeInteger&);
	LargeInteger& operator *=(const LargeInteger&);
    LargeInteger& operator *=(int);
	LargeInteger& operator /=(const LargeInteger&);
	LargeInteger& operator %=(const LargeInteger&);

	bool operator <(LargeInteger&);
	bool operator ==(LargeInteger&);
	bool operator >(LargeInteger&);
	bool operator >=(LargeInteger&);

	friend std::ostream& operator <<(std::ostream&, const LargeInteger&);
	friend std::istream& operator >>(std::istream&, LargeInteger&);

	LargeInteger Pow(int);
	LargeInteger TranslateNumberToBase10();
	LargeInteger TranslateNumberToBaseK(int);
    LargeInteger KaratsubaMultiple(const LargeInteger&) const;
};

LargeInteger operator +(const LargeInteger&, const LargeInteger&);
LargeInteger operator -(const LargeInteger&, const LargeInteger&);
LargeInteger operator *(const LargeInteger&, const LargeInteger&);
LargeInteger operator /(const LargeInteger&, const LargeInteger&);
LargeInteger operator %(const LargeInteger&, const LargeInteger&);

LargeInteger Fibonacci(int);
LargeInteger Factorial(int);
LargeInteger BinomialCoefficient(int, int);

#endif