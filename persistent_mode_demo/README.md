```bash
make

mkdir -p minimized-scenes
rm -rf minimized-scenes/*
afl-cmin -i scenes -o minimized-scenes -- ./persistent_demo

mkdir -p minimized-input
rm -rf minimized-input/*
i=0
for file in minimized-scenes/**; do
afl-tmin -i "$file" -o minimized-input/$i -- ./persistent_demo
i=$(($i + 1))
done

afl-fuzz -i minimized-input -o afl-output -- ./persistent_demo
```
