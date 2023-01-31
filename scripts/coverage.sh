#!/bin/bash

afl-cov -d afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT GCOV" --code-dir ../obj --live --overwrite --enable-branch-coverage --sleep 1 &

fuzz.sh

# docker exec -it amazing_hypatia bash
