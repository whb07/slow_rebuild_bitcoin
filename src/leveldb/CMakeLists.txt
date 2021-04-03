cmake_minimum_required(VERSION 3.15)
project(LEVELDB)

# This project can use C11 but will gracefully decay down to C89.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

# This project requires C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(".")

add_library(leveldb STATIC
        "port/port_stdcxx.h"
        "port/port.h"
        "port/thread_annotations.h"
        "db/log_format.h"
        "db/memtable.h"
        "db/version_set.h"
        "db/write_batch_internal.h"
        "db/filename.h"
        "db/version_edit.h"
        "db/dbformat.h"
        "db/builder.h"
        "db/log_writer.h"
        "db/db_iter.h"
        "db/skiplist.h"
        "db/db_impl.h"
        "db/table_cache.h"
        "db/snapshot.h"
        "db/log_reader.h"
        "table/filter_block.h"
        "table/block_builder.h"
        "table/block.h"
        "table/two_level_iterator.h"
        "table/merger.h"
        "table/format.h"
        "table/iterator_wrapper.h"
        "util/crc32c.h"
        "util/arena.h"
        "util/random.h"
        "util/posix_logger.h"
        "util/hash.h"
        "util/histogram.h"
        "util/coding.h"
        "util/testutil.h"
        "util/mutexlock.h"
        "util/logging.h"
        "util/no_destructor.h"
        "util/windows_logger.h"
        "db/builder.cc"
        "db/c.cc"
        "db/dbformat.cc"
        "db/db_impl.cc"
        "db/db_iter.cc"
        "db/dumpfile.cc"
        "db/filename.cc"
        "db/log_reader.cc"
        "db/log_writer.cc"
        "db/memtable.cc"
        "db/repair.cc"
        "db/table_cache.cc"
        "db/version_edit.cc"
        "db/version_set.cc"
        "db/write_batch.cc"
        "table/block_builder.cc"
        "table/block.cc"
        "table/filter_block.cc"
        "table/format.cc"
        "table/iterator.cc"
        "table/merger.cc"
        "table/table_builder.cc"
        "table/table.cc"
        "table/two_level_iterator.cc"
        "util/env_posix_test_helper.h"
        "util/env_windows_test_helper.h"
        "util/arena.cc"
        "util/bloom.cc"
        "util/cache.cc"
        "util/coding.cc"
        "util/comparator.cc"
        "util/crc32c.cc"
        "util/env.cc"
        "util/filter_policy.cc"
        "util/hash.cc"
        "util/histogram.cc"
        "util/logging.cc"
        "util/options.cc"
        "util/status.cc"
        )
target_compile_definitions(leveldb PUBLIC LEVELDB_PLATFORM_POSIX=1 LEVELDB_IS_BIG_ENDIAN=0)
target_include_directories(leveldb PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)


add_library(helpers STATIC
        "helpers/memenv/memenv.cc")
target_include_directories(helpers PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/helpers/memenv>
        )

target_link_libraries(helpers PUBLIC leveldb)
