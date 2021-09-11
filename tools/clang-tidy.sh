#!/bin/bash

cd $(dirname "$0")/..

if [[ "$1" == "--early-exit" ]]; then
    early_exit=1
    shift
else
    early_exit=0
fi


CLANG_TIDY=${1:-clang-tidy}
# Argument 2 is the path to the directory containing the compile_commands.json file
BUILD_OUTPUT_FOLDER=${2:-buildresults}

# ./tools/sources.sh \
# 	| xargs "${CLANG_TIDY}" --header-filter='.*' -p $BUILD_OUTPUT_FOLDER


error_code=0

for src in $(./tools/sources.sh); do
    # echo "--------------- $src"
    "${CLANG_TIDY}" --header-filter='.*' -p $BUILD_OUTPUT_FOLDER $src
    res="$?"
    # echo "res: $res"
    if [[ "$res" -ne "0" ]]; then
        # echo "fail $early_exit"
        if [[ "$early_exit" == "1" ]]; then
            # echo "early exit"
            exit 1
        fi
        error_code=1
    fi
done

exit "$error_code"