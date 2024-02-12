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
  stages {
    stage('Build') {
      // Run the windows and linux builds in parallel
      parallel {
        stage('Windows') {
          agent { label 'windows10' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            powershell '.devcontainer/docker_build_win.ps1 -python3_versions "' + python3Versions() + '"'
            archiveArtifacts artifacts: 'Output/*.zip'
          }
        }
//         stage('DEB AMD64') {
//           agent { label 'aws-amd64' }
//           options { skipDefaultCheckout() }
//           steps {
//             cleanWs()
//             checkout scm
//             sh '.devcontainer/docker_build_debs.sh --arch amd64 --python3Versions "' + python3Versions() + '"'
//             archiveArtifacts artifacts: 'build_ubuntu_amd64/*.deb'
//           }
//         }
//         stage('RPM AMD64') {
//           agent { label 'aws-amd64' }
//           options { skipDefaultCheckout() }
//           steps {
//             cleanWs()
//             checkout scm
//             sh '.devcontainer/docker_build_rpms.sh --arch amd64 --python3Versions "' + python3Versions() + '"'
//             archiveArtifacts artifacts: 'build_centos_amd64/*.rpm'
//           }
//         }
//         stage('DEB ARM64') {
//           agent { label 'aws-arm64' }
//           options { skipDefaultCheckout() }
//           steps {
//             cleanWs()
//             checkout scm
//             sh '.devcontainer/docker_build_debs.sh --arch arm64v8 --python3Versions "' + python3Versions() + '"'
//             archiveArtifacts artifacts: 'build_ubuntu_arm64v8/*.deb'
//           }
//         }
//         stage('DEB ARM32') {
//           agent { label 'aws-arm64' }
//           options { skipDefaultCheckout() }
//           steps {
//             cleanWs()
//             checkout scm
//             sh '.devcontainer/docker_build_debs.sh --arch arm32v7 --python3Versions "' + python3Versions() + '"'
//             archiveArtifacts artifacts: 'build_ubuntu_arm32v7/*.deb'
//           }
//         }
//         stage('RPM ARM64') {
//           agent { label 'aws-arm64' }
//           options { skipDefaultCheckout() }
//           steps {
//             cleanWs()
//             checkout scm
//             sh '.devcontainer/docker_build_rpms.sh --arch arm64v8 --python3Versions "' + python3Versions() + '"'
//             archiveArtifacts artifacts: 'build_centos_arm64v8/*.rpm'
//           }
//         }
      }
    }
  }
  post {
    failure {
      script {
//         if (BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master')) {
          withCredentials([string(credentialsId: 'MSCL_Notification_Emails', variable: 'NOTIFICATION_EMAILS')]) {
            echo "Emails: '${NOTIFICATION_EMAILS}'"
            mail to: "'${NOTIFICATION_EMAILS}'",
              subject: "Build Failed in Jenkins: ${env.JOB_NAME}",
              body: "See: ${env.BUILD_URL}",
              charset: 'UTF-8',
              mimeType: 'text/html';
          }
//         }
      }
    }
    changed {
      script {
        if (/*BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master') && */currentBuild.currentResult == 'SUCCESS') { // Other values: FAILURE, UNSTABLE
          withCredentials([string(credentialsId: 'MSCL_Notification_Emails', variable: 'NOTIFICATION_EMAILS')]) {
            echo "Emails: '${NOTIFICATION_EMAILS}'"
            mail to: "'${NOTIFICATION_EMAILS}'",
            subject: "Jenkins build is back to normal: ${env.JOB_NAME}",
            body: "See: ${env.BUILD_URL}",
            charset: 'UTF-8',
            mimeType: 'text/html';
          }
        }
      }
    }
  }
}
