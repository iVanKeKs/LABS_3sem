
#ifndef INC_2_POLYNOMIAL_H
#define INC_2_POLYNOMIAL_H

#include<iostream>
#include<climits>
#include<cstdarg>
#include<cstring>
#include<algorithm>

#include"List.h"

class PolynomialException
{
private:

	char *error;
	PolynomialException();

public:
    
	explicit PolynomialException(const char*);
	PolynomialException(const PolynomialException&);
	~PolynomialException();

	const char *WhatException();
};

class Polynomial : public List
{
private:

	void InitClassFields();
	void RemoveClassFields();
	void AddNodesWhileNotEven();
	Polynomial KaratsubaAlgorithm(const Polynomial &currentPolynomial) const;
	Polynomial(const Polynomial&, int, int);


public:

	explicit Polynomial(int = 0, ...);
	explicit Polynomial(char*);
	Polynomial(const Polynomial&);
	
	Polynomial(Polynomial&&);
	
	~Polynomial();

	void KillZeroNodes();
	void AddNumberOfNodeInStart(int);
	void AddNumberOfNodeToEnd(int);
	double SolvePolynomial(double);
	Polynomial Derivative();

	Polynomial& operator =(const Polynomial&);
	Polynomial& operator =(Polynomial&&);

	Polynomial& operator +=(const Polynomial&);
	Polynomial& operator -=(const Polynomial&);
	Polynomial& operator *=(const Polynomial&);
    Polynomial& operator *=(double);
	Polynomial& operator /=(const Polynomial&);
    Polynomial& operator /=(double);
	Polynomial& operator %=(const Polynomial&);

	friend std::ostream& operator<<(std::ostream&, const Polynomial&);
	friend std::istream& operator>>(std::istream&, Polynomial&);
};

Polynomial operator +(const Polynomial&, const Polynomial&);
Polynomial operator -(const Polynomial&, const Polynomial&);
Polynomial operator * (const Polynomial&, const Polynomial&);
Polynomial operator *(const Polynomial&, double);
Polynomial operator /(const Polynomial&, const Polynomial&);
Polynomial operator /(const Polynomial&, double);
Polynomial operator %(const Polynomial&, const Polynomial&);

#endif //INC_2_POLYNOMIAL_H