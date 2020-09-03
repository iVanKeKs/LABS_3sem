
#include "List.h"

ListException::ListException()
    :error(NULL)
{}

ListException::ListException(const char* errorName)
{
	if (errorName)
	{
		error = new char[strlen(errorName) + 1];
		strcpy(error, errorName);
	}
	else
	{
		error = nullptr;
	}
}

ListException::ListException(const ListException& exception)
{
	if (exception.error)
	{
		error = new char[strlen(exception.error) + 1];
		strcpy(error, exception.error);
	}
	else
	{
		error = nullptr;
	}
}

ListException::~ListException()
{
	delete[] error;
}

const char *ListException::WhatException()
{
	return error;
}


ListNode::ListNode() {}

ListNode::ListNode(double newValue)
{
	data = newValue;
	prev = nullptr;
	next = nullptr;
}

ListNode::~ListNode() {}

ListNode* ListNode::GetPrevious() const
{
	return prev;
}

ListNode* ListNode::GetNext() const
{
	return next;
}

double ListNode::GetValue() const
{
	return data;
}

void ListNode::SetPrevious(ListNode* newPreviousList)
{
    prev = newPreviousList;
}

void ListNode::SetNext(ListNode* newNextList)
{
    next = newNextList;
}

void ListNode::SetValue(double newValue)
{
	data = newValue;
}


ListNode& ListNode::operator =(double newValue)
{
    SetValue(newValue);
	return *this;
}

ListNode& ListNode::operator +=(const ListNode &secondNode)
{
    SetValue(GetValue() + secondNode.GetValue());
	return *this;
}

ListNode& ListNode::operator +=(double number)
{
    SetValue(GetValue() + number);
    return *this;
}

ListNode& ListNode::operator -=(const ListNode &secondNode)
{
    SetValue(GetValue() - secondNode.GetValue());
	return *this;
}

ListNode& ListNode::operator -=(double number)
{
    SetValue(GetValue() - number);
    return *this;
}

ListNode& ListNode::operator *=(const ListNode &secondNode)
{
    SetValue(GetValue() * secondNode.GetValue());
	return *this;
}

ListNode& ListNode::operator *=(double number)
{
    SetValue(GetValue() * number);
    return *this;
}

ListNode& ListNode::operator /=(const ListNode &secondNode)
{
	if (secondNode.GetValue() == 0)
	{
		throw ListException("Division by zero error");
	}

    SetValue(GetValue() / secondNode.GetValue());
	return *this;
}

ListNode& ListNode::operator /=(double number)
{
	if (std::abs(number) < EPSILON)
	{
		throw ListException("Division by zero error");
	}

    SetValue(GetValue() / number);
	return *this;
}

std::ostream& operator <<(std::ostream &outputStream, const ListNode& outputNode)
{
	outputStream << outputNode.GetValue();

	return outputStream;
}

double operator +(const ListNode &leftNode, const ListNode &rightNode)
{
	return leftNode.GetValue() + rightNode.GetValue();
}

double operator -(const ListNode &leftNode, const ListNode &rightNode)
{
	return leftNode.GetValue() - rightNode.GetValue();
}

double operator *(const ListNode &leftNode, const ListNode &rightNode)
{
	return leftNode.GetValue() * rightNode.GetValue();
}

double operator /(const ListNode &leftNode, const ListNode &rightNode)
{
	if (std::abs(rightNode.GetValue()) < EPSILON)
	{
		throw ListException("Division by zero error");
	}

	return leftNode.GetValue() / rightNode.GetValue();
}


List::List()
{
	head = new ListNode(0);
	head->SetNext(head);
    head->SetPrevious(head);
	size = 0;
}

List::~List()
{
	if (head != nullptr)
	{
		ListNode *currentNode = head->GetNext();
		while (currentNode != head)
		{
			ListNode *buff = currentNode;
            currentNode = currentNode->GetNext();
			delete buff;
		}

	}

    delete head;
    head = nullptr;
    size = 0;
}

int List::GetSize() const
{
	return size;
}

void List::AddNewNode(double value)
{
	ListNode *buff = GetLast();
	ListNode *newNode = new ListNode(value);

	newNode->SetNext(buff);
    newNode->SetPrevious(buff->GetPrevious());

    ListNode* previous = newNode->GetPrevious();
	previous->SetNext(newNode);
    buff->SetPrevious(newNode);

	++size;
}

void List::AddNewNodeUp(double value)
{
	ListNode *buff = GetFirst();
	ListNode *newNode = new ListNode(value);

	newNode->SetNext(buff);
    newNode->SetPrevious(buff->GetPrevious());

    ListNode *previous = newNode->GetPrevious();
	previous->SetNext(newNode);
    buff->SetPrevious(newNode);

	++size;
}

void List::DeleteFirstNode()
{
	if (size <= 0)
    {
	    return;
    }

	ListNode *nodeToDelete = GetFirst();
	ListNode *buff;

    buff = nodeToDelete->GetNext();
    buff->SetPrevious(nodeToDelete->GetPrevious());

    ListNode *previous = nodeToDelete->GetPrevious();
	previous->SetNext(buff);

	--size;
	free(nodeToDelete);
}

void List::DeleteLastNode()
{
	if (size <= 0)
    {
	    return;
    }

	ListNode* nodeToDelete = GetLast()->GetPrevious();
	ListNode* buff;

    buff = nodeToDelete->GetNext();
    buff->SetPrevious(nodeToDelete->GetPrevious());

    ListNode* prev = nodeToDelete->GetPrevious();
	prev->SetNext(buff);

	--size;
	free(nodeToDelete);
}


ListNode* List::GetFirst() const
{
	return head->GetNext();
}

ListNode* List::GetLast() const
{
	return head;
}

ListNode& List::operator [](int numberOfNode) const
{
	if (numberOfNode < 0 || numberOfNode >= size)
    {
        throw ListException("Out of range");
    }

	ListNode *currentNode = GetFirst();

	for (int i = 0; i < numberOfNode; ++i)
	{
        currentNode = currentNode->GetNext();
	}

	return *currentNode;
}

std::ostream& operator <<(std::ostream &outputStream, const List &listHead)
{
	outputStream << "List: ";

	ListNode* currentNode = listHead.GetFirst();

	for (int i = 0; i < listHead.size; ++i)
	{
		std::cout << currentNode->GetValue() << " ";
        currentNode = currentNode->GetNext();
	}

	return outputStream;
}
