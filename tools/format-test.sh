#!/bin/bash


cd $(dirname "$0")/..


failed_srcs=""

exit_code=0

if [[ -z ${CLANG_FORMAT} ]]; then
    CLANG_FORMAT=clang-format
fi


for src in $(./tools/sources.sh); do
    ${CLANG_FORMAT} -style=file -fallback-style=none $src > clang-format-out.tmp
    diff  $src clang-format-out.tmp >> /dev/null
    res="$?"
    if [[ "$res" -ne 0 ]]; then
        echo "vvvv source file: $src vvvv"
        diff -y --width=300 --suppress-common-lines $src clang-format-out.tmp
        echo -e "^^^^ source file: $src ^^^^\n"
        exit_code=1
        failed_srcs="${failed_srcs}\t${src}\n"
    fi
    rm clang-format-out.tmp
done

if [[ $exit_code -ne 0 ]]; then
    echo "Files with formatting issues:"
    echo -e ${failed_srcs}
fi

exit $exit_code