cmake_minimum_required(VERSION 3.16)
project(hw-2)


# <Flags>
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
# </Flags>


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


# <Add libraries>
option(PARALLEL "parallel implementation" OFF)

if (PARALLEL)
    add_subdirectory(sum/cmake_parallel)
else()
    add_subdirectory(sum/cmake_consistently)
endif (PARALLEL)
# </Add libraries>


# <Source>
include_directories("${PROJECT_SOURCE_DIR}/metrics/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/metrics/include/*.h"
        "${PROJECT_SOURCE_DIR}/metrics/src/*.c")
# </Source>


add_executable(${PROJECT_NAME} ${sources})


# <Link libraries>
if (PARALLEL)
    target_link_libraries(${PROJECT_NAME} PRIVATE sum_parallel_lib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE sum_consistently_lib)
endif (PARALLEL)
# </Link libraries>


# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>
