#pragma warning(disable:4996)
#include<iostream>
#include<algorithm>

#include "ListForMonomial.h"

#include "Monomial.h"


MonomialException::MonomialException()
    :error(NULL)
{}

MonomialException::MonomialException(const char *errorName)
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

MonomialException::MonomialException(const MonomialException &exception)
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

MonomialException::~MonomialException()
{
	delete[] error;
}

const char* MonomialException::WhatException()
{
	return error;
}


Monomial::Monomial() : ListForMonomial()
{
    coefficient = 0;
}

Monomial::Monomial(char *inputString) : ListForMonomial()
{
	try
	{
        coefficient = 0;
		bool isPlus = true;
		int power = 0;
		char name = '#';

		if (*inputString == '-')
		{
            isPlus = false;
			++inputString;
		}
		if (*inputString == '+')
		{
			++inputString;
		}

		if (isalpha(*inputString))
		{
            coefficient = 1;
		}
		else
		{
			while (!isalpha(*inputString) && *inputString != '\0' && *inputString != '\n' &&
			       *inputString != '+' && *inputString != '-')
			{
				if (isspace(*inputString))
				{
					++inputString;
					continue;
				}

				if (isdigit(*inputString))
				{
                    coefficient *= 10;
                    coefficient += *inputString - '0';
					++inputString;
				}
				else
				{
					throw MonomialException("Unexpected symbol");
				}
			}
		}

		if (isPlus == false)
		{
            coefficient *= -1;
		}

		while (*inputString != '\0' && *inputString != '\n'
		       && *inputString != '+' && *inputString != '-')
		{
			if (isspace(*inputString) || *inputString == '^')
			{
				++inputString;
				continue;
			}
			else if (isdigit(*inputString))
			{
				power *= 10;
				power += *inputString - '0';
				++inputString;
			}
			else if (isalpha(*inputString))
			{
				if (power != 0 && name != '#')
				{
                    InsertNewNode(name, power);
					power = 0;
					name = '#';
				}
				else
				{
					power = 0;
					name = '#';
				}

				name = *inputString;
				++inputString;
			}
			else
			{
				throw MonomialException("Unexpected symbol");
			}

			if (power != 0 && name != '#')
			{
                InsertNewNode(name, power);
				power = 0;
				name = '#';
			}
		}
	}
	catch (MonomialException &Ex)
	{
		std::cout << Ex.WhatException() << std::endl;
		head = new ListForMonomialItem('#', 0);
		head->SetNext(head);
        head->SetPrevious(head);
		size = 0;
	}
}

Monomial::Monomial(const Monomial &sourceMonomial) : ListForMonomial(sourceMonomial)
{
    coefficient = sourceMonomial.coefficient;
}

Monomial::Monomial(Monomial &&sourceMonomial) : ListForMonomial(sourceMonomial)
{
    coefficient = sourceMonomial.coefficient;
}


Monomial::~Monomial()
{

}


Monomial& Monomial::operator =(const Monomial &rightMonomial)
{
    DestroyNodes();
    CreateNewZeroList();

	ListForMonomialItem *currentNode = rightMonomial.GetFirst();

	for (int i = 0; i < rightMonomial.size; ++i)
	{
        InsertNewNode(currentNode->GetName(), currentNode->GetPower());
        currentNode = currentNode->GetNext();
	}

    coefficient = rightMonomial.coefficient;

	return *this;
}

Monomial& Monomial::operator =(Monomial &&leftMonomial)
{
    DestroyNodes();
    CreateNewZeroList();

	size = leftMonomial.size;
    leftMonomial.size = 0;

	head = leftMonomial.head;
    leftMonomial.head = nullptr;

    coefficient = leftMonomial.coefficient;

	return *this;
}

bool Monomial::operator <(const Monomial &rightMonomial)
{
	if (size == 0 && rightMonomial.size == 0)
	{
		return false;
	}
	if (size == 0)
	{
		return true;
	}
	if (rightMonomial.size == 0)
	{
		return false;
	}

	int maxSizeOfTwo = std::max(size, rightMonomial.size);

	ListForMonomialItem *currentNode = GetFirst();
	ListForMonomialItem *currentLeftNode = rightMonomial.GetFirst();

	for (int i = 0; i < maxSizeOfTwo; ++i)
	{
		if (currentNode->GetName() < currentLeftNode->GetName())
		{
			return true;
		}
		else if (currentNode->GetName() > currentLeftNode->GetName())
		{
			return false;
		}

		if (currentNode->GetPower() < currentLeftNode->GetPower())
		{
			return true;
		}
		else if (currentNode->GetPower() > currentLeftNode->GetPower())
		{
			return false;
		}

        currentNode = currentNode->GetNext();
        currentLeftNode = currentLeftNode->GetNext();
	}

	return false;
}

bool Monomial::operator ==(const Monomial &rightMonomial)
{
	if (size == 0 && rightMonomial.size == 0)
	{
		return true;
	}
	if (size == 0)
	{
		return false;
	}
	if (rightMonomial.size == 0)
	{
		return false;
	}
	if (size != rightMonomial.size)
	{
		return false;
	}

	ListForMonomialItem* currentNode = GetFirst();
	ListForMonomialItem* currentLeftNode = rightMonomial.GetFirst();

	for (int i = 0; i < size; ++i)
	{
		if (currentNode->GetName() != currentLeftNode->GetName())
		{
			return false;
		}

		if (currentNode->GetPower() != currentLeftNode->GetPower())
		{
			return false;
		}

        currentNode = currentNode->GetNext();
        currentLeftNode = currentLeftNode->GetNext();
	}

	return true;
}

bool Monomial::operator >(const Monomial &rightMonomial)
{
    return !((*this) < rightMonomial) && !((*this) == rightMonomial);
}

bool Monomial::operator !=(const Monomial &rightMonomial)
{
	return !((*this) == rightMonomial);
}

Monomial& Monomial::operator *=(const Monomial &rightMonomial)
{
	if (&rightMonomial == this)
	{
		ListForMonomialItem* currentNode = GetFirst();
		for (int i = 0; i < size; ++i)
		{
			currentNode->SetPower(currentNode->GetPower() * 2);
            currentNode = currentNode->GetNext();
		}
        coefficient *= coefficient;
		return *this;
	}

	ListForMonomialItem *currentNodeFromFirst = GetFirst();
	ListForMonomialItem *currentNodeFromLast = GetLast();
	ListForMonomialItem *currentRightMonomial = rightMonomial.GetFirst();

    coefficient *= rightMonomial.coefficient;

	for (int i = 0; i < rightMonomial.size; ++i)
	{
		while(true)
		{
			if (currentNodeFromFirst == currentNodeFromLast)
			{
                InsertNewNode(currentRightMonomial->GetName(), currentRightMonomial->GetPower());
				break;
			}

			if (currentNodeFromFirst->GetName() == currentRightMonomial->GetName())
			{
				(*currentNodeFromFirst) *= (*currentRightMonomial);
				if (currentNodeFromFirst->GetPower() == 0)
				{
					Delete(currentNodeFromFirst);
				}
                currentNodeFromFirst = currentNodeFromFirst->GetNext();
				break;
			}

			if (currentNodeFromFirst->GetName() > currentRightMonomial->GetName() && currentNodeFromFirst->GetName() != currentRightMonomial->GetName())
			{
                InsertNewNode(currentRightMonomial->GetName(), currentRightMonomial->GetPower());
				break;
			}
            currentNodeFromFirst = currentNodeFromFirst->GetNext();
		}

        currentRightMonomial = currentRightMonomial->GetNext();
	}

	return *this;
}

Monomial& Monomial::operator /=(const Monomial &rightMonomial)
{
	if (&rightMonomial == this)
	{
        DestroyNodes();
        CreateNewZeroList();
        coefficient = 1;
		return *this;
	}

	ListForMonomialItem *currentNodeFromFirst = GetFirst();
	ListForMonomialItem *currentNodeFromLast = GetLast();
	ListForMonomialItem *currentRightMonomial = rightMonomial.GetFirst();

    coefficient /= rightMonomial.coefficient;

	for (int i = 0; i < rightMonomial.size; ++i)
	{
		while (true)
		{
			if (currentNodeFromFirst == currentNodeFromLast)
			{
                InsertNewNode(currentRightMonomial->GetName(), -1 * currentRightMonomial->GetPower());
				break;
			}
			else if (currentNodeFromFirst->GetName() == currentRightMonomial->GetName())
			{
				(*currentNodeFromFirst) /= (*currentRightMonomial);
				if (currentNodeFromFirst->GetPower() == 0)
				{
                    currentNodeFromFirst = currentNodeFromFirst->GetPrevious();
					Delete(currentNodeFromFirst->GetNext());
				}
                currentNodeFromFirst = currentNodeFromFirst->GetNext();
				break;
			}
			else if (currentNodeFromFirst->GetName() > currentRightMonomial->GetName() && currentNodeFromFirst->GetName() != currentRightMonomial->GetName())
			{
                InsertNewNode(currentRightMonomial->GetName(), -1 * currentRightMonomial->GetPower());
				break;
			}
            currentNodeFromFirst = currentNodeFromFirst->GetNext();
		}

        currentRightMonomial = currentRightMonomial->GetNext();
	}

	return *this;
}

std::ostream& operator <<(std::ostream &outputStream, const Monomial &outputMonomial)
{
	outputStream << outputMonomial.coefficient;

	if (outputMonomial.size == 0)
	{
		return outputStream;
	}

	ListForMonomialItem *currentNode = outputMonomial.GetFirst();

	for (int i = 0; i < outputMonomial.size; ++i)
	{
		outputStream << *currentNode;
        currentNode = currentNode->GetNext();
	}

	return outputStream;
}

std::istream& operator >>(std::istream &inputStream, Monomial &inputMonomial)
{
	static char buff[BUFSIZ];

	inputStream >> buff;
    inputMonomial = Monomial(buff);

	return inputStream;
}


Monomial operator *(const Monomial &leftMonomial, const Monomial &rightMonomial)
{
	Monomial newMonomial(leftMonomial);
    newMonomial *= rightMonomial;
	return newMonomial;
}

Monomial operator /(const Monomial &leftMonomial, const Monomial &rightMonomial)
{
	Monomial newMonomial(leftMonomial);
    newMonomial /= rightMonomial;
	return newMonomial;
}


double Monomial::GetCoefficient() const
{
	return coefficient;
}

void Monomial::SetCoefficient(double newValue)
{
    coefficient = newValue;
}