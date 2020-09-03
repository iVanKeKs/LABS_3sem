
#ifndef INC_3_LISTFORMONOMIAL_H
#define INC_3_LISTFORMONOMIAL_H

#define EPSILON 0.00000000001

#include <cstring>

class ListForMonomialException
{
private:
	char* error;
	ListForMonomialException();


public:
	ListForMonomialException(const char*);
	ListForMonomialException(const ListForMonomialException&);
	~ListForMonomialException();

	const char* WhatException();
};


class ListForMonomialItem
{
private:

	char name;
	int power;
	ListForMonomialItem* previous;
	ListForMonomialItem* next;
	
	ListForMonomialItem();
	ListForMonomialItem(const ListForMonomialItem&);
	ListForMonomialItem(ListForMonomialItem&&);
	
	

public:
	ListForMonomialItem& operator =(ListForMonomialItem&&);
	ListForMonomialItem& operator =(const ListForMonomialItem&);

	ListForMonomialItem(char, int);
	~ListForMonomialItem();

	ListForMonomialItem& operator *=(const ListForMonomialItem&);
	ListForMonomialItem& operator /=(const ListForMonomialItem&);

	ListForMonomialItem* GetPrevious() const;
	ListForMonomialItem* GetNext() const;
	int GetPower() const;
	char GetName() const; 

	void SetPrevious(ListForMonomialItem *newPrevious);
	void SetNext(ListForMonomialItem*);
	void SetPower(int);
	void SetName(char);

	friend std::ostream& operator<<(std::ostream&, const ListForMonomialItem&);
	friend std::istream& operator>>(std::istream&, ListForMonomialItem&);
};


class ListForMonomial
{
protected:

	ListForMonomialItem* head;
	int size;

	ListForMonomialItem* GetFirst() const;
	ListForMonomialItem* GetLast() const;

	ListForMonomial();
	ListForMonomial(const ListForMonomial&);
	ListForMonomial(ListForMonomial&&);

	void DestroyNodes();
	void CreateNewZeroList();
	void Delete(ListForMonomialItem*);

public:
	
	~ListForMonomial();

	int GetSize() const;
	void InsertNewNode(char, int);

	ListForMonomialItem& operator[](int) const;

	friend std::ostream& operator<<(std::ostream&, const ListForMonomial&);
};

#endif //INC_3_LISTFORMONOMIAL_H