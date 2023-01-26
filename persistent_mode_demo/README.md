```bash
mkdir -p minimized-inputs
rm -rf minimized-inputs/*
afl-cmin -i inputs -o minimized-inputs -- ./persistent_demo

afl-fuzz -i minimized-inputs -o outputs -- ./persistent_demo
```
