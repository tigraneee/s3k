# S3K Tutorials

First, `cd` this directory and set up meson (using build directory `build`):
```
meson setup --cross-file=subprojects/s3k/cross/rv64imac.ini . build
```

Compile and run a tutorial (here tutorial.01):
```
meson compile -C build tut1-qemu
```
