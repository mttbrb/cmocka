# install cmake
sudo apt-get install cmake

# install cmocka
wget https://cmocka.org/files/1.0/cmocka-1.0.1.tar.xz
uncompress it
cd cmocka-1.0.1
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ..
make
sudo make install

# compile and run the lame example
cd tests
mkdir build
cmake ..
make
./example



