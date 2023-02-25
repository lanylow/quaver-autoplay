cmake_minimum_required(VERSION 3.8)

project("quaver-autoplay")

set(CXX_STANDARD 17)

include_directories(inc)

set(SOURCES
	src/entry.cpp
	src/memory.cpp
	src/autoplayer/autoplayer.cpp
	src/autoplayer/replay.cpp
)

add_library(quaver-autoplay SHARED ${SOURCES})