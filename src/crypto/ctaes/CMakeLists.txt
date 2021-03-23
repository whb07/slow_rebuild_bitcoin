cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(CTAES VERSION 0.1 LANGUAGES C)
enable_testing()


add_library(Ctaes ctaes.c ctaes.h)

add_executable(ctaes_tests test.c)
target_link_libraries(ctaes_tests Ctaes)
add_test(ctaes_tests_hello ctaes_tests)

add_executable(bench bench.c)
target_link_libraries(bench Ctaes)

target_include_directories(Ctaes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


