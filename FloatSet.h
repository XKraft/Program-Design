#include<iostream>
using namespace std;
class FloatSet
{
	float* numbers;
	int length, max_length;
	// 可根据需要添加其他成员变量
public:
	FloatSet();
	FloatSet(const FloatSet& s);
	~FloatSet();
	bool is_empty() const; //判断是否为空集
	int size() const; //获取元素个数
	bool is_element(float e) const; //判断e是否属于集合
	bool is_subset(const FloatSet& s) const; //判断集合是否包含于s
	bool is_equal(const FloatSet& s) const; //判断集合是否相等
	bool insert(float e); //将元素e加⼊集合，成功返回true，否则返回false(e已属于集合)
	bool remove(float e); //将e从集合中删除，成功返回true，否则返回false(e不属于集合)
	void display() const; //打印集合所有元素
	FloatSet union2(const FloatSet& s) const; //计算集合和s的并集
	FloatSet intersection2(const FloatSet& s) const; //计算集合和s的交集
	FloatSet difference2(const FloatSet& s) const; //计算集合和s的差
};
FloatSet::FloatSet()
{
	max_length = 10;
	numbers = new float[max_length];
	if (!numbers) exit(-1);
	length = 0;
}
FloatSet::FloatSet(const FloatSet& s)
{
	max_length = s.max_length;
	numbers = new float[s.max_length];
	length = s.length;
	for (int i = 0; i < length; ++i)
		numbers[i] = s.numbers[i];
}
FloatSet::~FloatSet()
{
	delete[]numbers;
	numbers = NULL;
}
bool FloatSet::is_empty() const //判断是否为空集
{
	if (!length)
		return true;
	else
		return false;
}
int FloatSet::size() const //获取元素个数
{
	return length;
}
bool FloatSet::is_element(float e) const//判断e是否属于集合
{
	for (int i = 0; i < length; ++i)
		if (numbers[i] == e)
			return true;
	return false;
}
bool FloatSet::is_subset(const FloatSet& s) const //判断集合是否包含于s
{
	if (length >= s.length)
		return false;
	int count = 0;
	for (int i = 0; i < length; ++i)
		for (int j = 0; j < s.length; ++j)
			if (is_element(s.numbers[j]))
			{
				++count;
				break;
			}
	if (count == length)
		return true;
	else
		return false;
}
bool FloatSet::is_equal(const FloatSet& s) const//判断集合是否相等
{
	if (length != s.length)
		return false;
	for (int i = 0; i < length; ++i)
		for (int j = 0; j < s.length; ++j)
			if (!is_element(s.numbers[j]))
				return false;
	return true;
}
bool FloatSet::insert(float e)//将元素e加⼊集合，成功返回true，否则返回false(e已属于集合)
{
	if (is_element(e))
		return false;
	if (length + 1 > max_length)
	{
		max_length += 10;
		float* p = new float[max_length];
		if (!p) exit(-1);
		for (int i = 0; i < length; ++i)
			p[i] = numbers[i];
		delete[]numbers;
		numbers = p;
		p = NULL;
	}
	numbers[length] = e;
	length++;
}
bool FloatSet::remove(float e)//将e从集合中删除，成功返回true，否则返回false(e不属于集合)
{
	if (is_empty())
		return false;
	for (int i = 0; i < length; ++i)
	{
		if (numbers[i] == e)
		{
			for (int j = i; j < length - 1; ++j)
				numbers[j] = numbers[j + 1];
			length--;
		}
	}
	return false;
}
void FloatSet::display() const //打印集合所有元素
{
	for (int i = 0; i < length; ++i)
		cout << numbers[i] << " ";
}
FloatSet FloatSet::union2(const FloatSet& s) const//计算集合和s的并集
{
	FloatSet s1(s);
	for (int i = 0; i < length; ++i)
		if (s.is_element(numbers[i]))
			s1.insert(numbers[i]);
	return s1;
}
FloatSet FloatSet::intersection2(const FloatSet& s) const //计算集合和s的交集
{
	FloatSet s1;
	for (int i = 0; i < length; ++i)
		if (s.is_element(numbers[i]))
			s1.insert(numbers[i]);
	return s1;
}
FloatSet FloatSet::difference2(const FloatSet& s) const //计算集合和s的差
{
	FloatSet s1;
	for (int i = 0; i < length; ++i)
		if (!s.is_element(numbers[i]))
			s1.insert(numbers[i]);
	return s1;
}