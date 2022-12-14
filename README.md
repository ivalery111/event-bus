## Build & Test
```
cmake -DENABLE_TESTING=ON -B build
cmake --build build
cd build && ctest -VV; cd ..
```

## Run in Docker
```
# Build Docker image
../tools$ make docker-build

# Run container
event-bus$ docker run --rm -it -v $(pwd):$(pwd) --workdir=$(pwd) --name event-bus-builder event-bus-builder
```

## Use GCC/Clang compilers
```
# GCC
event-bus$ cmake -DCMAKE_CXX_COMPILER=gcc -B build
event-bus$ cmake --build build

# Clang
event-bus$ cmake -DCMAKE_CXX_COMPILER=clang -B build
event-bus$ cmake --build build
```

## Use sanitizers
```
event-bus$ cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTING=ON -DENABLE_SANITIZER_ADDRESS=TRUE -DCMAKE_CXX_COMPILER=clang -B build
```
For more details please see `cmake/Sanitizers.cmake`
