#pragma warning(disable:4996)
#include<iostream>

#include "ListForMonomial.h"

////////////////////////////////////////////////////////
//		Исключения
////////////////////////////////////////////////////////

ListForMonomialException::ListForMonomialException()
:error(NULL)
{}

ListForMonomialException::ListForMonomialException(const char *errorName)
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

ListForMonomialException::ListForMonomialException(const ListForMonomialException& exception)
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

ListForMonomialException::~ListForMonomialException()
{
	delete[] error;
}

const char* ListForMonomialException::WhatException()
{
	return error;
}


ListForMonomialItem::ListForMonomialItem() {}

ListForMonomialItem::ListForMonomialItem(const ListForMonomialItem &sourceNode)
{
	name = sourceNode.name;
	power = sourceNode.power;
}


ListForMonomialItem::ListForMonomialItem(ListForMonomialItem &&sourceNode)
{
	name = sourceNode.name;
	power = sourceNode.power;
}

ListForMonomialItem::ListForMonomialItem(char newName, int newPower)
{
	name = newName;
	power = newPower;

    previous = nullptr;
	next = nullptr;
}

ListForMonomialItem::~ListForMonomialItem()
{

}

ListForMonomialItem *ListForMonomialItem::GetPrevious() const
{
	return previous;
}

ListForMonomialItem *ListForMonomialItem::GetNext() const
{
	return next;
}

char ListForMonomialItem::GetName() const
{
	return name;
}

int ListForMonomialItem::GetPower() const
{
	return power;
}


void ListForMonomialItem::SetPrevious(ListForMonomialItem *newPrevious)
{
	if (newPrevious != nullptr)
    {
	    previous = newPrevious;
    }
}

void ListForMonomialItem::SetNext(ListForMonomialItem *newNext)
{
	if (newNext != nullptr)
    {
	    next = newNext;
    }
}

void ListForMonomialItem::SetName(char newName)
{
	name = newName;
}

void ListForMonomialItem::SetPower(int newPower)
{
	power = newPower;
}


ListForMonomialItem& ListForMonomialItem::operator *=(const ListForMonomialItem &rightNode)
{
	SetPower(GetPower() + rightNode.GetPower());
	return *this;
}

ListForMonomialItem& ListForMonomialItem::operator /=(const ListForMonomialItem &rightNode)
{
	SetPower(GetPower() - rightNode.GetPower());
	return *this;
}

std::ostream& operator<<(std::ostream &outputStream, const ListForMonomialItem &outputNode)
{
	outputStream << outputNode.GetName() << "^" << outputNode.GetPower();
	return outputStream;
}

std::istream& operator >>(std::istream &inputStream, ListForMonomialItem &newNode)
{
	char name;
	int power;
	inputStream >> name;
	inputStream >> power;
    newNode = ListForMonomialItem(name, power);
	return inputStream;
}

ListForMonomialItem& ListForMonomialItem::operator =(ListForMonomialItem &&sourceNode)
{
	name = sourceNode.name;
	power = sourceNode.power;

    sourceNode.name = '\0';
    sourceNode.power = 0;

	return *this;
}

ListForMonomialItem& ListForMonomialItem::operator =(const ListForMonomialItem &sourceNode)
{
	name = sourceNode.name;
	power = sourceNode.power;
	
	return *this;
}



ListForMonomial::ListForMonomial()
{
	head = new ListForMonomialItem('#', 0);
	head->SetNext(head);
    head->SetPrevious(head);
	size = 0;
}

ListForMonomial::ListForMonomial(const ListForMonomial &sourceList)
{
    CreateNewZeroList();
	ListForMonomialItem *currentNode = sourceList.GetFirst();

	for (int i = 0; i < sourceList.size; ++i)
	{
        InsertNewNode(currentNode->GetName(), currentNode->GetPower());
        currentNode = currentNode->GetNext();
	}
}

ListForMonomial::ListForMonomial(ListForMonomial &&sourceList)
{
	size = sourceList.size;
    head = sourceList.head;

    sourceList.size = 0;
    sourceList.head = nullptr;
}

ListForMonomial::~ListForMonomial()
{
	if (head != nullptr)
	{
		ListForMonomialItem *currentNode = head->GetNext();
		while (currentNode != head)
		{
			ListForMonomialItem *buff = currentNode;
            currentNode = currentNode->GetNext();
			delete buff;
		}
		delete head;

		head = nullptr;
		size = 0;
	}
}

void ListForMonomial::CreateNewZeroList()
{
    head = new ListForMonomialItem('#', 0);
    head->SetNext(head);
    head->SetPrevious(head);
    size = 0;
}

void ListForMonomial::DestroyNodes()
{
	if (head != nullptr)
	{
		ListForMonomialItem *currentNode = head->GetNext();
		while (currentNode != head)
		{
			ListForMonomialItem *buff = currentNode;
            currentNode = currentNode->GetNext();
			delete buff;
		}
		delete head;

		head = nullptr;
		size = 0;
	}
}

int ListForMonomial::GetSize() const
{
	return size;
}

void ListForMonomial::InsertNewNode(char newName, int newPower)
{
	ListForMonomialItem *currentNode = GetFirst();
	ListForMonomialItem *lastNode = GetLast();
	ListForMonomialItem *newNode = new ListForMonomialItem(newName, newPower);
	
	while (currentNode->GetName() < newName && currentNode != lastNode)
	{
        currentNode = currentNode->GetNext();
	}

	newNode->SetNext(currentNode);
    newNode->SetPrevious(currentNode->GetPrevious());
	ListForMonomialItem *previous = newNode->GetPrevious();
	previous->SetNext(newNode);
    currentNode->SetPrevious(newNode);

	++size;
}

void ListForMonomial::Delete(ListForMonomialItem *nodeToDelete)
{
	if (size == 0)
    {
	    return;
    }

	ListForMonomialItem *buff;

    buff = nodeToDelete->GetNext();
    buff->SetPrevious(nodeToDelete->GetPrevious());
	ListForMonomialItem *previous = nodeToDelete->GetPrevious();
	previous->SetNext(buff);

	size--;
	free(nodeToDelete);
}

ListForMonomialItem* ListForMonomial::GetFirst() const
{
	return head->GetNext();
}

ListForMonomialItem* ListForMonomial::GetLast() const
{
	return head;
}

ListForMonomialItem& ListForMonomial::operator[](int index) const
{
	if (index < 0 || index >= size)
    {
	    throw ListForMonomialException("Out of range []");
    }

	ListForMonomialItem *currentNode = GetFirst();

	for (int i = 0; i < index; ++i)
	{
        currentNode = currentNode->GetNext();
	}

	return *currentNode;
}

std::ostream& operator <<(std::ostream &outputStream, const ListForMonomial &outputList)
{
	ListForMonomialItem *currentNode = outputList.GetFirst();

	for (int i = 0; i < outputList.size; ++i)
	{
		outputStream << currentNode;
        currentNode = currentNode->GetNext();
	}

	return outputStream;
}
