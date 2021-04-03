set(CMAKE_CXX_STANDARD 17)
add_library(
        Script bitcoinconsensus.cpp bitcoinconsensus.h descriptor.cpp descriptor.h
        interpreter.cpp interpreter.h keyorigin.h script.cpp script.h
        script_error.cpp script_error.h sigcache.cpp sigcache.h sign.cpp sign.h
        signingprovider.cpp signingprovider.h standard.cpp standard.h
)

target_link_libraries(Script Primitives Util   )
target_include_directories(Script PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
