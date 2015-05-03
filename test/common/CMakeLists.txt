cmake_minimum_required(VERSION 2.8.11)
project(atm-test-common)

file(GLOB SOURCES *.cpp)

include_directories(${atm-common_INCLUDE_DIRS})
include_directories(${MYSQLCPPCONN_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${atm-cache_INCLUDE_DIRS})

link_directories(${MYSQLCPPCONN_LIBRARY_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
link_directories(${atm-cache_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GMOCK_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${atm-common_LIBRARIES})

add_test(NAME "${PROJECT_NAME}" COMMAND ${PROJECT_NAME})
