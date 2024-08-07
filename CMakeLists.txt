cmake_minimum_required(VERSION 3.8)

project(quaver-autoplay)

set(CXX_STANDARD 17)

include_directories(
  "inc/"
)

file(GLOB_RECURSE SOURCES
  "src/*.cpp"
  "inc/*.hpp"
)

add_library(quaver-autoplay SHARED ${SOURCES})