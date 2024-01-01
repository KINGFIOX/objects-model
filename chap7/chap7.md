# chap7 - 内存

## new delete 运算符，内存高级话题

1. new 内存分配

一块内存的回收，影响范围很广，远远不是 10 个字节，而是一大片。

2.

### operator::new 和 operator::delete 的调用过程

1. new

- `A* pa = new A()`
  - `operator new()`
    - `malloc()`
  - `A::A()`

2. delete

- `delete pa`
  - `A::~A()`
  - `operator delete()`
    - `free`

### operator::new[] 和 operator::delete[]

有几个元素就会调用几次 构造函数，但是 operator::new 与 operator::delete 只会调用一次

malloc 的首地址 与 new 的首地址不一样，会相差 4 个字节（unsigned int），用来存放数组的大小。
这样，编译器就会知道给我们调用几次构造，几次析构。

## 内存池

### 内存池的概念 与 实验原理概述

malloc 浪费内存，频繁分配小块内存

内存池解决的问题：

1. 减少 malloc 的次数，减少 malloc 调用次数就意味着 减少 对内存的浪费
2. 减少 malloc 的调用次数，有一些速度和效率的提升，但是提升不大

内存池的实现原理：

1. 用 malloc 申请一大块内存，要分配的时候，一点一点进行分配

```cpp
#include <cstdlib>

// 单例模式，内存池
class A {
public:
    static void* operator new(size_t size); // operator new 静态
    static void operator delete(void* phead);
    static int m_iCout; // 分配计数，每new一次，统计一次
    static int m_iMallocCount; // 每malloc一次，统计一次
private:
    A* next; // 也就这个属于链表检点自己
    static A* m_FreePosi; // 总是指向一块可以分配出去的内存的 首地址
    static int m_sTrunkCount; // 一次分配 多少倍 的 该类内存
};

int A::m_iCout = 0;
int A::m_iMallocCount = 0;

A* A::m_FreePosi = nullptr;
int A::m_sTrunkCount = 5;

void* A::operator new(size_t size)
{
    A* tmplink;
    if (m_FreePosi == nullptr) {
        // 再次malloc，相当于是：链表的尾插
        size_t realsize = m_sTrunkCount * size;
        m_FreePosi = reinterpret_cast<A*>(new char[realsize]); // 分配字节
        tmplink = m_FreePosi;

        // 链起来
        for (; tmplink != &m_FreePosi[m_sTrunkCount - 1]; ++tmplink) {
            tmplink->next = tmplink + 1;
        }
        tmplink->next = nullptr;
        ++m_iMallocCount;
    }
    tmplink = m_FreePosi;
    m_FreePosi = m_FreePosi->next;
    ++m_iCout;
    return tmplink;
}

void A::operator delete(void* phead)
{
    // 相当于是进行了：链表的 头插
    (static_cast<A*>(phead))->next = m_FreePosi;
    m_FreePosi = static_cast<A*>(phead);
}
```

### 内存池代码后续说明

其实一个程序，内存膨胀到一定程度，就会动态平衡了。

程序结束，还是要归还内存给系统的，因此，需要记录每块内存的首地址，
程序结束时记得释放

## 重载全局的 operator new 和 operator delete

上面的内存池只是一个类的内存池，并不是全局的

### placement new （定位 new）

上面的 operator new 叫做：传统 new

有 placement new，但是没有 placement delete

功能：在已经分配的原始内存中，初始化一个对象（也就是 placement new 并不分配内存）

语法：

```cpp
new (地址) 类类型(实参)
```

这个 placement new 看起来要更加灵活一些

### 重载的 operator new

## 临时对象

返回值优化

```cpp
A operator+(const A& obj1, const A& obj2) {
	A tmpobj;
	// ...
	return tmpobj;
}

void func() {
	A myobj1;
	A myobj2;
	A resultobj = myobj1 + myobj2;
}
```

这个函数会调用 4 次构造函数和 4 次析构函数（但是实际上，应该是 5 次）

1. A myobj1 默认构造
2. A myobj2 默认构造
3. A tmpobj 默认构造
4. return tmpobj 返回的时候，产生临时对象，调用拷贝构造
5. A resultobj = myobj1 + myobj2 拷贝构造，相当于是 A resultobj = tmpobj

但是 RVO， 5 或许不会产生。随着标准的更新，这个 5 结果或许不一样。
可能是编译器默认的使用了`std::move`（事实上应该就是实现的方式不同了）。
（C++17 不会有 5，但是 C++14 有 5）

```out
A::A() 默认构造
A::A() 默认构造
A::A() 默认构造
A::A() 拷贝构造
A::~A() 析构
A::A() 拷贝构造
A::~A() 析构
A::~A() 析构
A::~A() 析构
A::~A() 析构
```

### 如果有移动构造，编译器会在 返回值 的时候优先使用移动构造函数

代码示例：

```cpp
#include <iostream>
using namespace std;

class A {
public:
    A()
    {
        cout << "A::A() 默认构造" << endl;
    }
    A(const A& tmpobj)
    {
        cout << "A::A() 拷贝构造" << endl;
    }
    A(const A&& other)
    {
        cout << "A::A() 移动构造" << endl;
    }
    ~A()
    {
        cout << "A::~A() 析构" << endl;
    }
};

A operator+(const A& obj1, const A& obj2)
{
    A tmpobj; // 默认构造
    // ...
    return tmpobj; // 产生临时对象，拷贝构造
}

void func()
{
    A myobj1; // 默认构造
    A myobj2; // 默认构造
    A resultobj = myobj1 + myobj2;
}

int main(void)
{
    func();
}
```

结果

```out
A::A() 默认构造
A::A() 默认构造
A::A() 默认构造
A::A() 移动构造
A::~A() 析构
A::A() 移动构造
A::~A() 析构
A::~A() 析构
A::~A() 析构
A::~A() 析构
```
