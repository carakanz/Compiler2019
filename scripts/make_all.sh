echo $(pwd)
mkdir build
cd build
scan-build cmake ..
scan-build cmake --build .