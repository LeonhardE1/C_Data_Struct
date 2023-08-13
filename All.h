//
// Created by lk129 on 2023/7/29.
// 总的头文件
//

#ifndef C_DATA_STRUCT_ALL_H
#define C_DATA_STRUCT_ALL_H

#include <stdio.h>
#include <stdlib.h>

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)

// Status 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char ElemType;


#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LIST_INCREMENT 10 //线性表存储空间的分配量

#define STACK_INIT_SIZE 100 //栈存储空间的初始分配量
#define STACK_INCREMENT 10 //栈存储空间的分配量

#endif //C_DATA_STRUCT_ALL_H
