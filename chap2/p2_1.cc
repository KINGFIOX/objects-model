#include <cstdio>

// 空类
class A {
public:
};

int main(void)
{
    A a;
    printf("ilen = %lu\n", sizeof(a));
}