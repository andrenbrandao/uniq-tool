#!/bin/bash

# Grabs the arguments from Bazel
echo "cmd: $1"
CMD=$1
INPUT_TXT=./testdata/test.txt
EXPECTED_TXT=./testdata/expected_output.txt
EXPECTED_COUNT_TXT=./testdata/expected_count_output.txt
EXPECTED_REPEATED_ONLY_TXT=./testdata/expected_repeated_only_output.txt
EXPECTED_UNIQUE_ONLY_TXT=./testdata/expected_unique_only_output.txt

clean() {
  rm test_output.txt
}

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
clean
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
clean
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

# Reads from file and saves to another
clean
$CMD $INPUT_TXT test_output.txt
if cmp test_output.txt $EXPECTED_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as expected_output.txt
  diff -u --color=always test_output.txt $EXPECTED_TXT
  echo '---' test: FAIL
  exit 1
fi

# Reads from stdin and saves to a file
clean
cat $INPUT_TXT | $CMD - test_output.txt
if cmp test_output.txt $EXPECTED_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as expected_output.txt
  diff -u --color=always test_output.txt $EXPECTED_TXT
  echo '---' test: FAIL
  exit 1
fi

# Count number of lines when flag -c is enabled
clean
$CMD -c $INPUT_TXT > test_output.txt
if cmp test_output.txt $EXPECTED_COUNT_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as $EXPECTED_COUNT_TXT
  diff -u --color=always test_output.txt $EXPECTED_COUNT_TXT
  echo '---' test: FAIL
  exit 1
fi

# Print only repeated lines when -d is enabled
clean
$CMD -d $INPUT_TXT > test_output.txt
if cmp test_output.txt $EXPECTED_REPEATED_ONLY_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as $EXPECTED_REPEATED_ONLY_TXT
  diff -u --color=always test_output.txt $EXPECTED_REPEATED_ONLY_TXT
  echo '---' test: FAIL
  exit 1
fi

# Print only unique lines when -u is enabled
clean
$CMD -u $INPUT_TXT > test_output.txt
if cmp test_output.txt $EXPECTED_UNIQUE_ONLY_TXT
then
  echo '---' test: PASS
else
  echo '---' output is not the same as $EXPECTED_UNIQUE_ONLY_TXT
  diff -u --color=always test_output.txt $EXPECTED_UNIQUE_ONLY_TXT
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
