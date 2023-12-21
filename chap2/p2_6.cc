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
};

int main(void)
{
    X x0;
    x0.m_i = 15;

    X x2(x0);

    X x3 = x0;
}