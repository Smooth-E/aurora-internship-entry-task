cmake_minimum_required(VERSION 3.29)
project("Book Store")

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(book_store
        Book.cpp
        Book.h
        BookStore.cpp
        BookStore.h
        main.cpp
        utils.cpp
        utils.h)
