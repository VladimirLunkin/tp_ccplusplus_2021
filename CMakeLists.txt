cmake_minimum_required(VERSION 3.16)
project(hw-1)

# <Coverage>
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs --coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs --coverage")
# </Coverage>

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
add_subdirectory(test)
# </Test>

# <Source>
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")
# </Source>

add_executable(hw-1 ${sources})
