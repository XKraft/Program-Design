#include<iostream>
#include"merchandise.h"
using namespace std;
#ifndef MERCHANDISELIST
#define MERCHANDISELIST
struct Node
{
	Merchandise* m;
	int value;
	struct Node* next;
};
class MerchandiseList
{
public:
	MerchandiseList();
	void AddRecord(Merchandise* merchandise, int value);
	void ModifyRecord(Merchandise* merchandise, int new_value);
	int FindRecord(Merchandise* merchandise);
	bool DeleteRecord(Merchandise* merchandise);
private:
	Node* head, *tail;
};
#endif // !MERCHANDISELIST