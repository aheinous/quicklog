#!/bin/bash

cd $(dirname "$0")/..

find src include configs examples platforms tests -type f -iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp \
	| grep -v doctest