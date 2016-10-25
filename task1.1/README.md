# how to build

## create assembly code
```
g++ -S -o greet_world.asm greet_world.cpp
```

## create executable`
```
g++ -o greet_world greet_world.cpp
```

## with cmake
use `sh run.sh` to build and run on Unix or `sh runWin.sh` on Windows machines.