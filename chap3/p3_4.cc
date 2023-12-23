#include <cstdio>
#include <iostream>

using namespace std;

class Base1 {
public:
    virtual void f()
    {
        cout << "Base1::f()" << endl;
    }

    virtual void g()
    {
        cout << "Base1::g()" << endl;
    }
};

class Base2 {
public:
    virtual void h()
    {
        cout << "base2::h()" << endl;
    }

    virtual void i()
    {
        cout << "Base2::i()" << endl;
    }
};

class Derived : public Base1, public Base2 {
public:
    virtual void f()
    {
        cout << "Derived::f()" << endl;
    }

    virtual void i()
    {
        cout << "Derived::i()" << endl;
    }
    virtual void h()
    {
        cout << "Derived::h()" << endl;
    }
    // 这个是类自己的
    virtual void mh()
    {
        cout << "Derived::mh()" << endl;
    }
    virtual void mi()
    {
        cout << "Derived::mi()" << endl;
    }
    virtual void mj()
    {
        cout << "Derived::mj()" << endl;
    }
};

int main(void)
{
    // 大小
    cout << sizeof(Base1) << endl;
    cout << sizeof(Base2) << endl;
    cout << sizeof(Derived) << endl;
    cout << "----------" << endl;

    Derived ins;
    Base1& b1 = ins;
    Base2& b2 = ins;
    Derived& d = ins;

    using Func = void (*)();

    long* pderived1 = (long*)(&d);
    long* vptr1 = (long*)(*pderived1);

    long* pderived2 = pderived1 + 1;
    long* vptr2 = (long*)(*pderived2);

    /**/

    cout << "vptr1" << endl;

    Func f0 = (Func)vptr1[0]; // (Func) 0x0000000100006edc (p3_4.out`Derived::f() at p3_4.cc:35)
    Func f1 = (Func)vptr1[1]; // (Func) 0x0000000100006f18 (p3_4.out`Base1::g() at p3_4.cc:14)

    // 这一条语句确实有点奇怪，在vs2017，这个就是明确在vptr2的
    Func f2 = (Func)vptr1[2]; // (Func) 0x0000000100006f54 (p3_4.out`Derived::i() at p3_4.cc:40)

    Func f3 = (Func)vptr1[3]; // (Func) 0x0000000100006f90 (p3_4.out`Derived::mh() at p3_4.cc:45)
    Func f4 = (Func)vptr1[4]; // (Func) 0x0000000100006fcc (p3_4.out`Derived::mi() at p3_4.cc:49)
    Func f5 = (Func)vptr1[5]; // (Func) 0x0000000100007008 (p3_4.out`Derived::mj() at p3_4.cc:53)
    Func f6 = (Func)vptr1[6]; // 非法
    Func f7 = (Func)vptr1[7];

    cout << "----------" << endl;

    cout << "vptr2" << endl;

    // 突然发现一个比较有趣的事情，就是我用lldb调试，这个地址每次都是一样的
    Func f00 = (Func)vptr2[0]; // (Func) 0x0000000100007044 (p3_4.out`Base2::h() at p3_4.cc:22)
    Func f11 = (Func)vptr2[1]; // (Func) 0x0000000100007080 (p3_4.out`non-virtual thunk to Derived::i() at p3_4.cc)
    Func f22 = (Func)vptr2[2]; // 非法
    Func f33 = (Func)vptr2[3];

    cout << "----------" << endl;

    b1.f();
    b2.i();
    d.f();
    d.i();
    d.mh();
}