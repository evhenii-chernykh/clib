cmake_minimum_required(VERSION 2.8)

project(clib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c89")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(EXPORT_HEADERS_DIRECTORY ${CMAKE_BINARY_DIR}/include)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(INC_LIST "${PROJECT_SOURCE_DIR}/include/list_stack.h"
             "${PROJECT_SOURCE_DIR}/include/atom.h"
             "${PROJECT_SOURCE_DIR}/include/linear_allocator.h"
             "${PROJECT_SOURCE_DIR}/include/list.h")

set(SRC_LIST "${PROJECT_SOURCE_DIR}/src/list_stack.c"
             "${PROJECT_SOURCE_DIR}/src/atom.c"
             "${PROJECT_SOURCE_DIR}/src/linear_allocator.c"
             "${PROJECT_SOURCE_DIR}/src/list.c")

set(CLIB_SRC_LIST ${INC_LIST} ${SRC_LIST})

source_group(src FILES ${CLIB_SRC_LIST})

add_library(${PROJECT_NAME} STATIC ${CLIB_SRC_LIST})

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
