
#!/bin/bash

################################################################################################################################################
# The purpose of this script is to build RPM files from MSCL for a CentOS version and an architecture
################################################################################################################################################
set -e

# Get some arguments from the user
arch="amd64"
centos_version="7"
python3_versions="3.7.16 3.8.16 3.9.16 3.10.9 3.11.1"
while [[ $# -gt 0 ]]; do
  case $1 in
    --arch)
      arch="$2"
      shift # past argument
      shift # past value
      ;;
    --centosVersion)
      centos_version="$2"
      shift # past argument
      shift # past value
      ;;
    --python3Versions)
      python3_versions="$2"
      shift # past argument
      shift # past value
      ;;
    *)
      shift # past argument
      ;;
  esac
done

# Find the script directory
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
project_dir="${script_dir}/.."
dockerfile="${script_dir}/Dockerfile.centos"
build_dir_name="build_centos_${arch}"

image_name="microstrain/mscl_centos_builder:${arch}"

# Pull the base image
docker pull "${arch}/centos:${centos_version}"

# Build the docker image
docker build \
  -t "${image_name}" \
  --build-arg ARCH="${arch}" \
  --build-arg CENTOS_VERSION="${centos_version}" \
  --build-arg PYTHON3_VERSIONS="${python3_versions}" \
  --build-arg USER_ID="$(id -u)" \
  --build-arg GROUP_ID="$(id -g)" \
  -f "${dockerfile}" \
  "${project_dir}"

# Determine the python locations based on the versions
for python3_version in ${python3_versions}; do
  python3_version_no_patch="$(echo ${python3_version} | cut -d'.' -f-2)"
  python3_dirs_flag="${python3_dirs_flag} --python3Dir /usr/lib/python${python3_version_no_patch}"
done

# Different flags for run depending on if we are running in jenkins or not
if [ "${ISHUDSONBUILD}" != "True" ]; then
  docker_it_flags="-it"
fi

# Run the build in the docker image
docker run \
  --rm \
  ${docker_it_flags} \
  --entrypoint="/bin/bash" \
  -v "${project_dir}:/home/microstrain/MSCL" \
  -w "/home/microstrain/MSCL" \
  --user="microstrain" \
  "${image_name}" -c -l " \
    git fetch origin --tags; \
    ./BuildScripts/build_linux.sh \
      ${python3_dirs_flag} \
      --python2Dir /usr/lib/python2.7 \
      --buildDir /home/microstrain/MSCL/${build_dir_name} \
  "