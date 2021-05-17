#pragma once
#include<iostream>
using namespace std;
template<class Type>
class MaxHeap {
private:
	Type* Data;
	int Size; //当前大小
	int Capacity; //总容量
public:
	MaxHeap(); //默认构造函数，容量为10
	MaxHeap(int Capacity);
	~MaxHeap();
	bool Insert(Type element); //插入一个元素
	Type DeleteMax(); //找出最大的元素返回，并进行删除
	bool IsFull(); //是否为满
	bool IsEmpty(); //是否为空
	void Print(); //打印
};
template<class Type>
MaxHeap<Type>::MaxHeap()
{
	Capacity = 10;
	Size = 0;
	Data = new Type[Capacity + 1];
}
template<class Type>
MaxHeap<Type>::MaxHeap(int _Capacity)
{
	Capacity = _Capacity;
	Size = 0;
	Data = new Type[Capacity + 1];
}
template<class Type>
MaxHeap<Type>::~MaxHeap()
{
	delete[]Data;
}
template<class Type>
bool MaxHeap<Type>::Insert(Type element)
{
	if (Size == Capacity)
		return false;
	Data[Size + 1] = element;
	for (int i = Size + 1; Data[i] > Data[i / 2]; i /= 2)
	{
		Type temp = Data[i / 2];
		Data[i / 2] = Data[i];
		Data[i] = temp;
	}
	return true;
}
template<class Type>
Type MaxHeap<Type>::DeleteMax()
{
	Type temp = Data[1];
	Data[1] = Data[Size];
	Data[Size] = temp;
	for (int i = 1; Data[i] < Data[2 * i] || Data[i] < Data[2 * i + 1]; )
	{
		if (Data[2 * i] > Data[2 * i + 1])
		{
			temp = Data[2 * i];
			Data[2 * i] = Data[i];
			Data[i] = temp;
			i = 2 * i;
		}
		else
		{
			temp = Data[2 * i + 1];
			Data[2 * i + 1] = Data[i];
			Data[i] = temp;
			i = 2 * i + 1;
		}

	}
	--Size;
	return Data[Size + 1];
}
template<class Type>
bool MaxHeap<Type>::IsFull()
{
	if (Size == Capacity)
		return true;
	else
		return false;
}
template<class Type>
bool MaxHeap<Type>::IsEmpty()
{
	if (Size == 0)
		return true;
	else
		return false;
}
template<class Type>
void MaxHeap<Type>::Print()
{
	for (int i = 1; i <= Size; ++i)
		cout << Data[i] << " ";
}