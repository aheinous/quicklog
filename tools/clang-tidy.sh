#!/bin/bash

cd $(dirname "$0")/..

# Argument 1 is the path to the directory containing the compile_commands.json file
CLANG_TIDY=${1:-clang-tidy}
BUILD_OUTPUT_FOLDER=${2:-buildresults}

./tools/sources.sh \
	| xargs "${CLANG_TIDY}" --header-filter='.*' -p $BUILD_OUTPUT_FOLDER