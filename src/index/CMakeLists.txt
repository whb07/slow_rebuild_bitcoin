set(CMAKE_CXX_STANDARD 20)
add_library(
        Index base.cpp base.h blockfilterindex.cpp blockfilterindex.h
        disktxpos.h txindex.cpp txindex.h
)

target_link_libraries(Index bitcoin-core)
target_include_directories(Index PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
