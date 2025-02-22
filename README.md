# libdxfrw

libdxfrw is a free C++ library to read and write DXF files in both formats, ascii and binary form.
Also can read DWG files from R14 to the last V2015.

This is a forked version of libdxfrw by adding supports to build it as WebAssembly using Emscripten embind.

## Build WebAssembly

```
autoconf
automake --add-missing --force-missing
mkdir build
cd build
emconfigure ../configure
cd src
emmake make
emcc -O2 -lembind *.o intern/*.o -o libdxfrw.js -s MODULARIZE=1 -s EXPORT_NAME="createModule" --emit-tsd libdxfrw.d.ts
```

If you want to debug WebAssembly in Chrome DevTools. Please compile your application with DWARF debug information included. Run the latest Emscripten compiler and pass it the -gsource-map flag. For example:

```
emcc -gsource-map -lembind *.o intern/*.o -o libdxfrw.js -s MODULARIZE=1 -s EXPORT_NAME="createModule" --emit-tsd libdxfrw.d.ts
```
