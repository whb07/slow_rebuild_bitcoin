cmake_minimum_required(VERSION 3.20)
project(levelme)

# This project can use C11, but will gracefully decay down to C89.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

# This project requires C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(GNUInstallDirs)

include_directories(".")

file(GLOB HEADER_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/leveldb/*.h")
# Make an automatic library - will be static or dynamic based on user setting
add_library(leveldb  ${HEADER_LIST} db/c.cc)
set_target_properties(leveldb PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(leveldb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")





######### PORT ################
file(GLOB PORT_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/helpers/memenv/memenv.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/port/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/port/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/port/*.h.*"
        )
add_library(port ${PORT_LIST} )
target_include_directories(port PUBLIC port)


######### DB ################
file(GLOB DB_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/db/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/db/*.cc"
        )
add_library(db ${DB_LIST})
target_include_directories(db PUBLIC db)
target_link_libraries(db PUBLIC leveldb port)


######### HELPERS ################
file(GLOB HELPERS_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/helpers/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/helpers/*/*.cc"
        )
add_library(helpers ${HELPERS_LIST})
target_include_directories(helpers PUBLIC helpers)
target_link_libraries(helpers PUBLIC leveldb port)


######### UTIL ################
file(GLOB UTIL_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/util/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/util/*.cc"
        )
list(REMOVE_ITEM UTIL_LIST "${CMAKE_CURRENT_SOURCE_DIR}/util/env_windows.cc")
add_library(util ${UTIL_LIST})
target_include_directories(util PUBLIC util)
target_link_libraries(util PUBLIC helpers leveldb port )

######### TABLE ################
file(GLOB TABLE_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/table/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/table/*.cc"
        )

add_library(table ${TABLE_LIST})
target_include_directories(table PUBLIC table)
target_link_libraries(table PUBLIC leveldb util)


target_compile_definitions(port PUBLIC LEVELDB_PLATFORM_POSIX=1 LEVELDB_IS_BIG_ENDIAN=0)
source_group(
        TREE "${CMAKE_CURRENT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)