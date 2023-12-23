#include <cstdio>
#include <iostream>
using namespace std;

class Base1 {
public:
    int m_i1;
    char m_c1;
};

class Base2 : public Base1 {
public:
    char m_c2;
};

class Base3 : public Base2 {
public:
    char m_c3;
};

int main(void)
{
    cout << sizeof(Base1) << endl;
    cout << sizeof(Base2) << endl;
    cout << sizeof(Base3) << endl;
    // cout << "&base3::m_i1 = " << &Base3::m_i1 << endl;
    // cout << "&base3::m_c1 = " << &Base3::m_c1 << endl;
    // cout << "&base3::m_c2 = " << &Base3::m_c2 << endl;
    // cout << "&base3::m_c3 = " << &Base3::m_c3 << endl;
    printf("%p\n", &Base3::m_i1); // 0
    printf("%p\n", &Base3::m_c1); // 4
    printf("%p\n", &Base3::m_c2); // 8
    printf("%p\n", &Base3::m_c3); // 9
}