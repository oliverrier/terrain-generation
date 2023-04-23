mkdir build-debug -p && cd build-debug || exit
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.. -DBUILD_SHARED_LIBS=ON
make
make install