# string_课时2

## 模版之问

我们知道标准库中的`string`实际是`basic_string`模版类关于`char`的实例化。而在《string》,也就是上篇文章里，官方文档其实已经说了`string`为模版的原因：

![image-20241017170223725](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410171702925.png)

一句话来说，这是为了让C++国际化，可以让不同国家和地区的字符语言需求都得到满足。本片文章的主要内容是实现一个基本的`string`类，但我们不会采用模版的方式，因为这涉及到一些我们还未学习的内容，再加上我们文档已经说了，对于多字节字符以及变长字符`string`都可以使用，所以我们就直接用`char`类型了，等以后对C++的学习更上一层楼后再回来真正地实现。

下面我们稍微过一过字符的主要编码模式：

当今计算机都是二进制的，为了让字符与二进制序列建立映射关系，就出现了ASCII码。ASCII码只有一个字节，它对于英语等拉丁字母语言差不多够用，但其它语言就不太够用了，所以就有人研究出了`Unicode`，其中最常用的就是`UTF-8`:

![image-20241017172651572](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410171726630.png)

如图所见`UTF-8`是一种变长编码，它的具体字节数并不确定，有一字节，两字节，三字节，四字节这四种。不过对于常用的汉字来说基本都在两字节。`UTF-8`的变长属性，可以使得它以更少的字节存储字符，但它的变长属性也使得它比较复杂，不易管理。不过它仍然是适用范围最广的编码格式。

为了让编码格式更适应于以汉字为基础的东亚文字字符系统，中国信息化技术标准委员会以`UTF-8`为基础，推出了`GBK`系列编码格式，以下为百度百科的相关描述：

![image-20241017182940363](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410171829406.png)

`Windows`系统主要是以GBK系列编码格式进行汉化的，微软的其它产品，例如VS，office他们的汉化也都主要用GBK系列。`Linux`系统则更喜欢使用`UTF-8`。

## 基本实现

我们的`string`其实就四个成员：字符串空间的索引指针，有效字符个数，可容纳个数，静态成员`npos`。不过我们先只写前三个成员，后续会用`npos`引出一些C++特别语法。

```cpp
namespace wind
{
	class string
	{
	public:
		
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
```

### string(const char* str)

我们在先前说过，对于构造函数来说，应尽可能使用初始化列表进行初始化，除此之外，我们还说了初始化列表的初始化顺序是依照声明顺序，而不是初始化列表顺序，这意味着，写初始化列表要以声明顺序来写，防止因顺序问题出现错误。

```cpp
wind::string::string(const char* str)
	:_str(nullptr)
	,_size(strlen(str))
	,_capacity(_size)
{
	// 注意，_capacity指的是可以容纳的有效字符个数
	// 它与开辟空间的大小不是同一概念
	// 为了兼容C语言，开辟空间的最后一个字符必须是'\0'
	// 而char* str身为C中的字符串最后一位就是'\0'
	// 所以_capacity的初始化是就是char* str的长度

	_str = new char[_capacity + 1];
	// 留一个成员空间，用来放`\0`

	strcpy(_str, str);
	// 严格来说，应该用memcpy，但既然确定
	// 不使用模版而使用char来写
	// 那就用C中的字符串相关函数
}

/*
// 因为初始化列表的初始化顺序是按照声明来写的
// 所以会先执行_str(new char[_capacity + 1])
// 但此时_size还未被定义
// 从而引发错误
wind::string::string(const char* str)
	:_size(strlen(str))
	,_capacity(_size + 1)
	,_str(new char[_capacity + 1])
{
	// 略
}
*/
```

### ~string()

```cpp
// 这真的没什么好说的
wind::string::~string()
{
	delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}
```

### string()

```cpp
wind::string::string()
	:_str(new char[1] {0})
	,_size(0)
	,_capacity(0)
{
	// C语言规定字符串的最后一位是'\0'
	// 这对空字符串仍然使用，所以要再
	// 开辟一个成员空间存放'\0'
	
	// 前面说过，我们的STL是SGI版本的
	// 之前我们试过，P.J.版本的string
	// 无参构造是会开辟多个空间的
	// 很明显打印P.J.版本的空string
	// 对象是不会打印出任何东西的
	// 所以个人猜测P.J.版本的空string
	// 对象最起码开头也要上道保险性质的'\0'
	// 防止打印出其它内容
}
```

可以把`string(const char* str)`和`string()`使用缺省值进行合并，`string(const char* str = "")`，由于C语言规定常量字符串必须以`\0`结尾，所以空字符串`""`其实并不完全空，后面还有一个`\0`，但这里就不合并了，因为合并之后会让文章逻辑不够顺畅。而且我还要重新排版。

### size_t size()const

```cpp
size_t wind::string::size()const
{
	return _size;
}
```

### size_t capacity()const

```cpp
size_t wind::string::capacity()const
{
	return _capacity;
}
```

### operator[]

```cpp
char& wind::string::operator[](size_t pos)
{
	assert(pos < _size);
	return _str[pos];
}

const char& wind::string::operator[](size_t pos)const
{
	assert(pos < _size);
	return _str[pos];
}
```

### iterator

```cpp
namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		string(const char* str);
		string();
		~string();
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		size_t size()const;
		size_t capacity()const;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}

wind::string::iterator wind::string::begin()
{
	return _str;
}

wind::string::iterator wind::string::end()
{
	return _str + _size;
}

wind::string::const_iterator wind::string::begin()const
{
	return _str;
}

wind::string::const_iterator wind::string::end()const
{
	return _str + _size;
}
```

### reserve

```cpp
void wind::string::reserve(size_t n)
{
	// 以前试过的，对于小于当前容量的参数
	// SGI和P.J.函数都不作处理
	if (n > _capacity)
	{
		// 注意，_capacity指的是可容纳的有效数据个数
		// 不是开辟空间的成员个数，要额外加一存'\0'

		// C++没原地扩容
		// 所以就new出来一个新空间
		// 然后再从原空间里拷贝内容

		auto p = new char[n + 1];
		strcpy(p, _str);
		delete[] _str;
		_str = p;
		_capacity = n;
	}
}
```

### push_back

```cpp
void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		reserve(_capacity * 2);
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}
```

### append

```cpp
void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		// 为了防止_capacity初始值为0
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}
```

### operator+=

```cpp
wind::string& wind::string::operator+=(const char ch)
{
	this->push_back(ch);
	return *this;
}

wind::string& wind::string::operator+=(const char* str)
{
	this->append(str);
	return *this;
}
```

### npos

这是第四个成员变量，它是一个静态无符号整型变量。我们前面说过，静态成员变量是类共用的，所以不会定义在初始化列表中，因此声明中不能给缺省值，理论上应该都定义在声明外，就像这样：

```cpp
// .h
namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator cbegin()const;
		const_iterator cend()const;
		string(const char* str);
		string();
		~string();
		void reserve(size_t n);
		char& operator[](size_t pos);
		string& operator+=(const char ch);
		string& operator+=(const char* str);
		const char& operator[](size_t pos)const;
		void push_back(const char ch);
		void append(const char* str);
		size_t size()const;
		size_t capacity()const;
		string& insert(size_t pos, const char* str);
		string& insert(size_t pos, const string& s);
		string& erase(size_t pos = 0, size_t len = npos);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		const static size_t npos = -1;
	};
}


// .cpp
const size_t wind::string::npos = -1;
```

但C++标准委员会对静态整型成员变量开了一个特例：它可以在声明中给缺省值。之所以说是特例，是因为静态整型成员变量才能这样做，静态浮点型，静态字符型等都不能给声明缺省，而必须在声明外定义，之前不说这个，是因为这个特例是反逻辑的，会干扰我们的学习逻辑。

```cpp
char* _str;
size_t _size;
size_t _capacity;
const static size_t npos = -1;
```

### insert

```cpp
wind::string& wind::string::insert(size_t pos, const char* str)
{
	// 插入位置合法性检查
	assert(pos <= _size);
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}
	size_t source = _size;
	size_t destination = _capacity;

	// 因为下标使用无符号整型
	// 所以很容易出现((size_t)-1) > ((size_t)others)

	// 强制类型转换或者把sour和dest用int类型也不行
	// 一是可能存在int溢出危险
	// 二是C++和C都有一个“算数转换”的说法：
	// 如果某个操作符的各个操作数属于不同的类型，那么
	// 除⾮其中⼀个操作数的转换为另⼀个操作数的类型
	// 否则操作就⽆法进⾏
	// 当int与size_t作比较时，int会被自动强转为size_t

	// 亦不能使用strcpy，因为待填充的空间可能与有限成员空间重叠
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// 退出循环，无非是两种情况：
	// source == 0：source已经处于临界值，再减就要变成最大值了
	// source < pos：不用再拷贝了
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// strcpy有'\0'，所以不能用
	memcpy(_str + pos, str, strlen(str));


	_size += len;

	return *this;
}

wind::string& wind::string::insert(size_t pos, const string& s)
{
	this->insert(pos, s._str);
	return *this;
}

wind::string& wind::string::insert(size_t pos, const char ch)
{
	assert(pos <= _size);
	if (_size == _capacity)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	size_t source = _size;
	size_t destination = source + 1;
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	_str[pos] = ch;
	_size++;
	return *this;
}
```

### relational

逻辑运算符在标准库中是以非成员函数的形式出现的，这是为了让运算符使用的更加灵活，第一个参数也可以不是对象，而是一个C中的字符串。

```cpp
const char* wind::string::c_str()
{
	return _str;
}

const char* wind::string::c_str()const
{
	return _str;
}

bool wind::operator>(const wind::string& s1, const wind::string& s2)
{
	// 模版当然不是这样写的，可能是以迭代器或者[]重载的形式
	// 一个个比较成员，但我们这里不是用模版的，所以就直接用
	if (strcmp(s1.c_str(), s2.c_str()) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) > 0)
		return true;
	else
		return false;
}


bool wind::operator==(const wind::string& s1, const wind::string& s2)
{
	if (strcmp(s1.c_str(), s2.c_str()) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) == 0)
		return true;
	else
		return false;
}


bool wind::operator<(const wind::string& s1, const wind::string& s2)
{
	if (s1 > s2 || s1 == s2)
		return false;
	else
		return true;
}

bool wind::operator<(const wind::string& s, const char* str)
{
	if (s > str || s == str)
		return false;
	else
		return true;
}

bool wind::operator<(const char* str, const string& s)
{
	if (str > s || str == str)
		return false;
	else
		return true;
}
// 其它就先不写了
```

### IO

在C++中，为了对多个对象进行流提取，会像C那样，把'\0'和'\n'默认为间隔符而不被读取，此时就要用`istream`的成员函数`get`，`get`会返回不加处理的原字符，同时，也支持指定某个字符为间隔符，获得一个字符串。

```cpp
std::ostream& wind::operator<<(std::ostream& out, const string& s)
{
	for (auto ch : s)
	{
		out << ch;
	}
	return out;
}

std::istream& wind::operator>>(std::istream& in, string& s)
{
	s.clear();
	// 为了区分多个对象的流提取
	// C++或者C默认以空格和换行为分隔符
	// 但这也为包含空格字符串的提取
	// 造成了困难，istream中的成员
	// 函数get可以自定义分隔符


	//// 空格和换行会被默认为分隔符
	//// 所以不会被提取
	//// 这会使得程序进入死循环
	//char ch;
	//in >> ch;
	//while (ch != ' ' && ch != '\n')
	//{
	//	s += ch;
	//}

	
	/*
	char ch;
	ch = in.get();
	while (ch != ' ' && ch != '\n')
	{
		s += ch;
	}
	这种写法虽然可行
	但扩容频繁效率较低
	*/

	// 字符缓冲区
	char buff[16];
	int curr = 0;
	char tmp;
	do
	{
		// 字符先存储入缓冲区
		tmp = in.get();
		buff[curr++] = tmp;

		// 当缓冲区满后
		// 一次性存入
		if (curr == 15)
		{
			buff[curr] = '\0';
			curr = 0;
			s += buff;
		}
	}while (tmp != ' ' && tmp != '\n');

	// 跳出循环，说明上一个位是
	// 终止位，将其改为'\0'
	buff[curr - 1] = '\0';
	s += buff;

	return in;
}

wind::string& wind::string::get(char delim, std::istream& in)
{
	char buff[16];
	int curr = 0;
	char tmp;
	do
	{
		tmp = in.get();
		buff[curr++] = tmp;

		if (curr == 15)
		{
			buff[curr] = '\0';
			curr = 0;
			*this += buff;
		}
	} while (tmp != delim);

	buff[curr - 1] = '\0';
	*this += buff;

	return *this;
}
```

![image-20241018132134218](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410181321367.png)

```cpp
int main()
{
	std::string s;
	// 输入"hello string"
	std::cin >> s;
	// 只会提取"hello"
	// "string"还留在缓冲区
	std::cout << s;
	return 0;
}
```

![image-20241018132034411](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410181320680.png)

### erase

```cpp
wind::string& wind::string::erase(size_t pos, size_t len)
{
	// 位置检查
	assert(pos < _size);
	// begin和end控制挪动的起始
	// 默认len不会超出有效区域
	size_t begin = pos + len;

	// len已经超出有效区域
	// 数据需要进行修正
	if (len == npos || pos + len >= _size)
	{
		// 修正起始位置
		begin = _size;
		// 修正丢弃字符个数
		len = begin - pos;
	}

	// end就是原终止位
	size_t end = _size;
	// 调整有效字符个数
	_size = _size - len;
	// 挪动未丢弃字符部分
	while (begin < end)
	{
		_str[pos++] = _str[begin++];
	}
	// 添加终止位
	_str[pos] = '\0';
	return *this;
}
```

### resize

```cpp
void wind::string::resize(size_t len, char holder)
{
	// 保证空间足够
	reserve(len);
	// 设置填充起始位置
	size_t begin = _size;
	// 修正有效字符个数
	_size = len;
	// 末尾添加终止符
	_str[_size] = '\0';

	// 填充开始
	while (begin < _size)
	{
		_str[begin++] = holder;
	}
}
```

### find

```cpp
size_t wind::string::find(const char ch, size_t pos)const
{
	assert(pos < _size);
	size_t goal = npos;
	size_t begin;
	for(begin = pos; begin < _size; begin++)
	{
		if(_str[begin] == ch)
		{
			goal = begin;
			break;
		}
	}
	return goal;
}

size_t wind::string::find(const char* str, size_t pos)const
{
	assert(pos < _size);
	size_t goal = npos;
	const char* p = strstr(_str + pos, str);
	if (p)
	{
		goal = (size_t)(p - _str);
	}
	return goal;
}

size_t wind::string::find(const wind::string& s, size_t pos)const
{
	assert(pos < _size);
	return find(_str, pos);
}
```

### swap

```cpp
void wind::string::swap(string& s)
{
	std::swap(_str, s._str);
	std::swap(_size, s._size);
	std::swap(_capacity, s._capacity);
}
```

### string

```cpp
//// 古典主义写法
//wind::string::string(const string& s)
//	:_str(new char[s._capacity + 1])
//	, _size(s._size)
//	, _capacity(s._capacity)
//{
//	strcpy(_str, s._str);
//}

// 现代主义写法
wind::string::string(const string& s)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	string tmp(s._str);

	// this->swap(tmp);
	// 省略this->也行
	swap(tmp);
}
```

古典的写法就是按照标准老老实实地去写，现代的写法则先构造一个满足要求的临时对象，然后交换一下。

### operator=

```cpp
//// 古典主义写法
//wind::string& wind::string::operator=(const wind::string& s)
//{
//	// 防止自我赋值
//	if (this != &s)
//	{
//		// 为了避免空闲空间太大或不够
//		// 直接销毁被赋值对象
//		delete _str[];
//		_str = new char[s._capacity + 1];
//		_size = s._size;
//		_capacity = s._capacity;
//		strcpy(_str, s._str);
//	}
//	return *this;
//}

//// 现代主义写法
//wind::string& wind::string::operator=(const wind::string& s)
//{
//	if (this != &s)
//	{
//		string tmp(s._str);
//		swap(tmp);
//	}
//	return *this;
//}

// 后现代主义写法
wind::string& wind::string::operator=(wind::string s)
{
	swap(s);
	return *this;
}
```

把以前的数据交换给临时对象，随临时对象的析构而析构。——把需要的从临时对象那夺过来，把不需要的扔给临时对象。

### substr

```cpp
wind::string wind::string::substr(size_t pos, size_t len)const
{
	assert(pos < _size);
	string tmp;
	if (len == npos || pos + len >= _size)
	{
		len = _size - pos;
	}
	tmp.reserve(len);
	tmp._size = len;
	tmp._str[len] = '\0';
	strncpy(tmp._str, _str + pos, len);
	return tmp;
}
```

## P.J.版本string组织形式

先来看一份代码：

```cpp
void test5()
{
	std::cout <<"std::string->" << sizeof(std::string)<<std::endl;
	std::cout <<"wind::string->" << sizeof(wind::string)<<std::endl;
}
```

`x64`环境下是

![image-20241020183721106](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410201837627.png)

在`x64`环境下，`size_t`是`unsigned long long`，它是八个字节的大小，`char*`是地址，也有八个字节，所以`sizeof(wind::string)`是24字节。

```cpp
private:
	char* _str;
	size_t _size;
	size_t _capacity;
	const static size_t npos;
```

在`x86`下，`size_t`是`unsigned int`，所以结果是12

![image-20241020183638609](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410201836361.png)

我们发现不管是`x86`还是`x64`，标准库里的大小都比我们自己的多`16`字节，这`16`字节是什么呢？

微软给`string`对象又加了一个16字节的静态数组，当有效字符个数小于16时，这些数据就会被存放在这个静态数组里，而当有效字符个数等于或者超过16之后，这个静态数组就会被完全弃用，而改用再`new`处空间的方式存储字符串。

微软这样做的原因是为了防止内存碎片的出现，当进行多次动态开辟之后，内存块间的空间就很难被利用，从而造成内存利用率低，又考虑到字符串一般都不是太长，所以微软直接为对象增了一个静态数组成员，就固定的16字节，微软的`string`大概长这个样子：

```cpp
char _buff[16];
char* _str;
size_t _size;
size_t _capacity;
```

![image-20241020185342122](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410201853765.png)

![image-20241020185508750](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410201855810.png)

![image-20241020185541659](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410201855722.png)

## SGI版本string组织形式

```shell
[wind@starry-sky ~]$ vim test.cpp
[wind@starry-sky ~]$ cat test.cpp
#include<string>
#include<iostream>

int main()
{
  std::cout <<"std::string->" << sizeof(std::string)<<std::endl;
  return 0; 
}
[wind@starry-sky ~]$ g++ test.cpp -o out
[wind@starry-sky ~]$ ./out
std::string->8
[wind@starry-sky ~]$
```

它`8`个字节。先说明一下，现在的`g++`默认`x64`。

这`8`个字节其实就是一个指针的大小，这个指针会指向一处空间，而这处空间里才存储着诸如`_size  _capacity _str`等信息。SGI的`string`从另一个角度提高效率，它使用了延迟拷贝的策略，我们上面写的拷贝构造和VS的大致相同，都是直接进行深拷贝，SGI不这样干，当发生拷贝时，它不会立刻进行深拷贝，而是把拷贝对象的指针赋给被构造对象，让这两个对象共用一处空间，而当这被构造对象要对空间写数据时，才进行深拷贝，让两个对象各用各的。

这处空间还存储着一个数据，这个数据用来描述现在有多少个对象同时使用这处空间，析构时，只对这个数据减一，而当数据为0时，才会`delete`。这个数据被称为“引用计数”。

```shell
[wind@starry-sky ~]$ vim test.cpp
[wind@starry-sky ~]$ cat test.cpp
#include<iostream>
#include<string>

int main()
{
  std::string s1("hello world");
  std::string s2(s1);
  std::cout<<(void*)s1.c_str()<<std::endl;
  std::cout<<(void*)s2.c_str()<<std::endl;
  s2[0]++;
  std::cout<<(void*)s1.c_str()<<std::endl;
  std::cout<<(void*)s2.c_str()<<std::endl;
  return 0;
}
[wind@starry-sky ~]$ g++ test.cpp -o out
[wind@starry-sky ~]$ ./out
0x1f0bc38
0x1f0bc38
0x1f0bc38
0x1f0bc68
[wind@starry-sky ~]$
```

就像进程的写时拷贝。

# 完