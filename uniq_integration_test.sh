#!/bin/bash

# Grabs the arguments from Bazel
echo "cmd: $1"
CMD=$1
INPUT_TXT=./testdata/test.txt
EXPECTED_TXT=./testdata/expected_output.txt

failed_any=0

# Executes main and compares if the result is expected.
$CMD $INPUT_TXT > test_output.txt
if cmp test_output.txt $EXPECTED_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as expected_output.txt
  diff -u --color=always test_output.txt $EXPECTED_TXT
  echo '---' test: FAIL
  exit 1
fi

# Reads from standard input
cat $INPUT_TXT | $CMD - > test_output.txt
if cmp test_output.txt $EXPECTED_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as expected_output.txt
  diff -u --color=always test_output.txt $EXPECTED_TXT
  echo '---' test: FAIL
  exit 1
fi

# Reads from standard input without - flag
cat $INPUT_TXT | $CMD > test_output.txt
if cmp test_output.txt $EXPECTED_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as expected_output.txt
  diff -u --color=always test_output.txt $EXPECTED_TXT
  echo '---' test: FAIL
  exit 1
fi

#########################################################
if [ $failed_any -eq 0 ]; then
    echo '***' PASSED ALL TESTS
else
    echo '***' FAILED SOME TESTS
    exit 1
fi
