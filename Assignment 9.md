# Assignment 9

####  一、概念简答题 

###### 1.以下关于函数模板的描述是否有错误？如果有错误请指出，并给出理由。 

1.函数模板必须由程序员实例化为可执行的函数模板 

错误。编译程序可以隐式地根据函数调用的实参类型自动地把函数模型实例化为具体的函数。

2.函数模板的实例化由编译器实现 

错误。如果参数的类型不统一或者函数模板带有非类型参数，需要程序员显示地进行实例化。

3.一个类定义中，只要有一个函数模板，则这个类是类模板 

错误。如果一个类定义中用到的类型可变、但功能不变，则该类称为类属类。所以只有类中用到了类型参数，才是类模板。

4.类模板的成员函数都是函数模板，类模板实例化后，成员函数也随之实例化 

错误。类模板的成员函数并不都是函数模板，如果没用到类型参数，则不属于函数模板。

###### 2.在类模版中使用静态成员有什么要注意的地方？ 

不同类模板实例之间不共享类模板中的静态成员。

###### 3.为什么通常情况下，类模板的定义和实现都放在头文件中？

模板属于源代码复用。使用一个模板前必须要对其实例化，而实例化是在编译时刻进行的，所以一定要见到相应的源代码。如果一个类模板的实现放在.cpp文件中，在其他地方使用时就可能会在连接时出错。

#### 二、代码编程题 

1. ###### 用模板类实现一个最大堆

```c++
#pragma once
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
	delete []Data;
}
template<class Type>
bool MaxHeap<Type>::Insert(Type element)
{
	if (Size == Capacity)
		return false;
	Data[Size + 1] = element;
	for (int i = Size + 1; i / 2 > 0 && Data[i] > Data[i / 2]; i /= 2)
	{
		Type temp = Data[i / 2];
		Data[i / 2] = Data[i];
		Data[i] = temp;
	}
	++Size;
	return true;
}
template<class Type>
Type MaxHeap<Type>::DeleteMax()
{
	Type temp = Data[1];
	Data[1] = Data[Size];
	Data[Size] = temp;
	--Size;
	int i = 1;
	while (i * 2 <= Size)
	{
		int max = 2 * i;
		if (2 * i + 1 <= Size)
			if (Data[2 * i + 1] > Data[2 * i])
				max = 2 * i + 1;
		if (Data[i] < Data[max])
		{
			Type temp = Data[max];
			Data[max] = Data[i];
			Data[i] = temp;
			i = max;
		}
		else
			break;
	}
	
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
```

![image-20210513232652052](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20210513232652052.png)

###### 2.在第五次作业中，我们实现了一个基于int类型的Matrix类，这次作业我们对这个类进行一次扩展，希望扩展后它能处理多种数据类型的矩阵运算，这些数据类型包括

1）int； 2）复数类（你得首先自己实现这个类Complex，请复习复数乘法和加法）。 注意：请结合最近的课程知识来完成编程题，自行构造测试用例来测试实现的功能，并提供运行截图

```C++
//Complex.h
#pragma once
#include<iostream>
using namespace std;
class Complex
{
public:
	Complex();
	Complex(double _real, double _imag);
	Complex(Complex& x);
	Complex(double r) { real = r; imag = 0; }
	void SetComplex(double _real, double _imag) { real = _real; imag = _imag; }
	Complex operator + (const Complex& x) const;
	Complex operator * (const Complex& x) const;
	bool operator == (const Complex& x) const;
	bool operator != (const Complex& x) const;
	friend ostream& operator <<(ostream& out, const Complex& x);

private:
	double real, imag;
};
Complex::Complex()
{
	real = 0;
	imag = 0;
}
Complex::Complex(double _real, double _imag)
{
	real = _real;
	imag = _imag;
}
Complex::Complex(Complex& x)
{
	real = x.real;
	imag = x.imag;
}
Complex Complex::operator + (const Complex& x) const
{
	Complex temp;
	temp.real = real + x.real;
	temp.imag = imag + x.imag;
	return temp;
}
Complex Complex::operator * (const Complex& x) const
{
	Complex temp;
	temp.real = real * x.real - imag * x.imag;
	temp.imag = imag * x.real + real * x.imag;
	return temp;
}
bool Complex::operator == (const Complex& x) const
{
	if (real == x.real && imag == x.imag)
		return true;
	else
		return false;
}
bool Complex::operator != (const Complex& x) const
{
	return !(*this == x);
}
ostream& operator <<(ostream& out, const Complex& x)
{
	out << x.real << "+" << x.imag << "i";
	return out;
}

//Matrix.h
#pragma once
#include<iostream>
using namespace std;
template <class Type>
class Matrix
{
	Type** p_data;
	int row, col;
public:
	Matrix(int r, int c); //构造函数
	Matrix(const Matrix<Type>& m);//拷贝构造函数
	~Matrix(); //析构函数
	Type*& operator[] (int i); //重载[], 对于Matrix对象m, 能够通过m[i][j]访问第i+1行、第j + 1列元素
	Matrix<Type> & operator = (const Matrix<Type> & m); //重载=, 实现矩阵整体赋值, 若行/列不等, 归还空间并重新分配
	bool operator == (const Matrix<Type>& m) const; //重载==, 判断矩阵是否相等
	Matrix<Type> operator + (const Matrix<Type>& m) const; //重载+, 完成矩阵加法, 可假设两矩阵满足加法条件(两矩阵行、列分别相等)
	Matrix<Type> operator * (const Matrix<Type>& m) const; //重载*, 完成矩阵乘法, 可假设两矩阵满足乘法条件(this.col = m.row)

	void display();
};
template <class Type>
Matrix<Type>::Matrix(int r, int c)
{
	row = r;
	col = c;
	p_data = new Type* [r];
	if (!p_data) exit(-1);
	for (int i = 0; i < r; ++i)
	{
		p_data[i] = new Type[c];
		if (!p_data[i]) exit(-1);
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			p_data[i][j] = 0;
}
template <class Type>
Matrix<Type>::Matrix(const Matrix<Type>& m)
{
	row = m.row;
	col = m.col;
	p_data = new Type* [row];
	if (!p_data) exit(-1);
	for (int i = 0; i < row; ++i)
	{
		p_data[i] = new Type[col];
		if (!p_data[i]) exit(-1);
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			p_data[i][j] = m.p_data[i][j];
}
template <class Type>
Matrix<Type>::~Matrix()
{
	for (int i = 0; i < row; ++i)
		delete[]p_data[i];
	delete[]p_data;
}
template <class Type>
Type*& Matrix<Type>::operator[] (int i)
{
	if (i >= row)
		exit(-2);
	return p_data[i];
}
template <class Type>
Matrix<Type>& Matrix<Type>::operator = (const Matrix<Type>& m)
{
	if (m.col != col || m.row != row)
	{
		for (int i = 0; i < row; ++i)
			delete[]p_data[i];
		delete[]p_data;//归还内存
		
		row = m.row;
		col = m.col;
		p_data = new Type* [row];
		if (!p_data) exit(-1);
		for (int i = 0; i < row; ++i)
		{
			p_data[i] = new Type[col];
			if (!p_data[i]) exit(-1);
		}//重新分配空间
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			p_data[i][j] = m.p_data[i][j];
	return *this;
}
template <class Type>
bool Matrix<Type>::operator == (const Matrix<Type>& m) const
{
	if (m.col != col || m.row != row)
		return false;
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (p_data[i][j] != m.p_data[i][j])
				return false;
	return true;
}
template <class Type>
Matrix<Type> Matrix<Type>::operator + (const Matrix<Type>& m) const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			temp.p_data[i][j] = p_data[i][j] + m.p_data[i][j];
	return temp;
}
template <class Type>
Matrix<Type> Matrix<Type>::operator * (const Matrix<Type>& m) const
{
	Matrix temp(row, m.col);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < m.col; ++j)
			for (int k = 0; k < col; ++k)
				temp.p_data[i][j] = temp.p_data[i][j] +  p_data[i][k] * m.p_data[k][j];
	return temp;
}
template <class Type>
void Matrix<Type>::display()
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
			cout << p_data[i][j] << " ";
		cout << endl;
	}
}
```

![image-20210514004823118](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20210514004823118.png)

