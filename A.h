#pragma once
#include<iostream>
using namespace std;
class A
{
public:
	static void* operator new(size_t size);
	static void operator delete(void* p);
	static void deleteall();
private:
	A* next; //������֯A��������ɿռ��������
	static A* p_free; //����ָ��A���������ɿռ�����ͷ��
	static A** pp_free;//�뷨������һ����̬���鴢��ÿ��������׵�ַ
	static int region_nums;//������
};
A* A::p_free = NULL;
A** A::pp_free = NULL;
int A::region_nums = 0;
const int NUM = 32;
void* A::operator new(size_t size)
{
	if (p_free == NULL)
	{	//����NUM��A�����Ĵ�ռ䡣
		p_free = (A*)malloc(size * NUM);  //һ����̬����
		  //�ڴ�ռ��Ͻ������ɽ������
		for (int i = 0;i < NUM - 1; i++)
			p_free[i].next = &p_free[i + 1];
		p_free[NUM - 1].next = NULL;

		++region_nums;//��������һ
		A** p = (A**)malloc(sizeof(A*) * region_nums);//����һ���µĴ��������׵�ַ������
		for (int i = 0; i < region_nums - 1; ++i)
			p[i] = pp_free[i];//���Ѵ���ĵ�ַ�������µ�����
		p[region_nums - 1] = p_free;//���¿��ٵ�������׵�ַ���浽������
		free(pp_free);
		pp_free = p;
		p = NULL;
	}
	//�������и���ǰ�������ռ�
	A* p = p_free;
	p_free = p_free->next;
	memset(p, 0, size);
	return p;
}
void A::operator delete(void* p)
{
	((A*)p)->next = p_free;
	p_free = (A*)p;
}
void A::deleteall()
{
	for (int i = 0; i < region_nums; ++i)
		free(pp_free[i]);
	free(pp_free);
	pp_free = NULL;
}