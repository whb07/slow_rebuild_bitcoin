
cmake_minimum_required(VERSION 3.20)
project(slow_rebuild_bitcoin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
#set(CMAKE_CXX_FLAGS "" CACHE STRING "C compiler flags" FORCE )
set(CMAKE_CXX_FLAGS_DEBUG  "-g")
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
set_property(TARGET sqlite3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SQLite3_INCLUDE_DIRS})
set_property(TARGET sqlite3 PROPERTY INTERFACE_LINK_LIBRARIES ${SQLite3_LIBRARIES})

# QT
set(Qt5_DIR "/usr/local/Cellar/qt\@5/5.15.2/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets Test REQUIRED)


file(GLOB BITCOIN_CORE_H
        "addrdb.h"
        "addrman.h"
        "attributes.h"
        "banman.h"
        "base58.h"
        "bech32.h"
        "blockencodings.h"
        "blockfilter.h"
        "bloom.h"
        "chain.h"
        "chainparams.h"
        "chainparamsbase.h"
        "chainparamsseeds.h"
        "checkqueue.h"
        "clientversion.h"
        "coins.h"
        "compat.h"
        "compat/assumptions.h"
        "compat/byteswap.h"
        "compat/cpuid.h"
        "compat/endian.h"
        "compat/sanity.h"
        "compressor.h"
        "consensus/consensus.h"
        "consensus/tx_check.h"
        "consensus/tx_verify.h"
        "core_io.h"
        "core_memusage.h"
        "cuckoocache.h"
        "dbwrapper.h"
        "flatfile.h"
        "fs.h"
        "httprpc.h"
        "httpserver.h"
        "i2p.h"
        "index/base.h"
        "index/blockfilterindex.h"
        "index/disktxpos.h"
        "index/txindex.h"
        "indirectmap.h"
        "init.h"
        "interfaces/chain.h"
        "interfaces/handler.h"
        "interfaces/node.h"
        "interfaces/wallet.h"
        "key.h"
        "key_io.h"
        "logging.h"
        "logging/timer.h"
        "mapport.h"
        "memusage.h"
        "merkleblock.h"
        "miner.h"
        "net.h"
        "net_permissions.h"
        "net_processing.h"
        "net_types.h"
        "netaddress.h"
        "netbase.h"
        "netmessagemaker.h"
        "node/coin.h"
        "node/coinstats.h"
        "node/context.h"
        "node/psbt.h"
        "node/transaction.h"
        "node/interface.h"
        "node/utxo_snapshot.h"
        "noui.h"
        "outputtype.h"
        "policy/feerate.h"
        "policy/fees.h"
        "policy/policy.h"
        "policy/rbf.h"
        "policy/settings.h"
        "pow.h"
        "protocol.h"
        "psbt.h"
        "random.h"
        "randomenv.h"
        "reverse_iterator.h"
        "rpc/blockchain.h"
        "rpc/client.h"
        "rpc/mining.h"
        "rpc/protocol.h"
        "rpc/rawtransaction_util.h"
        "rpc/register.h"
        "rpc/request.h"
        "rpc/server.h"
        "rpc/util.h"
        "scheduler.h"
        "script/descriptor.h"
        "script/keyorigin.h"
        "script/sigcache.h"
        "script/sign.h"
        "script/signingprovider.h"
        "script/standard.h"
        "shutdown.h"
        "signet.h"
        "streams.h"
        "support/allocators/secure.h"
        "support/allocators/zeroafterfree.h"
        "support/cleanse.h"
        "support/events.h"
        "support/lockedpool.h"
        "sync.h"
        "threadinterrupt.h"
        "threadsafety.h"
        "timedata.h"
        "torcontrol.h"
        "txdb.h"
        "txmempool.h"
        "txorphanage.h"
        "txrequest.h"
        "undo.h"
        "util/asmap.h"
        "util/bip32.h"
        "util/bytevectorhash.h"
        "util/check.h"
        "util/epochguard.h"
        "util/error.h"
        "util/fees.h"
        "util/getuniquepath.h"
        "util/golombrice.h"
        "util/hasher.h"
        "util/macros.h"
        "util/message.h"
        "util/moneystr.h"
        "util/rbf.h"
        "util/readwritefile.h"
        "util/settings.h"
        "util/sock.h"
        "util/spanparsing.h"
        "util/string_.h"
        "util/system.h"
        "util/threadnames.h"
        "util/time_.h"
        "util/tokenpipe.h"
        "util/trace.h"
        "util/translation.h"
        "util/change_type.h"
        "util/url.h"
        "util/vector.h"
        "validation.h"
        "validationinterface.h"
        "versionbits.h"
        "versionbitsinfo.h"
        "wallet/bdb.h"
        "wallet/coincontrol.h"
        "wallet/coinselection.h"
        "wallet/context.h"
        "wallet/crypter.h"
        "wallet/db.h"
        "wallet/dump.h"
        "wallet/external_signer.h"
        "wallet/external_signer_scriptpubkeyman.h"
        "wallet/feebumper.h"
        "wallet/fees.h"
        "wallet/ismine.h"
        "wallet/load.h"
        "wallet/rpcsigner.h"
        "wallet/rpcwallet.h"
        "wallet/salvage.h"
        "wallet/scriptpubkeyman.h"
        "wallet/sqlite.h"
        "wallet/wallet.h"
        "wallet/walletdb.h"
        "wallet/wallettool.h"
        "wallet/walletutil.h"
        "walletinitinterface.h"
        "warnings.h"
        "zmq/zmqabstractnotifier.h"
        "zmq/zmqnotificationinterface.h"
        "zmq/zmqpublishnotifier.h"
        "zmq/zmqrpc.h"
        "zmq/zmqutil.h"
        )


add_subdirectory(secp256k1)
include_directories(".")
# add_subdirectory(config)
# add_subdirectory(consensus)
add_subdirectory(crypto)
# add_subdirectory(primitives)
# add_subdirectory(support)
# add_subdirectory(util)
# add_subdirectory(policy)
# add_subdirectory(script)
add_subdirectory(univalue)
add_subdirectory(leveldb)

add_library(lib_bitcoin_includes INTERFACE)
target_link_libraries(lib_bitcoin_includes INTERFACE berkeley leveldb Univalue boost Secp256k1)
target_include_directories(lib_bitcoin_includes INTERFACE ".")


add_library(lib_bitcoin_common STATIC
        base58.cpp
        bech32.cpp
        bloom.cpp
        chainparams.cpp
        coins.cpp
        compressor.cpp
        core_read.cpp
        core_write.cpp
        key.cpp
        key_io.cpp
        merkleblock.cpp
        netaddress.cpp
        netbase.cpp
        net_permissions.cpp
        outputtype.cpp
        policy/feerate.cpp
        policy/policy.cpp
        protocol.cpp
        psbt.cpp
        rpc/rawtransaction_util.cpp
        rpc/util.cpp
        scheduler.cpp
        script/descriptor.cpp
        script/sign.cpp
        script/signingprovider.cpp
        script/standard.cpp
        versionbitsinfo.cpp
        warnings.cpp
        ${BITCOIN_CORE_H})

target_link_libraries(lib_bitcoin_common PUBLIC Univalue Secp256k1)
target_compile_definitions(lib_bitcoin_common PUBLIC HAVE_CONFIG_H=1)

add_library(lib_bitcoin_wallet STATIC
        wallet/coincontrol.cpp
        wallet/context.cpp
        wallet/crypter.cpp
        wallet/db.cpp
        wallet/dump.cpp
        wallet/external_signer_scriptpubkeyman.cpp
        wallet/external_signer.cpp
        wallet/feebumper.cpp
        wallet/fees.cpp
        wallet/interfaces.cpp
        wallet/load.cpp
        wallet/rpcdump.cpp
        wallet/rpcsigner.cpp
        wallet/rpcwallet.cpp
        wallet/scriptpubkeyman.cpp
        wallet/wallet.cpp
        wallet/walletdb.cpp
        wallet/walletutil.cpp
        wallet/coinselection.cpp
        ${BITCOIN_CORE_H})
target_link_libraries(lib_bitcoin_wallet PUBLIC sqlite3 lib_bitcoin_includes)
target_compile_definitions(lib_bitcoin_wallet PRIVATE HAVE_CONFIG_H=1)

add_library(lib_bitcoin_wallet_tool STATIC
        wallet/wallettool.cpp
        ${BITCOIN_CORE_H})
target_link_libraries(lib_bitcoin_wallet_tool PUBLIC lib_bitcoin_includes)
target_compile_definitions(lib_bitcoin_wallet_tool PRIVATE HAVE_CONFIG_H=1)


add_library(lib_bitcoin_consensus STATIC
        amount.h
        arith_uint256.cpp
        arith_uint256.h
        consensus/merkle.cpp
        consensus/merkle.h
        consensus/params.h
        consensus/tx_check.cpp
        consensus/validation.h
        hash.cpp
        hash.h
        prevector.h
        primitives/block.cpp
        primitives/block.h
        primitives/transaction.cpp
        primitives/transaction.h
        pubkey.cpp
        pubkey.h
        script/bitcoinconsensus.cpp
        script/interpreter.cpp
        script/interpreter.h
        script/script.cpp
        script/script.h
        script/script_error.cpp
        script/script_error.h
        serialize.h
        span.h
        tinyformat.h
        uint256.cpp
        uint256.h
        util/strencodings.cpp
        util/strencodings.h
        version.h)
target_link_libraries(lib_bitcoin_consensus PUBLIC
        Secp256k1
        lib_bitcoin_includes
        )

add_library(lib_bitcoin_util STATIC
        support/lockedpool.cpp
        chainparamsbase.cpp
        clientversion.cpp
        compat/glibcxx_sanity.cpp
        compat/strnlen.cpp
        fs.cpp
        interfaces/handler.cpp
        logging.cpp
        random.cpp
        randomenv.cpp
        rpc/request.cpp
        support/cleanse.cpp
        sync.cpp
        threadinterrupt.cpp
        util/asmap.cpp
        util/bip32.cpp
        util/bytevectorhash.cpp
        util/error.cpp
        util/fees.cpp
        util/getuniquepath.cpp
        util/hasher.cpp
        util/sock.cpp
        util/system.cpp
        util/message.cpp
        util/moneystr.cpp
        util/rbf.cpp
        util/readwritefile.cpp
        util/settings.cpp
        util/threadnames.cpp
        util/spanparsing.cpp
        util/strencodings.cpp
        util/string_.cpp
        util/time_.cpp
        util/tokenpipe.cpp
        util/url.cpp
        ${BITCOIN_CORE_H})
target_link_libraries(lib_bitcoin_util PUBLIC lib_bitcoin_includes libevent)
target_compile_definitions(lib_bitcoin_util PRIVATE HAVE_CONFIG_H=1)

add_library(lib_bitcoin_server STATIC
        addrdb.cpp
        addrman.cpp
        banman.cpp
        blockencodings.cpp
        blockfilter.cpp
        chain.cpp
        consensus/tx_verify.cpp
        dbwrapper.cpp
        flatfile.cpp
        httprpc.cpp
        httpserver.cpp
        i2p.cpp
        index/base.cpp
        index/blockfilterindex.cpp
        index/txindex.cpp
        init.cpp
        mapport.cpp
        miner.cpp
        net.cpp
        net_processing.cpp
        node/coin.cpp
        node/coinstats.cpp
        node/context.cpp
        node/interfaces.cpp
        node/psbt.cpp
        node/transaction.cpp
        node/interfaces.cpp
        noui.cpp
        policy/fees.cpp
        policy/rbf.cpp
        policy/settings.cpp
        pow.cpp
        rest.cpp
        rpc/blockchain.cpp
        rpc/mining.cpp
        rpc/misc.cpp
        rpc/net.cpp
        rpc/rawtransaction.cpp
        rpc/server.cpp
        script/sigcache.cpp
        shutdown.cpp
        signet.cpp
        timedata.cpp
        torcontrol.cpp
        txdb.cpp
        txmempool.cpp
        txorphanage.cpp
        txrequest.cpp
        validation.cpp
        validationinterface.cpp
        versionbits.cpp
        ${BITCOIN_CORE_H})


target_link_libraries(lib_bitcoin_server PUBLIC
        lib_bitcoin_includes
        libevent
        helpers
        leveldb)
target_compile_definitions(lib_bitcoin_server PRIVATE HAVE_CONFIG_H=1)

add_library(lib_bitcoin_cli STATIC
        compat/stdin.h
        compat/stdin.cpp
        rpc/client.cpp
        ${BITCOIN_CORE_H})
target_link_libraries(lib_bitcoin_cli PUBLIC lib_bitcoin_includes)

######## BINARIES ONLY ########
add_executable(bitcoin-cli bitcoin-cli.cpp)
target_link_libraries(bitcoin-cli PRIVATE
        lib_bitcoin_cli
        Univalue
        lib_bitcoin_util
        lib_bitcoin_includes
        Crypto)
target_compile_definitions(bitcoin-cli PRIVATE HAVE_CONFIG_H=1)


add_executable(bitcoin-tx bitcoin-tx.cpp)
target_link_libraries(bitcoin-tx PUBLIC
        Secp256k1
        lib_bitcoin_includes
        lib_bitcoin_common
        lib_bitcoin_util
        lib_bitcoin_consensus
        Crypto
        Univalue
        boost)
target_compile_definitions(bitcoin-tx PRIVATE HAVE_CONFIG_H=1)

add_executable(bitcoin-wallet bitcoin-wallet.cpp wallet/salvage.h wallet/salvage.cpp wallet/bdb.h wallet/bdb.cpp)
target_link_libraries(bitcoin-wallet PUBLIC
        lib_bitcoin_wallet
        lib_bitcoin_common
        lib_bitcoin_consensus
        lib_bitcoin_util
        lib_bitcoin_wallet_tool
        Crypto
        lib_bitcoin_includes
        berkeley
        )
target_compile_definitions(bitcoin-wallet PRIVATE HAVE_CONFIG_H=1 )

add_executable(bitcoin-util bitcoin-util.cpp)
target_link_libraries(bitcoin-util PUBLIC
        lib_bitcoin_includes
        lib_bitcoin_consensus
        lib_bitcoin_common
        lib_bitcoin_util
        Crypto
        Univalue
        Secp256k1
        libevent
        )
target_compile_definitions(bitcoin-util PRIVATE HAVE_CONFIG_H=1 )



