# - Try to find CIMG
# Once done, this will define
#
#  CIMG_FOUND - system has CIMG
#  CIMG_INCLUDE_DIRS - the CIMG include directories
#

find_path(CImg_INCLUDE_DIR
  NAMES CImg.h
  PATHS ${CIMG_PKGCONF_INCLUDE_DIRS}
)

set(CIMG_PROCESS_INCLUDES CImg_INCLUDE_DIR)

if(UNIX)
   find_package(X11 REQUIRED)
   link_libraries(${X11_LIBRARIES})
   include_directories(${X11_INCLUDE_DIR})
endif()

find_package(Threads REQUIRED)

include(FindPackageHandleStandardArgs)


set(CIMG_PROCESS_LIBS ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

mark_as_advanced(CIMG_PROCESS_LIBS CIMG_PROCESS_INCLUDES)

MESSAGE(STATUS ${X11_LIBRARIES})
set(CIMG_LIBRARIES ${CIMG_PROCESS_LIBS})
set(CIMG_INCLUDE_DIRS ${CImg_INCLUDE_DIR})
set(CImg_LIBRARIES ${CIMG_PROCESS_LIBS})
set(CImg_INCLUDE_DIRS ${CImg_INCLUDE_DIR})