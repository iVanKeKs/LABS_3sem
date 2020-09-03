
#include "ListForPolynomial.h"


ListForPolynomialException::ListForPolynomialException()
:error(NULL)
{}

ListForPolynomialException::ListForPolynomialException(const char *errorName)
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

ListForPolynomialException::ListForPolynomialException(const ListForPolynomialException &exception)
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

ListForPolynomialException::~ListForPolynomialException()
{
    delete[] error;
}

const char *ListForPolynomialException::WhatException()
{
	return error;
}


ListForPolynomialNode::ListForPolynomialNode() : Monomial()
{
    previous = nullptr;
	next = nullptr;
}

ListForPolynomialNode::ListForPolynomialNode(char *inputString) : Monomial(inputString)
{
    previous = nullptr;
	next = nullptr;
}

ListForPolynomialNode::ListForPolynomialNode(const ListForPolynomialNode &sourceNode) : Monomial(sourceNode)
{
    previous = nullptr;
	next = nullptr;
}

ListForPolynomialNode::ListForPolynomialNode(ListForPolynomialNode &&sourceNode) : Monomial(sourceNode)
{
    previous = nullptr;
	next = nullptr;
}

ListForPolynomialNode::~ListForPolynomialNode() {}

ListForPolynomialNode* ListForPolynomialNode::GetPrevious() const
{
	return previous;
}

ListForPolynomialNode* ListForPolynomialNode::GetNext() const
{
	return next;
}

void ListForPolynomialNode::SetPrevious(ListForPolynomialNode *newNode)
{
	if (newNode != nullptr)
    {
	    previous = newNode;
    }
}

void ListForPolynomialNode::SetNext(ListForPolynomialNode* newNode)
{
	if (newNode != nullptr)
    {
	    next = newNode;
    }
}


ListForPolynomial::ListForPolynomial()
{
	head = new ListForPolynomialNode();
	head->SetNext(head);
    head->SetPrevious(head);
	size = 0;
}

ListForPolynomial::~ListForPolynomial()
{
	if (head != nullptr)
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
}

int ListForPolynomial::GetSize() const
{
	return size;
}

void ListForPolynomial::InsertNewNode(ListForPolynomialNode &newNode, int mode)
{

	ListForPolynomialNode *currentNode = GetFirst();
	ListForPolynomialNode *lastNode = GetLast();
	ListForPolynomialNode *resultNode = new ListForPolynomialNode(newNode);
	
	if (size != 0)
	{
		while ((*currentNode < newNode) && currentNode != lastNode)
		{
            currentNode = currentNode->GetNext();
		}

		if (*currentNode == newNode)
		{
            currentNode->SetCoefficient(currentNode->GetCoefficient() + (mode * newNode.GetCoefficient()));

			if (std::abs(currentNode->GetCoefficient()) < EPSILON)
			{
                DeleteNode(currentNode);
			}
			return;
		}

	}

    resultNode->SetCoefficient(resultNode->GetCoefficient() * mode);

	resultNode->SetNext(currentNode);
    resultNode->SetPrevious(currentNode->GetPrevious());
	ListForPolynomialNode *previous = resultNode->GetPrevious();
    previous->SetNext(resultNode);
    currentNode->SetPrevious(resultNode);

	++size;
}


void ListForPolynomial::DeleteNode(ListForPolynomialNode *deletingNode)
{
	if (size == 0)
    {
	    return;
    }

	ListForPolynomialNode *buff;

    buff = deletingNode->GetNext();
    buff->SetPrevious(deletingNode->GetPrevious());
	ListForPolynomialNode *previous = deletingNode->GetPrevious();
    previous->SetNext(buff);

	--size;
	free(deletingNode);
}

ListForPolynomialNode *ListForPolynomial::GetFirst() const
{
	return head->GetNext();
}

ListForPolynomialNode *ListForPolynomial::GetLast() const
{
	return head;
}

ListForPolynomialNode& ListForPolynomial::operator[](int index) const
{
	if (index < 0 || index >= size)
    {
	    throw ListForPolynomialException("Out of range");
    }

	ListForPolynomialNode *currentNode = GetFirst();

	for (int i = 0; i != index; ++i)
	{
        currentNode = currentNode->GetNext();
	}

	return *currentNode;
}
