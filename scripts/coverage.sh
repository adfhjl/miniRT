#!/bin/bash

make -C /src DEBUG=1 GCOV=1

afl-cov -d /src/afl/afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir /src/obj_gcov --live --overwrite --enable-branch-coverage --lcov-web-all --sleep 1 &> /dev/null &

fuzz.sh
