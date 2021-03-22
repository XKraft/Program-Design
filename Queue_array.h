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
	int front, rear;
	int MaxLength;
	int* p;
};
void Queue::enQueue(int i)
{
	if ((front + 1) % MaxLength == rear)
		if (MaxLength > 100)
		{
			cout << "Queue is overflow." << endl;
			exit(-1);
		}
		else
		{
			
			int* p1 = new int[MaxLength + 10];
			if (!p1)
			{
				cout << "Stack is overflow." << endl;
				exit(-1);
			}
			int j = 0;
			for (int i = front; i != rear; ++j)
			{
				p1[j] = p[i];
				i = (i + 1) % MaxLength;
			}
			front = 0;
			rear = j;
			delete []p;
			p = p1;
			p1 = NULL;
			MaxLength += 10;
		}
	p[rear] = i;
	rear = (rear + 1) % MaxLength;
}
void Queue::deQueue(int& i)
{
	if (front == rear)
	{
		cout << "Queue is empty." << endl;
		exit(-1);
	}
	i = p[front];
	front = (front + 1) % MaxLength;
}
Queue::Queue()
{
	front = rear = 0;
	MaxLength = 10;
	p = new int[MaxLength];
	if (!p)
	{
		cout << "Stack is overflow." << endl;
		exit(-1);
	}
}
void Queue::printAll()
{
	if (front != rear)
	{
		for (int i = front; i != rear; )
		{
			cout << p[i] << endl;
			i = (i + 1) % MaxLength;
		}
	}
	else
		cout << "Queue is empty." << endl;
}