#include<iostream>
using namespace std;
class Time
{
public:
	Time(int h, int m, int s);//���캯��
	void set(int h, int m, int s); //����ʱ��
	void increment(); //ʱ�� +1 ��
	void display(); //��ʾʱ��ֵ
	bool equal(Time& other_time); //�Ƚ��Ƿ���ĳ��ʱ�����
	bool less_then(Time& other_time); //�Ƚ��Ƿ�����ĳ��ʱ��
private:
	int hour, minute, second;
};
Time::Time(int h, int m, int s)
{
	hour = h;
	minute = m;
	second = s;
}
void Time::set(int h, int m, int s)
{
	hour = h;
	minute = m;
	second = s;
}
void Time::increment()
{
	if (second + 1 >= 60)
	{
		if (minute + 1 >= 60)
		{
			if (hour + 1 >= 24)
				hour = 0;
			else
				++hour;
			minute = 0;
		}
		else
			++minute;
		second = 0;
	}
	else
		++second;
}
void Time::display()
{
	cout << hour << ":" << minute << ":" << second << endl;
}
bool Time::equal(Time& other_time)
{
	if (hour == other_time.hour && minute == other_time.second && second == other_time.second)
		return true;
	else
		return false;
}
bool Time::less_then(Time& other_time)
{
	if (hour > other_time.hour)
		return false;
	if (hour < other_time.hour)
		return true;
	if (minute > other_time.minute)
		return false;
	if (minute < other_time.minute)
		return true;
	if (second >= other_time.second)
		return false;
	if (second < other_time.second)
		return true;
}