cmake_minimum_required(VERSION 3.25)
project(C_Data_Struct C)

set(CMAKE_C_STANDARD 23)

add_executable(C_Data_Struct main.c Linear_List/All.h)

add_executable(List_Begin Linear_List/List_Sq.c)
add_executable(List_Link Linear_List/List_Link.c)
add_executable(Link_Circular_List Linear_List/Link_Circular_List.c)
add_executable(Link_Double_List Linear_List/Link_Double_List.c)