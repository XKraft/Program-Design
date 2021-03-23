#include"user.h"
User::User(const char* user_name):user_name(user_name)
{

}
void User::BrowseMerchandise(Merchandise* merchandise)
{
	m1.AddRecord(merchandise, 1);
}
MerchandiseList* User::GetBrowseHistory()
{
	return &m1;
}
void User::BuyMerchandise(Merchandise* Merchandise, int number)
{
	m2.AddRecord(Merchandise, number);
}
MerchandiseList* User::GetBuyHistory()
{
	return &m2;
}