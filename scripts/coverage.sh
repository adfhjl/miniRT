#!/bin/bash

make -C /src DEBUG=1 GCOV=1

# afl-cov -d /src/afl/afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir /src/obj_gcov --live --overwrite --enable-branch-coverage --lcov-web-all --sleep 1 &> /dev/null &

afl-cov -d /src/afl/afl-output/master/ --coverage-cmd "cat AFL_FILE | /src/miniRT_gcov" --code-dir /src/obj_gcov --live --overwrite --enable-branch-coverage --sleep 1 &> /dev/null &

replace_lcov_docker_work_directory () {
	while true
	do
		< /src/afl/afl-output/master/cov/lcov/trace.lcov_info_final sed 's#/src/src#/Users/sbos/Documents/Programming/Projects/miniRT/src#g' > /src/afl/afl-output/master/cov/lcov/lcov.info
		sleep 1
	done
}

replace_lcov_docker_work_directory &

fuzz.sh
