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