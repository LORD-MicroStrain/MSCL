

find_library(MSCL_LIB NAMES mscl)
find_path(MSCL_INCLUDE NAMES mscl/Version.h)

find_package(Boost REQUIRED COMPONENTS system filesystem)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Mscl DEFAULT_MSG MSCL_LIB MSCL_INCLUDE)

add_library(Mscl::mscl SHARED IMPORTED)

set_target_properties(Mscl::mscl PROPERTIES
  IMPORTED_LOCATION ${MSCL_LIB}
  INTERFACE_LINK_LIBRARIES "Boost::system;Boost::filesystem"
  INTERFACE_INCLUDE_DIRECTORIES ${MSCL_INCLUDE})

