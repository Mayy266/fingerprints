cmake_minimum_required(VERSION 3.0.0)

project(fingerprints)

#However, the file(GLOB...) allows for wildcard additions:

file(GLOB SOURCES "src/*.cpp")

list( APPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/external
)

# CImg
find_package( CImg REQUIRED )
list( APPEND PROJ_INCLUDE_DIRS
    ${CImg_INCLUDE_DIRS}
)

# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")

include_directories(${CImg_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)
MESSAGE(STATUS ${PROJ_LIBRARY_DIRS})

add_executable(fingerprints
	"./src/image_manipulation.cpp" "./src/coord.cpp"
)
MESSAGE(STATUS ${CIMG_LIBRARIES})
target_link_libraries(fingerprints ${CImg_LIBRARIES})
