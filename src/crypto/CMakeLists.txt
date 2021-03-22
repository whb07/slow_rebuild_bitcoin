set(CMAKE_CXX_STANDARD 20)
include_directories(ctaes)
add_library(Crypto aes.cpp aes.h chacha20.cpp chacha20.h chacha_poly_aead.cpp chacha_poly_aead.h common.h
        hkdf_sha256_32.cpp hkdf_sha256_32.h hmac_sha256.cpp hmac_sha256.h hmac_sha512.cpp hmac_sha512.h
        poly1305.cpp poly1305.h ripemd160.cpp ripemd160.h sha1.cpp sha1.h sha256.cpp sha256.h
        sha256_avx2.cpp sha256_shani.cpp sha256_sse4.cpp sha256_sse41.cpp sha512.cpp sha512.h
        siphash.cpp siphash.h
        )
target_include_directories (Crypto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Crypto Support)