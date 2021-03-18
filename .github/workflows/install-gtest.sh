#!/bin/bash
set -x

cd ..
git clone https://github.com/google/googletest.git
mkdir -p googletest/build
cd googletest/build
cmake ..
cmake --build .
sudo cmake --install .
