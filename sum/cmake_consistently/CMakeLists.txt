cmake_minimum_required(VERSION 3.16)
#project(sum_consistently)

set(SUM_PATH ../)

# <Creating a static library>
set(SUM_CONSISTENTLY_PATH ${SUM_PATH})
set(SUM_CONSISTENTLY_LIB
        ${SUM_CONSISTENTLY_PATH}/include/sum.h
        ${SUM_CONSISTENTLY_PATH}/src/sum_consistently.c)
add_library(sum_consistently_lib STATIC ${SUM_CONSISTENTLY_LIB})
target_include_directories(sum_consistently_lib PUBLIC ${SUM_CONSISTENTLY_PATH}/include)
# </Creating a static library>
