cmake_minimum_required(VERSION 2.8)
project(gion)

SET(GION_SOCKFD_PATH "/tmp/lime_sock")

# Sampleプログラムをビルドする場合は「ON」にしてください
SET(SAMPLE_BUILD ON)

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(STATUS "${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/include/config.hh.in ${PROJECT_SOURCE_DIR}/include/config.hh)

ADD_SUBDIRECTORY(src)

# Sample Build
if(SAMPLE_BUILD)
  ADD_SUBDIRECTORY(sample)
endif()
