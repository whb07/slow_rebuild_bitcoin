set(CMAKE_CXX_STANDARD 17)
add_library(
        Policy feerate.cpp feerate.h fees.cpp fees.h policy.cpp policy.h rbf.cpp rbf.h
        settings.cpp settings.h
)

target_include_directories(Policy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Policy PUBLIC Config Consensus Script Util boost)
