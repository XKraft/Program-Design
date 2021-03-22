#include<iostream>
using namespace std;
void sum_len(char* str1, char* str2)
{
	int len_1 = 0, len_2 = 0;
	while (str1[len_1] != '\0')
		++len_1;
	while (str2[len_2] != '\0')
		++len_2;
	cout << len_1 + len_2 << endl;
}
void merge(char* str1, char* str2)
{
	for (int i = 0; str1[i] != '\0'; ++i)
	{
		int min = i;
		for (int j = i + 1; str1[j] != '\0'; ++j)
		{
			if (str1[j] < str1[min])
				min = j;
		}
		char temp = str1[i];
		str1[i] = str1[min];
		str1[min] = temp;
	}
	for (int i = 0; str2[i] != '\0'; ++i)
	{
		int min = i;
		for (int j = i + 1; str2[j] != '\0'; ++j)
		{
			if (str2[j] < str2[min])
				min = j;
		}
		char temp = str2[i];
		str2[i] = str2[min];
		str2[min] = temp;
	}
	int i = 0, j = 0;
	while (str1[i] != '\0' && str2[j] != '\0')
		if (str1[i] < str2[j])
			cout << str1[i++];
		else
			cout << str2[j++];
	while(str1[i] != '\0')
		cout << str1[i++];
	while (str2[j] != '\0')
		cout << str2[j++];
}