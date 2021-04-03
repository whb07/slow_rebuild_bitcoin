set(CMAKE_CXX_STANDARD 17)
add_library(
        Consensus STATIC
        consensus.h
        merkle.cpp
        merkle.h
        params.h
        tx_check.cpp
        tx_check.h
        tx_verify.cpp
        tx_verify.h
        validation.h
)

target_include_directories(Consensus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Consensus PUBLIC Primitives Script   Util)