cmake_minimum_required(VERSION 3.17)
project(slow_rebuild_bitcoin)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
# Add pkg-config functionality
find_package(PkgConfig REQUIRED)
# libevent
pkg_search_module(EVENT REQUIRED libevent)
# boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
set_property(TARGET boost PROPERTY INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
include_directories(${Boost_INCLUDE_DIRS})



add_subdirectory(consensus)
add_subdirectory(crypto)
add_subdirectory(primitives)
add_subdirectory(support)
add_subdirectory(util)
add_subdirectory(policy)
add_subdirectory(script)
add_subdirectory(univalue)

file(GLOB_RECURSE source_list "*.cpp" "*.h")
list(REMOVE_ITEM source_list bitcoin-util.cpp)

add_library(bitcoin-core ${source_list})
target_include_directories(bitcoin-core PRIVATE ${EVENT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${SOME_DEP_DIR}/include)
target_compile_definitions(bitcoin-core PUBLIC COPYRIGHT_HOLDERS="anyone" HAVE_GMTIME_R=1  HAVE_GETCPUID=1 COPYRIGHT_HOLDERS_SUBSTITUTION="everyone" HAVE_DECL_STRNLEN=1 CLIENT_VERSION_IS_RELEASE=1 CLIENT_VERSION_BUILD=1 CLIENT_VERSION_MINOR=1 CLIENT_VERSION_MAJOR=1.0 COPYRIGHT_YEAR=2020 PACKAGE_NAME="BITCOIN")

target_link_libraries(bitcoin-core boost Consensus Crypto Primitives Support Util Policy Script Univalue)
add_executable(bitcoin-util bitcoin-util.cpp )



target_link_libraries(bitcoin-util bitcoin-core boost)


