cmake_minimum_required(VERSION 3.26)
project(library_sys_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(library_sys_files
        Author.cpp
        Author.h
        book.cpp
        book.h
        main.cpp
        )
