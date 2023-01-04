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
            powershell ".devcontainer/docker_build_win.ps1 -windows_version 1809"
            archiveArtifacts artifacts: 'Output/*.zip'
          }
        }
        stage('DEB AMD64') {
          agent { label 'aws-amd64' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            sh ".devcontainer/docker_build_debs.sh --arch amd64"
            archiveArtifacts artifacts: 'build_ubuntu_amd64/*.deb'
          }
        }
        stage('RPM AMD64') {
          agent { label 'aws-amd64' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            sh ".devcontainer/docker_build_rpms.sh --arch amd64"
            archiveArtifacts artifacts: 'build_centos_amd64/*.rpm'
          }
        }
        stage('DEB ARM64') {
          agent { label 'aws-arm64' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            sh ".devcontainer/docker_build_debs.sh --arch arm64v8"
            archiveArtifacts artifacts: 'build_ubuntu_arm64v8/*.deb'
          }
        }
        stage('DEB ARM32') {
          agent { label 'aws-arm64' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            sh "docker run --rm --privileged multiarch/qemu-user-static --reset -p yes"
            sh ".devcontainer/docker_build_debs.sh --arch arm32v7"
            archiveArtifacts artifacts: 'build_ubuntu_arm32v7/*.deb'
          }
        }
        stage('RPM ARM64') {
          agent { label 'aws-arm64' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            sh ".devcontainer/docker_build_rpms.sh --arch arm64v8"
            archiveArtifacts artifacts: 'build_centos_arm64v8/*.rpm'
          }
        }
      }
    }
  }
  post {
    failure {
      script {
        if (BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master')) {
          mail to: "melissa.gill@parker.com,rob.fisher@parker.com",
            subject: "Build Failed in Jenkins: ${env.JOB_NAME}",
            body: "See: ${env.BUILD_URL}",
            charset: 'UTF-8',
            mimeType: 'text/html';
        }
      }
    }
    changed {
      script {
        if (BRANCH_NAME && (BRANCH_NAME == 'main' || BRANCH_NAME == 'master') && currentBuild.currentResult == 'SUCCESS') { // Other values: FAILURE, UNSTABLE
          mail to: "melissa.gill@parker.com,rob.fisher@parker.com",
            subject: "Jenkins build is back to normal: ${env.JOB_NAME}",
            body: "See: ${env.BUILD_URL}",
            charset: 'UTF-8',
            mimeType: 'text/html';
        }
      }
    }
  }
}