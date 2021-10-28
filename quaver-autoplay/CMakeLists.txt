cmake_minimum_required(VERSION 3.8)

project ("quaver-autoplay")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(quaver-autoplay SHARED ${SOURCES})