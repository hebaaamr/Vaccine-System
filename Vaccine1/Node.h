#pragma once

template <class T>
class Node
{
public:
	Node<T>* next;
	T value;

	Node();
	Node(T val);
};
