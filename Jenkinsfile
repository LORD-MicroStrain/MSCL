// Utility function for getting the real branch name even in a pull request
def branchName() {
  if (env.CHANGE_BRANCH) {
    return env.CHANGE_BRANCH
  }
  else {
    return env.BRANCH_NAME
  }
}

// Utility function for checking out the repo since we want all the branches and tags
def checkoutRepo() {
  // Clean the workspace
  cleanWs()

  // Handles both PRs and branches
  script {
    BRANCH_NAME_REAL = branchName();
  }

  // Checkout the code from github
  checkout([  $class: 'GitSCM',
    branches: [[
      name: 'refs/heads/' + BRANCH_NAME_REAL
    ]],
    userRemoteConfigs: [[
      credentialsId: 'Github_User_And_Token',
      url: 'https://github.com/LORD-MicroStrain/MSCL.git'
    ]],
    extensions: [[
      $class: 'SubmoduleOption',
      disableSubmodules: false,
      parentCredentials: true,
      recursiveSubmodules: true,
      reference: '',
      trackingSubmodules: false
    ]],
    submoduleCfg: []
  ])

  // Set the branch name
  env.BRANCH_NAME = branchName()
}

// Calling CPack manually allows for packaging both Debug and Release packages
def packageTargets(Map config) {
  def packageLabel = 'Packaging'

  // Install both release and debug on single config generators
  if (config.isLinux) {
    // The build directory order doesn't actually matter in this case
    // Debug can be Release and vise versa
    def debugBuildDir   = env.BUILD_TYPES.split(';')[0].trim()
    def releaseBuildDir = env.BUILD_TYPES.split(';')[1].trim()

    sh(label: packageLabel, script: """
      ../.devcontainer/docker-run-container.sh --os ${BUILD_OS} --arch ${BUILD_ARCH} ' \
        cd ${BUILD_DIR}; \
        MICROSTRAIN_BUILD_DIR_DEBUG="${debugBuildDir}" \
        MICROSTRAIN_BUILD_DIR_RELEASE="${releaseBuildDir}" \
        cpack \
          --config "${releaseBuildDir}/microstrain-package-all.cmake" \
          -C "${env.BUILD_TYPES}"
      '
    """)
  }
  else {
    powershell(label: packageLabel, script: """
      cpack `
        --config "CPackConfig.cmake" `
        -C "${env.BUILD_TYPES}"
    """)
  }
}

// Build each target depending on the configuration
def buildTargets(Map config) {
  def buildType        = config.buildType.capitalize()
  def isLinux          = config.isLinux
  def releaseBuildType = 'Release'

  // Always build the Cpp
  def targets = ['MSCL-Cpp']

  if (config.libraryType.capitalize() == 'Static') {
    // There is no difference in building tests between static and shared so only build it once
    targets.addAll(['MSCL-Tests'])

    if (buildType == releaseBuildType) {
      targets.addAll(['MSCL-Python3'])
    }

    if (!isLinux) {
      targets.addAll(['MSCL-CSharp'])

      // Only need to build docs on one architecture
      if (buildType == releaseBuildType && env.BUILD_ARCH && env.BUILD_ARCH == "x64") {
        targets.addAll(['MSCL-Docs'])
      }
    }

    // There is no difference in building examples between static and shared so only build it once
    // Make sure it is at the end of the list so that all libraries are built first
    targets.addAll(['MSCL-Examples'])
  }

  targets.each { target ->
    def buildLabel = "Build ${target} (${buildType})"
    if (isLinux) {
      def crosscompile32 = ""

      // Compile using 32-bit terminal operations
      if (env.LINUX_CROSSCOMPILE_32) {
        crosscompile32 = "linux32"
      }

      sh(label: buildLabel, script: """
        ../.devcontainer/docker-run-container.sh --os ${BUILD_OS} --arch ${BUILD_ARCH} ' \
          cd ${BUILD_DIR}; \
          ${crosscompile32} cmake \
            --build ./${buildType} \
            --parallel \$(nproc) \
            --target ${target};
        '
      """)
    }
    else {
      powershell(label: buildLabel, script: """
        cmake `
          --build . `
          --config ${buildType} `
          --parallel \$env:NUMBER_OF_PROCESSORS `
          --target ${target}
      """)
    }
  }
}

// Configure the project based on the configuration
def configureProject(Map config) {
  def libraryType    = config.libraryType.capitalize() // Static or Shared
  def buildType      = config.buildType.capitalize()   // Debug or Release
  def isStatic       = libraryType == 'Static'
  def buildAllPython = env.BRANCH_NAME && env.BRANCH_NAME == 'master' // Build all supported versions of Python
  def isWindows      = config.isWindows
  def isLinux        = config.isLinux
  def buildDocs      = isStatic && isWindows ? 'ON' : 'OFF'

  def args = [
    '-DMSCL_BUILD_PACKAGE:BOOL=ON',
    '-DMSCL_WITH_SSL:BOOL=ON',
    '-DMSCL_WITH_WEBSOCKETS:BOOL=ON',
    '-DVCPKG_OVERLAY_TRIPLETS:PATH=${WORKSPACE}/cmake/triplets'
  ]

  if (env.TOOLCHAIN_FILE) {
    args.add("-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE:STRING=${env.TOOLCHAIN_FILE}")
  }

  // Architecture flag (Windows only)
  if (isWindows && env.BUILD_ARCH) {
    args.add("-A ${env.BUILD_ARCH}")

    // Only need to build docs on one architecture
    if (buildDocs == 'ON') {
      buildDocs = env.BUILD_ARCH == "x64" ? 'ON' : 'OFF'
    }
  }
  // Build type for single-config generators (Linux/Make)
  else {
    args.add("-DCMAKE_BUILD_TYPE:STRING=${buildType}")
  }

  // Determine boolean values for each component based on platform and build type
  def buildCSharp   = isStatic && isWindows ? 'ON' : 'OFF'
  def buildExamples = isStatic              ? 'ON' : 'OFF'
  def buildPython3  = isStatic              ? 'ON' : 'OFF'
  def buildTests    = isStatic              ? 'ON' : 'OFF'
  def buildShared   = !isStatic             ? 'ON' : 'OFF'

  // Add all of the configuration options
  args.addAll([
    "-DBUILD_SHARED_LIBS:BOOL=${buildShared}",
    "-DMSCL_BUILD_CSHARP:BOOL=${buildCSharp}",
    "-DMSCL_BUILD_DOCUMENTATION:BOOL=${buildDocs}",
    "-DMSCL_BUILD_EXAMPLES:BOOL=${buildExamples}",
    "-DMSCL_BUILD_PYTHON3:BOOL=${buildPython3}",
    "-DMSCL_BUILD_TESTS:BOOL=${buildTests}"
  ])

  // Build all supported versions of Python3
  // The project already defaults to the latest supported version
  if (buildPython3 && buildAllPython) {
    args.add('-DMSCL_PYTHON3_REQUESTED_VERSION:STRING=""')
  }

  // Configure the project
  def configLabel = "Configuring ${libraryType} library project"
  if (isLinux) {
    configLabel += " (${buildType})"
  }
  def cmakeArgs = args.join(' ')
  if (isLinux) {
    def crosscompile32 = ""

    // Compile using 32-bit terminal operations
    if (env.LINUX_CROSSCOMPILE_32) {
      crosscompile32 = "linux32"
    }

    sh(label: configLabel, script: """
      ../.devcontainer/docker-run-container.sh --os ${BUILD_OS} --arch ${BUILD_ARCH} ' \
        cd ${BUILD_DIR}; \
        ${crosscompile32} cmake .. -B ${buildType} ${cmakeArgs}
      '
    """)
  }
  else {
    powershell(label: configLabel, script: """
      cmake .. ${cmakeArgs}
    """)
  }
}

// Build and package the project
def buildAndPackageProject() {
  // Checkout the project
  checkoutRepo()

  def isLinux   = isUnix()
  def isWindows = !isLinux

  if (isLinux) {
    sh(label: "Prepare Docker Image", script: """
      ./.devcontainer/docker-build-image.sh --os ${BUILD_OS} --arch ${BUILD_ARCH}
    """)
  }

  // Build and package the project in the build directory
  dir(env.BUILD_DIR) {
    // Build static and shared variants
    env.LIBRARY_TYPES.split(',').each { libraryType ->
      libraryType = libraryType.trim()

      def runConfiguration = true

      // Build Release and Debug variants
      env.BUILD_TYPES.split(';').each { buildType ->
        buildType = buildType.trim()

        if (runConfiguration) {
          // Configure the project
          configureProject(
            isLinux: isLinux,
            isWindows: isWindows,
            libraryType: libraryType,
            buildType: buildType
          )

          // Always run the configuration step on Linux
          // Windows only needs it to run once
          runConfiguration = isLinux
        }

        // Build the targets
        buildTargets(
          isLinux: isLinux,
          libraryType: libraryType,
          buildType: buildType
        )
      }

      // Package all the available artifacts for both build types (Debug/Release)
      packageTargets(
          isLinux: isLinux
      )
    }

    def fileExtension = isLinux ? 'deb' : 'zip'
    archiveArtifacts artifacts: "*.${fileExtension}"
  }
}

pipeline {
  agent none
  environment {
    BUILD_TYPES   = 'Debug;Release'
    LIBRARY_TYPES = 'Shared,Static'
  }
  options {
    // Set a timeout for the whole pipeline. The timer starts when the project is queued
    timeout(time: 3, unit: 'HOURS')
    // Only keep this number of builds for the job
    buildDiscarder(logRotator(numToKeepStr: "10"))
    copyArtifactPermission('*')
  }
  stages {
    stage('Pre-Release') {
      when {
        branch pattern: "(develop|master)", comparator: "REGEXP"
      }
      agent { label 'linux-amd64' }
      options {
        skipDefaultCheckout()
        // TODO: Fix timeout issues on Jenkins for console activity
//         timeout(time: 10, activity: true, unit: 'MINUTES')
      }
      steps {
        checkout scm
        withCredentials([string(credentialsId: 'Github_Token', variable: 'GH_TOKEN')]) {
          sh """
            # Pre-release check/update before building on develop
            "${WORKSPACE}/BuildScripts/prerelease.sh" --target "${env.BRANCH_NAME}"
          """
        }
      }
    }
    stage('Build') {
      // Run the windows and linux builds in parallel
      parallel {
        stage('Windows x64') {
          agent {
            label 'windows10'
          }
          environment {
            BUILD_ARCH = "x64"
            BUILD_DIR  = "build_windows_x64"
          }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            buildAndPackageProject()
          }
        }
        stage('Windows x86') {
          agent {
            label 'windows10'
          }
          environment {
            BUILD_ARCH = "Win32"
            BUILD_DIR  = "build_windows_x86"
          }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            buildAndPackageProject()
          }
        }
        stage('Linux AMD64') {
          agent {
            label 'linux-amd64'
          }
          environment {
            BUILD_OS   = "ubuntu"
            BUILD_ARCH = "amd64"
            BUILD_DIR  = "build_linux_amd64"
          }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            buildAndPackageProject()
          }
        }
        stage('Linux ARM64') {
          agent {
            label 'linux-arm64'
          }
          environment {
            BUILD_OS   = "ubuntu"
            BUILD_ARCH = "arm64v8"
            BUILD_DIR  = "build_linux_arm64"
          }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            buildAndPackageProject()
          }
        }
        stage('Linux ARM32') {
          agent {
            label 'linux-arm64'
          }
          environment {
            BUILD_OS              = "ubuntu"
            BUILD_ARCH            = "arm32v7"
            BUILD_DIR             = "build_linux_arm32"
            TOOLCHAIN_FILE        = "arm-linux-crosscompile-toolchain.cmake"
            LINUX_CROSSCOMPILE_32 = true
          }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            buildAndPackageProject()
          }
        }
      }
    }
  }
  post {
    success {
      script {
        if (env.BRANCH_NAME && env.BRANCH_NAME == 'develop') {
          node("linux-amd64") {
            dir("/tmp/mscl_${env.BRANCH_NAME}_${currentBuild.number}") {
              copyArtifacts(projectName: "${env.JOB_NAME}", selector: specific("${currentBuild.number}"));
              withCredentials([string(credentialsId: 'Github_Token', variable: 'GH_TOKEN')]) {
                sh """
                  # Release to github
                  "${WORKSPACE}/BuildScripts/release.sh" \
                    --artifacts "\$(find \$(pwd) -type f)" \
                    --target "${env.BRANCH_NAME}" \
                    --release "latest" \
                    --docs-zip "\$(find \$(pwd) -type f -name 'MSCL_Documentation_*.zip' | sort | uniq)" \
                    --generate-notes
                """
              }
            }
          }
        }
        else if (env.BRANCH_NAME && env.BRANCH_NAME == 'master') {
          node("linux-amd64") {
            dir("/tmp/mscl_${env.BRANCH_NAME}_${currentBuild.number}") {
              copyArtifacts(projectName: "${env.JOB_NAME}", selector: specific("${currentBuild.number}"));
              withCredentials([string(credentialsId: 'Github_Token', variable: 'GH_TOKEN')]) {
                sh """
                  # Release to github. The release script will determine if master needs to be published
                  "${WORKSPACE}/BuildScripts/release.sh" \
                    --artifacts "\$(find \$(pwd) -type f)" \
                    --target "${env.BRANCH_NAME}" \
                    --release "\$(cd ${WORKSPACE} && git describe --match 'v*' --abbrev=0 --tags HEAD)" \
                    --docs-zip "\$(find \$(pwd) -type f -name 'MSCL_Documentation_*.zip' | sort | uniq)"
                """
              }
            }
          }
        }
      }
    }
  }
}
