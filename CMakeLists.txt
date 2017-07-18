cmake_minimum_required(VERSION 2.8)
project(VoIP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
endif()

include_directories("src")

### Common library ###
message("Creating common library..")
file(GLOB COMMON_SOURCES "src/common/*")
add_library(common STATIC ${COMMON_SOURCES})
if (WIN32)
    target_link_libraries(common Ws2_32.lib Iphlpapi.lib)
else ()
    target_link_libraries(common rt)
endif()

### SIP library ###
message("Creating SIP library..")
file(GLOB SIP_SOURCES "src/sip/*")
add_library(sip STATIC ${SIP_SOURCES})

### Common test ###
message("Creating common test executable..")
file(GLOB COMMON_TEST_SOURCES "test/common/*")
add_executable(common_test ${COMMON_TEST_SOURCES})
target_link_libraries(common_test common)

### SIP test ###
message("Creating SIP test executable..")
file(GLOB SIP_TEST_SOURCES "test/sip/*")
add_executable(sip_test ${SIP_TEST_SOURCES})
target_link_libraries(sip_test sip common)

enable_testing()
add_test(Common_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/common_test)
add_test(SIP_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sip_test)