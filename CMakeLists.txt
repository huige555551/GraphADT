cmake_minimum_required(VERSION 3.12)
project(GraphADT C)

set(CMAKE_C_STANDARD 99)

add_executable(GraphADT List.c List.h Graph.c Graph.h FindPath.c GraphTest.c)