cmake_minimum_required(VERSION 2.8)

project(clib_tests)

set(LIST_STACK_SRC "${PROJECT_SOURCE_DIR}/list_stack_test.c")
add_executable(list_stack_test ${LIST_STACK_SRC} ${CLIB_SRC_LIST})

set(ATOM_SRC "${PROJECT_SOURCE_DIR}/atom_test.c")
add_executable(atom_test ${ATOM_SRC} ${CLIB_SRC_LIST})
