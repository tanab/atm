cmake_minimum_required(VERSION 2.8.11)
project(atm)

# Include some common libraries and set appropriate compiler/linker flags
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(common)
include(testing)

find_package(MYSQLCPPCONN REQUIRED)
find_package(Boost 1.55.0 COMPONENTS system locale REQUIRED)

add_subdirectory(util)
add_subdirectory(cache)
add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(test)
