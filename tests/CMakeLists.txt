function(run_test test_name sources tests)
    foreach(file ${tests})
        set(name)
        get_filename_component(name ${file} NAME_WE)
        set(name ${name}_${test_name})
        add_executable("${name}"
                ${sources}
                ${file}
                "${PROJECT_SOURCE_DIR}/tests/main.cpp")
        target_link_libraries("${name}" gtest_main)
        add_test(NAME ${name} COMMAND "${name}")
    endforeach()
endfunction(run_test)


# <Source utils>
include_directories("${PROJECT_SOURCE_DIR}/metrics/include")

file(GLOB sources "${PROJECT_SOURCE_DIR}/metrics/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/metrics/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/array.cpp")
# </Source utils>

run_test("utils" "${sources}" "${tests}")


# <Source consistently>
include_directories("${PROJECT_SOURCE_DIR}/sum_lib/include")

file(GLOB sources "${PROJECT_SOURCE_DIR}/sum_lib/src_consistently/*.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/sum.cpp")
# </Source consistently>

run_test("consistently" "${sources}" "${tests}")


# <Source parallel>
include_directories("${PROJECT_SOURCE_DIR}/sum_lib/include")

file(GLOB sources "${PROJECT_SOURCE_DIR}/sum_lib/src_parallel/*.c")

file(GLOB tests
        "${PROJECT_SOURCE_DIR}/tests/pipes.cpp"
        "${PROJECT_SOURCE_DIR}/tests/sum.cpp")
# </Source parallel>

run_test("parallel" "${sources}" "${tests}")


# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>
