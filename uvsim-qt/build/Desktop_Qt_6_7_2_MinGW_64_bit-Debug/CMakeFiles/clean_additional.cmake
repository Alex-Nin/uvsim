# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\uvsim-qt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\uvsim-qt_autogen.dir\\ParseCache.txt"
  "uvsim-qt_autogen"
  )
endif()
