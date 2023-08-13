cmake_minimum_required(VERSION 3.25)
project(C_Data_Struct C)

set(CMAKE_C_STANDARD 23)

add_executable(C_Data_Struct main.c All.h)

#线性表
add_executable(List_Begin Linear_List/List_Sq.c)
add_executable(List_Link Linear_List/List_Link.c)
add_executable(Link_Circular_List Linear_List/Link_Circular_List.c)
add_executable(Link_Double_List Linear_List/Link_Double_List.c)

#栈和队列
add_executable(Stack Stack_Queue/Stack.c)
add_executable(Queue Stack_Queue/Queue.c)