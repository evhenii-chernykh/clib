cmake_minimum_required(VERSION 2.8)

project(clib_tests)

set(LIST_STACK_SRC "${PROJECT_SOURCE_DIR}/list_stack_test.c")
add_executable(list_stack_test ${LIST_STACK_SRC} ${CLIB_SRC_LIST})

set(ATOM_SRC "${PROJECT_SOURCE_DIR}/atom_test.c")
add_executable(atom_test ${ATOM_SRC} ${CLIB_SRC_LIST})

set(LINEAR_ALLOCATOR_SRC "${PROJECT_SOURCE_DIR}/linear_allocator_test.c")
add_executable(linear_allocator_test ${LINEAR_ALLOCATOR_SRC} ${CLIB_SRC_LIST})

set(LIST_SRC "${PROJECT_SOURCE_DIR}/list_test.c")
add_executable(list_test ${LIST_SRC} ${CLIB_SRC_LIST})

set(TABLE_SRC "${PROJECT_SOURCE_DIR}/table_test.c")
add_executable(table_test ${TABLE_SRC} ${CLIB_SRC_LIST})

set(HASH_SET_SRC "${PROJECT_SOURCE_DIR}/hash_set_test.c")
add_executable(hash_set_test ${HASH_SET_SRC} ${CLIB_SRC_LIST})
