cmake_minimum_required(VERSION 3.17)
project(slow_rebuild_bitcoin)

set(CMAKE_CXX_STANDARD 20)
# Include Boost as an imported target
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

# Add pkg-config functionality
find_package(PkgConfig REQUIRED)

# search for libevent.pc
pkg_search_module(EVENT REQUIRED libevent)




add_subdirectory(consensus)
add_subdirectory(crypto)
add_subdirectory(primitives)
add_subdirectory(support)
add_subdirectory(util)
add_subdirectory(policy)
add_subdirectory(script)

add_library(bitcoin-core  versionbitsinfo.h chainparamsbase.cpp logging.cpp chainparams.cpp versionbits.cpp
        versionbitsinfo.cpp arith_uint256.cpp arith_uint256.h
        clientversion.h clientversion.cpp config/bitcoin-config.h core_io.h core_read.cpp random.cpp random.h randomenv.h randomenv.cpp)
target_include_directories(bitcoin-core PRIVATE ${EVENT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${SOME_DEP_DIR}/include)
target_compile_definitions(bitcoin-core PUBLIC COPYRIGHT_HOLDERS="anyone" HAVE_GETCPUID=1 COPYRIGHT_HOLDERS_SUBSTITUTION="everyone" HAVE_DECL_STRNLEN=1 CLIENT_VERSION_IS_RELEASE=1 CLIENT_VERSION_BUILD=1 CLIENT_VERSION_MINOR=1 CLIENT_VERSION_MAJOR=1.0 COPYRIGHT_YEAR=2020 PACKAGE_NAME="BITCOIN")

target_link_libraries(bitcoin-core boost )
add_executable(bitcoin-util bitcoin-util.cpp )



target_link_libraries(bitcoin-util bitcoin-core Consensus Crypto Primitives Support Util Policy Script)
