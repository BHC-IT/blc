cmake_minimum_required(VERSION 3.1)
project(dev)

set (GCC_COVERAGE_COMPILE_FLAGS "-g3")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(blc REQUIRED)

set (SRCS
	main.cpp
	)

set (HEADER
	)

add_executable(test ${SRCS} ${HEADER})

target_link_libraries(test PRIVATE Threads::Threads)
target_link_libraries(test PRIVATE blc)

set_property(TARGET test PROPERTY CXX_STANDARD 17)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
