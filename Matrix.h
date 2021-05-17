#pragma once
#include<iostream>
using namespace std;
template <class Type>
class Matrix
{
	Type** p_data;
	int row, col;
public:
	Matrix(int r, int c); //���캯��
	Matrix(const Matrix<Type>& m);//�������캯��
	~Matrix(); //��������
	Type*& operator[] (int i); //����[], ����Matrix����m, �ܹ�ͨ��m[i][j]���ʵ�i+1�С���j + 1��Ԫ��
	Matrix<Type> & operator = (const Matrix<Type> & m); //����=, ʵ�־������帳ֵ, ����/�в���, �黹�ռ䲢���·���
	bool operator == (const Matrix<Type>& m) const; //����==, �жϾ����Ƿ����
	Matrix<Type> operator + (const Matrix<Type>& m) const; //����+, ��ɾ���ӷ�, �ɼ�������������ӷ�����(�������С��зֱ����)
	Matrix<Type> operator * (const Matrix<Type>& m) const; //����*, ��ɾ���˷�, �ɼ�������������˷�����(this.col = m.row)

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
		delete[]p_data;//�黹�ڴ�
		
		row = m.row;
		col = m.col;
		p_data = new Type* [row];
		if (!p_data) exit(-1);
		for (int i = 0; i < row; ++i)
		{
			p_data[i] = new Type[col];
			if (!p_data[i]) exit(-1);
		}//���·���ռ�
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