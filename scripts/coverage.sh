#!/bin/bash

cd /src

make DEBUG=1 GCOV=1

afl-cov -d afl/afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir obj_gcov --live --overwrite --enable-branch-coverage --lcov-web-all --sleep 1 &> /dev/null &

fuzz.sh

# docker exec -it amazing_hypatia bash
