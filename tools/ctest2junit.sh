#!/usr/bin/env bash

set -eu

ctest2junit_xsl=$(readlink -f `dirname ${BASH_SOURCE[0]}`)/ctest2junit.xsl
junit_xsd=$(readlink -f `dirname ${BASH_SOURCE[0]}`)/junit.xsd
junit2txt_xsl=$(readlink -f `dirname ${BASH_SOURCE[0]}`)/junit2txt.xsl

tests_dir=$1
if [ ! -d $tests_dir ];
then
  echo "ERROR! $tests_dir is not directory!"
  exit 1
fi

results_dir=$2
if [ ! -d $results_dir ];
then
  echo "ERROR! $results_dir is not directory!"
  exit 1
fi



tag=$(head -n 1 $tests_dir/Testing/TAG)
xsltproc --output $results_dir/ctest.xml $ctest2junit_xsl $tests_dir/Testing/$tag/Test.xml
xmllint --schema $junit_xsd $results_dir/ctest.xml --noout
xsltproc --output $results_dir/ctest.txt $junit2txt_xsl $results_dir/ctest.xml

echo ""
cat $results_dir/ctest.txt
echo ""

echo "Test report generated successfully"
