cmake_minimum_required(VERSION 3.15)


add_library(Config INTERFACE bitcoin-config.h)
target_include_directories(Config INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
