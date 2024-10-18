########################################################################################################################################################
# This script is responsible for zipping up the binaries produced by the build on windows. If running manually, this should be run after "build_win.ps1"
########################################################################################################################################################

# Get arguments from the user
param (
    [String]$arch = "x64"
)

# Find the script directory and set some constants
$script_dir = $PSScriptRoot
$project_dir = "${script_dir}/.."
$build_output_dir = "${project_dir}/build_windows_${arch}"
$release_build_output_dir = "${build_output_dir}_for_release"

# Find the version from Git
pushd "${project_dir}"
$mscl_git_version = (git describe --tag)                    # Tag and commit hash
$mscl_git_release_version = (git describe --tag --abbrev=0) # Just the tag
popd

# Function to handle compressing each package
function Compress-Files
{
    param (
        [String]$package_name = "",
        [String]$package_output_dir = ""
    )

    if (-Not (Test-Path -Path "${package_output_dir}"))
    {
        echo "Cannot compress package. Directory does not exist: ${package_output_dir}"
        return
    }

    # Copy the files to a temp dir to zip for release
    $full_release_package_name = "${release_build_output_dir}/MSCL_Windows_${arch}_${package_name}"
    $temp_zip_dir = "${full_release_package_name}_${mscl_git_release_version}"
    $zip_file = "${full_release_package_name}.zip"
    Copy-Item -Path "${package_output_dir}" -Destination "${temp_zip_dir}" -Recurse

    # Compress the temp directory and then remove it
    echo "Compressing ${temp_zip_dir} to ${zip_file} for release"
    Compress-Archive -Force -Path "${temp_zip_dir}" -DestinationPath "${zip_file}"
    Remove-Item "${temp_zip_dir}" -Recurse -Force

    # Compress the files with the git version
    $full_package_name = "${build_output_dir}/MSCL_Windows_${arch}_${package_name}"
    $versioned_zip_file = "${full_package_name}_${mscl_git_version}.zip"
    echo "Compressing contents of ${package_output_dir} to ${versioned_zip_file}"
    Compress-Archive -Force -Path "${package_output_dir}/*" -DestinationPath "${versioned_zip_file}"
}

# Make the build output directories
echo "Creating a Windows archive directory at ${build_output_dir}"
New-Item -Path "${build_output_dir}" -ItemType Directory -Force

echo "Creating a Windows archive directory for release at ${release_build_output_dir}"
New-Item -Path "${release_build_output_dir}" -ItemType Directory -Force

# MSCL build output directory
$output_dir = "${project_dir}/Output"

# Common C++ directory
$cpp_output_dir = "${output_dir}/C++"

# Zip up the Static library
$static_output_dir = "${cpp_output_dir}/Static"
Compress-Files -package_name "Static_C++" -package_output_dir "${static_output_dir}"

# Zip up the Shared library
$shared_output_dir = "${cpp_output_dir}/Shared"
Compress-Files -package_name "Shared_C++" -package_output_dir "${shared_output_dir}"

# Zip up the C# library
$dotnet_output_dir = "${output_dir}/DotNet"
Compress-Files -package_name "DotNet" -package_output_dir "${dotnet_output_dir}"

# Zip up the documentation
$documentation_output_dir = "${output_dir}/Documentation"
Compress-Files -package_name "Documentation" -package_output_dir "${documentation_output_dir}"

# Zip up the examples
$examples_output_dir = "${output_dir}/Examples"
Compress-Files -package_name "Examples" -package_output_dir "${examples_output_dir}"

# Zip up the python versions
$python_output_dir = "${output_dir}/Python"

# Test to make sure Python libraries were built
if (-Not (Test-Path -Path "${python_output_dir}"))
{
    echo "Python packages were not built. Cannot find directory: ${python_output_dir}"
    exit 1
}

Get-ChildItem "${python_output_dir}" -Directory | ForEach-Object
{
    $python_version = ${_}.Name
    $python_version_output_dir = ${_}.FullName
    Compress-Files -package_name "Python${python_version}" -package_output_dir "${python_version_output_dir}"
}
