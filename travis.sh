#!/bin/bash
set -ev

mkdir build/ && cd build/

cmake .. -DCMAKE_BUILD_TYPE=$CW3_BUILD_TYPE -DENABLE_TESTS=$CW3_TESTS -DGMOCK_LIBS=$GMOCK_LIBS -DGMOCK_SOURCE=$GMOCK_SOURCE && make

if [ "$CW3_TESTS" = "TRUE" ]
then
    ctest -V
fi
