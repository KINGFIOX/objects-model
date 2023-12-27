# 函数语义学

### 虚函数的调用方式

非多态，虚函数直接调用，不会走虚函数表

但是，如果是：

```cpp
class c{
    virutal void func1(){
        func2();
    }
    vitual void func2(){
        printf("hello world");
    }
};

int main(void){
    c c1;
    c1.func1();
}
```

这个`c1.func1()`是直接直接调用，不走虚函数表的，但是紧接着，
`func1`里面的`func2`却是走虚函数表的。

但是

```cpp
class c{
    virtual void func1(){
        c::func2();
    }
    virtual void func2(){
        printf("hello world");
    }
};

int main(void){
    c c1;
    c1.func1();
}
```

这里调用`C::func2()`的时候，却不会走虚函数表。
这种写法，压制了虚函数的发生机制。
怎么说，这种还是看需求。
这种情况就是明确的说明了，我不走虚函数表，而是明确的
