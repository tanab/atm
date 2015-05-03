cmake_minimum_required(VERSION 2.8.11)
project(atm-core)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDES ${PROJECT_SOURCE_DIR}/include/*.h)
list(APPEND SOURCES ${INCLUDES})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${atm-common_INCLUDE_DIRS})
include_directories(${atm-util_INCLUDE_DIRS})
include_directories(${atm-cache_INCLUDE_DIRS})
include_directories(${MYSQLCPPCONN_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

link_directories(${atm-common_LIBRARY_DIRS})
link_directories(${atm-util_LIBRARY_DIRS})
link_directories(${atm-cache_LIBRARY_DIRS})
link_directories(${MYSQLCPPCONN_LIBRARY_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${atm-common_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${atm-util_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${atm-cache_LIBRARIES})

# Exporting include dirs, library dirs and libraries
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)

set(${PROJECT_NAME}_LIBRARY_DIRS ${PROJECT_BINARY_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Library Directories" FORCE
)

set(${PROJECT_NAME}_LIBRARIES atm-core
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE
)

