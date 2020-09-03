#pragma warning(disable:4996)
#include<iostream>
#include<stdarg.h>
#include<cstring>
#include<algorithm>

#include "Polynomial.h"

#define DEBUGj

////////////////////////////////////////////////////////
//		Исключения
////////////////////////////////////////////////////////

PolynomialException::PolynomialException()
    :error(nullptr)
{}

PolynomialException::PolynomialException(const char *errorName)
{
	if (errorName != nullptr)
	{
		error = new char[strlen(errorName) + 1];
		strcpy(error, errorName);
	}
	else
	{
		error = nullptr;
	}
}

PolynomialException::PolynomialException(const PolynomialException &exception)
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

PolynomialException::~PolynomialException()
{
    delete[] error;
}

const char* PolynomialException::WhatException()
{
	return error;
}


Polynomial::Polynomial() {}

Polynomial::Polynomial(const char *inputString)
{
	char *buff = new char[strlen(inputString) + 1];

	strcpy(buff, inputString);
	char *currentChar = buff;

	try
	{
		char *nextChar = currentChar;

		while (*currentChar != '\0' && *currentChar != '\n')
		{
			while (*nextChar != '\0' && *nextChar != '\n' && *nextChar != '+' && *nextChar != '-')
			{
				++nextChar;
			}

			if (*currentChar == '!')
			{
				*currentChar = '+';
			}
			if (*currentChar == '?')
			{
				*currentChar = '-';
			}

			if (*nextChar == '+' || *nextChar == '!')
			{
				*nextChar = '\0';
				ListForPolynomialNode newNode(currentChar);


                currentChar = nextChar;
                InsertNewNode(newNode);
				*nextChar = '!';
			}
			else if (*nextChar == '-' || *nextChar == '?')
			{
				*nextChar = '\0';
				ListForPolynomialNode newNode(currentChar);

                currentChar = nextChar;
                InsertNewNode(newNode);
				*nextChar = '?';
			}
			else
			{
				ListForPolynomialNode newNode(currentChar);

                currentChar = nextChar;
                InsertNewNode(newNode);
			}
		}

		delete[] buff;
	}
	catch (PolynomialException &exception)
	{
		std::cout << exception.WhatException() << std::endl;
		head = new ListForPolynomialNode();
		head->SetNext(head);
        head->SetPrevious(head);
		size = 0;

		delete[] buff;
	}
}

Polynomial::Polynomial(const Polynomial &sourcePolynomial)
{
	ListForPolynomialNode *currentNode = sourcePolynomial.GetFirst();

	for (int i = 0; i < sourcePolynomial.size; ++i)
	{
        InsertNewNode(*currentNode);
        currentNode = currentNode->GetNext();
	}
}

Polynomial::Polynomial(Polynomial &&sourcePolynomial)
{
	delete head;

	size = sourcePolynomial.size;
	head = sourcePolynomial.head;

    sourcePolynomial.head = nullptr;
}


void Polynomial::CreateNewZeroNode()
{
	head = new ListForPolynomialNode();
	head->SetNext(head);
    head->SetPrevious(head);
	size = 0;
}

void Polynomial::DestructPolynomial()
{
	ListForPolynomialNode *currentNode = head->GetNext();

	while (currentNode != head)
	{
		ListForPolynomialNode *buff = currentNode;
        currentNode = currentNode->GetNext();
		delete buff;
	}

	delete head;

	head = nullptr;
	size = 0;
}

Polynomial::~Polynomial() {}


Polynomial& Polynomial::operator =(const Polynomial &rightPolynomial)
{
	if (&rightPolynomial == this)
	{
		return *this;
	}

    DestructPolynomial();
    CreateNewZeroNode();

	ListForPolynomialNode *currentNode = rightPolynomial.GetFirst();

	for (int i = 0; i < rightPolynomial.size; ++i)
	{
        InsertNewNode(*currentNode);
        currentNode = currentNode->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator =(Polynomial &&rightPolynomial)
{
	if (&rightPolynomial == this)
	{
		return *this;
	}

    DestructPolynomial();

	size = rightPolynomial.size;
	head = rightPolynomial.head;

    rightPolynomial.head = nullptr;

	return *this;
}


Polynomial& Polynomial::operator +=(const Polynomial &rightPolynomial)
{
	if (size == 0 && rightPolynomial.size == 0)
    {
	    return *this;
    }

	ListForPolynomialNode *currentNode = rightPolynomial.GetFirst();

	for (int i = 0; i < rightPolynomial.size; ++i)
	{
        InsertNewNode(*currentNode);
        currentNode = currentNode->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator -=(const Polynomial &rightPolynomial)
{
	if (size == 0 && rightPolynomial.size == 0)
    {
	    return *this;
    }

	ListForPolynomialNode *currentNode = rightPolynomial.GetFirst();

	for (int i = 0; i < rightPolynomial.size; ++i)
	{
        InsertNewNode(*currentNode, -1);
        currentNode = currentNode->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator *=(const Polynomial &rightPolynomial)
{
	if (size == 0 && rightPolynomial.size == 0)
    {
	    return *this;
    }

	Polynomial newPolynomial;

	ListForPolynomialNode *currentOldNode = rightPolynomial.GetFirst();
	int n = rightPolynomial.size;

	for (int i = 0; i < n; ++i)
	{
		Polynomial newBuffPol = (*this) * (*currentOldNode);

		ListForPolynomialNode *currentNodeFromNewPol = newBuffPol.GetFirst();

		for (int j = 0; j < newBuffPol.size; ++j)
		{
            newPolynomial.InsertNewNode(*currentNodeFromNewPol);
            currentNodeFromNewPol = currentNodeFromNewPol->GetNext();
		}

        currentOldNode = currentOldNode->GetNext();
	}

	(*this) = newPolynomial;

	return *this;
}

bool Polynomial::operator ==(const Polynomial &rightPolynomial)
{
	if (size == 0 && rightPolynomial.size == 0)
	{
		return true;
	}
	if (size == 0)
	{
		return false;
	}
	if (rightPolynomial.size == 0)
	{
		return false;
	}
	if (size != rightPolynomial.size)
	{
		return false;
	}

	ListForPolynomialNode *currentLeftNode = GetFirst();
	ListForPolynomialNode *currentRightNode = rightPolynomial.GetFirst();

	for (int i = 0; i < size; ++i)
	{
		if (*currentLeftNode != *currentRightNode)
		{
			return false;
		}

        currentLeftNode = currentLeftNode->GetNext();
        currentRightNode = currentRightNode->GetNext();
	}

	return true;
}

bool Polynomial::operator !=(const Polynomial &rightPolynomial)
{
    return !((*this) == rightPolynomial);
}


std::ostream& operator <<(std::ostream &outputStream, const Polynomial &outputPolynomial)
{
	outputStream << "Polynomial: ";

	if (outputPolynomial.size == 0)
	{
		outputStream << 0;
		return outputStream;
	}

	ListForPolynomialNode *currentNode = outputPolynomial.GetFirst();

	for (int i = 0; i < outputPolynomial.GetSize(); ++i)
	{
	    if (currentNode->GetCoefficient() > 0)
		{
			std::cout << "+" << *currentNode;
            currentNode = currentNode->GetNext();
		}
		else
		{
			std::cout << *currentNode;
            currentNode = currentNode->GetNext();
		}
	}
	return outputStream;
}

std::istream& operator >>(std::istream &inputStream, Polynomial &newPolynomial)
{
	char buff[BUFSIZ];

	inputStream >> buff;
    newPolynomial = Polynomial(buff);

	return inputStream;
}


Polynomial operator +(const Polynomial &leftPolynomial, const Polynomial &rightPolynomial)
{
	Polynomial newPolynomial(leftPolynomial);
    newPolynomial += rightPolynomial;
	
	return newPolynomial;
}

Polynomial operator -(const Polynomial &leftPolynomial, const Polynomial &rightPolynomial)
{
	Polynomial newPolynomial(leftPolynomial);
    newPolynomial -= rightPolynomial;

	return newPolynomial;
}

Polynomial operator *(const Polynomial &leftPolynomial, const Polynomial &rightPolynomial)
{
	Polynomial newPolynomial(leftPolynomial);
    newPolynomial *= rightPolynomial;

	return newPolynomial;
}

Polynomial operator *(const Polynomial &leftPolynomial, const ListForPolynomialNode &rightNode)
{
	Polynomial newPolynomial(leftPolynomial);

	ListForPolynomialNode* item = newPolynomial.GetFirst();

	for (int i = 0; i < newPolynomial.size; ++i)
	{
		*item *= rightNode;
		item = item->GetNext();
	}

	return newPolynomial;
}
