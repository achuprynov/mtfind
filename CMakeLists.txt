# 
# Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
# This file is part of solution of test task described in README.md.
#
cmake_minimum_required(VERSION 3.0)

project(mtfind)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(Boost COMPONENTS program_options REQUIRED)
IF(NOT Boost_FOUND)
    message(FATAL_ERROR "Failed to find boost")
ENDIF()

file(GLOB SOURCES "*.cpp")

add_executable(mtfind ${SOURCES})

target_link_libraries(mtfind ${Boost_LIBRARIES} pthread)

