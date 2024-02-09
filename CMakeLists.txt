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


IF (MSVC)
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

set(INCLUDE_LOCAL_DIRS "test/inc" "lib/inc" "inc")

IF (MSVC)
	IF(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS 1930)
		SET(INCLUDE_DIRS "V:/3rdparty/librdkafka_2.2.0/include")
		SET(LIBRDKAFKA_LIB_DIR "V:/3rdparty/librdkafka_2.2.0/lib")
		SET(LIBRDKAFKA_LIB_NAME "librdkafka.lib")
		SET(LIBRDKAFKA_CPP_LIB_NAME "librdkafkacpp.lib")
	ELSEIF(MSVC_VERSION GREATER_EQUAL 1930)
		SET(INCLUDE_DIRS "E:/users/chfl/app/vcpkg/packages/librdkafka_x64-windows//include/librdkafka")
		SET(LIBRDKAFKA_LIB_DIR "E:/users/chfl/app/vcpkg/packages/librdkafka_x64-windows/lib")
		SET(LIBRDKAFKA_LIB_NAME "rdkafka.lib")
		SET(LIBRDKAFKA_CPP_LIB_NAME "rdkafka++.lib")
	ENDIF()
ELSE ()
	SET(LIBRDKAFKA_LIB_DIR "/usr/lib/x86_64-linux-gnu")
	SET(LIBRDKAFKA_LIB_NAME "librdkafka.so")
	SET(LIBRDKAFKA_CPP_LIB_NAME "librdkafka++.so")
ENDIF ()

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRDKAFKA_LIB_DIR})

#using Clang or GNU

#------------------------------------------------------------------------------
# add the cpp producer
#------------------------------------------------------------------------------
SET(PRODUCER_CPP_NAME "kafka_cpp_producer")
add_executable(${PRODUCER_CPP_NAME}

	main/main_01.cpp
)
target_link_libraries(${PRODUCER_CPP_NAME} ${LIBRDKAFKA_LIB_NAME} ${LIBRDKAFKA_CPP_LIB_NAME})
target_include_directories(${PRODUCER_CPP_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})

#------------------------------------------------------------------------------
# add the cpp consumer
#------------------------------------------------------------------------------
SET(CONSUMER_CPP_NAME "kafka_cpp_consumer")
add_executable(${CONSUMER_CPP_NAME}

	main/main_02.cpp
)
target_link_libraries(${CONSUMER_CPP_NAME} ${LIBRDKAFKA_LIB_NAME} ${LIBRDKAFKA_CPP_LIB_NAME})
target_include_directories(${CONSUMER_CPP_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})


#using Clang or GNU
#using MSVC

#------------------------------------------------------------------------------
# add the librdkafka api producer
#------------------------------------------------------------------------------
SET(PRODUCER_NAME "kafka_producer")
add_executable(${PRODUCER_NAME}
	inc/kafka_producer.h
	src/kafka_producer.cpp

	main/main_01_01.cpp
)
target_link_libraries(${PRODUCER_NAME} ${LIBRDKAFKA_LIB_NAME})
target_include_directories(${PRODUCER_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})

#------------------------------------------------------------------------------
# add the librdkafka api consumer
#------------------------------------------------------------------------------
SET(CONSUMER_NAME "kafka_consumer")
add_executable(${CONSUMER_NAME}
	inc/kafka_consumer.h
	src/kafka_consumer.cpp

	main/main_02_01.cpp
)
target_link_libraries(${CONSUMER_NAME} ${LIBRDKAFKA_LIB_NAME})
target_include_directories(${CONSUMER_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})


#------------------------------------------------------------------------------
# add g_sender
#------------------------------------------------------------------------------
SET(G_SENDER_NAME "g_sender")
add_executable(${G_SENDER_NAME}

	inc/in_file_writer.h

	inc/in_kafka_writer.h
	src/in_kafka_writer.cpp

	inc/kafka_producer.h
	src/kafka_producer.cpp

	inc/application_g.h

	main/main_g_sender.cpp
)
target_link_libraries(${G_SENDER_NAME} ${LIBRDKAFKA_LIB_NAME})
target_include_directories(${G_SENDER_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})

#------------------------------------------------------------------------------
# add c_receiver
#------------------------------------------------------------------------------
SET(C_RECEIVER_NAME "c_receiver")
add_executable(${C_RECEIVER_NAME}

	inc/th_s_queue.h
	inc/background_worker.h
	inc/collable_class.h

	inc/from_file_reader.h

	inc/from_kafka_reader.h
	src/from_kafka_reader.cpp

	inc/kafka_consumer.h
	src/kafka_consumer.cpp

	inc/application_c.h

	main/main_c_receiver.cpp
)
target_link_libraries(${C_RECEIVER_NAME} ${LIBRDKAFKA_LIB_NAME})
target_include_directories(${C_RECEIVER_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})

