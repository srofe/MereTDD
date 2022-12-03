cmake_minimum_required(VERSION 3.23)
project(MereTDD)

set(CMAKE_CXX_STANDARD 20)

add_executable(MereTDD tests/main.cc tests/Creation.cc tests/Confirm.cc)
