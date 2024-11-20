#!/bin/bash

# Exit on error
set -ex
set +x

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
#if [ -z "${artifacts}" ] || [ -z "${docs_zip}" ] || [ -z "${release_name}" ] || [ -z "${target}" ]; then
#  echo "Script must be called with --target, --docs-zip, --artifacts and --release"
#  exit 1
#fi

# Some constants and other important variables
#repo="LORD-MicroStrain/MSCL"
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
project_dir="${script_dir}/.."
#tmp_dir="/tmp"
#docs_dir="${tmp_dir}/mip_sdk_documentation"docs_dir="${project_dir}/mip_sdk_documentation"
#docs_release_dir="${docs_dir}/${release_name}"

# Find the commit that this project is built on
pushd "${project_dir}"
mscl_commit="$(git rev-parse HEAD)"
popd

## Generate a release notes file
#documentation_link="https://lord-microstrain.github.io/mip_sdk_documentation/${release_name}"
#changelog_link="https://github.com/LORD-MicroStrain/MSCL/blob/${release_name}/CHANGELOG.txt"
#release_notes_file="${tmp_dir}/mip-sdk-release-notes-${release_name}.md"
#echo "## Useful Links" > ${release_notes_file}
#echo "* [Changelog](${changelog_link})" >> ${release_notes_file}
#echo "* [Documentation](${documentation_link})" >> ${release_notes_file}
#
## Deploy the artifacts to Github
#gh release delete \
#  -y \
#  -R "${repo}" \
#  "${release_name}" || echo "No existing release named ${release_name}. Creating now..."
#gh release create \
#  -R "${repo}" \
#  --title "${release_name}" \
#  --target "${target}" \
#  ${generate_notes_flag} \
#  --notes-file "${release_notes_file}" \
#  "${release_name}" ${artifacts}
#rm -f "${release_notes_file}"
#
## Commit the documentation to the github pages branch
#rm -rf "${docs_dir}"
#git clone -b "main" "https://github.com/LORD-MicroStrain/mip_sdk_documentation.git" "${docs_dir}"
#rm -rf "${docs_release_dir}"
#mkdir -p "${docs_release_dir}"
#pushd "${docs_release_dir}"
#unzip "${docs_zip}" -d "${docs_release_dir}"

changelog_file="${project_dir}/CHANGELOG.txt"

# Remove any leading 'v' from the release tag
if [[ ${release_name} =~ ^v ]]; then
    release_name="${release_name:1}"
fi

forthcoming="Forthcoming"

# Get the date of release
today=$(date '+%Y-%m-%d')

# Shift the forthcoming details down and prepend the version tag
sed -i -e "s/${forthcoming}/${forthcoming}\n\n${release_name} - ${today}/g" "${changelog_file}"

# /BuildScripts/release.sh --release "$(git describe --tag --abbrev=0)"

## Only commit if there are changes
#if ! git diff-index --quiet HEAD --; then
#  git add --all
#  git commit -m "Adds/updates documentation for release ${release_name} at ${repo}@${mscl_commit}."
#
#  # Set up the auth for github assuming that a valid token is in the environment at "GH_TOKEN"
#  git_askpass_file="${project_dir}/.mip-sdk-git-askpass"
#  echo 'echo ${GH_TOKEN}' > "${git_askpass_file}"
#  chmod 700 "${git_askpass_file}"
#  GIT_ASKPASS="${git_askpass_file}" git push origin main
#  rm "${git_askpass_file}"
#else
#  echo "No changes to commit to documentation"
#fi
#popd
