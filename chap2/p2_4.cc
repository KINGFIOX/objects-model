#include <iostream>

using namespace std;

class MATX {
public:
    MATX()
    {
        cout << "MATX()" << endl;
    }
};

class MBTX {
public:
    int m_i;
    // int m_j;
    MATX m_matx;
    void funct()
    {
        cout << "Iamverygood" << endl;
    }
};

int main(void)
{
    MBTX mb;
    return 0;
}
