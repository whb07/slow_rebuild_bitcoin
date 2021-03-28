
cmake_minimum_required(VERSION 3.20)
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
find_package(LIBEVENT REQUIRED)
add_library(libevent INTERFACE IMPORTED)
set_property(TARGET libevent PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${LIBEVENT_INCLUDE_DIRS})
set_property(TARGET libevent PROPERTY INTERFACE_LINK_LIBRARIES ${LIBEVENT_LIBRARIES})
include_directories(${LIBEVENT_INCLUDE_DIRS})

# berkeleydb
find_path(BK_XX
        NAMES db_cxx.h
        PATH_SUFFIXES include/
        PATHS /usr/local/Cellar/berkeley-db\@4/4.8.30 /usr/local/ /usr/
        REQUIRED
        NO_DEFAULT_PATH
        )
get_filename_component(PARENT_DIR ${BK_XX} DIRECTORY)
set(BK_LIBRARY "${PARENT_DIR}/lib/libdb_cxx.a")
add_library(berkeley STATIC IMPORTED)
set_property(TARGET berkeley PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BK_XX})
set_property(TARGET berkeley PROPERTY IMPORTED_LOCATION ${BK_LIBRARY})
# sqlite3
find_package(SQLite3 COMPONENTS REQUIRED)
add_library(sqlite3 INTERFACE IMPORTED)
if(SQLite3_FOUND)
    message("YIPEE KAYEEE MOFO LINE 40")
endif()
set_property(TARGET sqlite3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SQLite3_INCLUDE_DIRS})
set_property(TARGET sqlite3 PROPERTY INTERFACE_LINK_LIBRARIES ${SQLite3_LIBRARIES})



add_subdirectory(consensus)
add_subdirectory(crypto)
add_subdirectory(primitives)
add_subdirectory(support)
add_subdirectory(util)
add_subdirectory(policy)
add_subdirectory(script)
add_subdirectory(univalue)
add_subdirectory(leveldb)
add_subdirectory(secp256k1)
add_subdirectory(rpc)
add_subdirectory(node)
add_subdirectory(interfaces)
add_subdirectory(index)
add_subdirectory(wallet)






file(GLOB_RECURSE source_list "*.cpp" "*.h")
list(REMOVE_ITEM source_list bitcoin-util.cpp bitcoin-tx.cpp bitcoin-wallet.cpp bitcoind.cpp)

add_library(bitcoin-core STATIC ${source_list} )
#target_include_directories(bitcoin-core PRIVATE ${EVENT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${SOME_DEP_DIR}/include)
target_compile_definitions(bitcoin-core PUBLIC HAVE_GMTIME_R=1  HAVE_GETCPUID=1
        HAVE_CONFIG_H=1
        PACKAGE_BUGREPORT="https://github.com/bitcoin/bitcoin/issues")

target_link_libraries(bitcoin-core boost Consensus Crypto
        Primitives Support Util Policy Script Univalue Secp256k1 RPC Node Interfaces Index libevent berkeley leveldb
        sqlite3)

add_executable(bitcoin-util bitcoin-util.cpp )
add_executable(bitcoin-tx bitcoin-tx.cpp )
add_executable(bitcoin-cli bitcoin-cli.cpp )
add_executable(bitcoin-wallet bitcoin-wallet.cpp)
add_executable(bitcoind bitcoind.cpp)

target_link_libraries(bitcoin-util bitcoin-core boost)
target_link_libraries(bitcoin-tx bitcoin-core)
target_link_libraries(bitcoin-cli bitcoin-core)
target_link_libraries(bitcoin-wallet Wallet)
target_link_libraries(bitcoind bitcoin-core sqlite3 leveldb libevent)
#
target_compile_definitions(bitcoind PUBLIC HAVE_GMTIME_R=1  HAVE_GETCPUID=1
        HAVE_CONFIG_H=1
        PACKAGE_BUGREPORT="https://github.com/bitcoin/bitcoin/issues")
