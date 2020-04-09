#!/bin/sh

#init lcov
lcov -c -i -d ./build/CMakeFiles -o ./build/cov.info

#run unit test executable
./build/test

#capture coverage after running executable
lcov --exclude '*test/*' --exclude '/usr/*' -c -d ./build/CMakeFiles -o ./coverage/lcov.info
# lcov --remove ./build/cov.info '/usr/*' --output-file ./build/cov.info
# lcov --remove ./build/cov.info './test/*' --output-file ./build/cov.info

# I added this in- Excludes some third party code
# lcov --remove $TARGET_DIR/cov.info '/opt/*' '/usr/*' '$ROOT_DIR/Common?ExternalLibraries/*'

#I added this in-generate report
genhtml ./coverage/lcov.info -o ./build/out