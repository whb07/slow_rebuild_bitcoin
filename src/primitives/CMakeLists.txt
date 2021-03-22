set(CMAKE_CXX_STANDARD 20)
add_library(
        Primitives block.cpp block.h transaction.cpp transaction.h
)

target_include_directories(Primitives PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Primitives Script Util)