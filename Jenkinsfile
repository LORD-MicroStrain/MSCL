pipeline {
  agent none
  stages {
    stage('Build') {
      // Run the windows build
      parallel {
        stage('Windows') {
          agent { label 'windows10' }
          options { skipDefaultCheckout() }
          steps {
            cleanWs()
            checkout scm
            bat "BuildScripts/build_CPP.cmd"
            archiveArtifacts artifacts: 'Output/*.zip'
          }
        }
      }
    }
  }
}