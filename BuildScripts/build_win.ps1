# Get arguments from the user
param (
    [Parameter(Mandatory = $true, HelpMessage = 'The Directory to build MSCL in. Should be different than the MSCL source directory')]
    [String]$buildDir,
    [String]$arch = "x64",
    [String]$generator = "Visual Studio 15 2017",
    [String]$toolset = "v140",
    [String]$branch = "unknown",
    [String[]]$python3Dirs,
    [String[]]$python2Dirs
)

# Use 2>&1 at the end of a command to forward errors to the standard output and be able to catch them
# I.E.
#
# cmd -option 2>&1
#
# OR (to use it on a new line)
#
# cmd -option `
# 2>&1

# Cache the error action to reset it later
$CacheErrorActionPreference = ${ErrorActionPreference}

# Stop executing when cmdlets fail (does not stop functions from stopping execution)
$ErrorActionPreference = 'Stop'

try
{
    # Get some directory information
    $script_dir = "${PSScriptRoot}"
    $project_dir = "${script_dir}/.."

    # Windows has multiple build configurations, so build for each of those
    $configs = "Debug", "Release"

    # Make sure the build directory exists
    New-Item "${buildDir}" -ItemType Directory -Force `
    2>&1

    # Configure MSCL to build the documentation and zip examples only on x64 release
    if ("$arch" -eq "x64")
    {
        cmake -S "${project_dir}" -B "${buildDir}" -G "${generator}" -A "${arch}" -T "${toolset}" `
        -DCMAKE_VERBOSE_MAKEFILE="ON" `
        -DBUILD_SHARED_LIBS="OFF" `
        -DMSCL_BUILD_PYTHON2="OFF" `
        -DMSCL_BUILD_PYTHON3="OFF" `
        -DMSCL_BUILD_CSHARP="OFF" `
        -DMSCL_BUILD_TESTS="OFF" `
        -DMSCL_BUILD_EXAMPLES="OFF" `
        -DMSCL_ZIP_EXAMPLES="ON" `
        -DMSCL_BUILD_DOCUMENTATION="ON" `
        -DMSCL_BUILD_PACKAGE="ON" `
        -DMSCL_BRANCH="${branch}" `
        2>&1

        cmake --build "${buildDir}" --config "Release" --target package `
        2>&1
    }

    # Configure MSCL to build with everything except csharp, python2, and python3
    cmake -S "${project_dir}" -B "${buildDir}" -G "${generator}" -A "${arch}" -T "${toolset}" `
        -DCMAKE_VERBOSE_MAKEFILE="ON" `
        -DBUILD_SHARED_LIBS="ON" `
        -DMSCL_BUILD_PYTHON2="OFF" `
        -DMSCL_BUILD_PYTHON3="OFF" `
        -DMSCL_BUILD_CSHARP="OFF" `
        -DMSCL_BUILD_TESTS="ON" `
        -DMSCL_BUILD_EXAMPLES="ON" `
        -DMSCL_ZIP_EXAMPLES="OFF" `
        -DMSCL_BUILD_DOCUMENTATION="OFF" `
        -DMSCL_BUILD_PACKAGE="ON" `
        -DMSCL_BRANCH="${branch}" `
        2>&1

    # Build multiple configurations
    foreach ($config in ${configs})
    {
        cmake --build "${buildDir}" --config "${config}" --target package `
        2>&1

        cmake --build "${buildDir}" --config "${config}" --target "RUN_TESTS" `
        2>&1
    }

    # Build CSharp
    cmake -S "${project_dir}" -B "${buildDir}" -G "${generator}" -A "${arch}" -T "${toolset}" `
        -DCMAKE_VERBOSE_MAKEFILE="ON" `
        -DBUILD_SHARED_LIBS="ON" `
        -DMSCL_BUILD_PYTHON2="OFF" `
        -DMSCL_BUILD_PYTHON3="OFF" `
        -DMSCL_BUILD_CSHARP="ON" `
        -DMSCL_BUILD_TESTS="OFF" `
        -DMSCL_BUILD_EXAMPLES="ON" `
        -DMSCL_ZIP_EXAMPLES="OFF" `
        -DMSCL_BUILD_DOCUMENTATION="OFF" `
        -DMSCL_BUILD_PACKAGE="ON" `
        -DMSCL_BRANCH="${branch}" `
        2>&1

    # Build multiple configurations for CSharp
    foreach ($config in ${configs})
    {
        cmake --build "${buildDir}" --config "${config}" --target package `
        2>&1
    }

    # Build python3
    if ($python3Dirs.Count)
    {
        foreach ($python3Dir in ${python3Dirs}.split(","))
        {
            cmake -S "${project_dir}" -B "${buildDir}" -G "${generator}" -A "${arch}" -T "${toolset}" `
                -DCMAKE_VERBOSE_MAKEFILE="ON" `
                -DBUILD_SHARED_LIBS="OFF" `
                -DMSCL_BUILD_PYTHON2="OFF" `
                -DMSCL_BUILD_PYTHON3="ON" `
                -DMSCL_BUILD_CSHARP="OFF" `
                -DMSCL_BUILD_TESTS="OFF" `
                -DMSCL_BUILD_EXAMPLES="OFF" `
                -DMSCL_ZIP_EXAMPLES="OFF" `
                -DMSCL_BUILD_DOCUMENTATION="OFF" `
                -DMSCL_BUILD_PACKAGE="ON" `
                -DMSCL_BRANCH="${branch}" `
                `
                -UPython3_ROOT -DPython3_ROOT="${python3Dir}" `
                -UPython3_ROOT_DIR -DPython3_ROOT_DIR="${python3Dir}" `
                -UPython3_INCLUDE_DIR `
                -UPython3_EXECUTABLE -DPython3_EXECUTABLE="${python3Dir}/python.exe" `
                2>&1

            # Build multiple configurations
            foreach ($config in ${configs})
            {
                cmake --build "${buildDir}" --config "${config}" --target package `
                2>&1
            }
        }
    }

    # Build python2 for each arch
    if ($python2Dirs.Count)
    {
        foreach ($python2Dir in ${python2Dirs}.split(","))
        {
            cmake -S "${project_dir}" -B "${buildDir}" -G "${generator}" -A "${arch}" -T "${toolset}" `
                -DCMAKE_VERBOSE_MAKEFILE="ON" `
                -DBUILD_SHARED_LIBS="OFF" `
                -DMSCL_BUILD_PYTHON2="ON" `
                -DMSCL_BUILD_PYTHON3="OFF" `
                -DMSCL_BUILD_CSHARP="OFF" `
                -DMSCL_BUILD_TESTS="OFF" `
                -DMSCL_BUILD_EXAMPLES="OFF" `
                -DMSCL_ZIP_EXAMPLES="OFF" `
                -DMSCL_BUILD_DOCUMENTATION="OFF" `
                -DMSCL_BUILD_PACKAGE="ON" `
                -DMSCL_BRANCH="${branch}" `
                `
                -UPython2_ROOT -DPython2_ROOT="${python2Dir}" `
                -UPython2_ROOT_DIR -DPython2_ROOT_DIR="${python2Dir}" `
                -UPython2_INCLUDE_DIR `
                -UPython2_EXECUTABLE -DPython2_EXECUTABLE="${python2Dir}/python.exe" `
                2>&1

            # Build multiple configurations
            foreach ($config in ${configs})
            {
                cmake --build "${buildDir}" --config "${config}" --target package `
                2>&1
            }
        }
    }
}
catch
{
    # Print the error to the console
    $errorMessage = $_ | Out-String
    Write-Host -ForegroundColor Red $errorMessage
}
finally
{
    # Reset the ErrorActionPreference
    $ErrorActionPreference = ${CacheErrorActionPreference}
}
