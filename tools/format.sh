#!/bin/bash

cd $(dirname "$0")/..

./tools/sources.sh | xargs clang-format -style=file -i -fallback-style=none