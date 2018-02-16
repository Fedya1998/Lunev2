#!/bin/bash

make clean
g++ -fprofile-arcs -ftest-coverage -o cov test.cpp stack.cpp structure.cpp iter.cpp
./cov
rm cov
gcov stack.cpp iter.cpp structure.cpp
