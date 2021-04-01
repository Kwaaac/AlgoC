cmake_minimum_required(VERSION 3.17)
project(TP5 C)

set(CMAKE_C_STANDARD 90)

set(SOURCES
        bakery.c
        customer.c
        event.c
        prioqueue.c
        queue.c)

set(HEADERS
        customer.h
        event.h
        prioqueue.h
        queue.h)

add_executable(TP5 ${SOURCES} ${HEADERS})