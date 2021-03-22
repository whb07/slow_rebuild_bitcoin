set(CMAKE_C_STANDARD 11)
enable_language(C)
enable_testing()


add_library(Ctaes ctaes.c ctaes.h)

add_executable(ctaes_tests test.c)
target_link_libraries(ctaes_tests LINK_PUBLIC ctaes)
add_test(ctaes_tests_hello ctaes_tests)

add_executable(bench bench.c)
target_link_libraries(bench LINK_PUBLIC ctaes)

set(CMAKE_C_FLAGS "-Weverything -Wall -Wextra -Wshadow -Wconversion -Wno-reserved-id-macro -Wno-long-long -pedantic -fsanitize=address -fno-omit-frame-pointer" CACHE STRING "C compiler flags" FORCE )

target_include_directories(Ctaes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# the compiler flags for compiling C sources
MESSAGE(STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})