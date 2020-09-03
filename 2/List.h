
#ifndef INC_2_LIST_H
#define INC_2_LIST_H

#include <iostream>
#include <cstring>

#define EPSILON 0.00000000001

class ListException
{
private:

	char *error;
	ListException();

public:

	ListException(const char*);
	ListException(const ListException&);
	~ListException();

	const char* WhatException();
};


class ListNode
{
private:

    double data;
	ListNode *prev;
	ListNode *next;
	
	ListNode();
	ListNode(ListNode&);
	ListNode(ListNode&&);
	
	ListNode& operator =(ListNode&&);
	ListNode& operator =(const ListNode&);

public:

	explicit ListNode(double);
	~ListNode();

	ListNode& operator =(double);

	ListNode& operator +=(const ListNode&);
    ListNode& operator +=(double);
    ListNode& operator -=(const ListNode&);
    ListNode& operator -=(double);
    ListNode& operator *=(const ListNode&);
    ListNode& operator *=(double);
    ListNode& operator /=(const ListNode&);
	ListNode& operator /=(double);

	friend std::ostream& operator <<(std::ostream&, const ListNode&);

    ListNode *GetNext() const;
    ListNode *GetPrevious() const;
    double GetValue() const;

    void SetNext(ListNode *);
    void SetPrevious(ListNode *newPreviousList);
	void SetValue(double);
};

double operator +(const ListNode&, const ListNode&);
double operator -(const ListNode&, const ListNode&);
double operator *(const ListNode&, const ListNode&);
double operator /(const ListNode&, const ListNode&);


class List
{
protected:

	ListNode *head;
	int size;

	List();
	List(const List&);
	List(const List&&);

    ListNode *GetFirst() const;
    ListNode *GetLast() const;

public:
	
	~List();

	int GetSize() const;
	void AddNewNode(double);
	void AddNewNodeUp(double);
	void DeleteFirstNode();
	void DeleteLastNode();

	ListNode& operator[](int) const;

	friend std::ostream& operator <<(std::ostream&, const List&);
};

#endif //INC_2_LIST_H