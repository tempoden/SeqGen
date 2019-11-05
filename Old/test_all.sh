#!/bin/bash
mkdir build
mkdir out
cd ./build
cmake ..
make
./super > ../out/super.out
./nonlinear > ../out/nonlinear.out
./linearxor > ../out/linearxor.out
./super_s_block > ../out/super_s_block.out

#dieharder -a -g 201 -f <filename> - for binary tests
