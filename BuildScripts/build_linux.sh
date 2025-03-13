#!/bin/bash

################################################################################################################################################
# This script is responsible for building and testing MSCL on Jenkins. This can be run locally to test if the builds will pass on Jenkins
################################################################################################################################################
set -e

# Find the script directory
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"

# Define some important directories
project_dir="${script_dir}/.."
build_dir="${project_dir}/jenkins_build"

# Get some arguments from the user
python2Dirs=()
python3Dirs=()
branch="unknown"
while [[ $# -gt 0 ]]; do
  case $1 in
    --python3Dir)
      python3Dirs+=("$2")
      shift # past argument
      shift # past value
      ;;
    --python2Dir)
      python2Dirs+=("$2")
      shift # past argument
      shift # past value
      ;;
    --buildDir)
      build_dir="${2}"
      shift # past argument
      shift # past value
      ;;
    --branch)
      branch="${2}"
      shift # past argument
      shift # past value
      ;;
  esac
done

# Build MSCL with everything except python2 and python3
mkdir -p "${build_dir}"
echo "!! Building MSCL in ${build_dir}"
cmake -S "${project_dir}" -B "${build_dir}" \
  -DCMAKE_VERBOSE_MAKEFILE="ON" \
  -DCMAKE_BUILD_TYPE="Release" \
  -DBUILD_SHARED_LIBS="ON" \
  -DMSCL_BUILD_PYTHON2="OFF" \
  -DMSCL_BUILD_PYTHON3="OFF" \
  -DMSCL_BUILD_TESTS="ON" \
  -DMSCL_BUILD_EXAMPLES="ON" \
  -DMSCL_ZIP_EXAMPLES="OFF" \
  -DMSCL_BUILD_DOCUMENTATION="OFF" \
  -DMSCL_WITH_SSL="OFF" \
  -DMSCL_WITH_WEBSOCKETS="OFF" \
  -DMSCL_BUILD_PACKAGE="ON" \
  -DMSCL_LINK_STATIC_DEPS="OFF" \
  -DMSCL_BRANCH="${branch}"
cmake --build "${build_dir}" -j$(nproc)

# Run the unit tests
cmake --build "${build_dir}" --target "test"

# Package everything up
cmake --build "${build_dir}" --target "package"

# Build for each requested python3 version
for python3Dir in "${python3Dirs[@]}"; do
  echo "!! Building MSCL with python ${python3Dir}"
  cmake -S "${project_dir}" -B "${build_dir}" \
    -DCMAKE_VERBOSE_MAKEFILE="ON" \
    -DCMAKE_BUILD_TYPE="Release" \
    -DBUILD_SHARED_LIBS="OFF" \
    -DMSCL_BUILD_PYTHON2="OFF" \
    -DMSCL_BUILD_PYTHON3="ON" \
    -DMSCL_BUILD_TESTS="OFF" \
    -DMSCL_BUILD_EXAMPLES="OFF" \
    -DMSCL_ZIP_EXAMPLES="OFF" \
    -DMSCL_BUILD_DOCUMENTATION="OFF" \
    -DMSCL_WITH_SSL="OFF" \
    -DMSCL_WITH_WEBSOCKETS="OFF" \
    -DMSCL_BUILD_PACKAGE="ON" \
    -DMSCL_LINK_STATIC_DEPS="ON" \
    -DMSCL_BRANCH="${branch}" \
    \
    -UPython3_ROOT -DPython3_ROOT="${python3Dir}" \
    -UPython3_ROOT_DIR -DPython3_ROOT_DIR="${python3Dir}" \
    -UPython3_INCLUDE_DIR \
    -UPython3_EXECUTABLE -DPython3_EXECUTABLE=$(echo "${python3Dir}" | sed "s/lib/bin/g" | sed 's/\/$//')

  cmake --build "${build_dir}" -j$(nproc)
  cmake --build "${build_dir}" --target "package"
done

# Build for each requested python2 version
for python2Dir in "${python2Dirs[@]}"; do
  echo "!! Building MSCL with python ${python2Dir}"
  cmake -S "${project_dir}" -B "${build_dir}" \
    -DCMAKE_VERBOSE_MAKEFILE="ON" \
    -DCMAKE_BUILD_TYPE="Release" \
    -DBUILD_SHARED_LIBS="OFF" \
    -DMSCL_BUILD_PYTHON2="ON" \
    -DMSCL_BUILD_PYTHON3="OFF" \
    -DMSCL_BUILD_TESTS="OFF" \
    -DMSCL_BUILD_EXAMPLES="OFF" \
    -DMSCL_ZIP_EXAMPLES="OFF" \
    -DMSCL_BUILD_DOCUMENTATION="OFF" \
    -DMSCL_WITH_SSL="OFF" \
    -DMSCL_WITH_WEBSOCKETS="OFF" \
    -DMSCL_BUILD_PACKAGE="ON" \
    -DMSCL_LINK_STATIC_DEPS="ON" \
    -DMSCL_BRANCH="${branch}" \
    \
    -UPython2_ROOT -DPython2_ROOT="${python2Dir}" \
    -UPython2_ROOT_DIR -DPython2_ROOT_DIR="${python2Dir}" \
    -UPython2_INCLUDE_DIR \
    -UPython2_EXECUTABLE -DPython2_EXECUTABLE=$(echo "${python2Dir}" | sed "s/lib/bin/g" | sed 's/\/$//')

  cmake --build "${build_dir}" -j$(nproc)
  cmake --build "${build_dir}" --target "package"
done
