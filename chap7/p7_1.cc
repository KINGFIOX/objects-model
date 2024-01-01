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