#!/bin/bash

##############################################################################
# This script is a passthrough for arbitrary shell commands to run in Docker #
# It requires an image be build beforehand using the same os and arch names  #
##############################################################################
set -e

# Get some arguments from the user
os="ubuntu"
arch="amd64"
env_vars=()
remaining_args=()
while [[ $# -gt 0 ]]; do
  case $1 in
    --os)
      os="$2"
      shift # past argument
      shift # past value
      ;;
    --arch)
      arch="$2"
      shift # past argument
      shift # past value
      ;;
    --env|-e)
      env_vars+=("-e" "$2")
      shift # past argument
      shift # past value
      ;;
    *)
      remaining_args+=("$1")
      shift # past argument
      ;;
  esac
done

# If no arguments were passed, default to just running a shell
if [[ ${#remaining_args[@]} -eq 0 ]]; then
  remaining_args=("/bin/bash")
fi

# Wrap commands with linux32 for ARM32 architecture
if [[ "${arch}" == "arm32v7" ]]; then
  remaining_args=("linux32" "${remaining_args[@]}")
fi

# Find the script directory
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
project_dir="${script_dir}/.."
docker_project_dir="/home/microstrain/workspace"
image_name="microstrain/${os}_builder:${arch}"


# Different flags for run depending on if we are running in jenkins or not
if [ "${ISHUDSONBUILD}" != "True" ]; then
  docker_it_flags="-it"
fi

# Run a shell in the docker image
docker run \
    --rm \
    ${docker_it_flags} \
    --entrypoint="/bin/bash" \
    -v "${project_dir}:${docker_project_dir}" \
    -w "${docker_project_dir}" \
    --user="microstrain" \
    "${env_vars[@]}" \
    "${image_name}" -c "${remaining_args[@]}"
