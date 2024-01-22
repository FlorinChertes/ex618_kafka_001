# set minimum cmake version
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# project name and language
project (ex618_kafka_001_prj  LANGUAGES CXX)


IF (MSVC)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
ELSE()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
        GIT_SHALLOW    1
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


IF (MSVC)
	# Avoid error LNK2038
	set(gtest_force_shared_crt on)

	# Activate C++ exception handling 
	IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc") 
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	ENDIF ()
ELSE ()
	if(CMAKE_BUILD_TYPE STREQUAL "")
		# Build type is not set e.g., command was "cmake .."
		message(STATUS " Build type unspecified, set to Release")
		set(CMAKE_BUILD_TYPE Release)
	else()
		message(STATUS " Build type specified as '${CMAKE_BUILD_TYPE}'")
	endif()

	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wnull-dereference")

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		SET(GCC_STD_CPP_CONCEPTS_COMPILE_FLAGS "-fconcepts")
		SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_CONCEPTS_COMPILE_FLAGS}")
	endif()

	SET(GCC_STD_CPP_PERMISIV_COMPILE_FLAGS "-fpermissive")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_PERMISIV_COMPILE_FLAGS}")
ENDIF () 

set(INCLUDE_DIRS "test/inc" "lib/inc")

include_directories(${INCLUDE_DIRS})


#------------------------------------------------------------------------------
# add the executable 001
#------------------------------------------------------------------------------
add_executable(ex618_kafka_001_ex

	main/main_01.cpp
)



