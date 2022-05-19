# Get arguments from the user
param (
  [Parameter(Mandatory=$true,HelpMessage='The Directory to build MSCL in. Should be different than the MSCL source directory')][string]$buildDir,
  [String]$generator = "Visual Studio 15 2017",
  [String[]]$python3Dirs_x86,
  [String[]]$python3Dirs_x64,
  [String[]]$python2Dirs_x86,
  [String[]]$python2Dirs_x64
)

# Get some directory information
$script_dir = "${PSScriptRoot}"
$project_dir = "${script_dir}/.."

# Windows has multiple build configurations, so build for each of those
$x86_cmake_arch = "Win32"
$x64_cmake_arch = "x64"
$arches = "${x86_cmake_arch}", "${x64_cmake_arch}"
$configs = "Debug", "Release"

# Build for each arch
foreach ($arch in ${arches}) {
  # Make sure the build directory exists
  $arch_build_dir = "${buildDir}/${arch}"
  New-Item "${arch_build_dir}" -ItemType Directory -Force

  # Configure MSCL to build with everything except python2 and python3
  cmake -S "${project_dir}" -B "${arch_build_dir}" -G "${generator}" -A "${arch}" `
    -DBUILD_SHARED_LIBS="ON" `
    -DBUILD_PYTHON2="OFF" `
    -DBUILD_PYTHON3="OFF" `
    -DBUILD_CSHARP="ON" `
    -DBUILD_TESTS="ON" `
    -DBUILD_EXAMPLES="ON" `
    -DBUILD_DOCUMENTATION="ON"
  if (-not $?) {
    exit $?
  }

  # Build multiple configurations
  foreach ($config in ${configs}) {
    cmake --build "${arch_build_dir}" --config "${config}"
    if (-not $?) {
      exit $?
    }
    cmake --build "${arch_build_dir}" --config "${config}" --target "RUN_TESTS"
    if (-not $?) {
      exit $?
    }
  }
}

# Build python3 for each arch
if(${python3Dirs_x86}) {
  foreach ($python3Dir_x86 in ${python3Dirs_x86}.split(",")) {
    $python3_build_dir = "${buildDir}/${x86_cmake_arch}"
    cmake -S "${project_dir}" -B "${python3_build_dir}" -G "${generator}" -A "${x86_cmake_arch}"`
      -DBUILD_SHARED_LIBS="OFF" `
      -DBUILD_PYTHON2="OFF" `
      -DBUILD_PYTHON3="ON" `
      -DBUILD_CSHARP="OFF" `
      -DBUILD_TESTS="OFF" `
      -DBUILD_EXAMPLES="OFF" `
      -DBUILD_DOCUMENTATION="OFF" `
      `
      -UPython3_ROOT -DPython3_ROOT="${python3Dir_x86}" `
      -UPython3_ROOT_DIR -DPython3_ROOT_DIR="${python3Dir_x86}" `
      -UPython3_INCLUDE_DIR `
      -UPython3_EXECUTABLE -DPython3_EXECUTABLE="${python3Dir_x86}\python.exe"

    # Build multiple configurations
    foreach ($config in ${configs}) {
      cmake --build "${python3_build_dir}" --config "${config}"
      if (-not $?) {
        exit $?
      }
    }
  }
}
if(${python3Dirs_x64}) {
  foreach ($python3Dir_x64 in ${python3Dirs_x64}.split(",")) {
    $python3_build_dir = "${buildDir}/${x64_cmake_arch}"
    cmake -S "${project_dir}" -B "${python3_build_dir}" -G "${generator}" -A "${x64_cmake_arch}"`
      -DBUILD_SHARED_LIBS="OFF" `
      -DBUILD_PYTHON2="OFF" `
      -DBUILD_PYTHON3="ON" `
      -DBUILD_CSHARP="OFF" `
      -DBUILD_TESTS="OFF" `
      -DBUILD_EXAMPLES="OFF" `
      -DBUILD_DOCUMENTATION="OFF" `
      `
      -UPython3_ROOT -DPython3_ROOT="${python3Dir_x64}" `
      -UPython3_ROOT_DIR -DPython3_ROOT_DIR="${python3Dir_x64}" `
      -UPython3_INCLUDE_DIR `
      -UPython3_EXECUTABLE -DPython3_EXECUTABLE="${python3Dir_x64}\python.exe"

    # Build multiple configurations
    foreach ($config in ${configs}) {
      cmake --build "${python3_build_dir}" --config "${config}"
      if (-not $?) {
        exit $?
      }
    }
  }
}

# Build python2 for each arch
if(${python2Dirs_x86}) {
  foreach ($python2Dir_x86 in ${python2Dirs_x86}.split(",")) {
    $python2_build_dir = "${buildDir}/${x86_cmake_arch}"
    cmake -S "${project_dir}" -B "${python2_build_dir}" -G "${generator}" -A "${x86_cmake_arch}"`
      -DBUILD_SHARED_LIBS="OFF" `
      -DBUILD_PYTHON2="ON" `
      -DBUILD_PYTHON3="OFf" `
      -DBUILD_CSHARP="OFF" `
      -DBUILD_TESTS="OFF" `
      -DBUILD_EXAMPLES="OFF" `
      -DBUILD_DOCUMENTATION="OFF" `
      `
      -UPython2_ROOT -DPython2_ROOT="${python2Dir_x86}" `
      -UPython2_ROOT_DIR -DPython2_ROOT_DIR="${python2Dir_x86}" `
      -UPython2_INCLUDE_DIR `
      -UPython2_EXECUTABLE -DPython2_EXECUTABLE="${python2Dir_x86}\python.exe"

    # Build multiple configurations
    foreach ($config in ${configs}) {
      cmake --build "${python2_build_dir}" --config "${config}"
      if (-not $?) {
        exit $?
      }
    }
  }
}
if(${python2Dirs_x64}) {
  foreach ($python2Dir_x64 in ${python2Dirs_x64}.split(",")) {
    $python2_build_dir = "${buildDir}/${x64_cmake_arch}"
    cmake -S "${project_dir}" -B "${python2_build_dir}" -G "${generator}" -A "${x64_cmake_arch}"`
      -DBUILD_SHARED_LIBS="OFF" `
      -DBUILD_PYTHON2="ON" `
      -DBUILD_PYTHON3="OFF" `
      -DBUILD_CSHARP="OFF" `
      -DBUILD_TESTS="OFF" `
      -DBUILD_EXAMPLES="OFF" `
      -DBUILD_DOCUMENTATION="OFF" `
      `
      -UPython2_ROOT -DPython2_ROOT="${python2Dir_x64}" `
      -UPython2_ROOT_DIR -DPython2_ROOT_DIR="${python2Dir_x64}" `
      -UPython2_INCLUDE_DIR `
      -UPython2_EXECUTABLE -DPython2_EXECUTABLE="${python2Dir_x64}\python.exe"

    # Build multiple configurations
    foreach ($config in ${configs}) {
      cmake --build "${python2_build_dir}" --config "${config}"
      if (-not $?) {
        exit $?
      }
    }
  }
}