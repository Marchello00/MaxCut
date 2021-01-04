#!/bin/bash

if [ $# -lt 2 ]; then
  echo "Usage: ./run_test_dir.sh <test_dir, after \"testing/tests\"> [--bruteforce] [--random] [--greed] [--goemans-williamson]"
  return
fi

DIRNAME=$1
shift

mkdir -p "../results/${DIRNAME}"

for test_file in $(ls "../tests/${DIRNAME}"); do
  ../../bin/RunTest "../tests/${DIRNAME}/${test_file}" "$@" >"../results/${DIRNAME}/${test_file}.a"
done
