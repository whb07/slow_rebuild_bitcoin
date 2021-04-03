set(CMAKE_CXX_STANDARD 17)

add_library(
        Interfaces handler.cpp handler.h node.h wallet.h chain.h
        ${BITCOIN_CORE_H}
)

target_link_libraries(Interfaces PUBLIC Primitives Util Script Support Wallet)
target_include_directories(Interfaces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
