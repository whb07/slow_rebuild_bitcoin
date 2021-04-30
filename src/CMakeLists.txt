
cmake_minimum_required(VERSION 3.20)
project(slow_rebuild_bitcoin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl--no-undefined")
#set(CMAKE_CXX_FLAGS "" CACHE STRING "C compiler flags" FORCE )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
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

# zmq
find_package(ZeroMQ REQUIRED)
add_library(zeromq INTERFACE IMPORTED)
set_property(TARGET zeromq PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ZeroMQ_INCLUDE_DIR})
set_property(TARGET zeromq PROPERTY INTERFACE_LINK_LIBRARIES ${ZeroMQ_LIBRARY})
include_directories(${ZeroMQ_INCLUDE_DIR})


file(GLOB BITCOIN_CORE_H
        "addrdb.cpp"
        "addrdb.h"
        "addrman.cpp"
        "addrman.h"
        "attributes.cpp"
        "attributes.h"
        "banman.cpp"
        "banman.h"
        "base58.cpp"
        "base58.h"
        "bech32.cpp"
        "bech32.h"
        "blockencodings.cpp"
        "blockencodings.h"
        "blockfilter.cpp"
        "blockfilter.h"
        "bloom.cpp"
        "bloom.h"
        "chain.cpp"
        "chain.h"
        "chainparams.cpp"
        "chainparams.h"
        "chainparamsbase.cpp"
        "chainparamsbase.h"
        "chainparamsseeds.cpp"
        "chainparamsseeds.h"
        "checkqueue.cpp"
        "checkqueue.h"
        "clientversion.cpp"
        "clientversion.h"
        "coins.cpp"
        "coins.h"
        "compat.cpp"
        "compat.h"
        "compat/assumptions.cpp"
        "compat/assumptions.h"
        "compat/byteswap.cpp"
        "compat/byteswap.h"
        "compat/cpuid.cpp"
        "compat/cpuid.h"
        "compat/endian.cpp"
        "compat/endian.h"
        "compat/sanity.cpp"
        "compat/sanity.h"
        "compressor.cpp"
        "compressor.h"
        "consensus/consensus.cpp"
        "consensus/consensus.h"
        "consensus/tx_check.cpp"
        "consensus/tx_check.h"
        "consensus/tx_verify.cpp"
        "consensus/tx_verify.h"
        "core_io.cpp"
        "core_io.h"
        "core_memusage.cpp"
        "core_memusage.h"
        "cuckoocache.cpp"
        "cuckoocache.h"
        "dbwrapper.cpp"
        "dbwrapper.h"
        "flatfile.cpp"
        "flatfile.h"
        "fs.cpp"
        "fs.h"
        "httprpc.cpp"
        "httprpc.h"
        "httpserver.cpp"
        "httpserver.h"
        "i2p.cpp"
        "i2p.h"
        "index/base.cpp"
        "index/base.h"
        "index/blockfilterindex.cpp"
        "index/blockfilterindex.h"
        "index/disktxpos.cpp"
        "index/disktxpos.h"
        "index/txindex.cpp"
        "index/txindex.h"
        "indirectmap.cpp"
        "indirectmap.h"
        "init.cpp"
        "init.h"
        "interfaces/chain.cpp"
        "interfaces/chain.h"
        "interfaces/handler.cpp"
        "interfaces/handler.h"
        "interfaces/node.cpp"
        "interfaces/node.h"
        "interfaces/wallet.cpp"
        "interfaces/wallet.h"
        "key.cpp"
        "key.h"
        "key_io.cpp"
        "key_io.h"
        "logging.cpp"
        "logging.h"
        "logging/timer.cpp"
        "logging/timer.h"
        "mapport.cpp"
        "mapport.h"
        "memusage.cpp"
        "memusage.h"
        "merkleblock.cpp"
        "merkleblock.h"
        "miner.cpp"
        "miner.h"
        "net.cpp"
        "net.h"
        "net_permissions.cpp"
        "net_permissions.h"
        "net_processing.cpp"
        "net_processing.h"
        "net_types.cpp"
        "net_types.h"
        "netaddress.cpp"
        "netaddress.h"
        "netbase.cpp"
        "netbase.h"
        "netmessagemaker.cpp"
        "netmessagemaker.h"
        "node/coin.cpp"
        "node/coin.h"
        "node/coinstats.cpp"
        "node/coinstats.h"
        "node/context.cpp"
        "node/context.h"
        "node/interface.cpp"
        "node/interface.h"
        "node/psbt.cpp"
        "node/psbt.h"
        "node/transaction.cpp"
        "node/transaction.h"
        "node/utxo_snapshot.cpp"
        "node/utxo_snapshot.h"
        "noui.cpp"
        "noui.h"
        "outputtype.cpp"
        "outputtype.h"
        "policy/feerate.cpp"
        "policy/feerate.h"
        "policy/fees.cpp"
        "policy/fees.h"
        "policy/policy.cpp"
        "policy/policy.h"
        "policy/rbf.cpp"
        "policy/rbf.h"
        "policy/settings.cpp"
        "policy/settings.h"
        "pow.cpp"
        "pow.h"
        "protocol.cpp"
        "protocol.h"
        "psbt.cpp"
        "psbt.h"
        "random.cpp"
        "random.h"
        "randomenv.cpp"
        "randomenv.h"
        "reverse_iterator.cpp"
        "reverse_iterator.h"
        "rpc/blockchain.cpp"
        "rpc/blockchain.h"
        "rpc/client.cpp"
        "rpc/client.h"
        "rpc/mining.cpp"
        "rpc/mining.h"
        "rpc/protocol.cpp"
        "rpc/protocol.h"
        "rpc/rawtransaction_util.cpp"
        "rpc/rawtransaction_util.h"
        "rpc/register.cpp"
        "rpc/register.h"
        "rpc/request.cpp"
        "rpc/request.h"
        "rpc/server.cpp"
        "rpc/server.h"
        "rpc/util.cpp"
        "rpc/util.h"
        "scheduler.cpp"
        "scheduler.h"
        "script/descriptor.cpp"
        "script/descriptor.h"
        "script/keyorigin.cpp"
        "script/keyorigin.h"
        "script/sigcache.cpp"
        "script/sigcache.h"
        "script/sign.cpp"
        "script/sign.h"
        "script/signingprovider.cpp"
        "script/signingprovider.h"
        "script/standard.cpp"
        "script/standard.h"
        "shutdown.cpp"
        "shutdown.h"
        "signet.cpp"
        "signet.h"
        "streams.cpp"
        "streams.h"
        "support/allocators/secure.cpp"
        "support/allocators/secure.h"
        "support/allocators/zeroafterfree.cpp"
        "support/allocators/zeroafterfree.h"
        "support/cleanse.cpp"
        "support/cleanse.h"
        "support/events.cpp"
        "support/events.h"
        "support/lockedpool.cpp"
        "support/lockedpool.h"
        "sync.cpp"
        "sync.h"
        "threadinterrupt.cpp"
        "threadinterrupt.h"
        "threadsafety.cpp"
        "threadsafety.h"
        "timedata.cpp"
        "timedata.h"
        "torcontrol.cpp"
        "torcontrol.h"
        "txdb.cpp"
        "txdb.h"
        "txmempool.cpp"
        "txmempool.h"
        "txorphanage.cpp"
        "txorphanage.h"
        "txrequest.cpp"
        "txrequest.h"
        "undo.cpp"
        "undo.h"
        "util/asmap.cpp"
        "util/asmap.h"
        "util/bip32.cpp"
        "util/bip32.h"
        "util/bytevectorhash.cpp"
        "util/bytevectorhash.h"
        "util/change_type.cpp"
        "util/change_type.h"
        "util/check.cpp"
        "util/check.h"
        "util/epochguard.cpp"
        "util/epochguard.h"
        "util/error.cpp"
        "util/error.h"
        "util/fees.cpp"
        "util/fees.h"
        "util/getuniquepath.cpp"
        "util/getuniquepath.h"
        "util/golombrice.cpp"
        "util/golombrice.h"
        "util/hasher.cpp"
        "util/hasher.h"
        "util/macros.cpp"
        "util/macros.h"
        "util/message.cpp"
        "util/message.h"
        "util/moneystr.cpp"
        "util/moneystr.h"
        "util/rbf.cpp"
        "util/rbf.h"
        "util/readwritefile.cpp"
        "util/readwritefile.h"
        "util/settings.cpp"
        "util/settings.h"
        "util/sock.cpp"
        "util/sock.h"
        "util/spanparsing.cpp"
        "util/spanparsing.h"
        "util/string.cpp"
        "util/string.h"
        "util/system.cpp"
        "util/system.h"
        "util/threadnames.cpp"
        "util/threadnames.h"
        "util/time.cpp"
        "util/time.h"
        "util/tokenpipe.cpp"
        "util/tokenpipe.h"
        "util/trace.cpp"
        "util/trace.h"
        "util/translation.cpp"
        "util/translation.h"
        "util/url.cpp"
        "util/url.h"
        "util/vector.cpp"
        "util/vector.h"
        "validation.cpp"
        "validation.h"
        "validationinterface.cpp"
        "validationinterface.h"
        "versionbits.cpp"
        "versionbits.h"
        "versionbitsinfo.cpp"
        "versionbitsinfo.h"
        "wallet/bdb.cpp"
        "wallet/bdb.h"
        "wallet/coincontrol.cpp"
        "wallet/coincontrol.h"
        "wallet/coinselection.cpp"
        "wallet/coinselection.h"
        "wallet/context.cpp"
        "wallet/context.h"
        "wallet/crypter.cpp"
        "wallet/crypter.h"
        "wallet/db.cpp"
        "wallet/db.h"
        "wallet/dump.cpp"
        "wallet/dump.h"
        "wallet/external_signer.h"
        "wallet/external_signer_scriptpubkeyman.cpp"
        "wallet/external_signer_scriptpubkeyman.h"
        "wallet/feebumper.cpp"
        "wallet/feebumper.h"
        "wallet/fees.cpp"
        "wallet/fees.h"
        "wallet/ismine.cpp"
        "wallet/ismine.h"
        "wallet/load.cpp"
        "wallet/load.h"
        "wallet/rpcsigner.h"
        "wallet/rpcwallet.cpp"
        "wallet/rpcwallet.h"
        "wallet/salvage.cpp"
        "wallet/salvage.h"
        "wallet/scriptpubkeyman.cpp"
        "wallet/scriptpubkeyman.h"
        "wallet/sqlite.cpp"
        "wallet/sqlite.h"
        "wallet/wallet.cpp"
        "wallet/wallet.h"
        "wallet/walletdb.cpp"
        "wallet/walletdb.h"
        "wallet/wallettool.cpp"
        "wallet/wallettool.h"
        "wallet/walletutil.cpp"
        "wallet/walletutil.h"
        "walletinitinterface.cpp"
        "walletinitinterface.h"
        "warnings.cpp"
        "warnings.h"
        "zmq/zmqabstractnotifier.cpp"
        "zmq/zmqabstractnotifier.h"
        "zmq/zmqnotificationinterface.cpp"
        "zmq/zmqnotificationinterface.h"
        "zmq/zmqpublishnotifier.cpp"
        "zmq/zmqpublishnotifier.h"
        "zmq/zmqrpc.cpp"
        "zmq/zmqrpc.h"
        "zmq/zmqutil.cpp"
        "zmq/zmqutil.h"
        )


add_subdirectory(secp256k1)
include_directories(".")
add_subdirectory(crypto)
add_subdirectory(univalue)
add_subdirectory(leveldb)
add_subdirectory(config)

add_library(lib_bitcoin_includes INTERFACE)
target_link_libraries(lib_bitcoin_includes INTERFACE berkeley leveldb Univalue boost Secp256k1 zeromq helpers Config)
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

target_link_libraries(lib_bitcoin_common PUBLIC Univalue Secp256k1 lib_bitcoin_includes)
target_compile_definitions(lib_bitcoin_common PUBLIC HAVE_CONFIG_H=1)

add_library(lib_bitcoin_wallet STATIC
        wallet/coincontrol.cpp
        wallet/context.cpp
        wallet/crypter.cpp
        wallet/db.cpp
        wallet/dump.cpp
        wallet/external_signer_scriptpubkeyman.cpp
        wallet/feebumper.cpp
        wallet/fees.cpp
        wallet/interfaces.cpp
        wallet/load.cpp
        wallet/rpcdump.cpp
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
target_link_libraries(lib_bitcoin_wallet_tool PUBLIC lib_bitcoin_includes lib_bitcoin_wallet)
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
        util/string.cpp
        util/time.cpp
        util/tokenpipe.cpp
        util/url.cpp
        ${BITCOIN_CORE_H})
target_link_libraries(lib_bitcoin_util PUBLIC lib_bitcoin_includes libevent lib_bitcoin_consensus)
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
target_link_libraries(lib_bitcoin_cli PUBLIC lib_bitcoin_includes Config)
target_compile_definitions(lib_bitcoin_cli PUBLIC HAVE_CONFIG_H=1)

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

