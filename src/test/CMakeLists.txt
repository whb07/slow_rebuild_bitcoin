cmake_minimum_required(VERSION 3.20)

include_directories(".")

file(GLOB TEST_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/util/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/util/*.h"
        )
list(REMOVE_ITEM TEST_LIST "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/fuzz.cpp")
add_library(testlib STATIC ${TEST_LIST})
target_link_libraries(testlib PUBLIC Config Univalue Secp256k1)

add_executable(test "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/fuzz.cpp")
target_link_libraries(test PUBLIC testlib)
target_compile_definitions(testlib PUBLIC HAVE_CONFIG_H=1)
target_include_directories(testlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")