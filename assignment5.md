#### 一. 概念题 

###### 1.1 C++所提供的隐式赋值操作存在什么样的问题？如何解决这样的问题？ 

当成员对象中含有指针类型的数据成员时，两个对象中的指针指向同一个区域，使得两个对象都能对指针指向的区域的值进行改变。尤其是当该指针指向动态数据时，当对象消亡时，会对同一块内存进行多次归还。

应该为该类对象提供一个显示的赋值操作，对被赋值对象的指针重新分配内存。

###### 1.2 请简述拷贝构造函数与赋值操作符"="重载函数的区别. 

拷贝构造函数只能用于对象的初始化，而赋值操作符“=”重载函数既可以用于赋值，也可以达到等价的初始化作用。

当对对象初始化时，会最先调用拷贝构造函数，而不会去调用赋值操作符“=”重载函数。

当函数返回一个对象时，如果不加引用，返回的是一个临时空间，如果没有拷贝构造函），该临时空间也不能正常赋值给=操作符（重载的=参数不是右值引用）左边的对象。

###### 1.3 为什么会对操作符new和delete进行重载？ 

系统提供的new和delete是调用系统的堆内存管理来进行动态内存的分配与归还。而系统的堆内存管理要考虑各种堆内存的分配与归还，还会面临“碎片”问题。其效率并不高。对操作符new和delete进行重载，使得程序能以自己的方式来实现动态对象空间的分配和释放功能，可以提高内存分配和归还的效率。

###### 1.4 C++是如何实现λ表达式的？

通过函数对象来实现。当使用一个λ表达式时，会隐式定义一个类，类的数据成员对应表达式中使用到的环境变量。重载函数调用操作符，使该对象可以作为函数对象来使用，重载函数按表达式中的功能来实现。然后创建一个临时对象，再使用到上述表达式的地方就用临时对象来代替。

#### 二. 编程题 

###### 2.1 完成int型矩阵类Matrix的实现，要求补充 '?' 处内容并完成如下的接口.

```C++
class Matrix
{
	int** p_data;
	int row, col;
public:
	Matrix(int r, int c); //构造函数
	Matrix(const Matrix& m);//拷贝构造函数
	~Matrix(); //析构函数
	int*& operator[] (int i); //重载[], 对于Matrix对象m, 能够通过m[i][j]访问第i+1行、第j + 1列元素
	Matrix & operator = (const Matrix & m); //重载=, 实现矩阵整体赋值, 若行/列不等, 归还空间并重新分配
	bool operator == (const Matrix& m) const; //重载==, 判断矩阵是否相等
	Matrix operator + (const Matrix& m) const; //重载+, 完成矩阵加法, 可假设两矩阵满足加法条件(两矩阵行、列分别相等)
	Matrix operator * (const Matrix& m) const; //重载*, 完成矩阵乘法, 可假设两矩阵满足乘法条件(this.col = m.row)
};
Matrix::Matrix(int r, int c)
{
	row = r;
	col = c;
	p_data = new int* [r];
	if (!p_data) exit(-1);
	for (int i = 0; i < r; ++i)
	{
		p_data[i] = new int[c];
		if (!p_data[i]) exit(-1);
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			p_data[i][j] = 0;
}
Matrix::Matrix(const Matrix& m)
{
	row = m.row;
	col = m.col;
	p_data = new int* [row];
	if (!p_data) exit(-1);
	for (int i = 0; i < row; ++i)
	{
		p_data[i] = new int[col];
		if (!p_data[i]) exit(-1);
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			p_data[i][j] = m.p_data[i][j];
}
Matrix::~Matrix()
{
	for (int i = 0; i < row; ++i)
		delete[]p_data[i];
	delete[]p_data;
}
int*& Matrix::operator[] (int i)
{
	if (i >= row)
		exit(-2);
	return p_data[i];
}
Matrix& Matrix::operator = (const Matrix& m)
{
	if (m.col != col || m.row != row)
	{
		for (int i = 0; i < row; ++i)
			delete[]p_data[i];
		delete[]p_data;//归还内存
		
		row = m.row;
		col = m.col;
		p_data = new int* [row];
		if (!p_data) exit(-1);
		for (int i = 0; i < row; ++i)
		{
			p_data[i] = new int[col];
			if (!p_data[i]) exit(-1);
		}//重新分配空间
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			p_data[i][j] = m.p_data[i][j];
	return *this;
}
bool Matrix::operator == (const Matrix& m) const
{
	if (m.col != col || m.row != row)
		return false;
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (p_data[i][j] != m.p_data[i][j])
				return false;
	return true;
}
Matrix Matrix::operator + (const Matrix& m) const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			temp.p_data[i][j] = p_data[i][j] + m.p_data[i][j];
	return temp;
}
Matrix Matrix::operator * (const Matrix& m) const
{
	Matrix temp(row, m.col);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < m.col; ++j)
			for (int k = 0; k < col; ++k)
				temp.p_data[i][j] += p_data[i][k] * m.p_data[k][j];
	return temp;
}
```

###### 2.2 设计一种能解决教材例6-10中把存储块归还到堆空间的方法. (提 示：可以在每次申请存储块时多申请一个能存储一个指针的空间，用 该指针把每个存储块链接起来.)

```c++
class A
{
public:
	static void* operator new(size_t size);
	static void operator delete(void* p);
	static void deleteall();
private:
	A* next; //用于组织A类对象自由空间结点的链表。
	static A* p_free; //用于指向A类对象的自由空间链表头。
	static A** pp_free;//想法是利用一个动态数组储存每个区块的首地址
	static int region_nums;//区块数
};
A* A::p_free = NULL;
A** A::pp_free = NULL;
int A::region_nums = 0;
const int NUM = 32;
void* A::operator new(size_t size)
{
	if (p_free == NULL)
	{	//申请NUM个A类对象的大空间。
		p_free = (A*)malloc(size * NUM);  //一个动态数组
		  //在大空间上建立自由结点链表。
		for (int i = 0;i < NUM - 1; i++)
			p_free[i].next = &p_free[i + 1];
		p_free[NUM - 1].next = NULL;

		++region_nums;//区块数加一
		A** p = (A**)malloc(sizeof(A*) * region_nums);//建议一个新的储存区块首地址的数组
		for (int i = 0; i < region_nums - 1; ++i)
			p[i] = pp_free[i];//将已储存的地址拷贝到新的数组
		p[region_nums - 1] = p_free;//将新开辟的区块的首地址储存到数组中
		free(pp_free);
		pp_free = p;
		p = NULL;
	}
	//从链表中给当前对象分配空间
	A* p = p_free;
	p_free = p_free->next;
	memset(p, 0, size);
	return p;
}
void A::operator delete(void* p)
{
	((A*)p)->next = p_free;
	p_free = (A*)p;
}
void A::deleteall()
{
	for (int i = 0; i < region_nums; ++i)
		free(pp_free[i]);
	free(pp_free);
	pp_free = NULL;
}
```

