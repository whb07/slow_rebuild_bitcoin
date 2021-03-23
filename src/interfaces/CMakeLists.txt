set(CMAKE_CXX_STANDARD 20)
add_library(
        Interfaces handler.cpp handler.h node.h wallet.h chain.h
)

target_link_libraries(RPC Primitives bitcoin-core Util Script Support)
target_include_directories(Interfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
