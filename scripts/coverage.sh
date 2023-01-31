#!/bin/bash

# TODO: Not sure if the DEBUG=1 is necessary
cd ..

mv miniRT miniRT_backup
make fclean
mv miniRT_backup miniRT

CC=afl-gcc-fast make DEBUG=1 GCOV=1
cd afl

afl-cov -d afl-output/master/ --live --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir ../obj &
# afl-cov -d afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir ../obj --overwrite

fuzz.sh

# docker exec -it amazing_hypatia bash
