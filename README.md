# CMinus
C-语言编译器以及自制的可运行编译结果的虚拟机

## 使用方法：

### 1. 生成CMinus编译器：

用CodeBlocks打开Compiler目录下的`.cbp`项目，并编译。

编译成功后可以在Debug或Release目录（取决于CodeBlocks的编译模式）下找到执行文件。
```
├─Compiler
    ├─bin/
    │  ├─Debug
    │  └─Release
    └─obj/
    └─tool/
```

取出`CMinus.exe`放入test目录下：
```
├─test
```

### 2. 生成CMinus运行虚拟机：

同样的，用CodeBlocks打开Compiler目录下的`.cbp`项目，并编译。

编译成功后可以在Debug或Release目录（取决于CodeBlocks的编译模式）下找到执行文件。
```
├─VM
    ├─bin/
    │  ├─Debug
    │  └─Release
    └─obj/
```

取出`CMinusVM.exe`放入test目录下。

### 3. 编译运行CMinus代码

进入text目录，默认有3个CMinus源码：

```
├─test
    ├─CMinus.exe
    ├─CMinusVM.exe
    ├─fib.c
    ├─gcd.c
    └─loop.c
```

编译CMinus源码：
```
CMinus.exe xxx.c
```

就可以生成编译之后的中间代码`xxx.gcd`和目标代码`xxx.mc`

运行CMinus代码
```
CMinusVm.exe xxx.mc
```
