cmake_minimum_required(VERSION 2.8)
project(VoIP)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
endif()

include_directories("src")

### SIP library ###
message("Creating SIP library..")
file(GLOB SIP_SOURCES "src/sip/*")
add_library(sip STATIC ${SIP_SOURCES})

### SIP test ###
message("Creating SIP test executable..")
file(GLOB SIP_TEST_SOURCES "test/sip/*")
add_executable(siptest ${SIP_TEST_SOURCES})
target_link_libraries(siptest sip)

add_test(SIP_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/siptest)