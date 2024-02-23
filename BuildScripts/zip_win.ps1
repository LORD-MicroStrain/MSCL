########################################################################################################################################################
# This script is responsible for zipping up the binaries produced by the build on windows. If running manually, this should be run after "build_win.ps1"
########################################################################################################################################################

# Find the script directory and set some constants
$script_dir = $PSScriptRoot
$project_dir = "${script_dir}/.."
$build_output_dir = "${project_dir}/build_windows"
$output_dir = "${project_dir}/Output"
$cpp_output_dir = "${output_dir}/C++"
$static_output_dir = "${cpp_output_dir}/Static"
$shared_output_dir = "${cpp_output_dir}/Shared"
$dotnet_output_dir = "${output_dir}/DotNet"
$documentation_output_dir = "${output_dir}/Documentation"
$examples_output_dir = "${output_dir}/Examples"
$python_output_dir = "${output_dir}/Python"

# Find the version from git
pushd "${project_dir}"
$mscl_git_version = (git describe --tags)
popd

# Zip up the Static library
$static_zip_file = "mscl_${mscl_git_version}_Windows_Static_C++.zip"
pushd "${output_dir}/${static_output_dir}"
echo "Compressing ${pwd} to ${build_output_dir}/${static_zip_file}"
Compress-Archive -Force -Path ./* -DestinationPath "${build_output_dir}/${static_zip_file}"
popd

# Zip up the Shared library
$shared_zip_file = "mscl_${mscl_git_version}_Windows_Shared_C++.zip"
pushd "${output_dir}/${shared_output_dir}"
echo "Compressing ${pwd} to ${build_output_dir}/${shared_zip_file}"
Compress-Archive -Force -Path ./* -DestinationPath "${build_output_dir}/${shared_zip_file}"
popd

# Zip up the C# library
$dotnet_zip_file = "mscl_${mscl_git_version}_Windows_DotNet.zip"
pushd "${output_dir}/${dotnet_output_dir}"
echo "Compressing ${pwd} to ${build_output_dir}/${dotnet_zip_file}"
Compress-Archive -Force -Path ./* -DestinationPath "${build_output_dir}/${dotnet_zip_file}"
popd

# Zip up the documentation
$documentation_zip_file = "mscl_${mscl_git_version}_Documentation.zip"
pushd "${output_dir}/${documentation_output_dir}"
echo "Compressing ${pwd} to ${build_output_dir}/${documentation_zip_file}"
Compress-Archive -Force -Path . -DestinationPath "${build_output_dir}/${documentation_zip_file}"
popd

# Zip up the examples
$examples_zip_file = "mscl_${mscl_git_version}_Examples.zip"
pushd "${output_dir}/${examples_output_dir}"
echo "Compressing ${pwd} to ${build_output_dir}/${examples_zip_file}"
Compress-Archive -Force -Path . -DestinationPath "${build_output_dir}/${examples_zip_file}"
popd

# Zip up the python versions
Get-ChildItem "${python_output_dir}" -Directory | ForEach-Object {
  $python_version = ${_}.Name
  $python_version_output_dir = ${_}.FullName
  $python_zip_file = "mscl_${mscl_git_version}_Python${python_version}.zip"
  pushd "${output_dir}/${python_version_output_dir}"
  echo "Compressing ${pwd} to ${build_output_dir}/${python_zip_file}"
  Compress-Archive -Force -Path ./* -DestinationPath "${build_output_dir}/${python_zip_file}"
  popd
}
