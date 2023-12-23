#include <cstdio>
#include <iostream>

using namespace std;

class Base1
{
  
  public: 
  inline virtual void f()
  {
    std::operator<<(std::cout, "Base1::f()").operator<<(std::endl);
  }
  
  inline virtual void g()
  {
    std::operator<<(std::cout, "Base1::g()").operator<<(std::endl);
  }
  
  // inline constexpr Base1() noexcept = default;
};



class Base2
{
  
  public: 
  inline virtual void h()
  {
    std::operator<<(std::cout, "base2::h()").operator<<(std::endl);
  }
  
  inline virtual void i()
  {
    std::operator<<(std::cout, "Base2::i()").operator<<(std::endl);
  }
  
  // inline constexpr Base2() noexcept = default;
};



class Derived : public Base1, public Base2
{
  
  public: 
  inline virtual void f()
  {
    std::operator<<(std::cout, "Derived::f()").operator<<(std::endl);
  }
  
  inline virtual void i()
  {
    std::operator<<(std::cout, "Derived::i()").operator<<(std::endl);
  }
  
  inline virtual void h()
  {
    std::operator<<(std::cout, "Derived::h()").operator<<(std::endl);
  }
  
  inline virtual void mh()
  {
    std::operator<<(std::cout, "Derived::mh()").operator<<(std::endl);
  }
  
  inline virtual void mi()
  {
    std::operator<<(std::cout, "Derived::mi()").operator<<(std::endl);
  }
  
  inline virtual void mj()
  {
    std::operator<<(std::cout, "Derived::mj()").operator<<(std::endl);
  }
  
  // inline constexpr Derived() noexcept = default;
};



int main()
{
  std::cout.operator<<(sizeof(Base1)).operator<<(std::endl);
  std::cout.operator<<(sizeof(Base2)).operator<<(std::endl);
  std::cout.operator<<(sizeof(Derived)).operator<<(std::endl);
  std::operator<<(std::cout, "----------").operator<<(std::endl);
  Derived ins = Derived();
  Base1 & b1 = static_cast<Base1&>(ins);
  Base2 & b2 = static_cast<Base2&>(ins);
  Derived & d = ins;
  using Func = void (*)();
  long * pderived1 = reinterpret_cast<long *>((&d));
  long * vptr1 = reinterpret_cast<long *>((*pderived1));
  long * pderived2 = pderived1 + 1;
  long * vptr2 = reinterpret_cast<long *>((*pderived2));
  std::operator<<(std::cout, "vptr1").operator<<(std::endl);
  using FuncPtr_87 = Func;
  FuncPtr_87 f0 = reinterpret_cast<void (*)()>(vptr1[0]);
  using FuncPtr_88 = Func;
  FuncPtr_88 f1 = reinterpret_cast<void (*)()>(vptr1[1]);
  using FuncPtr_91 = Func;
  FuncPtr_91 f2 = reinterpret_cast<void (*)()>(vptr1[2]);
  using FuncPtr_93 = Func;
  FuncPtr_93 f3 = reinterpret_cast<void (*)()>(vptr1[3]);
  using FuncPtr_94 = Func;
  FuncPtr_94 f4 = reinterpret_cast<void (*)()>(vptr1[4]);
  using FuncPtr_95 = Func;
  FuncPtr_95 f5 = reinterpret_cast<void (*)()>(vptr1[5]);
  using FuncPtr_96 = Func;
  FuncPtr_96 f6 = reinterpret_cast<void (*)()>(vptr1[6]);
  using FuncPtr_97 = Func;
  FuncPtr_97 f7 = reinterpret_cast<void (*)()>(vptr1[7]);
  std::operator<<(std::cout, "----------").operator<<(std::endl);
  std::operator<<(std::cout, "vptr2").operator<<(std::endl);
  using FuncPtr_104 = Func;
  FuncPtr_104 f00 = reinterpret_cast<void (*)()>(vptr2[0]);
  using FuncPtr_105 = Func;
  FuncPtr_105 f11 = reinterpret_cast<void (*)()>(vptr2[1]);
  using FuncPtr_106 = Func;
  FuncPtr_106 f22 = reinterpret_cast<void (*)()>(vptr2[2]);
  using FuncPtr_107 = Func;
  FuncPtr_107 f33 = reinterpret_cast<void (*)()>(vptr2[3]);
  std::operator<<(std::cout, "----------").operator<<(std::endl);
  b1.f();
  b2.i();
  d.f();
  d.i();
  d.mh();
  return 0;
}
