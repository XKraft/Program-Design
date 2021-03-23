#include"merchandise_list.h"
#ifndef USER
#define USER
class User
{
public:
	User(const char* user_name);
	void BrowseMerchandise(Merchandise* merchandise);
	MerchandiseList* GetBrowseHistory();
	void BuyMerchandise(Merchandise* Merchandise, int nmmber);
	MerchandiseList* GetBuyHistory();
private:
	MerchandiseList m1;
	MerchandiseList m2;
	const char* user_name;
};
#endif