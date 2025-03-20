// Utility function to determine what python versions to build
def python3Versions() {
  // Different version depending on the OS
  String[] versions;
  if (isUnix()) {
    versions = ["3.9.21", "3.10.16", "3.11.11", "3.12.8", "3.13.1"];
  } else {
    versions = ["3.9.0", "3.10.0", "3.11.0", "3.12.0", "3.13.0"];
  }

  // If a PR build, just build the most recent, otherwise build all versions
  if (BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master')) {
    return versions.join(" ");
  } else {
    return versions.last();
  }
}

pipeline {
  agent none
  options {
    // Set a timeout for the whole pipeline. The timer starts when the project is queued
    timeout(time: 3, unit: 'HOURS')
    // Only keep this number of builds for the job
    buildDiscarder(logRotator(numToKeepStr: "10"))
  }
  stages {
    stage('Pre-Release') {
      agent { label 'linux-amd64' }
      options {
        skipDefaultCheckout()
        // TODO: Fix timeout issues on Jenkins for console activity
//         timeout(time: 10, activity: true, unit: 'MINUTES')
      }
      steps {
        checkout scm
        withCredentials([string(credentialsId: 'Github_Token', variable: 'GH_TOKEN')]) {
          sh '''
            # Pre-release check/update before building on develop
            "${WORKSPACE}/BuildScripts/prerelease.sh" --target "${BRANCH_NAME}"
          '''
        }
      }
    }
    stage('Build') {
      // Run the windows and linux builds in parallel
      parallel {
        stage('Windows x64') {
          agent { label 'windows10' }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            cleanWs()
            checkout scm
            powershell '.devcontainer/docker_build_win.ps1 -arch x64 -python3_versions "' + python3Versions() + '"'
            archiveArtifacts artifacts: 'build_windows_x64/*.zip'
          }
        }
        stage('Windows x86') {
          agent { label 'windows10' }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            cleanWs()
            checkout scm
            powershell '.devcontainer/docker_build_win.ps1 -arch x86 -python3_versions "' + python3Versions() + '"'
            archiveArtifacts artifacts: 'build_windows_x86/*.zip'
          }
        }
        stage('DEB AMD64') {
          agent { label 'linux-amd64' }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            cleanWs()
            checkout scm
            sh '.devcontainer/docker_build_debs.sh --arch amd64 --python3Versions "' + python3Versions() + '"'
            archiveArtifacts artifacts: 'build_ubuntu_amd64/*.deb'
          }
        }
        stage('DEB ARM64') {
          agent { label 'linux-arm64' }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            cleanWs()
            checkout scm
            sh '.devcontainer/docker_build_debs.sh --arch arm64v8 --python3Versions "' + python3Versions() + '"'
            archiveArtifacts artifacts: 'build_ubuntu_arm64v8/*.deb'
          }
        }
        stage('DEB ARM32') {
          agent { label 'linux-arm64' }
          options {
            skipDefaultCheckout()
            // TODO: Fix timeout issues on Jenkins for console activity
//             timeout(time: 20, activity: true, unit: 'MINUTES')
          }
          steps {
            cleanWs()
            checkout scm
            sh '.devcontainer/docker_build_debs.sh --arch arm32v7 --python3Versions "' + python3Versions() + '"'
            archiveArtifacts artifacts: 'build_ubuntu_arm32v7/*.deb'
          }
        }
      }
    }
  }
  post {
    success {
      script {
        if (BRANCH_NAME && BRANCH_NAME == 'develop') {
          node("linux-amd64") {
            dir("/tmp/mscl_${env.BRANCH_NAME}_${currentBuild.number}") {
              copyArtifacts(projectName: "${env.JOB_NAME}", selector: specific("${currentBuild.number}"));
              withCredentials([string(credentialsId: 'Github_Token', variable: 'GH_TOKEN')]) {
                sh '''
                  # Release to github
                  "${WORKSPACE}/BuildScripts/release.sh" \
                    --artifacts "$(find "$(pwd)" -type f)" \
                    --target "${BRANCH_NAME}" \
                    --release "latest" \
                    --docs-zip "$(find "$(pwd)" -type f -name "MSCL_Documentation_*.zip" | sort | uniq)" \
                    --generate-notes
                '''
              }
            }
          }
        } else if (BRANCH_NAME && BRANCH_NAME == 'master') {
          node("linux-amd64") {
            dir("/tmp/mscl_${env.BRANCH_NAME}_${currentBuild.number}") {
              copyArtifacts(projectName: "${env.JOB_NAME}", selector: specific("${currentBuild.number}"));
              withCredentials([string(credentialsId: 'Github_Token', variable: 'GH_TOKEN')]) {
                sh '''
                  # Release to github. The release script will determine if master needs to be published
                  "${WORKSPACE}/BuildScripts/release.sh" \
                    --artifacts "$(find "$(pwd)" -type f)" \
                    --target "${BRANCH_NAME}" \
                    --release "$(cd ${WORKSPACE} && git describe --match "v*" --abbrev=0 --tags HEAD)" \
                    --docs-zip "$(find "$(pwd)" -type f -name "MSCL_Documentation_*.zip" | sort | uniq)"
                '''
              }
            }
          }
        }
      }
    }
  }
}
