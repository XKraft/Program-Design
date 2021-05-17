# Assignment 8

#### 一、概念题

1.

（1）多继承的含义：指一个类可以有两个或者两个以上的直接基类。

（2）当多个基类中包含同名函数时，它们在派生类中就会出现二义性。C++通过基类名受限来消除二义性。

```c++
//例子
class A
{
    int m;
public:
    int f();
};
class B
{
    int n;
public:
    int f();
};
class C: public A, public B
{
    int r;
public:
    int g()
    {
        A::f();//调用A中的f
        B::f();//调用B中的f
    }
};
```

2.

（1）优缺点：

继承与封装存在矛盾，聚合和组合则否。

继承更容易实现子类型，而聚合和组合关系的两个不具有子类型关系。

（2）适用的场景

如果复用的类与基类具有is a kind of的关系，或者需要当作子类型使用，则应该采用继承的方式实现代码复用。如果存在is a part of的关系，则更适合以聚合和组合的方式实现复用。

#### 二、编程题

1.

构造顺序：Object()->Base()->Derived1()->Object()->Derived2()->Mid()->Object()->Derived1()->Object()->Base()->Object()->Derived2()->Final()

在多继承中，对基类的说明次序决定基类构造函数的调用次序，所以依次调用Mid(),Object(),Derived1(),,而在调用Mid()前，由于Mid的基类是由虚基类Base继承而来，所以优先调用Base的构造函数，而在调用Base的构造函数前，应该调用Base的基类Object的构造函数，在调用完Base的构造函数后，再按照Mid中的说明次序依次调用Derived1，Derived2的构造函数，而Derived2中还有成员对象，应该先调用成员对象Object的构造函数，再调用Derived2的构造函数，Mid的基类的构造函数调用完后，再调用Mid自己的构造函数，至此Final的基类Mid的构造完毕，接着调用Object的构造函数，再调用Derived1的构造函数，而Derived1与MId具有公共的基类Base，所以不再调用Base的构造函数，最后初始化Final的成员对象Derived2，则应该先调用其基类的构造函数，而Base又是继承而来，则应最先调用object的构造函数，再调用Base的构造函数，之后因为Derived2含有成员对象Object，所以再调用Object的构造函数，最后调用Derived2的构造函数，最后进入Final自己的构造函数，至此初始化完毕。

析构顺序：Final()->Derival2()->Object()->Base()->Object()->Derived1()->Object()->Mid()->Derived2()->Object()->Derived1()->Base()->Object()

析构与构造顺序相反

2.

```C++
#pragma once
typedef char byte;
int double_compare(const void* p1, const void* p2) {
	if (*(double*)p1 > *(double*)p2)
		return 1;
	else if (*(double*)p1 < *(double*)p2)
		return -1;
	else
		return 0;
}

void merge_sort(void* base, unsigned int count, unsigned int element_size,int (*cmp)(const void*, const void*)) 
{
	for (unsigned int i = 1; i <= count; i *= 2)
	{
		byte* temp = new byte[i * 2 * element_size];
		for (unsigned int j = 0; j + i < count; j += i * 2)
		{
			unsigned int m = 0, n = 0, k = 0;
			while ( m < i && n < i && j + i + n < count)
			{
				if (cmp((byte*)base + (j + m) * element_size, (byte*)base + (j + i + n) * element_size) == 1)
				{
					for (unsigned int a = 0; a < element_size; ++a)
						temp[k++] = ((byte*)base)[(j + i + n) * element_size + a];
					++n;
				}
				else
				{
					for (unsigned int a = 0; a < element_size; ++a)
						temp[k++] = ((byte*)base)[(j + m) * element_size + a];
					++m;
				}
			}
			while (m < i)
			{
				for (unsigned int a = 0; a < element_size; ++a)
					temp[k++] = ((byte*)base)[(j + m) * element_size + a];
				++m;
			}
			while (n < i && j + i + n < count)
			{
				for (unsigned int a = 0; a < element_size; ++a)
					temp[k++] = ((byte*)base)[(j + i + n) * element_size + a];
				++n;
			}
			k = 0;
			for (unsigned int b = 0; b < 2 * i && j + b < count; ++b)
				for (unsigned int a = 0; a < element_size; ++a)
					((byte*)base)[(b + j) * element_size + a] = temp[k++];
		}
		delete []temp;
	}
}
```

