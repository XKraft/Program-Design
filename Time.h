#pragma once
#include<iostream>
using namespace std;

enum TimeZone {
	W12 = -12, W11, W10, W9, W8, W7, W6, W5, W4, W3, W2, W1,
	GMT, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12
};

class Time
{
public:
	Time(int h, int m, int s);//构造函数
	void set(int h, int m, int s); //调整时间
	void increment(); //时间 +1 秒
	void display(); //显示时间值
	bool equal(Time& other_time); //比较是否与某个时间相等
	bool less_then(Time& other_time); //比较是否早于某个时间
protected:
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
class ExtTime :public Time
{
public:
	ExtTime(); //设置为GMT时间
	ExtTime(int h, int m, int s, TimeZone t); //构造函数
	void set(int h, int m, int s, TimeZone t); //调整时间
	void display();//展示时间，首先打印时区，再打印时间
	bool equal(const ExtTime& other_time); //判断是否相等
	bool less_than(const ExtTime& other_time);//判断是否小于
private:
	TimeZone timezone;
};
ExtTime::ExtTime():Time(0, 0, 0)
{
	timezone = GMT;
}
ExtTime::ExtTime(int h, int m, int s, TimeZone t) : Time(h, m, s)
{
	timezone = t;
}
void ExtTime::set(int h, int m, int s, TimeZone t)
{
	Time::set(h, m, s);
	timezone = t;
}
void ExtTime::display()
{
	int t = (int)timezone;
	if (t < 0)
		cout << "W" << -t << " ";
	if (t > 0)
		cout << "E" << t << " ";
	if (t == 0)
		cout << "GMT" << " ";
	Time::display();
}
bool ExtTime::equal(const ExtTime& other_time)
{
	int _hour = hour - ((int)timezone - (int)other_time.timezone);
	if (_hour == other_time.hour && minute == other_time.minute && second == other_time.second)
		return true;
	else
		return false;
}
bool ExtTime::less_than(const ExtTime& other_time)
{
	ExtTime temp(other_time);
	temp.hour -= (int)other_time.timezone - (int)timezone;
	if (Time::less_then(temp))
		return true;
	else
		return false;
}