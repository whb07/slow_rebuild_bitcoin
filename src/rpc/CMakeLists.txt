set(CMAKE_CXX_STANDARD 17)
add_library(
        RPC blockchain.cpp blockchain.h client.cpp client.h mining.cpp mining.h
        misc.cpp net.cpp protocol.h rawtransaction.cpp rawtransaction_util.cpp rawtransaction_util.h
        register.h request.cpp request.h server.cpp server.h util.cpp util.h
)

target_link_libraries(RPC Univalue Util bitcoin_includes libevent)
target_include_directories(RPC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
