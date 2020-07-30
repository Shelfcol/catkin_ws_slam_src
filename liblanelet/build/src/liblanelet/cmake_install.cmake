# Install script for directory: /home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/gxf/catkin_ws_slam/src/liblanelet/export")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmainx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libliblanelet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libliblanelet.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libliblanelet.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/gxf/catkin_ws_slam/src/liblanelet/build/lib/libliblanelet.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libliblanelet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libliblanelet.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libliblanelet.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmainx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmainx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/liblanelet" TYPE FILE FILES
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/Attribute.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/BoundingBox.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/convert_coordinates.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/ImportExport.h"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LaneletBase.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LaneletFwd.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LaneletGraph.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/Lanelet.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LaneletMap.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/lanelet_point.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LineStrip.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/llet_xml.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LLTree.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/LocalGeographicCS.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/normalize_angle.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/EventRegion.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/Polygon.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/prettyprint.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/RegulatoryElement.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/RTree.h"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/Corridor.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/Exceptions.h"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/ParkingSpace.hpp"
    "/home/gxf/catkin_ws_slam/src/liblanelet/src/liblanelet/TrafficLight.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmainx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/gxf/catkin_ws_slam/src/liblanelet/build/bin/lanelet_demo")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo"
         OLD_RPATH "/home/gxf/catkin_ws_slam/src/liblanelet/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/lanelet_demo")
    endif()
  endif()
endif()

