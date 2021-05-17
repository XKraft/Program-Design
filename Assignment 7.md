# Assignment 7 

#### 一. 概念题 

###### 1.1 C++中虚函数的作用是什么？为什么C++中析构函数往往是虚函数？ 

虚函数的作用：

（1）指定消息采用动态绑定

（2）指出基类中可以被重定义的成员函数

为什么析构函数往往是虚函数

因为如果用基类的指针指向派生类时，如果析构函数不是虚函数，则只会默认绑定基类的析构函数，而无法析构派生类中多定义的动态变量，造成内存泄漏。

###### 1.2 简述C++中静态绑定和动态绑定的概念，并说明动态绑定发生的情况.

静态绑定指C++默认的消息绑定方式：采用基类的消息处理。

动态绑定是指消息的处理根据实际指向或引用的对象选择对应的消息处理。在C++中用虚函数指出动态绑定。

只有通过指针或引用访问类的虚函数时才进行动态绑定。

#### 二. 编程题 

###### 2.1 请阅读下面的代码，写出程序的运行结果

```c++
#include <iostream>
using namespace std;
class A {
public:
A() { cout << "default construct A" << endl; }
A(const A& a) { cout << "copy construct A" << endl; }
virtual ~A() { cout << "destruct A" << endl; }
void f () { cout << "A::f" << endl; }
virtual void g() { cout << "A::g" << endl; }
};
class B : public A {
public:
B() { cout << "default construct B" << endl; }
B(const B& b) { cout << "copy construct B" << endl; }
~B() { cout << "destruct B" << endl; }
void f() { cout << "B::f" << endl; }
void g() { cout << "B::g" << endl; }
};
void func1(A a) {
a.f();
a.g();
}
void func2(A &a) {
a.f();
a.g();
}
int main() {
A *a = new A();
A *b = new B();
func1(*a); func2(*a);
func1(*b); func2(*b);
*a = *b;
func1(*a); func2(*a);
delete a; delete b;
return 0;
}
```

运行结果：

default construct A
default construct A
default construct B
copy construct A
A::f
A::g
destruct A
A::f
A::g
copy construct A
A::f
A::g
destruct A
A::f
B::g
copy construct A
A::f
A::g
destruct A
A::f
A::g
destruct A
destruct B
destruct A

###### 2.2 要求基于抽象类Queue实现三种形式的队列，其中Queue1按照先进先出的原则，Queue2选择最小的元素出列，Queue3选择最大 的元素出列.

```c++
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
```

