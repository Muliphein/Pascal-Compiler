# Pascal-Compiler
 a simple Pascal Compiler based on Lexer, Yacc and LLVM

### Enviroment
Clang: version 10.0.0-4ubuntu1
Target: x86_64-pc-linux-gnu
System: Linux DESKTOP-CNMF2QD 4.4.0-19041-Microsoft #488-Microsoft Mon Sep 01 13:43:00 PST 2020 x86_64 x86_64 x86_64 GNU/Linux

### Timeline

#### 5/29/2021
完成了基本的全局变量，基本变量(Integer, Real, Bool, Char)，完成了输入和输出的系统调用。
现在可以运行Generator中的test1来进行测试

#### 5/30/2021
完成了局部变量和结构体的调用，现在可以运行GeneratorTest的test6来进行测试

#### 5/31/2021
完成了函数调用以及一些基本语句，包括跳转，循环以及返回值的设置。
处理了空函数的调用以及返回问题，以及主函数的返回问题。
功能全部完成。
