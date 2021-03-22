#include<iostream>
using namespace std;
class Queue
{
public:
	void enQueue(int i);
	void deQueue(int& i);
	Queue();
	void printAll();
private:
	struct Node
	{
		int data;
		struct Node* next;
	}*front, * rear;
	int Queue_Length;
};
void Queue::enQueue(int i)
{
	if (Queue_Length > 100)
	{
		cout << "Queue is overflow.\n" << endl;
		exit(-1);
	}
	Node* p = new Node;
	p->data = i;
	p->next = NULL;
	rear->next = p;
	rear = p;
	++Queue_Length;
}
void Queue::deQueue(int& i)
{
	if (Queue_Length < 0)
	{
		cout << "Queue is empty.\n" << endl;
		exit(-1);
	}
	Node* p = front->next;
	i = p->data;
	front->next = p->next;
	delete p;
	p = NULL;
	--Queue_Length;
}
Queue::Queue()
{
	front = rear = new Node;
	if (!front)
	{
		cout << "Stack is overflow." << endl;
		exit(-1);
	}
	front->next = NULL;
	Queue_Length = 0;
}
void Queue::printAll()
{
	Node* p = front->next;
	while (p)
	{
		cout << p->data << endl;
		p = p->next;
	}
}
