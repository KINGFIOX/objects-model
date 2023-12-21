#include <iostream>

using namespace std;

class CTempValue {
public:
    int val1;
    int val2;

public:
    CTempValue(int v1 = 0, int v2 = 0)
        : val1(v1)
        , val2(v2)
    {
        cout << "调用了CTempValue类的构造函数" << endl;
        cout << "val1 = " << val1 << endl;
        cout << "val2 = " << val2 << endl;
    }

    CTempValue(const CTempValue& t)
        : val1(t.val1)
        , val2(t.val2)
    {
        cout << "调用了CTempValue类的拷贝构造函数" << endl;
    }

    virtual ~CTempValue()
    {
        cout << "调用了CTempValue类的析构函数" << endl;
    }
};

CTempValue Double(CTempValue& ts)
{
    CTempValue tmp;
    tmp.val1 = ts.val1 * 2;
    tmp.val2 = ts.val2 * 2;
    return tmp;
}

int main(void)
{
    CTempValue ts1(10, 20);
    Double(ts1);
}
