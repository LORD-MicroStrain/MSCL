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
release_build_dir="${build_dir}_release"

# Get some arguments from the user
python2Dirs=()
python3Dirs=()
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
      release_build_dir="${build_dir}_release"
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
  -DBUILD_PYTHON2="OFF" \
  -DBUILD_PYTHON3="OFF" \
  -DBUILD_TESTS="ON" \
  -DBUILD_EXAMPLES="ON" \
  -DBUILD_DOCUMENTATION="OFF" \
  -DWITH_SSL="OFF" \
  -DWITH_WEBSOCKETS="OFF" \
  -DBUILD_PACKAGE="ON" \
  -DLINK_STATIC_DEPS="OFF"
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
    -DBUILD_PYTHON2="OFF" \
    -DBUILD_PYTHON3="ON" \
    -DBUILD_TESTS="OFF" \
    -DBUILD_EXAMPLES="OFF" \
    -DBUILD_DOCUMENTATION="OFF" \
    -DWITH_SSL="OFF" \
    -DWITH_WEBSOCKETS="OFF" \
    -DBUILD_PACKAGE="ON" \
    -DLINK_STATIC_DEPS="ON" \
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
    -DBUILD_PYTHON2="ON" \
    -DBUILD_PYTHON3="OFF" \
    -DBUILD_TESTS="OFF" \
    -DBUILD_EXAMPLES="OFF" \
    -DBUILD_DOCUMENTATION="OFF" \
    -DWITH_SSL="OFF" \
    -DWITH_WEBSOCKETS="OFF" \
    -DBUILD_PACKAGE="ON" \
    -DLINK_STATIC_DEPS="ON" \
    \
    -UPython2_ROOT -DPython2_ROOT="${python2Dir}" \
    -UPython2_ROOT_DIR -DPython2_ROOT_DIR="${python2Dir}" \
    -UPython2_INCLUDE_DIR \
    -UPython2_EXECUTABLE -DPython2_EXECUTABLE=$(echo "${python2Dir}" | sed "s/lib/bin/g" | sed 's/\/$//')

  cmake --build "${build_dir}" -j$(nproc)
  cmake --build "${build_dir}" --target "package"
done

# Copy and rename all the packages into a release directory
# Renaming makes it easier for the release process
# Create the new directory
mkdir -p "${release_build_dir}"
for deb_package in "${build_dir}"/*".deb" ; do
  if [[ -f "$deb_package" ]]; then
    printf("Handling file: ${deb_package}\n")
    release_package_name=$(basename "${deb_package}")                  # Get the name of the file
    release_package_name="${release_package_name%_*}.deb"              # Remove the version number
    cp "${deb_package}" "${release_build_dir}/${release_package_name}" # Copy into a release directory
  else
    printf("Error with file: ${deb_package}\n")
  fi
done
