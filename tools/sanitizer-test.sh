 #!/bin/bash

cd $(dirname "$0")/..

TYPE="$1"


builddir="sanitizer_builds/${TYPE}"
mkdir -p $builddir

BUILDRESULTS="$builddir" OPTIONS=" -DENABLE_COVERAGE=No -DCMAKE_BUILD_TYPE=Debug -DUSE_SANITIZER=${TYPE}" make

cd ${builddir}

ninja run-qkl-unittests
exit "$?"