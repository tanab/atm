cmake_minimum_required(VERSION 2.8.11)
project(atm-test-core)

file(GLOB SOURCES *.cpp)

#include_directories(${atm-core_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GMOCK_LIBRARIES})
add_test(NAME "${PROJECT_NAME}" COMMAND ${PROJECT_NAME})
