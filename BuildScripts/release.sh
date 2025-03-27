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
generate_notes_flag=""
while [[ $# -gt 0 ]]; do
  case $1 in
    --artifacts)
      artifacts="$2"
      shift # past argument
      shift # past value
      ;;
    --docs-zip)
      docs_zip="$2"
      shift # past argument
      shift # past value
      ;;
    --target)
      target="$2"
      shift # past argument
      shift # past value
      ;;
    --release)
      release_name="$2"
      shift # past argument
      shift # past value
      ;;
    --generate-notes)
      generate_notes_flag="--generate-notes"
      shift # past argument
      ;;
    *)
      shift # past argument
      ;;
  esac
done
if [ -z "${artifacts}" ] || [ -z "${docs_zip}" ] || [ -z "${release_name}" ] || [ -z "${target}" ]; then
  echo "Script must be called with --target, --docs-zip, --artifacts and --release"
  exit 1
fi

# Only need to perform a release for master or develop
if [ "${target}" != "master" ] && [ "${target}" != "develop" ]; then
  echo "No release required for ${target}"
  exit 0
fi

# Some constants and other important variables
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
project_dir="${script_dir}/.."

pushd "${project_dir}"

# Make sure we are on the target branch
git checkout -b ${target}

# Make sure the tags are pulled
git pull --tags

if [ "${target}" == "master" ]; then
  pushd "${project_dir}/build_ubuntu_amd64"

  github_release_version=$(git describe --tags --match "v*" --abbrev=0 HEAD)
  project_release_version="v$(cmake --system-information | awk -F= '$1~/CMAKE_PROJECT_VERSION:STATIC/{print$2}')"

  popd

  # Make sure the release version changed
  if [[ $(version_compare "${project_release_version:1}" "${github_release_version:1}") -le 0 ]]; then
    echo "The project version needs to be greater than the last release. Fix the new release number before proceeding."
    exit 1
  fi

  # Use the release name from the project
  release_name=${project_release_version}
fi

# Some more constants and other important variables
repo="LORD-MicroStrain/MSCL"
tmp_dir="/tmp"
docs_dir="${tmp_dir}/MSCL_documentation"
docs_release_dir="${docs_dir}/${release_name}"

# Set up the auth for github assuming that a valid token is in the environment at "GH_TOKEN"
git_askpass_file="${project_dir}/.mscl-git-askpass"
echo 'echo ${GH_TOKEN}' > "${git_askpass_file}"
chmod 700 "${git_askpass_file}"

# Find the commit that this project is built on
mscl_commit="$(git rev-parse HEAD)"

# Only delete the last 'latest' release which is for develop
if [ "${target}" == "develop" ]; then
  # Delete the release before the tag. Deleting the tag before the release may cause issues
  gh release delete \
    -y \
    -R "${repo}" "${release_name}" || echo "No existing release named ${release_name}."

  # Delete the tag if it exists
  GIT_ASKPASS="${git_askpass_file}" git push --delete origin "${release_name}" || echo "No existing tag named ${release_name}."
fi

popd

# Generate a release notes file
documentation_link="https://lord-microstrain.github.io/MSCL_documentation/${release_name}"
changelog_link="https://github.com/LORD-MicroStrain/MSCL/blob/${release_name}/CHANGELOG.md"
release_notes_file="${tmp_dir}/mscl-release-notes-${release_name}.md"
echo "## Useful Links" > ${release_notes_file}
echo "* [Changelog](${changelog_link})" >> ${release_notes_file}
echo "* [Full Documentation](${documentation_link}/MSCL_API_Docs)" >> ${release_notes_file}
echo "* [Public Documentation](${documentation_link}/MSCL_Docs)" >> ${release_notes_file}

regex_pattern='^## [0-9]+.+'
if [ -z "${generate_notes_flag}" ]; then
  add_changes=0

  while IFS= read line; do
    # Read between release notes (I.E. '## 1.2.4...' and '## 1.2.3...')
    if [[ "${line}" =~ ${regex_pattern} ]]; then
      # Start reading change notes
      if [[ ${add_changes} -eq 0 ]]; then
        add_changes=1
        echo "" >> ${release_notes_file}
        echo "## What's Changed" >> ${release_notes_file}
        continue
      # Stop reading change notes
      else
        break
      fi
    fi

    if [[ ${add_changes} -eq 1 ]]; then
      # End of the changes (empty line)
      if [[ "${line}" == "" ]]; then
        break
      fi

      # Append the changes to the release notes while keeping leading whitespaces
      echo -e "${line}" >> ${release_notes_file}
    fi
  done < "${project_dir}/CHANGELOG.md"
fi

# Deploy the artifacts to Github
gh release create \
  "${release_name}" ${artifacts} \
  --repo "${repo}" \
  --title "${release_name}" \
  --target "${target}" \
  ${generate_notes_flag} \
  --notes-file "${release_notes_file}"

rm -f "${release_notes_file}"

pushd "${project_dir}"
  # Update the local tags after creating the release (just a precaution to prevent issues with future releases)
  git fetch --tags origin
popd

# Commit the documentation to the github pages branch
rm -rf "${docs_dir}"
git clone -b "main" "https://github.com/LORD-MicroStrain/MSCL_documentation.git" "${docs_dir}"
rm -rf "${docs_release_dir}"
mkdir -p "${docs_release_dir}"

pushd "${docs_release_dir}"

unzip "${docs_zip}" -d "${docs_release_dir}"

documentation_readme="${docs_dir}/README.md"

# If the tag is not already in the readme, add it after latest
if ! grep -q -E "^\| ${release_name} +\|" "${documentation_readme}"; then
  # Variables to simplify the append process
  full_documentation_link="${documentation_link}/MSCL_API_Docs"
  public_documentation_link="${documentation_link}/MSCL_Docs"
  append_links="\n| $release_name | [Full Documentation]($full_documentation_link) | [Public Documentation]($public_documentation_link) |"

  # Append the new links after release so new releases are at the top
  sed -i -E "/^\| latest +/s,$,${append_links},g" "${documentation_readme}"
fi

# Add any pending changes
git add --all

# Only commit if there are changes
if ! git diff-index --quiet HEAD --; then
  git commit -m "Adds/updates documentation for release ${release_name} at ${repo}@${mscl_commit}." --author="microstrain-build <support@sensorcloud.com>"

  GIT_ASKPASS="${git_askpass_file}" git push origin main
else
  echo "No changes to commit to documentation"
fi
popd

rm "${git_askpass_file}"
