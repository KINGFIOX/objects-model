#include <iostream>
using namespace std;

class Base {
public:
    // void myvirfunc() { }

    int m_bi;
};

class MYACLS : public Base {
public:
    int m_i;
    int m_j;
    virtual void myvirfunc()
    {
    }
    MYACLS()
    {
        int abc = 1; // 只是为了方便添加断点
    }
    ~MYACLS()
    {
        int def = 0; // 只是为了方便添加断点
    }
};

int main(void)
{
    cout << sizeof(MYACLS) << endl; // 24
    printf("MYACLS::m_i = %d\n", &MYACLS::m_i); // 12 因为有一个 vptr 和 一个 int
    printf("MYACLS::m_j = %d\n", &MYACLS::m_j); // 16
    printf("MYACLS::m_bi = %d\n", &MYACLS::m_bi); // 0

    MYACLS myobj;

    myobj.m_bi = 9;
    myobj.m_i = 3;
    myobj.m_j = 6;

    return 0;
}