cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME microservices)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 20)


#! By default - build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()


##########################################################
# Project files, packages, libraries and so on
##########################################################

add_executable(facade-service facade_service/src/facade_service.cpp)
target_include_directories(facade-service PRIVATE include)

add_executable(logging-service logging_service/src/logging_service.cpp)
target_include_directories(logging-service PRIVATE include)

add_executable(messages-service messages_service/src/messages_service.cpp)
target_include_directories(messages-service PRIVATE include)

add_executable(get-example test_programs/send_get_request.cpp)
add_executable(post-example test_programs/send_post_request.cpp)
target_include_directories(get-example PRIVATE include)
target_include_directories(post-example PRIVATE include)


IF(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(facade-service PRIVATE ENABLE_DEBUG_INFO)
	target_compile_definitions(logging-service PRIVATE ENABLE_DEBUG_INFO)
	target_compile_definitions(messages-service PRIVATE ENABLE_DEBUG_INFO)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

set(JSONCPP_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/libs/jsoncpp/include)
set(JSONCPP_LIB_PATH ${PROJECT_SOURCE_DIR}/libs/jsoncpp/build/lib/libjsoncpp.so)

target_include_directories(facade-service PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_include_directories(logging-service PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_include_directories(messages-service PRIVATE ${JSONCPP_INCLUDE_DIRS})

target_link_libraries(facade-service ${JSONCPP_LIB_PATH} -pthread)
target_link_libraries(logging-service ${JSONCPP_LIB_PATH} -pthread)
target_link_libraries(messages-service ${JSONCPP_LIB_PATH} -pthread)

add_compile_definitions(FACADE_SERVICE_LOGS_ENABLED)
add_compile_definitions(LOGGING_SERVICE_LOGS_ENABLED)
add_compile_definitions(MESSAGE_SERVICE_LOGS_ENABLED)

find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(logging-service ${Boost_LIBRARIES})
endif()