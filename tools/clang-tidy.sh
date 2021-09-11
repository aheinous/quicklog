#!/bin/bash

cd $(dirname "$0")/..

# if [[ "$1" == "--early-exit" ]]; then
#     early_exit=1
#     shift
# else
#     early_exit=0
# fi


CLANG_TIDY=${1:-clang-tidy}
# Argument 2 is the path to the directory containing the compile_commands.json file
BUILD_OUTPUT_FOLDER=${2:-buildresults}

# ./tools/sources.sh \
# 	| xargs "${CLANG_TIDY}" --header-filter='.*' -p $BUILD_OUTPUT_FOLDER


if [[ $3 ]]; then
    outfile="$3"
    rm "$outfile" 2>/dev/null
fi

mkdir -p $(dirname ${outfile})

error_code=0

for src in $(./tools/sources.sh); do
    # echo "--------------- $src"
    if [[ $outfile ]]; then
        "${CLANG_TIDY}" --header-filter='.*' -p $BUILD_OUTPUT_FOLDER $src >> $outfile
        res="$?"
    else
        "${CLANG_TIDY}" --use-color --header-filter='.*' -p $BUILD_OUTPUT_FOLDER $src
        res="$?"
    fi

    # echo "res: $res"
    if [[ "$res" -ne "0" ]]; then
        # echo "fail $early_exit"
        # if [[ "$early_exit" == "1" ]]; then
        #     # echo "early exit"
        #     exit 1
        # fi
        error_code=1
    fi
done

if [[ $outfile ]]; then
    cat $outfile
fi

exit "$error_code"