#!/bin/bash

# Grabs the arguments from Bazel
echo "cmd: $1"
CMD=$1
EXPECTED_TXT=./testdata/expected_output.txt

# Executes main and compares if the result is expected.
$CMD > test_output.txt
if cmp test_output.txt $EXPECTED_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as expected_output.txt
  diff -u --color=always test_output.txt $EXPECTED_TXT
  echo '---' test: FAIL
  exit 1
fi
