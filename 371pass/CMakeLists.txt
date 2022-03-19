cmake_minimum_required(VERSION 3.21)
project(371pass)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(371pass
        src/371pass.cpp
        src/371pass.h
        src/category.cpp
        src/category.h
        src/item.cpp
        src/item.h
        src/lib_catch.hpp
        src/lib_catch_main.cpp
        src/lib_cxxopts.hpp
        src/lib_cxxopts_argv.hpp
        src/lib_json.hpp
        src/main.cpp
        src/wallet.cpp
        src/wallet.h
        tests/test1.cpp
        tests/test2.cpp
        tests/test3.cpp
        tests/test4.cpp
        tests/test5.cpp
        tests/test6.cpp
        tests/test7.cpp
        tests/test8.cpp
        tests/test9.cpp
        tests/testall.cpp)
