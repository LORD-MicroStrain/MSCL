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
  def packageLabel   = 'Packaging'
  def cPackConfig    = 'CPackConfig.cmake'
  def buildType1      = env.BUILD_TYPES.split(';')[0].trim()
  def buildType2      = env.BUILD_TYPES.split(';')[1].trim()
  def installProjects = "CPACK_INSTALL_CMAKE_PROJECTS=\"${buildType1};MSCL;ALL;/;${buildType2};MSCL;ALL;/\""

  // Install both release and debug on single config generators
  if (config.isLinux) {
    sh(label: packageLabel, script: """
      cpack \
        --config "${buildType1}/${cPackConfig}" \
        -D "${installProjects}"
    """)
  }
  else {
    powershell(label: packageLabel, script: """
      cpack `
        --config "${cPackConfig}" `
        -C "${env.BUILD_TYPES}"
    """)
  }
}

// Build each target depending on the configuration
def buildTargets(Map config) {
  def buildType        = config.buildType
  def isLinux          = config.isLinux
  def releaseBuildType = 'Release'

  // Always build the Cpp and test targets
  def targets = ['MSCL-Cpp', 'MSCL-Tests']

  if (config.libraryType == 'static') {
    if (buildType == releaseBuildType) {
      targets.addAll(['MSCL-Python2', 'MSCL-Python3'])
    }

    if (isLinux) {
      if (buildType == releaseBuildType) {
        targets.addAll(['MSCL-Examples'])
      }
    }
    else {
      targets.addAll(['MSCL-CSharp'])

      if (buildType == releaseBuildType) {
        targets.addAll(['MSCL-Docs'])
      }
    }
  }

  targets.each { target ->
    def buildLabel = "Build ${target} (${buildType})"
    if (isLinux) {
      sh(label: buildLabel, script: """
        cmake \
          --build ./${buildType} \
          --parallel \$(nproc) \
          --target ${target}
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
  def libraryType    = config.libraryType // static or shared
  def buildType      = config.buildType   // Debug or Release
  def isStatic       = libraryType == 'static'
  def buildAllPython = env.BRANCH_NAME && env.BRANCH_NAME == 'master'
  def isWindows      = config.isWindows
  def isLinux        = config.isLinux

  def args = []

  // Architecture flag (Windows only)
  if (env.BUILD_ARCH) {
    args.add("-A ${env.BUILD_ARCH}")
  }
  // Build type for single-config generators (Linux/Make)
  else {
    args.add("-D CMAKE_BUILD_TYPE:STRING=${buildType}")
  }

  // Determine boolean values for each component based on platform and build type
  def buildCSharp   = isStatic && isWindows ? 'ON' : 'OFF'
  def buildDocs     = isStatic && isWindows ? 'ON' : 'OFF'
  def buildExamples = isStatic && isLinux   ? 'ON' : 'OFF'
  def buildPython2  = isStatic              ? 'ON' : 'OFF'
  def buildPython3  = isStatic              ? 'ON' : 'OFF'
  def buildTests    = isStatic              ? 'ON' : 'OFF'
  def buildShared   = !isStatic             ? 'ON' : 'OFF'

  // Add all of the configuration options
  args.addAll([
    "-D BUILD_SHARED_LIBS:BOOL=${buildShared}",
    '-D MSCL_BUILD_PACKAGE:BOOL=ON',
    "-D MSCL_BUILD_CSHARP:BOOL=${buildCSharp}",
    "-D MSCL_BUILD_DOCUMENTATION:BOOL=${buildDocs}",
    "-D MSCL_BUILD_EXAMPLES:BOOL=${buildExamples}",
    "-D MSCL_BUILD_PYTHON2:BOOL=${buildPython2}",
    "-D MSCL_BUILD_PYTHON3:BOOL=${buildPython3}",
    "-D MSCL_BUILD_TESTS:BOOL=${buildTests}",
    '-D MSCL_WITH_SSL:BOOL=ON',
    '-D MSCL_WITH_WEBSOCKETS:BOOL=ON'
  ])

  // Build all supported versions of Python2
  // The project already defaults to the latest supported version
  if (buildPython2 && buildAllPython) {
    args.add('-D MSCL_PYTHON2_REQUESTED_VERSION:STRING=""')
  }

  // Build all supported versions of Python3
  // The project already defaults to the latest supported version
  if (buildPython3 && buildAllPython) {
    args.add('-D MSCL_PYTHON3_REQUESTED_VERSION:STRING=""')
  }

  // Configure the project
  def configLabel = "Configuring ${libraryType.capitalize()} library project"
  if (isLinux) {
    configLabel += " (${buildType})"
  }
  def cmakeArgs = args.join(' ')
  if (isLinux) {
    sh(label: configLabel, script: """
      mkdir ${buildType}
      cmake .. -B ${buildType} ${cmakeArgs}
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
    LIBRARY_TYPES = 'static,shared'
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
            BUILD_DIR  = "build_linux_arm32"
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
