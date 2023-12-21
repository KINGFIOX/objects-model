#include <cstdio>
#include <iostream>

using namespace std;

class Base {
public:
    virtual void f() { cout << "Base::f()" << endl; }
    virtual void g() { cout << "Base::g()" << endl; }
    virtual void h() { cout << "Base::h()" << endl; }
};

class Derive : public Base {
    virtual void g() { cout << "Derive::g()" << endl; }
};

int main(void)
{
    printf("Base:\t%lu\n", sizeof(Base));
    printf("Derive:\t%lu\n", sizeof(Derive));

    printf("long:\t%lu\n", sizeof(long));

    Derive* d = new Derive(); // 指向对象的指针

    long* pvptr = (long*)d; // 指向对象的指针d转为long*类型

    long* vptr = (long*)*pvptr; // (*pvptr) 表示pvptr指向的对象，也就是Derive对象，
    // *pvptr转为long*类型，就是虚函数表的地址
}