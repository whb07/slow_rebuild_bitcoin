
project(UNIVALUE LANGUAGES CXX)
cmake_minimum_required(VERSION 3.2)

add_library(Univalue
    lib/univalue_escapes.h
    lib/univalue_get.cpp
    lib/univalue_read.cpp
    lib/univalue_utffilter.h
    lib/univalue_write.cpp
    lib/univalue.cpp
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(Univalue PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
PRIVATE lib)

set(JSON_TEST_SRC "${CMAKE_CURRENT_SOURCE_DIR}/test")
message(STATUS "JSON_TEST_SRC include dir: ${JSON_TEST_SRC}")
target_compile_definitions(Univalue PUBLIC JSON_TEST_SRC="${JSON_TEST_SRC}")

add_executable(gen gen/gen.cpp)
target_link_libraries(gen Univalue)

add_executable(no_nul
    test/no_nul.cpp
)
target_link_libraries(no_nul Univalue)
add_executable(object
    test/object.cpp
)
target_link_libraries(object Univalue)

add_executable(unitester
    test/unitester.cpp
)
target_link_libraries(unitester Univalue)


add_test(no_nul no_nul)
add_test(object object)
add_test(unitester unitester)