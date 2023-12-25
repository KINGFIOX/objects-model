#include <cstdio>
#include <iostream>
using namespace std;

class Base1 {
public:
    int m_b1i;

public:
    Base1()
    {
        printf("Base1::Base1()的this =\t%p\n", this);
    }
};

class Base2 {
public:
    int m_b2i;

public:
    Base2()
    {
        printf("Base2::Base2()的this =\t%p\n", this);
    }
};

class Derived : public Base1, public Base2 {
public:
    int m_di;

public:
    Derived()
    {
        printf("Base2::Base2()的this =\t%p\n", this);
    }
};

int main(void)
{
    printf("sizeof(Base1)\t=\t%lu\n", sizeof(Base1));
    printf("sizeof(Base2)\t=\t%lu\n", sizeof(Base2));
    printf("sizeof(Derived)\t=\t%lu\n", sizeof(Derived));
    printf("&Derived::m_b1i\t=\t%p\n", &Derived::m_b1i);
    printf("&Derived::m_b2i\t=\t%p\n", &Derived::m_b2i);
    printf("&Derived::m_di\t=\t%p\n", &Derived::m_di);
    Base2* pbase2 = new Derived();
    // delete pbase2; // 这里在删除的时候遇到问题
    // delete (Base1*)pbase2;  // 这里也是遇到了问题
    // delete reinterpret_cast<Base1*>(pbase2); // 也遇到了问题
    delete ((char*)(pbase2)-4); // 这里就正常
    printf("delete pbase2;");
    return 0;
}