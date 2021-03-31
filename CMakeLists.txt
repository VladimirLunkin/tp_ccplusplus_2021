cmake_minimum_required(VERSION 3.16)
project(hw-2)


# <Flags>
set(CMAKE_C_FLAGS "-Wall -Werror -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
# </Flags>


# <Add libraries>
option(PARALLEL "parallel implementation" OFF)

set(SUM_PATH ${PROJECT_SOURCE_DIR}/sum_lib)

if (PARALLEL)
    set(SUM "sum_parallel")
    set(SUM_PARALLEL_LIB
            ${SUM_PATH}/include/sum.h
            ${SUM_PATH}/include/pipes.h
            ${SUM_PATH}/src_parallel/sum.c
            ${SUM_PATH}/src_parallel/pipes.c)

    add_library(${SUM}_lib SHARED ${SUM_PARALLEL_LIB})
else()
    set(SUM "sum_consistently")
    set(SUM_CONSISTENTLY_LIB
            ${SUM_PATH}/include/sum.h
            ${SUM_PATH}/src_consistently/sum.c)

    add_library(${SUM}_lib STATIC ${SUM_CONSISTENTLY_LIB})
endif (PARALLEL)

target_include_directories(${SUM}_lib PUBLIC ${SUM_PATH}/include)
# </Add libraries>


# <Test>
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(tests)
# </Test>


# <Source>
include_directories("${PROJECT_SOURCE_DIR}/metrics/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/metrics/include/*.h"
        "${PROJECT_SOURCE_DIR}/metrics/src/*.c")
# </Source>


add_executable(${PROJECT_NAME} ${sources})


# <Link libraries>
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUM}_lib -ldl)
# </Link libraries>


# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>
