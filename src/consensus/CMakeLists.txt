set(CMAKE_CXX_STANDARD 20)
add_library(
        Consensus consensus.h merkle.cpp merkle.h params.h tx_check.cpp tx_check.h tx_verify.cpp
        tx_verify.h validation.h
)

target_include_directories(Consensus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Consensus Primitives bitcoin-core Util)