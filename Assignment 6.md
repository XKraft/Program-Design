## Assignment 6 

#### 一、概念简答题 

1. ###### 在C++中，protected类成员访问控制的作用是什么？ 

类中protected说明的成员不可以通过类的对象使用，但可以在该类的派生类中使用。引入protected访问控制可以缓解封装与继承的矛盾。

1. ###### 请简述派生类对象的初始化和析构顺序，并简述理由，为什么需要按照这个顺序？ 

初始化顺序：调用基类的构造函数->调用派生类中成员对象的构造函数->调用派生类的构造函数

析构顺序：调用派生类的析构函数->调用成员对象的析构函数->调用基类的析构函数

理由：由于派生类由基类继承而来，派生类对基类的成员或多或少有所依赖，使用应最先调用基类的构造函数使基类部分的成员可以使用，然后再初始化成员对象。而析构时有可能在基类成员中储存动态变量，所以应该由外到内逐步归还内存。

#### 二、代码编程题 

1. ###### 下面的设计有什么问题？如何解决？

```c++
class Rectangle { //矩形类
public:
	Rectangle(double w, double h) : width(w), height(h) {}
	void set_width(double w) { width = w; }
	void set_height(double h) { height = h; }
	double get_width() const { return width; }
	double get_height() const { return height; }
	double area() const { return width * height; }
	void print() const { cout << width << " " << height << endl; }
private:
	double width; //宽
	double height; //高
};
class Square : public Rectangle {//正方形类
public:
	Square(double s) : Rectangle(s, s) {}
	void set_side(double s) { //设置边长。
		set_width(s);
		set_height(s);
	}
	double get_side() const { //获取边长。
		return get_width();
	}
};
```

从用户安全考虑，该题不适用于用public继承，使用public继承后，基类中的成员函数在派生类中的声明仍未public，用户仍然可以通过派生类的对象使用原来基类中的成员函数，但是基类中的成员函数并不符合派生类的含义，应该以protected继承。

2. ###### 在作业二中，我们定义了时间类Time，现在我们利用时间类 Time，定义一个带 时区的时间类 ExtTime。除了构造函数和时间调整函数外， ExtTime 的其它功能与 Time 类似。

```c++
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
```

###### 思考：此题适合使用public继承吗？ 和第一题比较，思考何时使用public继承？相比较public继 承，protected继承和private继承到底有什么用？

适合，因为这题中的派生类ExtTime中对基类中的成员函数基本都进行了再定义，所以可以防止用户调用基类的成员函数。当基类中的操作大多适用于派生类或者派生类对基类的成员函数基本进行了再定义时，用户在派生类中调用基类的成员函数的风险较小时，可以以public继承。而如果想限制用户在派生类的对象或者派生类的派生类中调用从基类继承来的成员时，则以private继承，如果只限制用户通过派生类调用从基类继承的成员时，则用protected继承。