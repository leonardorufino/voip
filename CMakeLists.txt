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

### Util library ###
message("Creating util library..")
file(GLOB UTIL_SOURCES "src/util/*")
add_library(util STATIC ${UTIL_SOURCES})
if (WIN32)
    target_link_libraries(util Ws2_32.lib Iphlpapi.lib)
else ()
    target_link_libraries(util rt pthread)
endif()

### SDP library ###
message("Creating SDP library..")
file(GLOB SDP_SOURCES "src/sdp/*")
add_library(sdp STATIC ${SDP_SOURCES})
target_link_libraries(sdp util)

### SIP library ###
message("Creating SIP library..")
file(GLOB SIP_SOURCES "src/sip/*")
add_library(sip STATIC ${SIP_SOURCES})
target_link_libraries(sip sdp util)

### Util test ###
message("Creating util test executable..")
file(GLOB UTIL_TEST_SOURCES "test/util/*")
add_executable(util_test ${UTIL_TEST_SOURCES})
target_link_libraries(util_test util)

### SDP test ###
message("Creating SDP test executable..")
file(GLOB SDP_TEST_SOURCES "test/sdp/*")
add_executable(sdp_test ${SDP_TEST_SOURCES})
target_link_libraries(sdp_test sdp)

### SIP test ###
message("Creating SIP test executable..")
file(GLOB SIP_TEST_SOURCES "test/sip/*")
add_executable(sip_test ${SIP_TEST_SOURCES})
target_link_libraries(sip_test sip)

enable_testing()
add_test(Util_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/util_test)
add_test(SDP_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sdp_test)
add_test(SIP_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sip_test)
