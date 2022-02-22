#include "Queue.h"
#include <iostream>
#include <assert.h>

template <class T>
Queue<T>::Queue()
{
	size = 5;
	count = 0;
	front = back = -1;
	arr = new T[size];
}

template <class T>
int Queue<T>::length()
{
	return count;
}

template <class T>
void Queue<T>::enqueue(T val)
{
	assert(!full());
	if (count == 0)
		front = 0;
	back = (back + 1) % size;
	arr[back] = val;
	count++;
}

template <class T>
void Queue<T>::dequeue()
{
	assert(!empty());
	if (count == 1)
		front = back = -1;
	else
		front = (front + 1) % size;
	count--;
}

template <class T>
T Queue<T>::Front()
{
	assert(!empty());
	return arr[front];
}

template <class T>
bool Queue<T>::full()
{
	return (count == size);
}

template <class T>
bool Queue<T>::empty()
{
	return (count == 0);
}

template <class T>
void Queue<T>::clear()
{
	delete[] arr;
}

template <class T>
Queue<T>::~Queue(void)
{
}
