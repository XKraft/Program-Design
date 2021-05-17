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
	A* next; //用于组织A类对象自由空间结点的链表。
	static A* p_free; //用于指向A类对象的自由空间链表头。
	static A** pp_free;//想法是利用一个动态数组储存每个区块的首地址
	static int region_nums;//区块数
};
A* A::p_free = NULL;
A** A::pp_free = NULL;
int A::region_nums = 0;
const int NUM = 32;
void* A::operator new(size_t size)
{
	if (p_free == NULL)
	{	//申请NUM个A类对象的大空间。
		p_free = (A*)malloc(size * NUM);  //一个动态数组
		  //在大空间上建立自由结点链表。
		for (int i = 0;i < NUM - 1; i++)
			p_free[i].next = &p_free[i + 1];
		p_free[NUM - 1].next = NULL;

		++region_nums;//区块数加一
		A** p = (A**)malloc(sizeof(A*) * region_nums);//建议一个新的储存区块首地址的数组
		for (int i = 0; i < region_nums - 1; ++i)
			p[i] = pp_free[i];//将已储存的地址拷贝到新的数组
		p[region_nums - 1] = p_free;//将新开辟的区块的首地址储存到数组中
		free(pp_free);
		pp_free = p;
		p = NULL;
	}
	//从链表中给当前对象分配空间
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