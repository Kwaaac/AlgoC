cmake_minimum_required(VERSION 3.17)
project(TD6 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic")

set(PROJECT_HEADERS
        )

set(PROJECT_SOURCES
        main.c)

add_executable(MAIN ${PROJECT_SOURCES} ${PROJECT_SOURCES})