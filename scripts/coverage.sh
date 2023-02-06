#!/bin/bash

export AFL_LLVM_LAF_ALL=1

# These are mutually exclusive
export AFL_HARDEN=1
# TODO: Right now this prints "ld.lld: error: cannot open /usr/lib/llvm-14/lib/clang/14.0.6/lib/linux/libclang_rt.asan_static-x86_64.a: No such file or directory"
# TODO: Might not work well with parallelization "you should only run one afl-fuzz instance per sanitizer type."
# https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/fuzzing_in_depth.md#c-selecting-sanitizers
# export AFL_USE_ASAN=1

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
