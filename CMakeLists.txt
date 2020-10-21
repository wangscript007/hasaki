cmake_minimum_required(VERSION 2.5)

project(hasaki)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()


# for macOSx warning
set(CMAKE_MACOSX_RPATH 1)


# set the dynamic libs path, when hasaki build .
set(LIBRARY_OUTPUT_DIRECTORY, ${PROJECT_SOURCE_DIR}/lib)

# enable debug and stdc++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

# set the src files which wants to be compiled.
aux_source_directory(. SRC_LIST)

# compile dynamic lib
add_library(hasaki SHARED ${SRC_LIST})

