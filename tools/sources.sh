#!/bin/bash

cd $(dirname "$0")/..




filters=" -type f -false"

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -c | --c)
      filters="${filters} -o -iname '*.c'"
      shift # past argument
      ;;
    --cpp)
      filters="${filters} -o -iname '*.cpp'"
      shift # past argument
      ;;
    --headers)
      filters="${filters} -o -iname '*.h'"
      shift # past argument
      ;;
    --no-configs)
      no_configs=1
      shift # past argument
      ;;

    --no-platforms)
      no_platforms=1
      shift # past argument
      ;;
    *)
    echo "invalid arg $1" >&2
    exit 1
    ;;
esac
done


find_dirs="src include examples tests"

if [[ "$no_configs" != "1" ]]; then
    find_dirs="${find_dirs} configs"
fi

if [[ "$no_platforms" != "1" ]]; then
    find_dirs="${find_dirs} platforms"
fi



eval "find ${find_dirs} ${filters}"  \
	| grep -v doctest \
    | grep -v build
