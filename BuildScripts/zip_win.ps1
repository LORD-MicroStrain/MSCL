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

# Find the version and branch from Git
pushd "${project_dir}"
$mscl_git_branch = (git rev-parse --abbrev-ref HEAD)

# Just get the release version on master
if ((${mscl_git_branch} -eq "masterTest"))
{
    $mscl_git_version = (git describe --tags --abbrev=0)
}
# Get the tag and commit hash for all other branches
else
{
    $mscl_git_version = (git describe --tag)
}
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

    echo "Copying contents to temporary directory for cross-platform compatibility"
    $cross_platform_temp_dir = New-TemporaryFile

    Copy-Item -Path $package_output_dir -Destination $cross_platform_temp_dir -Recurse -Force -Container | ForEach-Object
    {
        $cross_platform_output_dir = $_.FullName.Replace($cross_platform_temp_dir, '').Replace('\', '/')
        Rename-Item -Path $_.FullName -NewName $cross_platform_output_dir
    }

    $package_name_prefix = "MSCL"

    # Documentation and Examples are not Windows specific
    if (("${package_name}" -ne "Documentation") -and ("${package_name}" -ne "Examples"))
    {
        $package_name_prefix = "${package_name_prefix}_Windows_${arch}"
    }

    # Compress the files with the git version
    $full_package_name = "${build_output_dir}/${package_name_prefix}_${package_name}"
    $versioned_zip_file = "${full_package_name}_${mscl_git_version}.zip"
    echo "Compressing contents of ${cross_platform_output_dir} to ${versioned_zip_file}"
    Compress-Archive -Force -Path "${cross_platform_output_dir}/*" -DestinationPath "${versioned_zip_file}"
}

# Make the build output directories
echo "Creating a Windows archive directory at ${build_output_dir}"
New-Item -Path "${build_output_dir}" -ItemType Directory -Force

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

# Only compress the Documentation and Examples for x64
if (("${arch}" -eq "x64"))
{
    # Zip up the documentation
    $documentation_output_dir = "${output_dir}/Documentation"
    Compress-Files -package_name "Documentation" -package_output_dir "${documentation_output_dir}"

    # Zip up the examples
    $examples_output_dir = "${output_dir}/Examples"
    Compress-Files -package_name "Examples" -package_output_dir "${examples_output_dir}"
}

# Zip up the python versions
$python_output_dir = "${output_dir}/Python"

# Test to make sure Python libraries were built
if ((-Not (Test-Path -Path "${python_output_dir}")) -or (Get-ChildItem -Path "$python_output_dir" -Recurse -File).Count -eq 0)
{
    echo "Python packages were not built"
    exit 1
}

$python_directories = Get-ChildItem -Path "${python_output_dir}" -Directory

foreach ($directory in $python_directories)
{
    if ((Get-ChildItem -Path "$(${directory}.FullName)" -Recurse -File).Count -eq 0)
    {
        echo "Python Error: No binaries built in ${directory}"
        continue
    }

    $python_version = ${directory}.Name
    $python_version_output_dir = ${directory}.FullName
    Compress-Files -package_name "Python${python_version}" -package_output_dir "${python_version_output_dir}"
}
