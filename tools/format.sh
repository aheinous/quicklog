#!/bin/bash

cd $(dirname "$0")/..

./tools/sources.sh --c --cpp --headers | xargs clang-format -style=file -i -fallback-style=none