#pragma once
#include "Node.h"

template <class T>
class LinkedList
{
	int count;
	Node<T>* head;
	Node<T>* tail;
public:
	LinkedList();
	int Length();
	T At(int);
	void InsertAt(int, T);
	void Append(T);
	void DeleteAt(int);
	~LinkedList(void);
};
