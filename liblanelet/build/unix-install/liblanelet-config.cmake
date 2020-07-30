# ===================================================================================
#  liblanelet CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(liblanelet REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${liblanelet_LIBRARIES})
#
#    This file will define the following variables:
#      - liblanelet_LIBRARIES            : The list of libraries to links against.
#      - liblanelet_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                                                with this path is NOT needed.
#      - liblanelet_INCLUDE_DIRS         : The include directories.
#
#    Advanced variables:
#      - liblanelet_CONFIG_PATH
#
# =================================================================================================

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component(liblanelet_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component(liblanelet_INSTALL_PATH "${liblanelet_CONFIG_PATH}/../.." REALPATH)

# ======================================================
# Include directories to add to the user project:
# ======================================================

# Provide the include directories to the caller
SET(liblanelet_INCLUDE_DIRS "${liblanelet_INSTALL_PATH}/include")

# ======================================================
# Link directories to add to the user project:
# ======================================================

SET(liblanelet_LIB_COMPONENTS liblanelet)

SET(liblanelet_DEFINITIONS "-D_IC_BUILDER_LIBLANELET_")

# Provide the libs directory anyway, it may be needed in some cases.
SET(liblanelet_LIB_DIR "${liblanelet_INSTALL_PATH}/lib")
LINK_DIRECTORIES(${liblanelet_LIB_DIR})

# fill *_LIBRARIES and *_LIBRARY
SET(liblanelet_LIBRARIES "")
FOREACH(comp ${liblanelet_LIB_COMPONENTS}  )
  SET(liblanelet_LIBRARIES ${liblanelet_LIBRARIES} ${comp})
  SET(${comp}_LIBRARY ${comp})
ENDFOREACH()

# check for requested components (=libraries)
FOREACH(comp ${liblanelet_FIND_COMPONENTS}  )
  LIST(FIND liblanelet_LIB_COMPONENTS ${comp} _index)
  IF(${_index} GREATER -1)
    SET(liblanelet_${comp}_FOUND 1)
  ELSE()
    SET(liblanelet_${comp}_FOUND 0)
    IF(liblanelet_FIND_REQUIRED_${comp})
      MESSAGE(FATAL_ERROR "liblanelet ${comp} not available.")
    ENDIF()
  ENDIF()
ENDFOREACH()
