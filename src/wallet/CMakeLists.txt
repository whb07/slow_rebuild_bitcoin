set(CMAKE_CXX_STANDARD 17)
add_library(
        Wallet
        bdb.cpp bdb.h coincontrol.cpp coincontrol.h coinselection.cpp coinselection.h
        context.cpp context.h crypter.cpp crypter.h db.cpp db.h dump.cpp dump.h external_signer.cpp
        external_signer.h external_signer_scriptpubkeyman.cpp external_signer_scriptpubkeyman.h
        feebumper.cpp feebumper.h fees.cpp fees.h init.cpp interfaces.cpp ismine.h load.cpp load.h
        rpcdump.cpp rpcsigner.cpp rpcsigner.h rpcwallet.cpp rpcwallet.h salvage.cpp salvage.h
        scriptpubkeyman.cpp scriptpubkeyman.h sqlite.cpp sqlite.h wallet.cpp wallet.h walletdb.cpp
        walletdb.h wallettool.cpp wallettool.h walletutil.cpp walletutil.h
        ${BITCOIN_CORE_H}
)

target_include_directories(Wallet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(Wallet PRIVATE HAVE_CONFIG_H=1)
target_link_libraries(Wallet Primitives Crypto RPC Policy Util Script Univalue Interfaces berkeley sqlite3 boost)