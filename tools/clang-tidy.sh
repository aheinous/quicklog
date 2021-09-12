#!/bin/bash

cd $(dirname "$0")/..



CLANG_TIDY=${1:-clang-tidy}
# Argument 2 is the path to the directory containing the compile_commands.json file
BUILD_OUTPUT_FOLDER=${2:-buildresults}


if [[ $3 ]]; then
    usr_outfile="$3"
    rm "$usr_outfile" 2>/dev/null
    mkdir -p $(dirname ${usr_outfile})
fi


error_code=0

tmp_file=$(mktemp /tmp/clang-tidy.XXXXXX)

for src in $(./tools/sources.sh); do
    clang_tidy_cmd="${CLANG_TIDY} --quiet --header-filter='.*' -p $BUILD_OUTPUT_FOLDER $src"

    eval ${clang_tidy_cmd} > "${tmp_file}"
    grep -P  '^(.*?):(\d+?):(\d+?:)?\s+(warning|error):\s+(.*)$' "${tmp_file}"
    res="$?"

    if [[ "$res" == "0"  ]]; then
        if [[ $usr_outfile ]]; then
            cat ${tmp_file} >> $usr_outfile
        else
            cat "${tmp_file}"
            rm "${tmp_file}"
        fi
        error_code=1
    fi
done


if [[ -e "$usr_outfile" ]]; then
    cat $usr_outfile
fi

exit "$error_code"