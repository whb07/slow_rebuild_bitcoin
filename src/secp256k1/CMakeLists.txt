
project(SECP256K1 LANGUAGES C)
cmake_minimum_required(VERSION 3.2)
# gmp
find_package(GMP REQUIRED)
add_library(gmp INTERFACE IMPORTED)
set_property(TARGET gmp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${GMP_INCLUDES})
set_property(TARGET gmp PROPERTY INTERFACE_LINK_LIBRARIES ${GMP_LIBRARIES})

# file(GLOB_RECURSE source_list "src/*.c" "src/*.h")
add_library(Secp256k1
        "src/basic-config.h"
        "src/asm"
        "src/assumptions.h"
        "src/ecdsa.h"
        "src/ecdsa_impl.h"
        "src/eckey.h"
        "src/eckey_impl.h"
        "src/ecmult.h"
        "src/ecmult_const.h"
        "src/ecmult_const_impl.h"
        "src/ecmult_gen.h"
        "src/ecmult_gen_impl.h"
        "src/ecmult_impl.h"
        "src/ecmult_static_context.h"
        "src/field.h"
        "src/field_10x26.h"
        "src/field_10x26_impl.h"
        "src/field_5x52.h"
        "src/field_5x52_asm_impl.h"
        "src/field_5x52_impl.h"
        "src/field_5x52_int128_impl.h"
        "src/field_impl.h"
        "src/gen_context.c"
        "src/group.h"
        "src/group_impl.h"
        "src/hash.h"
        "src/hash_impl.h"
        "src/libsecp256k1-config.h"
        "src/modules"
        "src/num.h"
        "src/num_gmp.h"
        "src/num_gmp_impl.h"
        "src/num_impl.h"
        "src/scalar.h"
        "src/scalar_4x64.h"
        "src/scalar_4x64_impl.h"
        "src/scalar_8x32.h"
        "src/scalar_8x32_impl.h"
        "src/scalar_impl.h"
        "src/scalar_low.h"
        "src/scalar_low_impl.h"
        "src/scratch.h"
        "src/scratch_impl.h"
        "src/secp256k1.c"
        "src/util.h"
        "src/modules/ecdh/main_impl.h"
        "src/modules/extrakeys/main_impl.h"
        "src/modules/recovery/main_impl.h"
        "src/modules/schnorrsig/main_impl.h"
)

target_include_directories(Secp256k1 PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE src)

target_compile_definitions(Secp256k1 PUBLIC USE_BASIC_CONFIG=1  ECMULT_GEN_PREC_BITS=8 USE_NUM_GMP=0 USE_WIDEMUL_64=1  ECMULT_WINDOW_SIZE=15 USE_FIELD_INV_BUILTIN=1 USE_SCALAR_INV_BUILTIN=1 )
target_link_libraries(Secp256k1 gmp)