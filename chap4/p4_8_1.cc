#include <cstdio>
#include <iostream>
using namespace std;

class Grand {
public:
    int m_grand;
};

class A1 : virtual public Grand {
public:
};

class A2 : virtual public Grand {
public:
};

class C1 : public A1, public A2 {
public:
};

int main(void)
{
    C1 c;
    long* pvbptr1 = (long*)&c; // 虚基类指针
    long* pvbptr2 = (long*)&c + 1; // 虚基类指针
    printf("%p\n", pvbptr1);
    printf("%p\n", pvbptr2);

    cout << sizeof(Grand) << endl; // 4
    cout << sizeof(A1) << endl; // 16
    cout << sizeof(A2) << endl; // 16
    cout << sizeof(C1) << endl; // 24
}