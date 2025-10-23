mkdir build

cmake --preset=debug -DCOMPILE_CONFIG_EDITOR=True
mingw32-make -C ./build -j8
