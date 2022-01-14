cmake_minimum_required(VERSION 3.15)
project(cpplearn)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../mingw-std-threads)

add_executable(cpplearn main.cpp Headers/IncludesAll.h Headers/Defines.h Headers/Chapter2/SimpleVector.h Headers/Chapter3/OperatorOverloading.h Headers/Chapter3/AbstractContainer.h Headers/Chapter3/BetterVector.h Headers/Chapter3/CopyingAndMoving.h Headers/Chapter3/Templates.h)