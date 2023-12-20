### lldb 的使用

- b 断点
- r 运行直到断点
- s 进入
- n 下一步
- bt 栈
- f 帧
- c 继续执行

#### 查看汇编

```lldb
disassemble --frame
```

### objdump

```sh
objdump -d <可执行文件>
```

查看编译器生成的默认构造函数

```sh
objdump -C -t <可执行文件>
```

`-C` 选项表示对 C++ 符号进行 demangling（符号重整），`-t` 选项表示显示符号表。因此，`objdump -C -t <可执行文件>` 命令将显示带有符号重整的符号表。

显示汇编
