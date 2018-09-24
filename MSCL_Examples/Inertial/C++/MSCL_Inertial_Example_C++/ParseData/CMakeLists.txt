project(parsedata)
 
cmake_minimum_required(VERSION 3.5)
 
find_package(Boost REQUIRED filesystem system)
 
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")


set(MSCL_INC "(path to mscl)/MSCL/MSCL/source") 

include_directories(${MSCL_INC})
 
 
LINK_DIRECTORIES("(path to mscl)/MSCL/Output/C++/Release")
 
SET(PARSE_SRCS ParseData.cpp)
 
LINK_LIBRARIES("libmscl.so")
 
ADD_EXECUTABLE(parse ${PARSE_SRCS})
