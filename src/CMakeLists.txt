cmake_minimum_required(VERSION 3.17)
project(slow_rebuild_bitcoin)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)
# Add pkg-config functionality
find_package(PkgConfig REQUIRED)
# boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
set_property(TARGET boost PROPERTY INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
include_directories(${Boost_INCLUDE_DIRS})
# libevent
pkg_search_module(EVENT REQUIRED libevent)

add_library(libevent INTERFACE IMPORTED)
set_property(TARGET libevent PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${EVENT_INCLUDE_DIRS})
set_property(TARGET libevent PROPERTY INTERFACE_LINK_LIBRARIES ${EVENT_LINK_LIBRARIES})
include_directories(${EVENT_INCLUDE_DIRS})


add_subdirectory(consensus)
add_subdirectory(crypto)
add_subdirectory(primitives)
add_subdirectory(support)
add_subdirectory(util)
add_subdirectory(policy)
add_subdirectory(script)
add_subdirectory(univalue)
add_subdirectory(secp256k1)
add_subdirectory(rpc)
add_subdirectory(node)
add_subdirectory(interfaces)
add_subdirectory(leveldb)
add_subdirectory(index)


file(GLOB_RECURSE source_list "*.cpp" "*.h")
list(REMOVE_ITEM source_list bitcoin-util.cpp bitcoin-tx.cpp)

add_library(bitcoin-core ${source_list})
target_include_directories(bitcoin-core PRIVATE ${EVENT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${SOME_DEP_DIR}/include)
target_compile_definitions(bitcoin-core PUBLIC HAVE_GMTIME_R=1  HAVE_GETCPUID=1
        HAVE_CONFIG_H=1
        PACKAGE_BUGREPORT="https://github.com/bitcoin/bitcoin/issues")

target_link_libraries(bitcoin-core boost Consensus Crypto
        Primitives Support Util Policy Script Univalue Secp256k1 RPC Node Interfaces leveldb Index libevent)
add_executable(bitcoin-util bitcoin-util.cpp )

add_executable(bitcoin-tx bitcoin-tx.cpp )
add_executable(bitcoin-cli bitcoin-cli.cpp )


target_link_libraries(bitcoin-util bitcoin-core boost)
target_link_libraries(bitcoin-tx bitcoin-core)
target_link_libraries(bitcoin-cli bitcoin-core)
