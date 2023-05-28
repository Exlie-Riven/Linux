#include<stdio.h>
#include<string.h>
#include<iostream>
#define STRCPY(a,b) strcpy(a##_p,#b)

/*
测试 ## 连接符与宏展开问题
    char var1_p[20];
    char var2_p[30];

    strcpy(var1_p,"aaaa");
    strcpy(var2_p,"bbbb");
    STRCPY(var1,var2);
    // STRCPY(var2,var2);
    STRCPY(STRCPY(var1,var2),var2); // 会展开成  STRCPY(STRCPY(var1,var2)_p,var2); 
    //char* my_char = STRCPY(STRCPY(var1,var2_p),var2);
*/
int main(void)
{

    std::cout<<c<<std::endl;
    return 0;

}