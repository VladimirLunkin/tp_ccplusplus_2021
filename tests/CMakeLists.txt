include_directories("${PROJECT_SOURCE_DIR}/sum_lib/include")
if (PARALLEL)
    file(GLOB sources "${PROJECT_SOURCE_DIR}/sum_lib/src_parallel/*.c")
else()
    file(GLOB sources "${PROJECT_SOURCE_DIR}/sum_lib/src_consistently/*.c")
endif (PARALLEL)

include_directories("${PROJECT_SOURCE_DIR}/metrics/include")
file(GLOB sources "${sources}" "${PROJECT_SOURCE_DIR}/metrics/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/metrics/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests/main.cpp")

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/tests/main.cpp")
    target_link_libraries("${name}_tests" gtest_main)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()

# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>
