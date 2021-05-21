cmake_minimum_required(VERSION 3.18)
project(TP10 C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic")

set(PROJECT_HEADERS
        heap.h)

set(PROJECT_SOURCES
        main.c
        heap.c)

add_executable(MAIN ${PROJECT_SOURCES} ${PROJECT_HEADERS})