#!/bin/bash

# afl-fuzz -i /src/afl/second-minimized-scenes -o /src/afl/afl-output -D -M master -- /src/miniRT
afl-fuzz -i /src/afl/second-minimized-scenes -o /src/afl/afl-output -M master -- /src/miniRT
