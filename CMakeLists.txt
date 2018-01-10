project(Mscl LANGUAGES C)

cmake_minimum_required(VERSION 3.8)

set (CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED filesystem system)

add_custom_command(
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT Output/C++/Release/libmscl.so
  COMMAND bjam MSCL//stage_c++ release cxxflags="-std=c++11" --without-websockets -j 4
  )
add_custom_target(mscl_lib ALL DEPENDS Output/C++/Release/libmscl.so)

install(FILES Output/C++/Release/libmscl.so RENAME libmscl.so DESTINATION lib)
install(DIRECTORY MSCL/source/mscl DESTINATION include FILES_MATCHING PATTERN *.h)
install(FILES MsclConfig.cmake DESTINATION share/cmake/mscl/)
