#include <cstdio>
#include <iostream>

using namespace std;

class A {
public:
    int i;
    virtual void testfunc() { }
};

int main(void)
{
    A a;
    int ilen = sizeof(a);
    // 内存对齐，这里是16
    char* p1 = reinterpret_cast<char*>(&a);
    char* p2 = reinterpret_cast<char*>(&(a.i));
    cout << ilen << "\n";
    printf("%p\n", p1);
    printf("%p\n", p2);
    printf("%lu\n", sizeof(int));
    return 0;
}