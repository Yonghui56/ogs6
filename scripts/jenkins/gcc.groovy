defaultDockerArgs = '-v /home/jenkins/.ccache:/usr/src/.ccache'
defaultCMakeOptions = '-DOGS_LIB_BOOST=System -DOGS_LIB_VTK=System'

node('docker')
{
    step([$class: 'GitHubSetCommitStatusBuilder', statusMessage: [content: 'Started Jenkins gcc build']])

    stage 'Checkout'
    dir('ogs') { checkout scm }

    docker.image('ogs6/gcc-base:latest').inside(defaultDockerArgs)
    {
        stage 'Configure'
        configure 'build', ''

        stage 'Build'
        build 'build', ''
        if (env.BRANCH_NAME == 'master')
            build 'build', 'package'

        stage 'Test'
        build 'build', 'tests ctest'
    }

    stage 'Post'
    publishTestReports 'build/Testing/**/*.xml', 'build/Tests/testrunner.xml',
        'ogs/scripts/jenkins/clang-log-parser.rules'

    archive 'build*/*.tar.gz'
}

def configure(buildDir, cmakeOptions) {
    sh "rm -rf ${buildDir} && mkdir ${buildDir}"
    sh "cd ${buildDir} && cmake ../ogs ${defaultCMakeOptions} ${cmakeOptions}"
}

def build(buildDir, target) {
    sh "cd ${buildDir} && make -j \$(nproc) ${target}"
}

def publishTestReports(ctestPattern, gtestPattern, parseRulefile) {
    step([$class: 'XUnitPublisher', testTimeMargin: '3000', thresholdMode: 1,
        thresholds: [
            [$class: 'FailedThreshold', failureNewThreshold: '', failureThreshold: '', unstableNewThreshold: '', unstableThreshold: ''],
            [$class: 'SkippedThreshold', failureNewThreshold: '', failureThreshold: '', unstableNewThreshold: '', unstableThreshold: '']],
        tools: [
            [$class: 'CTestType', deleteOutputFiles: true, failIfNotNew: true, pattern: "${ctestPattern}", skipNoTestFiles: false, stopProcessingIfError: true],
            [$class: 'GoogleTestType', deleteOutputFiles: true, failIfNotNew: true, pattern: "${gtestPattern}", skipNoTestFiles: false, stopProcessingIfError: true]]
    ])

    step([$class: 'LogParserPublisher', failBuildOnError: true, unstableOnWarning: false,
            projectRulePath: "${parseRulefile}", useProjectRule: true])

    step([$class: 'GitHubCommitNotifier', resultOnFailure: 'FAILURE', statusMessage: [content: 'Finished Jenkins gcc build']])

}

properties ([[$class: 'BuildDiscarderProperty', strategy: [$class: 'LogRotator', artifactDaysToKeepStr: '', artifactNumToKeepStr: '5', daysToKeepStr: '', numToKeepStr: '25']]])
