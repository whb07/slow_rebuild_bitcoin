set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE source_list "*.cpp" "*.h")
add_library(Util ${source_list})

target_include_directories(Util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(Util PUBLIC HAVE_CONFIG_H=1 HAVE_GMTIME_R=1 MAC_OSX=1)
target_link_libraries(Util PUBLIC Config boost Univalue   Crypto Policy Primitives)

