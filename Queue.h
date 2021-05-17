#pragma once
#include<iostream>
using namespace std;
struct Node
{
	int data;
	struct Node* next;
};
class Queue 
{
public:
	virtual bool enqueue(int num) = 0; //入列
	virtual bool dequeue(int& num) = 0; //出列
	virtual ~Queue() {}
};
class Queue1 : public Queue 
{
public:
	Queue1();
	bool enqueue(int num);
	bool dequeue(int& num);
	~Queue1();
private:
	Node* front, * rear;
	int Queue_Length;
	int Max_Length;
};
class Queue2 : public Queue 
{
public:
	Queue2();
	bool enqueue(int num);
	bool dequeue(int& num);
	~Queue2();
private:
	Node* front;
	int Queue_Length;
	int Max_Length;
};
class Queue3 : public Queue 
{
public:
	Queue3();
	bool enqueue(int num);
	bool dequeue(int& num);
	~Queue3();
private:
	Node* front;
	int Queue_Length;
	int Max_Length;
};
Queue1::Queue1()
{
	front = NULL;
	rear = NULL;
	Queue_Length = 0;
	Max_Length = 100;
}
Queue1::~Queue1()
{
	Node* cur = front;
	while (front)
	{
		cur = front;
		front = front->next;
		delete cur;
	}
	front = rear = NULL;
}
bool Queue1::enqueue(int num)
{
	if (Queue_Length >= Max_Length)
		return false;
	Node* p = new Node;
	if (!p) exit(-1);
	p->data = num;
	p->next = NULL;
	if (front == NULL)
		front = p;
	else
		rear->next = p;
	rear = p;
	++Queue_Length;
	return true;
}
bool Queue1::dequeue(int& num)
{
	if (Queue_Length == 0)
		return false;
	Node* cur = front;
	num = front->data;
	front = front->next;
	delete cur;
	cur = NULL;
	--Queue_Length;
	return true;
}
Queue2::Queue2()
{
	front = NULL;
	Queue_Length = 0;
	Max_Length = 100;
}
Queue2::~Queue2()
{
	Node* cur = front;
	while (front)
	{
		cur = front;
		front = front->next;
		delete cur;
	}
	front = NULL;
}
bool Queue2::enqueue(int num)
{
	if (Queue_Length >= Max_Length)
		return false;
	Node* p = new Node;
	if (!p) exit(-1);
	p->data = num;
	p->next = NULL;
	if (front == NULL)
	{
		front = p;
		++Queue_Length;
		return true;
	}
	if (num <= front->data)
	{
		p->next = front;
		front = p;
		++Queue_Length;
		return true;
	}
	else
	{
		Node* cur = front;
		Node* prev = cur;
		while (cur && num > cur->data)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = p;
		p->next = cur;
		++Queue_Length;
		return true;
	}
}
bool Queue2::dequeue(int& num)
{
	if (Queue_Length == 0)
		return false;
	num = front->data;
	Node* cur = front;
	front = front->next;
	delete cur;
	cur = NULL;
	--Queue_Length;
	return true;
}
Queue3::Queue3()
{
	front = NULL;
	Queue_Length = 0;
	Max_Length = 100;
}
Queue3::~Queue3()
{
	Node* cur = front;
	while (front)
	{
		cur = front;
		front = front->next;
		delete cur;
	}
	front = NULL;
}
bool Queue3::enqueue(int num)
{
	if (Queue_Length >= Max_Length)
		return false;
	Node* p = new Node;
	if (!p) exit(-1);
	p->data = num;
	p->next = NULL;
	if (front == NULL)
	{
		front = p;
		++Queue_Length;
		return true;
	}
	if (num >= front->data)
	{
		p->next = front;
		front = p;
		++Queue_Length;
		return true;
	}
	else
	{
		Node* cur = front;
		Node* prev = cur;
		while (cur && num < cur->data)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = p;
		p->next = cur;
		++Queue_Length;
		return true;
	}
}
bool Queue3::dequeue(int& num)
{
	if (Queue_Length == 0)
		return false;
	num = front->data;
	Node* cur = front;
	front = front->next;
	delete cur;
	cur = NULL;
	--Queue_Length;
	return true;
}