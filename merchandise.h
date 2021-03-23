#include<iostream>
using namespace std;
#ifndef MERCHANDISE
#define MERCHANDISE
class Merchandise
{
public:
	Merchandise(const char* name, int price);
	const char* GetMerchandiseName();
	int GetMerchandisePrice();
private:
	const char* name;
	int price;
};
#endif // !MERCHANDISE