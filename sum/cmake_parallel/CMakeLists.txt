cmake_minimum_required(VERSION 3.16)
project(sum_parallel)

set(SUM_PATH ../)

# <Creating a dynamic library>
set(SUM_PARALLEL_PATH ${SUM_PATH})
set(SUM_PARALLEL_LIB
        ${SUM_PARALLEL_PATH}/include/sum.h
        ${SUM_PARALLEL_PATH}/src/sum_parallel.c)
add_library(sum_parallel_lib SHARED ${SUM_PARALLEL_LIB})
target_include_directories(sum_parallel_lib PUBLIC ${SUM_PARALLEL_PATH}/include)
# </Creating a dynamic library>
