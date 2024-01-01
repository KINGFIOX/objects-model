#include <cstdlib>

// 单例模式，内存池
class A {
public:
    static void* operator new(size_t size); // operator new 静态
    static void operator delete(void* phead);
    static int m_iCout; // 分配计数，每new一次，统计一次
    static int m_iMallocCount; // 每malloc一次，统计一次
private:
    A* next; // 也就这个属于链表检点自己
    static A* m_FreePosi; // 总是指向一块可以分配出去的内存的 首地址
    static int m_sTrunkCount; // 一次分配 多少倍 的 该类内存
};

int A::m_iCout = 0;
int A::m_iMallocCount = 0;

A* A::m_FreePosi = nullptr;
int A::m_sTrunkCount = 5;

void* A::operator new(size_t size)
{
    A* tmplink;
    if (m_FreePosi == nullptr) {
        // 再次malloc，相当于是：链表的尾插
        size_t realsize = m_sTrunkCount * size;
        m_FreePosi = reinterpret_cast<A*>(new char[realsize]); // 分配字节
        tmplink = m_FreePosi;

        // 链起来
        for (; tmplink != &m_FreePosi[m_sTrunkCount - 1]; ++tmplink) {
            tmplink->next = tmplink + 1;
        }
        tmplink->next = nullptr;
        ++m_iMallocCount;
    }
    tmplink = m_FreePosi;
    m_FreePosi = m_FreePosi->next;
    ++m_iCout;
    return tmplink;
}

void A::operator delete(void* phead)
{
    // 相当于是进行了：链表的 头插
    (static_cast<A*>(phead))->next = m_FreePosi;
    m_FreePosi = static_cast<A*>(phead);
}
