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

    cout << "------------------" << endl;

    Derive* d = new Derive(); // 指向对象的指针

    long* pvptr = (long*)d; // 指向对象的指针d转为long*类型

    long* vptr = (long*)(*pvptr); // (*pvptr) 表示pvptr指向的对象，也就是Derive对象，
    // *pvptr转为long*类型，就是虚函数表的地址

    for (int i = 0; i < 5; i++) {
        printf("Derived: vptr[%d] = %p\n", i, (long*)vptr[i]);
    }

    cout << "------------------" << endl;

    Base* b = new Base(); // 指向对象的指针

    long* b_pvptr = (long*)b; // 指向对象的指针d转为long*类型

    long* b_vptr = (long*)(*b_pvptr); // (*pvptr) 表示pvptr指向的对象，也就是Derive对象，
    // *pvptr转为long*类型，就是虚函数表的地址

    for (int i = 0; i < 5; i++) {
        printf("Base: b_vptr[%d] = %p\n", i, (long*)b_vptr[i]);
    }

    cout << "------------------" << endl;

    // 来一点 俚语
    ((void (*)())(*((long*)*((long*)d))))();
    reinterpret_cast<void (*)()>((*((long*)*((long*)d))))();
    // 讲解一下
    // 1. (long*)d：将指向对象的指针转化为long*类型
    // 2. *((long*)d)：得到对象
    // 3. (long*)*((long*)d)，选取对象的第一段空间，里面存放的是vptr，
    //      vptr就相当于是一个数组名，直接解引用*((long*)*((long*)d))，得到的就是vptr[0]
    // 4. *((long*)*((long*)d))，得到vtable的第一个函数的地址
    // 5. 选取为函数指针void (*)()，然后调用

    cout << "------------------" << endl;

    // 其实也可以不用那么 俚语
    using F = void (*)();
    for (int i = 0; i < 3; i++) {
        reinterpret_cast<F>(vptr[i])();
    }

    cout << "------------------" << endl;
}