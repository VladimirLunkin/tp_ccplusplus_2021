#!/usr/bin/env bash

print_header() {
    echo "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck --enable=all --language=c --error-exitcode=1 sum_lib/*/* metrics/*/* --suppress=missingInclude

print_header "RUN cpplint.py"
cpplint --extensions=c sum_lib/*/* metrics/*/*

print_header "TESTS"
print_header "RUN cppcheck"
cppcheck --enable=all --error-exitcode=1 tests --suppress=missingInclude

print_header "RUN cpplint.py"
cpplint --extensions=cpp tests/*.cpp

print_header "SUCCESS"
