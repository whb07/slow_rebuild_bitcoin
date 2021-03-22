set(CMAKE_CXX_STANDARD 20)
add_library(
        Policy feerate.cpp feerate.h fees.cpp fees.h policy.cpp policy.h rbf.cpp rbf.h
        settings.cpp settings.h
)

target_include_directories(Policy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Policy Consensus Script boost)
target_compile_definitions(Policy PRIVATE COPYRIGHT_HOLDERS="anyone" COPYRIGHT_HOLDERS_SUBSTITUTION="everyone" HAVE_DECL_STRNLEN=1 CLIENT_VERSION_IS_RELEASE=1 CLIENT_VERSION_BUILD=1 CLIENT_VERSION_MINOR=1 CLIENT_VERSION_MAJOR=1.0 COPYRIGHT_YEAR=2020 PACKAGE_NAME="BITCOIN")
