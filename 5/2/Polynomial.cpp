
#include "Polynomial.h"

PolynomialException::PolynomialException()
    :error(NULL)
{}

PolynomialException::PolynomialException(const char* errorName)
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

PolynomialException::PolynomialException(const PolynomialException& exception)
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

const char *PolynomialException::WhatException()
{
	return error;
}


Polynomial::Polynomial(int numberOfNodes, ...)
{
    if(numberOfNodes == 0)
    {
        AddNewNode(0);
    }
    else
    {
        va_list arguments;
        va_start(arguments, numberOfNodes);

        for (int i = 0; i < numberOfNodes; ++i)
        {
            AddNewNode(va_arg(arguments, double));
        }

        va_end(arguments);
    }
}

Polynomial::Polynomial(char *inputString)
{
	try
	{
		int buffNumber = 0;
		int lengthOfInput = strlen(inputString);
		char sign = '+';

		bool firstFound = false,
		     isPower = false,
		     started = false;

		int buffPower = 0,
		    currentPower = -1;

		head = new ListNode(0);
		head->SetNext(head);
        head->SetPrevious(head);
		size = 0;

		if (*inputString == 'x')
		{
            buffNumber = 1;
		}

		for (int i = 0; i < lengthOfInput + 1; ++i)
		{
			if (isspace(*inputString))
			{
				continue;
			}
			else if (*inputString == '\0' || *inputString == '-' || *inputString == '+' || *inputString == '^')
			{
			}
			else if (isdigit(*inputString))
			{
				if (isPower == true)
				{
                    buffPower *= 10;
                    buffPower += *inputString - '0';
				}
				else
				{
                    buffNumber *= 10;
                    buffNumber += *inputString - '0';
				}
			}
			else if (*inputString == 'x')
			{
				if (*(inputString + 1) == '^')
				{
					isPower = true;
				}
				else
				{
                    buffPower = 1;
				}
			}
			else
			{
				throw PolynomialException("Unexpected symbol");
			}

			if ((*inputString == '\0' || *inputString == '-' || *inputString == '+') && started)
			{
				if (firstFound == false)
				{
                    currentPower = buffPower + 1;
                    firstFound = true;
				}

				if (buffPower >= currentPower)
                {
				    throw PolynomialException("Wrong degree order");
                }

				while (currentPower - buffPower != 1)
				{
                    AddNewNode(0);
					currentPower--;
				}

				if (sign == '-')
                {
                    buffNumber *= -1;
                }

                AddNewNode(buffNumber);

                currentPower = buffPower;
                buffNumber = 0;
				isPower = false;
                buffPower = 0;
			}

			if (*inputString == '-' || *inputString == '+')
			{
				sign = *inputString;
				if (*(inputString + 1) == 'x')
				{
                    buffNumber = 1;
				}
			}

			started = true;
			++inputString;
		}

		while (currentPower != 0)
		{
            AddNewNode(0);
			--currentPower;
		}

	}
	catch (PolynomialException &exception)
	{
		std::cout << exception.WhatException() << std::endl;
		head = new ListNode(0);
		head->SetNext(head);
        head->SetPrevious(head);
		size = 0;
	}
}

Polynomial::Polynomial(const Polynomial &sourcePolynomial)
{
	ListNode* currentNode = sourcePolynomial.GetFirst();

	for (int i = 0; i < sourcePolynomial.size; ++i)
	{
        AddNewNode(currentNode->GetValue());
        currentNode = currentNode->GetNext();
	}
}

Polynomial::Polynomial(const Polynomial &polynomial, int begin, int end)
{
	if (begin < 0)
    {
	    begin = 0;
    }

	if (begin > polynomial.size - 1)
    {
	    begin = polynomial.size - 1;
    }

	if (end < 0)
    {
	    end = 0;
    }

	if (end > polynomial.size)
    {
	    end = polynomial.size;
    }

	ListNode *currentNode = &polynomial[begin];

	for (int i = begin; i < end; ++i)
	{
        AddNewNode(currentNode->GetValue());
        currentNode = currentNode->GetNext();
	}
}

Polynomial::Polynomial(Polynomial &&polynomial)
{
	delete head;

	size = polynomial.size;
	
	head = polynomial.head;

	polynomial.head = nullptr;
}


void Polynomial::InitClassFields()
{
	head = new ListNode(0);
	head->SetNext(head);
    head->SetPrevious(head);
	size = 0;
}


void Polynomial::RemoveClassFields()
{
	ListNode *currentNode = head->GetNext();
	while (currentNode != head)
	{
		ListNode *buff = currentNode;
        currentNode = currentNode->GetNext();
		delete buff;
	}

	delete head;
	head = nullptr;
	size = 0;
}

Polynomial::~Polynomial() {}


Polynomial& Polynomial::operator =(const Polynomial &polynomial)
{
    RemoveClassFields();
    InitClassFields();

	ListNode *currentNode = polynomial.GetFirst();

	for (int i = 0; i < polynomial.size; ++i)
	{
        AddNewNode(currentNode->GetValue());
        currentNode = currentNode->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator =(Polynomial &&polynomial)
{
    RemoveClassFields();

	size = polynomial.size;
	head = polynomial.head;

	polynomial.head = nullptr;

	return *this;
}


Polynomial& Polynomial::operator +=(const Polynomial &rightPolynomial)
{
	if (size == 0 && rightPolynomial.size == 0)
    {
	    return *this;
    }

	while(size < rightPolynomial.size)
	{
        AddNewNodeUp(0);
	}

	ListNode* currentNodeFromRightPol = rightPolynomial.GetFirst();
	ListNode* currentNodeFromLeftPol = GetFirst();
		
	for (int i = 0; i < size - rightPolynomial.size; ++i)
    {
        currentNodeFromLeftPol = currentNodeFromLeftPol->GetNext();
    }

	for (int i = 0; i < rightPolynomial.size; ++i)
	{
        currentNodeFromLeftPol->SetValue(currentNodeFromLeftPol->GetValue() + currentNodeFromRightPol->GetValue());

        currentNodeFromLeftPol = currentNodeFromLeftPol->GetNext();
        currentNodeFromRightPol = currentNodeFromRightPol->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator -=(const Polynomial &rightPolynomial)
{
	if (size == 0 && rightPolynomial.size == 0)
    {
	    return *this;
    }

	while (size < rightPolynomial.size)
	{
        AddNewNodeUp(0);
	}

	ListNode* currentNodeFromRightPol = rightPolynomial.GetFirst();
	ListNode* currentNodeFromLeftPol = GetFirst();

	for (int i = 0; i < size - rightPolynomial.size; ++i)
    {
        currentNodeFromLeftPol = currentNodeFromLeftPol->GetNext();
    }

	for (int i = 0; i < rightPolynomial.size; ++i)
	{
        currentNodeFromLeftPol->SetValue(currentNodeFromLeftPol->GetValue() - currentNodeFromRightPol->GetValue());

        currentNodeFromLeftPol = currentNodeFromLeftPol->GetNext();
        currentNodeFromRightPol = currentNodeFromRightPol->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator *=(const Polynomial &rightPolynomial)
{
	(*this) = KaratsubaAlgorithm(rightPolynomial);

	return *this;
}

Polynomial& Polynomial::operator /=(const Polynomial &rightPolynomial)
{
	if (rightPolynomial.size == 0)
	{
		throw PolynomialException("Division by zero");
	}

	Polynomial buffRight(rightPolynomial);
    KillZeroNodes();
    buffRight.KillZeroNodes();

	if (size < rightPolynomial.size)
	{
        RemoveClassFields();
        InitClassFields();
        AddNewNode(0);

		return *this;
	}

	Polynomial resultOfDivision;
	Polynomial minus;
	int zeros = size - buffRight.size;

	while (size >= buffRight.size)
	{
		double m = (*this)[0] / buffRight[0];

		minus = buffRight * m;

        minus.AddNumberOfNodeToEnd(minus.size + zeros);

        *this -= minus;

        KillZeroNodes();

		--zeros;

        resultOfDivision.AddNewNode(m);
	}

	(*this) = resultOfDivision;

	return *this;
}

Polynomial& Polynomial::operator %=(const Polynomial &rightPolynomial)
{
	if (rightPolynomial.size == 0)
	{
		throw PolynomialException("Empty Polynomial");
	}

	if (size < rightPolynomial.size)
	{
        RemoveClassFields();
        InitClassFields();
        AddNewNode(0);

		return *this;
	}

	Polynomial res;
	Polynomial minus;
	int zeros = size - rightPolynomial.size;

	while (size >= rightPolynomial.size)
	{
		double m = (*this)[0] / rightPolynomial[0];

		minus = rightPolynomial * m;

        minus.AddNumberOfNodeToEnd(minus.size + zeros);

        *(this) -= minus;

        KillZeroNodes();

		--zeros;
	}

	return *this;
}

Polynomial& Polynomial::operator *=(double number)
{
	ListNode *currentNode = GetFirst();

	for (int i = 0; i < size; ++i)
	{
        currentNode->SetValue(currentNode->GetValue() * number);

        currentNode = currentNode->GetNext();
	}

	return *this;
}

Polynomial& Polynomial::operator /=(double number)
{
	if (std::abs(number) < EPSILON)
	{
		throw PolynomialException("Division by zero error");
	}

	ListNode *currentNode = GetFirst();

	for (int i = 0; i < size; ++i)
	{
        currentNode->SetValue(currentNode->GetValue() / number);

        currentNode = currentNode->GetNext();
	}

	return *this;
}


std::ostream& operator<<(std::ostream &outputStream, const Polynomial &outpuPolynomial)
{
	outputStream << "Polynomial: ";

	ListNode *currentNode = outpuPolynomial.GetFirst();
	int size = outpuPolynomial.GetSize();

	for (int i = 0; i < size; ++i)
	{
		if (currentNode->GetValue() == 0)
		{
            currentNode = currentNode->GetNext();
		}
		else if (currentNode->GetValue() > 0)
		{
			std::cout << "+" << currentNode->GetValue() << "x^" << size - i - 1;
            currentNode = currentNode->GetNext();
		}
		else
		{
			std::cout << currentNode->GetValue() << "x^" << size - i - 1;
            currentNode = currentNode->GetNext();
		}
	}

	return outputStream;
}

std::istream& operator >>(std::istream &inputStream, Polynomial &newPolynomial)
{
	char buff[BUFSIZ];

	std::cin >> buff;

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

Polynomial operator /(const Polynomial &leftPolynomial, const Polynomial &rightPolynomial)
{
	Polynomial newPolynomial(leftPolynomial);

    newPolynomial /= rightPolynomial;

	return newPolynomial;
}

Polynomial operator%(const Polynomial &leftPolynomial, const Polynomial &rightPolynomial)
{
	Polynomial newPolynomial(leftPolynomial);

    newPolynomial %= rightPolynomial;

	return newPolynomial;
}


Polynomial operator *(const Polynomial &leftPolynomial, double number)
{
	Polynomial newPolynomial(leftPolynomial);

    newPolynomial *= number;

	return newPolynomial;
}

Polynomial operator /(const Polynomial &leftPolynomial, double number)
{
	Polynomial newPolynomial(leftPolynomial);

    newPolynomial /= number;

	return newPolynomial;
}


void Polynomial::AddNodesWhileNotEven()
{
	if (size & 1)
	{
        AddNewNodeUp(0);
	}
}

void Polynomial::AddNumberOfNodeInStart(int numberOfNodes)
{
	while (size < numberOfNodes)
	{
        AddNewNodeUp(0);
	}
}

void Polynomial::AddNumberOfNodeToEnd(int numberOfNodes)
{
	while (size < numberOfNodes)
	{
        AddNewNode(0);
	}
}

void Polynomial::KillZeroNodes()
{
	ListNode *currentNode = GetFirst();

	int n = size - 1;
	for (int i = 0; i < n; ++i)
	{
		if (currentNode->GetValue() != 0)
        {
		    break;
        }

        currentNode = currentNode->GetNext();
        DeleteFirstNode();
	}
}

Polynomial Polynomial::KaratsubaAlgorithm(const Polynomial &currentPolynomial) const
{
	if (size == 0 || currentPolynomial.size == 0)
	{
		throw PolynomialException("Empty Polynomial");
	}
	
	Polynomial multipleResult;

	if (size == 1 && currentPolynomial.size == 1)
	{
        multipleResult.AddNewNode((*this)[0] * currentPolynomial[0]);
		return multipleResult;
	}

	Polynomial X(*this);
	Polynomial Y(currentPolynomial);

    X.AddNodesWhileNotEven();
    Y.AddNodesWhileNotEven();

	const int maxOfVar = std::max(X.size, Y.size);

    X.AddNumberOfNodeInStart(maxOfVar);
    Y.AddNumberOfNodeInStart(maxOfVar);

	int k = maxOfVar / 2;

	Polynomial Xl(X, 0, k);
	Polynomial Xr(X, k, INT_MAX);
	Polynomial Yl(Y, 0, k);
	Polynomial Yr(Y, k, INT_MAX);

	Polynomial P1 = Xl.KaratsubaAlgorithm(Yl);
	Polynomial P2 = Xr.KaratsubaAlgorithm(Yr);
	Polynomial P3 = (Xr + Xl).KaratsubaAlgorithm(Yl + Yr);

	P3 -= P2;
	P3 -= P1;

    P1.AddNumberOfNodeToEnd(P1.size + maxOfVar);
    P3.AddNumberOfNodeToEnd(P3.size + k);

    multipleResult = P1 + P2 + P3;

	return multipleResult;
}

double Polynomial::SolvePolynomial(double X)
{
	if (size <= 0)
	{
		throw PolynomialException("Empty Polynomial");
	}

	double res = 0;

	ListNode *currentNode = GetLast()->GetPrevious();

	res += currentNode->GetValue();

    currentNode = currentNode->GetPrevious();

	for (int i = 1; i < size; ++i)
	{
		res += currentNode->GetValue() * X;
        currentNode = currentNode->GetPrevious();
        X *= X;
	}

	return res;
}

Polynomial Polynomial::Derivative()
{
	if (size <= 0)
	{
		throw PolynomialException("Empty Polynomial");
	}

	Polynomial derivative(*this);

	ListNode *currentNode = derivative.GetLast()->GetPrevious();

	for (int i = 0; i < size; ++i)
	{
        currentNode->SetValue(currentNode->GetValue() * i);
        currentNode = currentNode->GetPrevious();
	}

    derivative.DeleteLastNode();

	return derivative;
}