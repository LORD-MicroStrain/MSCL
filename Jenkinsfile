// Utility function to determine what python versions to build
def python3Versions() {
  // Different version depending on the OS
  String[] versions;
  if (isUnix()) {
    versions = ["3.7.16", "3.8.16", "3.9.16", "3.10.9", "3.11.1"];
  } else {
    versions = ["3.7.0", "3.8.0", "3.9.0", "3.10.0", "3.11.0"];
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
  }
  stages {
    stage('Build') {
      // Run the windows and linux builds in parallel
      parallel {
        stage('Windows x64') {
          agent { label 'windows10' }
          options {
            skipDefaultCheckout()
            timeout(time: 20, activity: true, unit: 'MINUTES')
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
            timeout(time: 20, activity: true, unit: 'MINUTES')
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
            timeout(time: 20, activity: true, unit: 'MINUTES')
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
            timeout(time: 20, activity: true, unit: 'MINUTES')
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
            timeout(time: 20, activity: true, unit: 'MINUTES')
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
        agent { label 'windows10' }
        timeout(time: 20, activity: true, unit: 'MINUTES')
        powershell 'BuildScripts/zip_win.ps1'
        archiveArtifacts artifacts: 'build_windows/*.zip'        
      }
    }
//     failure {
//       script {
//         if (BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master')) {
//           mail to: "${env.Notification_Emails_MSCL}",
//             subject: "Build Failed in Jenkins: ${env.JOB_NAME}",
//             body: "See: ${env.BUILD_URL}",
//             charset: 'UTF-8',
//             mimeType: 'text/html';
//         }
//       }
//     }
//     changed {
//       script {
//         if (BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master') && currentBuild.currentResult == 'SUCCESS') { // Other values: FAILURE, UNSTABLE
//           mail to: "${env.Notification_Emails_MSCL}",
//           subject: "Jenkins build is back to normal: ${env.JOB_NAME}",
//           body: "See: ${env.BUILD_URL}",
//           charset: 'UTF-8',
//           mimeType: 'text/html';
//         }
//       }
//     }
  }
}
