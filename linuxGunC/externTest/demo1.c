/*
测试时间： 2023年4月18日14点58分

程序说明：这是一段测试代码，用于测试以下功能
        1. extern 关键字的使用
        2. 不同.c文件包含同一名字的变量，同时声明不加extern关键字的运行结果

总结：
1. gcc 遇到两个头文件只是声明变量而没有定义，则编译通过，链接通过
2. gcc 如果只是引用某个.c文件中的某个函数，不想包含.c文件，则可以使用extern包含特定函数，只需在gcc后面添加指定的.c文件
3. gcc 包含了目标的头文件，再使用extern就会报错，这时候需要在gcc后面包含..c文件
4. gcc 如果在主文件中已经包含了.c文件(注意不是.h)文件，那么在gcc后面包含.c文件时就会出现重复定义的错误
*/

#include<stdlib.h>
#include"demo2.h"
int global_var; // 声明全局变量，表示该变量在其他文件中定义
//extern fun3();

int main(int argc,char* argv[])
{
   // global_var = 5555;
    fun3();
    return 0;
}