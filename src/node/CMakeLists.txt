set(CMAKE_CXX_STANDARD 20)
add_library(
        Node coin.cpp coin.h coinstats.cpp coinstats.h context.cpp context.h
        interfaces.cpp psbt.cpp psbt.h transaction.cpp transaction.h ui_interface.cpp
        ui_interface.h utxo_snapshot.h
)

target_link_libraries(Node bitcoin-core Consensus Crypto Util Policy Primitives)
target_include_directories(Node PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
