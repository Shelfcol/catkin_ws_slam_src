# ===================================================================================
#  icmaker CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(icmaker REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${icmaker_LIBRARIES})
#
#    This file will define the following variables:
#      - icmaker_LIBRARIES                 : The list of libraries to links against.
#      - icmaker_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                              with this path is NOT needed.
#      - icmaker_INCLUDE_DIRS         : The include directories.
#
#    Advanced variables:
#      - icmaker_CONFIG_PATH
#
# =================================================================================================

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component(icmaker_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component(icmaker_INSTALL_PATH "${icmaker_CONFIG_PATH}/../.." REALPATH)


# ======================================================
# provide ICMAKER_DIRECTORY variable
# ======================================================

SET(icmaker_CMAKE_MODULE_DIRS "${icmaker_INSTALL_PATH}/share/icmaker")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${icmaker_CMAKE_MODULE_DIRS}/CMakeModules")

SET(ICMAKER_DIRECTORY "${icmaker_CMAKE_MODULE_DIRS}")


