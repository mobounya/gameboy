#!/usr/bin/env bash

# Current directory
__THIS_DIR=$(pwd)

function dl {
    git clone https://github.com/google/googletest.git
}

# Unpack and Build
function build {
    printf "\n  Building GTest and Gmock\n\n"
    cd googletest
    mkdir build 
    cd build/
    cmake -DBUILD_GMOCK=OFF -Dgtest_build_samples=OFF -Dgtest_build_tests=OFF ../
    make
}

# Install header files and library
function install {
    printf "\n  Installing GTest\n\n"

    GTEST_DIR="$HOME/shared/gtest/"

    mkdir -p $GTEST_DIR
    cp lib/*.a $GTEST_DIR
    cp -r ../googletest/include/gtest/ $GTEST_DIR
}

# Final Clean up.
function cleanup {
    printf "\n  Running Cleanup\n\n"

    cd $__THIS_DIR
    rm -rf $(pwd)/googletest
}

dl && build && install && cleanup