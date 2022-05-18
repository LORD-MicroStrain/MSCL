
#!/bin/bash

################################################################################################################################################
# The purpose of this script is to build DEB files from MSCL for a Ubuntu version and an architecture
################################################################################################################################################
set -e

# Update this variable to change the python versions to build against
python3_versions="3.5.10 3.6.15 3.7.13"

# Get some arguments from the user
arch="amd64"
while [[ $# -gt 0 ]]; do
  case $1 in
    --arch)
      arch="$2"
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
dockerfile="${script_dir}/Dockerfile.ubuntu"
build_dir_name="build_ubuntu_${arch}"

image_name="microstrain/mscl_ubnutu_builder:${arch}"

# Build the docker image
docker build \
  -t "${image_name}" \
  --build-arg ARCH="${arch}" \
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
  --user="microstrain" \
  "${image_name}" -c " \
    /home/microstrain/MSCL/BuildScripts/jenkins_linux.sh \
      ${python3_dirs_flag} \
      --buildDir /home/microstrain/MSCL/${build_dir_name} \
  "

# Zip up the resulting artifacts
deb_files=$(find "${project_dir}/${build_dir_name}" -maxdepth 1 -mindepth 1 -name "*.deb" -printf '%f\n')
tar -C "${project_dir}/${build_dir_name}" -cvjSf "${project_dir}/mscl_ubuntu_${arch}.tar.bz2" ${deb_files}