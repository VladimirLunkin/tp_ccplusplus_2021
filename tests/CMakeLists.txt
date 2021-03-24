message(STATUS "PARALLEL: ${PARALLEL}")

# <Source>
if (PARALLEL)
    include_directories("${PROJECT_SOURCE_DIR}/sum_lib/include")

    file(GLOB sources "${PROJECT_SOURCE_DIR}/sum_lib/src_parallel/*.c")

    file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/pipes.cpp"
                    "${PROJECT_SOURCE_DIR}/tests/sum.cpp")
else()
    include_directories("${PROJECT_SOURCE_DIR}/sum_lib/include"
                        "${PROJECT_SOURCE_DIR}/metrics/include")

    file(GLOB sources
            "${PROJECT_SOURCE_DIR}/sum_lib/src_consistently/*.c"
            "${PROJECT_SOURCE_DIR}/metrics/src/*.c")
    list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/metrics/src/main.c")

    file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/array.cpp"
                    "${PROJECT_SOURCE_DIR}/tests/sum.cpp")
endif (PARALLEL)
# </Source>

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
