#!/bin/bash

make -C .. DEBUG=1 GCOV=1

afl-cov -d afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir ../obj_gcov --live --overwrite --enable-branch-coverage --sleep 1 &

fuzz.sh

# docker exec -it amazing_hypatia bash
