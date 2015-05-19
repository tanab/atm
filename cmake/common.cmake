# Common compiler flags
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-braces")

if(NOT DEFINED CMAKE_MACOSX_RPATH)
    set(CMAKE_MACOSX_RPATH 0)
endif(NOT DEFINED CMAKE_MACOSX_RPATH)

# Enable testing globaly
enable_testing()
