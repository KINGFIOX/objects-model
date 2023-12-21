#include <iostream>

using namespace std;

class X {
public:
    int m_i;
    X(const X& tmpx)
    {
        m_i = tmpx.m_i;
        cout << "X类的拷贝构造函数被调用" << endl;
    }
    X()
    {
        m_i = 0;
        cout << "X类的默认构造函数被调用" << endl;
    }
    ~X()
    {
        cout << "X类的析构函数被调用" << endl;
    }
    X(int value)
        : m_i(value)
    {
        cout << "X类的构造函数被调用" << endl;
    }
};

int main(void)
{
    cout << "----begin----" << endl;
    X x10(1000);
    cout << "-----------" << endl;
    X x11 = 1000;
    cout << "-----------" << endl;
    X x12 = X(1000);
    cout << "-----------" << endl;
    X x13 = (X)1000;
    cout << "-----------" << endl;
    X x14 { 1000 };
    cout << "----end----" << endl;
}