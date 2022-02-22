#include "Node.h"

template <class T>
Node<T>::Node()
{
	value = 0;
	next = 0;
}

template <class T>
Node<T>::Node(T val)
{
	value = val;
	next = 0;
}
