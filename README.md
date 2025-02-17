# libdxfrw

libdxfrw is a free C++ library to read and write DXF files in both formats, ascii and binary form.
Also can read DWG files from R14 to the last V2015.

This is a forked version of libdxfrw by adding supports to build it as WebAssembly using Emscripten embind.

## Build WebAssembly

```
mkdir build
cd build
emconfigure ../configure
emmake make
emcc -O2 --bind src/bindings.o src/*.o src/intern/*.o -o src/libdxfrw.js
```
