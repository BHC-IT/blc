#!/bin/sh

#init lcov
lcov --no-external -c -i -d ./build/CMakeFiles -o ./build/cov.info

#run unit test executable
./build/test

#capture coverage after running executable
lcov --no-external -c -d ./build/CMakeFiles -o ./build/cov.info

# I added this in- Excludes some third party code
# lcov --remove $TARGET_DIR/cov.info '/opt/*' '/usr/*' '$ROOT_DIR/Common?ExternalLibraries/*'

#I added this in-generate report
genhtml ./build/cov.info -o ./build/out