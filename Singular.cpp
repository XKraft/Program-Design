#include<iostream>
using namespace std;
void get_min_asc(char* str)
{
	char ch = str[0];
	for (int i = 0; str[i] != '\0'; ++i)
		if (str[i] < ch)
			ch = str[i];
	cout << ch;
}
void reorder(char* str)
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		int min = i;
		for (int j = i + 1; str[j] != '\0'; ++j)
		{
			if (str[j] < str[min])
				min = j;
		}
		char temp = str[i];
		str[i] = str[min];
		str[min] = temp;
	}
	//printf("%s", str);
	cout << str << endl;
}