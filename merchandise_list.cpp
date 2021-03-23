#include"merchandise_list.h"
#include<string.h>
// 构造函数，初始化⼀个MerchandiseList类的对象。
MerchandiseList::MerchandiseList()
{
	head = NULL;
	tail = NULL;
}
// 成员函数，往MerchandiseList对象中增加⼀条记录(每条记录包括⼀个Merchandise指针，和⼀个数值)
void MerchandiseList::AddRecord(Merchandise* merchandise, int value)
{
	Node* cur = head;
	while (cur)
	{
		if (!strcmp((*(cur->m)).GetMerchandiseName(), (*merchandise).GetMerchandiseName()))
		{
			cur->value += value;
			return;
		}
		cur = cur->next;
	}
	Node* p = new Node;
	p->m = merchandise;
	p->value = value;
	p->next = NULL;
	if (head == NULL)
		head = p;
	else
		tail->next = p;
	tail = p;
}
// 成员函数，修改商品merchandise所在的那条记录中的value值为new_value，若商品不在列表中，不进⾏操作直接返回。
void MerchandiseList::ModifyRecord(Merchandise* merchandise, int new_value)
{
	Node* cur = head;
	while (cur)
	{
		if (!strcmp((*(cur->m)).GetMerchandiseName(), (*merchandise).GetMerchandiseName()))
		{
			cur->value = new_value;
			return;
		}
		cur = cur->next;
	}
}
// 成员函数，查找merchandise所代表商品的记录，并返回这条记录中的value值(若未找到记录则返回 - 1)
int MerchandiseList::FindRecord(Merchandise* merchandise)
{
	Node* cur = head;
	while (cur)
	{
		if (!strcmp((*(cur->m)).GetMerchandiseName(), (*merchandise).GetMerchandiseName()))
		{
			return cur->value;
		}
		cur = cur->next;
	}
	return -1;
}
// 成员函数，删除merchandise所代表商品的记录，成功删除后返回true，如果不存在该记录，则不做操作并返回false
bool MerchandiseList::DeleteRecord(Merchandise* merchandise)
{
	if (!head)
		return false;
	Node* cur = head;
	if (!strcmp((*(head->m)).GetMerchandiseName(), (*merchandise).GetMerchandiseName()))
	{
		head = head->next;
		delete cur;
		cur = NULL;
		return true;
	}
	else
	{
		Node* prev = cur;
		while (cur)
		{
			if (!strcmp((*(cur->m)).GetMerchandiseName(), (*merchandise).GetMerchandiseName()))
			{
				if (cur == tail)
					tail = prev;
				prev->next = cur->next;
				delete cur;
				cur = NULL;
				return true;
			}
			prev = cur;
			cur = cur->next;			
		}
	}
	return false;
}