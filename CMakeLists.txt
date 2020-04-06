
cmake_minimum_required(VERSION 3.1)
project(blc)

set(blc_MAJOR_VERSION 0)
set(blc_MINOR_VERSION 1)
set(blc_PATCH_VERSION 0)
set(blc_VERSION
	${blc_MAJOR_VERSION}.${blc_MINOR_VERSION}.${blc_PATCH_VERSION}
	)


set(SRCS
	src/bindTest.cpp
	src/cinReadable.cpp
	src/client.cpp
	src/client2way.cpp
	src/errorHandle.cpp
	src/fileSize.cpp
	src/float.cpp
	src/global.cpp
	src/nonCopyable.cpp
	src/pipe.cpp
	src/pipeCluster.cpp
	src/promise.cpp
	src/regex.cpp
	src/serializable.cpp
	src/server.cpp
	src/server2way.cpp
	src/singleServer.cpp
	src/socket.cpp
	src/stream.cpp
	src/stringOp.cpp
	src/VFiles.cpp
	)

if (!WIN32)
	set(SRCS ${SRCS}
		src/ForkServer.cpp
	)
endif()

set(TEMPLATE
	blc/pair.tpp
	blc/protocolFactory.tpp
	blc/protocolCaps.tpp
	blc/vecteur2.tpp
	)

set(HEADERS
	blc/actor.hpp
	blc/blc.hpp
	blc/client.hpp
	blc/cinReadable.hpp
	blc/client2way.hpp
	blc/concept.hpp
	blc/constraint.hpp
	blc/errorHandle.hpp
	blc/fileSize.hpp
	blc/float.hpp
	blc/global.hpp
	blc/nonCopyable.hpp
	blc/pair.hpp
	blc/pipe.hpp
	blc/pipeCluster.hpp
	blc/promise.hpp
	blc/protocolCaps.hpp
	blc/protocolFactory.hpp
	blc/regex.hpp
	blc/serializable.hpp
	blc/server.hpp
	blc/server2way.hpp
	blc/singleServer.hpp
	blc/socket.hpp
	blc/stream.hpp
	blc/stringOp.hpp
	blc/vecteur2.hpp
	blc/bindTest.hpp
	blc/VFiles.hpp
	)

set(CONCEPTS
	concept/operable.hpp
)

set(TEST
	test/main.cpp
	test/pipe.cpp
)

if (!WIN32)
	set(HEADERS ${HEADERS}
		include/ForkServer.hpp
	)
endif()

set (GCC_COVERAGE_COMPILE_FLAGS "")
if (WIN32)
	set (GCC_COVERAGE_COMPILE_FLAGS "")
endif()

add_library(objlib OBJECT ${SRCS} ${TEMPLATE} ${HEADERS} ${CONCEPTS})

#set the objlib dummy
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
set_property(TARGET objlib PROPERTY CXX_STANDARD 17)
target_include_directories(objlib PRIVATE .)
target_compile_features(objlib PUBLIC cxx_nullptr)

add_library(blc STATIC $<TARGET_OBJECTS:objlib> src/main.cpp blc/blcmain.hpp)
add_library(blc.2 SHARED $<TARGET_OBJECTS:objlib>)

set_property(TARGET blc PROPERTY CXX_STANDARD 17)
set_property(TARGET blc.2 PROPERTY CXX_STANDARD 17)

target_compile_features(blc PUBLIC cxx_nullptr)
target_compile_features(blc.2 PUBLIC cxx_nullptr)

target_include_directories(blc PRIVATE .)
target_include_directories(blc.2 PRIVATE .)


# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
#set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
	set(DEF_INSTALL_CMAKE_DIR CMake)
else()
	set(DEF_INSTALL_CMAKE_DIR share/cmake/blc)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

foreach(p LIB BIN INCLUDE CMAKE)
	set(var INSTALL_${p}_DIR)
	if(NOT IS_ABSOLUTE "${${var}}")
		set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
	endif()
endforeach()

export(TARGETS blc blc.2 FILE "${PROJECT_BINARY_DIR}/blcTargets.cmake")
export(PACKAGE BLC)
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(blcConfig.cmake.in "${PROJECT_BINARY_DIR}/blcConfig.cmake" @ONLY)
set(CONF_INCLUDE_DIRS "\${BLC_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(blcConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/blcConfig.cmake" @ONLY)
configure_file(blcConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/blcConfigVersion.cmake" @ONLY)

install(FILES
	"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/blcConfig.cmake"
	"${PROJECT_BINARY_DIR}/blcConfigVersion.cmake"
	DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
install(EXPORT blcTargets DESTINATION
	"${INSTALL_CMAKE_DIR}" COMPONENT dev)


install(TARGETS blc blc.2 EXPORT blcTargets
	ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
	LIBRARY DESTINATION ${INSTALL_LIB_DIR})
install(FILES ${HEADERS} ${TEMPLATE} DESTINATION ${INSTALL_INCLUDE_DIR}/blc)
install(FILES ${CONCEPTS} DESTINATION ${INSTALL_INCLUDE_DIR}/concept)
install(FILES blc/blcmain.hpp DESTINATION ${INSTALL_INCLUDE_DIR}/blc)



set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(WIN32)
	target_link_libraries(objlib wsock32 ws2_32)
	target_link_libraries(blc wsock32 ws2_32)
	target_link_libraries(blc.2 wsock32 ws2_32)
	target_link_libraries(objlib Threads::Threads)
endif()

target_link_libraries(blc Threads::Threads)
target_link_libraries(blc.2 Threads::Threads)

find_package(Doxygen QUIET
	#OPTIONAL_COMPONENTS mscgen dia dot
	)

if(Doxygen_FOUND)
	set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	configure_file(${doxyfile_in} ${doxyfile})
	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM)

	message("-- Doxygen found")
else ()
	message("Doxygen not found")
endif()


add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")


if(test)
	add_executable(test ${TEST} ${SRCS} ${CONCEPTS} ${HEADERS})
	target_compile_features(test PUBLIC cxx_nullptr)
	target_link_libraries(test Threads::Threads)
	target_include_directories(test PRIVATE .)
	set_property(TARGET test PROPERTY CXX_STANDARD 17)
	if(WIN32)
		target_link_libraries(test wsock32 ws2_32)
	endif()
endif()


