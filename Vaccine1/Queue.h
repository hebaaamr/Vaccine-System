#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_

template <class T>
class Queue
{
	T* arr;
	int count, size;
	int front, back;
public:
	Queue();
	int length();
	void enqueue(T);
	void dequeue();
	T Front();
	bool empty();
	void clear();
	bool full();
	~Queue();
};

#endif
