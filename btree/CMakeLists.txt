cmake_minimum_required(VERSION 3.8)
project(btree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        btree.h
        btree_iterator.h
        test10.cpp)

add_executable(btree ${SOURCE_FILES})