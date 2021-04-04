#include<iostream>
using namespace std;
int _month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Date
{
private:
	int _year, _month, _day;
public:
	Date(int year, int month, int day);
	bool is_leap() const;
	friend class Datetime;
};
class Time
{
private:
	int _hour, _minute, _second;
public:
	Time(int hour, int minute, int second);
	friend class Datetime;
};
class Datetime
{
private:
	Date _date;
	Time _time;
public:
	Datetime(const Date& date, const Time& time);
	Datetime operator +(long) const;
	Datetime operator -(long) const;
	Datetime& operator ++();
	Datetime& operator --();
	bool operator < (const Datetime&) const;
	bool operator ==(const Datetime&) const;
};

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}
bool Date::is_leap() const
{
	if (_year % 4 == 0 && _year % 100 != 0 || _year % 400 == 0)
		return true;
	else
		return false;
}

Time::Time(int hour, int minute, int second)
{
	_hour = hour;
	_minute = minute;
	_second = second;
}

Datetime::Datetime(const Date& date, const Time& time):_date(date), _time(time){}
Datetime Datetime::operator +(long second) const
{
	Datetime temp(*this);
	temp._time._second += second % 60;
	if (temp._time._second > 59)
	{	
		temp._time._minute++;
		temp._time._second -= 60;
	}
	long minute = second / 60;
	temp._time._minute += minute % 60;
	if (temp._time._minute > 59)
	{
		temp._time._hour++;
		temp._time._minute -= 60;
	}
	long hour = minute / 60;
	temp._time._hour += hour % 24;
	if (temp._time._hour > 23)
	{
		temp._date._day++;
		temp._time._hour -= 24;
	}
	temp._date._day += hour / 24;
	while (1)
	{
		if (temp._date.is_leap())
			_month_day[1] = 29;
		else
			_month_day[1] = 28;
		if (temp._date._day > _month_day[temp._date._month - 1])
		{
			temp._date._day -= _month_day[temp._date._month - 1];
			if (temp._date._month == 12)
			{
				temp._date._year++;
				temp._date._month = 1;
			}
			else
				temp._date._month++;
		}
		else
			break;
	}
	return temp;
}
Datetime Datetime::operator -(long second) const
{
	Datetime temp(*this);
	temp._time._second -= second % 60;
	if (temp._time._second < 0)
	{
		temp._time._minute--;
		temp._time._second += 60;
	}
	long minute = second / 60;
	temp._time._minute -= minute % 60;
	if (temp._time._minute < 0)
	{
		temp._time._hour--;
		temp._time._minute += 60;
	}
	long hour = minute / 60;
	temp._time._hour -= hour % 24;
	if (temp._time._hour < 0)
	{
		temp._date._day--;
		temp._time._hour += 24;
	}
	temp._date._day -= hour / 24;
	while (1)
	{
		if (temp._date.is_leap())
			_month_day[1] = 29;
		else
			_month_day[1] = 28;
		if (temp._date._day <= 0)
		{
			if (temp._date._month == 1)
			{
				temp._date._year--;
				temp._date._month = 12;
			}
			else
				temp._date._month--;
			temp._date._day += _month_day[temp._date._month - 1];
		}
		else
			break;
	}
	return temp;
}
Datetime& Datetime::operator ++()
{
	_time._second++;
	if (_time._second > 59)
	{
		_time._minute++;
		_time._second -= 60;
	}
	if (_time._minute > 59)
	{
		_time._hour++;
		_time._minute -= 60;
	}
	if (_time._hour > 23)
	{
		_date._day++;
		_time._hour -= 24;
	}
	if (_date.is_leap())
		_month_day[1] = 29;
	else
		_month_day[1] = 28;
	if (_date._day > _month_day[_date._month - 1])
	{
		_date._day -= _month_day[_date._month - 1];
		if (_date._month == 12)
		{
			_date._year++;
			_date._month = 1;
		}
		else
			_date._month++;
	}
	return *this;
}
Datetime& Datetime::operator --()
{
	_time._second--;
	if (_time._second < 0)
	{
		_time._minute--;
		_time._second += 60;
	}
	if (_time._minute < 0)
	{
		_time._hour--;
		_time._minute += 60;
	}
	if (_time._hour < 0)
	{
		_date._day--;
		_time._hour += 24;
	}
	if (_date.is_leap())
		_month_day[1] = 29;
	else
		_month_day[1] = 28;
	if (_date._day < 1)
	{
		if (_date._month == 1)
		{
			_date._year--;
			_date._month = 12;
		}
		else
			_date._month--;
		_date._day += _month_day[_date._month - 1];
	}
	return *this;
}
bool Datetime::operator < (const Datetime& dt) const
{
	if (_date._year < dt._date._year)
		return true;
	if (_date._year > dt._date._year)
		return false;
	if (_date._month < dt._date._month)
		return true;
	if (_date._month < dt._date._month)
		return false;
	if (_date._day < dt._date._day)
		return true;
	if (_date._day > dt._date._day)
		return false;
	if (_time._hour < dt._time._hour)
		return true;
	if (_time._hour > dt._time._hour)
		return false;
	if (_time._minute > dt._time._minute)
		return true;
	if (_time._minute < dt._time._minute)
		return false;
	if (_time._second > dt._time._second)
		return true;
	else
		return false;
}
bool Datetime::operator ==(const Datetime& dt) const
{
	int count = 0;
	if (_date._year == dt._date._year)
		++count;
	if(_date._month == dt._date._month)
		++count;
	if (_date._day == dt._date._day)
		++count;
	if (_time._hour == dt._time._hour)
		++count;
	if (_time._minute == dt._time._minute)
		++count;
	if (_time._second == dt._time._second)
		++count;
	if (count == 6)
		return true;
	else
		return false;
}