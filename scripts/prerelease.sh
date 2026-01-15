#!/bin/bash

# Exit on error
set -ex

# Compare versions
function version_compare() {
  local IFS=.
  local i ver1=($1) ver2=($2)

  # fill empty fields in ver1 with zeros
  for ((i=${#ver1[@]}; i<${#ver2[@]}; i++)); do
    ver1[i]=0
  done

  # fill empty fields in ver2 with zeros
  for ((i=${#ver2[@]}; i<${#ver1[@]}; i++)); do
    ver2[i]=0
  done

  for ((i=0; i<${#ver1[@]}; i++)); do
    if [[ -z ${ver1[i]} ]]; then
      ver1[i]=0
    fi
    if [[ -z ${ver2[i]} ]]; then
      ver2[i]=0
    fi
    if ((10#${ver1[i]} > 10#${ver2[i]})); then
      echo 1
      return
    elif ((10#${ver1[i]} < 10#${ver2[i]})); then
      echo -1
      return
    fi
  done

  echo 0
}

# On Jenkins, log all commands
if [ "${ISHUDSONBUILD}" == "True" ]; then
  set -x
fi

# Get some arguments from the user
while [[ $# -gt 0 ]]; do
  case $1 in
    --target)
      target="$2"
      shift # past argument
      shift # past value
      ;;
    *)
      shift # past argument
      ;;
  esac
done

if [ -z "${target}" ]; then
  echo "Script must be called with --target"
  exit 1
fi

# Only need to perform a pre-release check for develop
if [ "${target}" != "develop" ]; then
  echo "No pre-release check required for ${target}"
  exit 0
fi

# Some constants and other important variables
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
project_dir="${script_dir}/.."
build_dir="${project_dir}/build_prerelease"

mkdir -p "${build_dir}"

# Configure a basic cmake project so we can check the version
cmake -S "${project_dir}" -B "${build_dir}" -DCMAKE_BUILD_TYPE="Release" \
  || echo "" # Failures are OK. Project version is added to the cache immediately

# Only continue the prerelease if the project version changed on develop
pushd "${build_dir}"

# Make sure the tags are fetched
git fetch --tags

github_release_version=$(git describe --tags --match "v*" --abbrev=0 HEAD)
project_release_version="v$(cmake --system-information | awk -F= '$1~/CMAKE_PROJECT_VERSION:STATIC/{print$2}')"

popd

# No need for the build directory after getting the project version
rm -rf "${build_dir}"

# Check for a new release version
if [[ $(version_compare "${project_release_version:1}" "${github_release_version:1}") -eq 0 ]]; then
  echo "No new version to update for pre-release from ${target} since the current version matches the latest version"
  exit 0
fi

# Make sure the release version didn't go down
if [[ $(version_compare "${project_release_version:1}" "${github_release_version:1}") -lt 0 ]]; then
  echo "The project version is lower than the last release. Fix the new release number before proceeding."
  exit 1
fi

# Set up the auth for github assuming that a valid token is in the environment at "GH_TOKEN"
git_askpass_file="${project_dir}/.mscl-git-askpass"
echo 'echo ${GH_TOKEN}' > "${git_askpass_file}"
chmod 700 "${git_askpass_file}"

pushd "${project_dir}"

# Find the commit that this project is built on
mscl_commit="$(git rev-parse HEAD)"

# Delete the tag if it exists
GIT_ASKPASS="${git_askpass_file}" git push --delete origin "${project_release_version}" || echo "No existing tag named ${project_release_version}."

changelog_file="${project_dir}/CHANGELOG.md"
forthcoming_header="^## Forthcoming"

# Check if there are any changes in the changelog first
if [ $(grep -A 1 "${forthcoming_header}" ${changelog_file} | grep -v -e "${forthcoming_header}" -e "^$" | wc -l) -eq 0 ]; then
  echo "Nothing to update"
  exit 0
fi

changelog_release_name="${project_release_version}"

# Remove any leading 'v' from the release tag
if [[ ${changelog_release_name} =~ ^v ]]; then
  changelog_release_name="${changelog_release_name:1}"
fi

# Get the date of release
today=$(date '+%Y-%m-%d')

# Shift the forthcoming details down and prepend the version tag
sed -i -e "/^## Forthcoming/s,$,\n\n## ${changelog_release_name} - ${today},g" "${changelog_file}"

# Replace all the previous release asset links with the new links
sed -i -e "s,${github_release_version},${project_release_version},g" "${project_dir}/README.md"

# Add any pending changes
git add --all

# Only commit if there are changes
if ! git diff-index --quiet HEAD --; then
  git commit -m "Pre-release updates for release ${project_release_version}." --author="microstrain-build <support@sensorcloud.com>"

  GIT_ASKPASS="${git_askpass_file}" git push origin ${target}
else
  echo "No changes to commit for pre-release"
fi

popd

rm "${git_askpass_file}"
