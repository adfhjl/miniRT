# miniRT

## Commands
* `docker build -t afl-glfw .`
* `docker run -it -v /Users/sbos/Documents/Programming/Projects/miniRT/:/src afl-glfw`
* `setup.sh`
* `fuzz.sh`
* `minimize_output.sh`
* `coverage.sh`

## Foo
* `afl-showmap -o baz -- /src/miniRT /src/scenes/valid/example.rt`
* `< ../crashes.rt cat | afl-showmap -o baz -- /src/miniRT`
