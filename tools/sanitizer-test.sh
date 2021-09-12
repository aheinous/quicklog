 #!/bin/bash

cd $(dirname "$0")/..

TYPE="$1"


builddir="sanitizer_builds/${TYPE}"
mkdir -p $builddir

BUILDRESULTS="$builddir" OPTIONS=" -DENABLE_COVERAGE=No -DCMAKE_BUILD_TYPE=Debug -DUSE_SANITIZER=${TYPE}" make

cd ${builddir}

ninja run-qkl-unittests
res1="$?"
ninja run-speed-test
res2="$?"

if [ "$res1" != "0" -o "$res2" != "0" ]; then
    exit 1
else
    exit 0
fi