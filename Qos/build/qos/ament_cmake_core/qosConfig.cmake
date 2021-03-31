# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_qos_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED qos_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(qos_FOUND FALSE)
  elseif(NOT qos_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(qos_FOUND FALSE)
  endif()
  return()
endif()
set(_qos_CONFIG_INCLUDED TRUE)

# output package information
if(NOT qos_FIND_QUIETLY)
  message(STATUS "Found qos: 0.0.0 (${qos_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'qos' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message(WARNING "${_msg}")
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(qos_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_include_directories-extras.cmake")
foreach(_extra ${_extras})
  include("${qos_DIR}/${_extra}")
endforeach()
