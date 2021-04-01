cmake_minimum_required(VERSION 3.17)
<<<<<<< HEAD
project(TP5 C)

set(CMAKE_C_STANDARD 90)

set(SOURCES
=======
project(bakery C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic")

set(PROJECT_HEADERS
        customer.h
        event.h
        prioqueue.h
        queue.h)

set(PROJECT_SOURCES
>>>>>>> main
        bakery.c
        customer.c
        event.c
        prioqueue.c
        queue.c)

<<<<<<< HEAD
set(HEADERS
        customer.h
        event.h
        prioqueue.h
        queue.h)

add_executable(TP5 ${SOURCES} ${HEADERS})
=======

add_executable(main ${PROJECT_SOURCES} ${PROJECT_HEADERS})
>>>>>>> main
