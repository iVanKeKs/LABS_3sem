
#ifndef INC_3_POLYNOMIAL_H
#define INC_3_POLYNOMIAL_H

#include"ListForPolynomial.h"

class PolynomialException
{
private:

	char *error;
	PolynomialException();

public:

	PolynomialException(const char *);
	PolynomialException(const PolynomialException&);
	~PolynomialException();

	const char *WhatException();
};


class Polynomial : public ListForPolynomial
{
private:
	
	void CreateNewZeroNode();
	void DestructPolynomial();


public:

	Polynomial();
	Polynomial(const char*);
	Polynomial(const Polynomial&);
	Polynomial(Polynomial&&);
	
	~Polynomial();

	Polynomial& operator =(const Polynomial&);
	Polynomial& operator =(Polynomial&&);

	Polynomial& operator +=(const Polynomial&);
	Polynomial& operator -=(const Polynomial&);
	Polynomial& operator *=(const Polynomial&);

	bool operator ==(const Polynomial&);
	bool operator !=(const Polynomial&);

    friend Polynomial operator +(const Polynomial&, const Polynomial&);
    friend Polynomial operator -(const Polynomial&, const Polynomial&);
    friend Polynomial operator *(const Polynomial&, const Polynomial&);
    friend Polynomial operator *(const Polynomial&, const ListForPolynomialNode&);

    friend std::ostream& operator <<(std::ostream&, const Polynomial&);
    friend std::istream& operator >>(std::istream&, Polynomial&);
};

#endif //INC_3_POLYNOMIAL_H