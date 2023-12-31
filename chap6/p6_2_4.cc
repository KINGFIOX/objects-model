#include <iostream>
using namespace std;

class JI {
public:
    virtual ~JI()
    {
        cout << "JI::~JI()" << endl;
    }
};

class A : public JI {
public:
    virtual ~A()
    {
        cout << "A::~A()" << endl;
    }
};

int main(void)
{
    A a;
    return 0;
}