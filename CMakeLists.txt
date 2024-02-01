# set minimum cmake version
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# project name and language
project (ex618_kafka_001_prj  LANGUAGES CXX)


IF (MSVC)
	message(STATUS " MSVC version '${MSVC_VERSION}'")
	IF(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS 1930)
		set(CMAKE_CXX_STANDARD 20)
	ELSEIF(MSVC_VERSION GREATER_EQUAL 1930)
		set(CMAKE_CXX_STANDARD 23)
	ENDIF()

	set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
ELSE()
	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

# include(FetchContent)

# FetchContent_Declare(
        # googletest
        # GIT_REPOSITORY https://github.com/google/googletest.git
        # GIT_TAG        release-1.11.0
        # GIT_SHALLOW    1
# )
# FetchContent_MakeAvailable(googletest)
# include(GoogleTest)


IF (MSVC)
	# Avoid error LNK2038
	#set(gtest_force_shared_crt on)

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

IF (MSVC)
	message(STATUS " MSVC version '${MSVC_VERSION}'")
	IF(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS 1930)
		SET(INCLUDE_DIRS "V:/3rdparty/librdkafka_2.2.0/include")
		SET(LIBRDKAFKA_LIB_DIR "V:/3rdparty/librdkafka_2.2.0/lib")
		SET(LIBRDKAFKA_LIB_NAME "librdkafka.lib")
	ELSEIF(MSVC_VERSION GREATER_EQUAL 1930)
		SET(INCLUDE_DIRS "E:/users/chfl/app/vcpkg/packages/librdkafka_x64-windows//include/librdkafka")
		SET(LIBRDKAFKA_LIB_DIR "E:/users/chfl/app/vcpkg/packages/librdkafka_x64-windows/lib")
		SET(LIBRDKAFKA_LIB_NAME "rdkafka++.lib")
	ENDIF()
ELSE ()
	SET(LIBRDKAFKA_LIB_DIR "/usr/lib/x86_64-linux-gnu")
	SET(LIBRDKAFKA_LIB_NAME "librdkafka++.so")
ENDIF ()

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRDKAFKA_LIB_DIR})


IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	#usinf Clang or GNU

	#------------------------------------------------------------------------------
	# add the executable producer
	#------------------------------------------------------------------------------
	SET(PRODUCER_EXEC_NAME "kafka_exec_producer")
	add_executable(${PRODUCER_EXEC_NAME}

		main/main_01.cpp
	)
	target_link_libraries(${PRODUCER_EXEC_NAME} ${LIBRDKAFKA_LIB_NAME})


	#------------------------------------------------------------------------------
	# add the executable consumer
	#------------------------------------------------------------------------------
	SET(CONSUMER_EXEC_NAME "kafka_exec_consumer")
	add_executable(${CONSUMER_EXEC_NAME}

		main/main_02.cpp
	)
	target_link_libraries(${CONSUMER_EXEC_NAME} ${LIBRDKAFKA_LIB_NAME})

ELSEIF()
	#using MSVC

	#------------------------------------------------------------------------------
	# add the librdkafka api producer
	#------------------------------------------------------------------------------
	SET(PRODUCER_NAME "kafka_producer")
	add_executable(${PRODUCER_NAME}

		main/main_01_01.cpp
	)
	target_link_libraries(${PRODUCER_NAME} ${LIBRDKAFKA_LIB_NAME})

	#------------------------------------------------------------------------------
	# add the librdkafka api consumer
	#------------------------------------------------------------------------------
	SET(CONSUMER_NAME "kafka_consumer")
	add_executable(${CONSUMER_NAME}

		main/main_02_01.cpp
	)
	target_link_libraries(${CONSUMER_NAME} ${LIBRDKAFKA_LIB_NAME})

ENDIF()


