
#ifndef INC_3_MONOMIAL_H
#define INC_3_MONOMIAL_H

#include"ListForMonomial.h"


class MonomialException
{
private:

	char *error;
	MonomialException();


public:

	explicit MonomialException(const char *);
	MonomialException(const MonomialException&);
	~MonomialException();

	const char *WhatException();
};


class Monomial : public ListForMonomial
{
private:

	double coefficient;

public:

	Monomial();
	Monomial(char*);
	Monomial(const Monomial&);
	Monomial(Monomial&&);

    ~Monomial();

	Monomial& operator =(const Monomial&);
	Monomial& operator =(Monomial&&);

	Monomial& operator *=(const Monomial&);
	Monomial& operator /=(const Monomial&);

	bool operator <(const Monomial&);
	bool operator ==(const Monomial&);
	bool operator !=(const Monomial&);
	bool operator >(const Monomial&);

	double GetCoefficient() const;
	void SetCoefficient(double);

	friend std::ostream& operator <<(std::ostream&, const Monomial&);
	friend std::istream& operator >>(std::istream&, Monomial&);

    friend Monomial operator *(const Monomial&, const Monomial&);
    friend Monomial operator /(const Monomial&, const Monomial&);
};

#endif //INC_3_MONOMIAL_H