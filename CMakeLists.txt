
cmake_minimum_required (VERSION 3.26)

#projects name
project ("Direct3D")

#settings cmake options
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
endif()

set(CMAKE_CXX_STANDARD 20)


#COMPILER VERSION CHECK
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message(STATUS "Using MSVC Version,${MSVN_VERSION} ")
else()
	message(FATAL_ERROR "Compiler are not supported,${MSVN_VERSION} ")
endif()


#settings output directory
add_subdirectory ("Source")
