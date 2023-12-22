## 虚函数

### 多继承

《来源 p3_4.cc》

多继承，在 clang 上确实与 msvc 不一样

```sh
(lldb) b p3_4.cc:108
Breakpoint 1: where = p3_4.out`main + 432 at p3_4.cc:109:5, address = 0x0000000100006c8c
(lldb) r
Process 7528 launched: '/Users/wangfiox/DOCS_OFFLINE/objectsModel/chap3/p3_4.out' (arm64)
8
8
16
----------
vptr1
----------
vptr2
----------
Process 7528 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x0000000100006c8c p3_4.out`main at p3_4.cc:109:5
   106
   107      cout << "----------" << endl;
   108
-> 109      b1.f();
   110      b2.i();
   111      d.f();
   112      d.i();
(lldb) print (Func)vptr[0]
error: <user expression 0>:1:7: use of undeclared identifier 'vptr'
    1 | (Func)vptr[0]
      |       ^
(lldb) print (Func)vptr1[0]
(Func) 0x0000000100006e7c (p3_4.out`Derived::f() at p3_4.cc:34)
(lldb) print (Func)vptr1[1]
(Func) 0x0000000100006eb8 (p3_4.out`Base1::g() at p3_4.cc:13)
(lldb) print (Func)vptr1[2]
(Func) 0x0000000100006ef4 (p3_4.out`Derived::i() at p3_4.cc:39)
(lldb) print (Func)vptr1[3]
(Func) 0x0000000100006f30 (p3_4.out`Derived::h() at p3_4.cc:43)
(lldb) print (Func)vptr1[4]
(Func) 0x0000000100006f6c (p3_4.out`Derived::mh() at p3_4.cc:48)
(lldb) print (Func)vptr1[5]
(Func) 0x0000000100006fa8 (p3_4.out`Derived::mi() at p3_4.cc:52)
(lldb) print (Func)vptr1[6]
(Func) 0x0000000100006fe4 (p3_4.out`Derived::mj() at p3_4.cc:56)
(lldb) print (Func)vptr1[7]
(Func) 0xfffffffffffffff8
(lldb) print (Func)vptr2[0]
(Func) 0x0000000100007020 (p3_4.out`non-virtual thunk to Derived::h() at p3_4.cc)
(lldb) print (Func)vptr2[1]
(Func) 0x0000000100007038 (p3_4.out`non-virtual thunk to Derived::i() at p3_4.cc)
(lldb) print (Func)vptr2[2]
(Func) 0x00000001dae8bc88 (libc++abi.dylib`vtable for __cxxabiv1::__class_type_info + 16)
(lldb) print (Func)vptr2[3]
(Func) 0x8000000100007ef5 (actual=0x0000000100007ef5 p3_4.out`typeinfo name for Base1)
```

可以看到，在 clang 编译的情况下：

如果发生了重写，那么 vtable2 的 "虚函数" 会出现在 vtable1 中
