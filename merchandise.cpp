#include"merchandise.h"
Merchandise::Merchandise(const char* name, int price):name(name), price(price)
{

}
const char* Merchandise::GetMerchandiseName()
{
	return name;
}
int Merchandise::GetMerchandisePrice()
{
	return price;
}