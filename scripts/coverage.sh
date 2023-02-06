#!/bin/bash

export AFL_LLVM_LAF_ALL=1
export AFL_HARDEN=1

make -C /src DEBUG=1 GCOV=1

# In case you want to view the web result, use this instead of the line below it
# afl-cov -d /src/afl/afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir /src/obj_gcov --live --overwrite --enable-branch-coverage --lcov-web-all --sleep 1 &> /dev/null &

afl-cov -d /src/afl/afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir /src/obj_gcov --live --overwrite --enable-branch-coverage --disable-lcov-web --sleep 1 &> /dev/null &

replace_lcov_docker_work_directory () {
	while true
	do
		sleep 1
		< /src/afl/afl-output/master/cov/lcov/trace.lcov_info_final sed 's#/src/src#/Users/sbos/Documents/Programming/Projects/miniRT/src#g' > /src/afl/afl-output/master/cov/lcov/lcov.info
	done
}

replace_lcov_docker_work_directory &

fuzz.sh
