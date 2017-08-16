#
# Copyright (C) 2016-2018, Abundant Robotics (R)
#

project(Mscl LANGUAGES C)

cmake_minimum_required(VERSION 3.8)

find_package(Boost REQUIRED filesystem system)

add_custom_command(
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT Output/C++/Release/libmscl.so
  COMMAND bjam MSCL//stage_c++ release -j 4
  )
add_custom_target(mscl_lib ALL DEPENDS Output/C++/Release/libmscl.so)

install(FILES Output/C++/Release/libmscl.so RENAME libmscl.so DESTINATION lib)
install(DIRECTORY MSCL/source/mscl DESTINATION include FILES_MATCHING PATTERN *.h)
install(FILES FindMscl.cmake DESTINATION share/cmake/mscl/)
