
#ifndef INC_3_LISTFORPOLYNOMIAL_H
#define INC_3_LISTFORPOLYNOMIAL_H

#include<iostream>
#include<algorithm>

#include "Monomial.h"


class ListForPolynomialException
{
private:

	char *error;
	ListForPolynomialException();

public:

	ListForPolynomialException(const char*);
	ListForPolynomialException(const ListForPolynomialException&);
	~ListForPolynomialException();

	const char *WhatException();
};


class ListForPolynomialNode : public Monomial
{
private:

	ListForPolynomialNode *previous;
	ListForPolynomialNode *next;

	ListForPolynomialNode& operator =(ListForPolynomialNode&&);
	ListForPolynomialNode& operator =(const ListForPolynomialNode&);

public:

	ListForPolynomialNode();
	ListForPolynomialNode(char*);
	ListForPolynomialNode(const ListForPolynomialNode&);
	ListForPolynomialNode(ListForPolynomialNode&&);

	~ListForPolynomialNode();

	ListForPolynomialNode *GetPrevious() const;
	ListForPolynomialNode *GetNext() const;
	void SetPrevious(ListForPolynomialNode *newNode);
	void SetNext(ListForPolynomialNode*);
};


class ListForPolynomial
{
protected:

	ListForPolynomialNode *head;
	int size;

	ListForPolynomialNode *GetFirst() const;
	ListForPolynomialNode *GetLast() const;
	ListForPolynomial();
	ListForPolynomial(const ListForPolynomial&);
	ListForPolynomial(const ListForPolynomial&&);

public:
	
	~ListForPolynomial();

	int GetSize() const;
	void InsertNewNode(ListForPolynomialNode &newNode, int mode = 1);
	void DeleteNode(ListForPolynomialNode *deletingNode);

	ListForPolynomialNode& operator[](int) const;
};

#endif //INC_3_LISTFORPOLYNOMIAL_H