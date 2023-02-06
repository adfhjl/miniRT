# miniRT

## Commands
* `docker build -t afl-glfw . && docker run -it -v /Users/sbos/Documents/Programming/Projects/miniRT/:/src afl-glfw`
* `setup.sh`
* `fuzz.sh`
* `minimize_output.sh`
* `coverage.sh`

## Foo
* `< /src/scenes/valid/example.rt cat | afl-showmap -o /src/baz.txt -- /src/miniRT_ctmin`
* `afl-analyze -i /src/afl/minimized-crashes/* -- /src/miniRT_ctmin`
