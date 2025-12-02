#!/bin/bash

#######################################################
# Prepare a Docker image given an OS and architecture #
#######################################################
set -e

# Get some arguments from the user
os="ubuntu"
arch="amd64"
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
    --no-cache)
      no_cache="--no-cache"
      shift # past argument
      ;;
    *)
      shift # past argument
      ;;
  esac
done

# Find the script directory
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
project_dir="${script_dir}/.."
dockerfile="${script_dir}/Dockerfile.${os}"
image_name="microstrain/${os}_builder:${arch}"

# Build the docker image
docker build \
  -t "${image_name}" \
  ${no_cache} \
  --build-arg ARCH="${arch}" \
  --build-arg USER_ID="$(id -u)" \
  --build-arg GROUP_ID="$(id -g)" \
  -f "${dockerfile}" \
  "${project_dir}"
