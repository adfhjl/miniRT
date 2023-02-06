#!/bin/bash

afl-fuzz -i /src/afl/trimmed-scenes -o /src/afl/afl-output -M master -- /src/miniRT
