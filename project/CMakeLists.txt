cmake_minimum_required(VERSION 2.8.9)
project(fingerprints)

#Bring the headers, such as Student.h into the project
#include_directories(include)
#set(EXECUTABLE_OUTPUT_PATH ${bin})
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
#file(GLOB SOURCES "src/*.cpp")


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Os -Wall -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "-s ${CIMG_FLAGS}")
include_directories(include)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
set(SOURCES src/starter1.cpp)

add_library(CImg INTERFACE IMPORTED GLOBAL)
set_property(
    TARGET CImg
    APPEND
    PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/CImg"s)
add_executable(run ${SOURCES})
