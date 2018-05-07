cmake_minimum_required(VERSION 3.10)
project(openicpbr CXX)

# Set some basic variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall -Wextra -pedantic -Wshadow -g")
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

# macOS stuff
if (APPLE)
	set(BUNDLE_EXTENSION ".app")
    message(STATUS "Assuming you installed OpenSSL 1.1 via Homebrew")
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
endif()

# Get OpenSSL
find_package(OpenSSL 1.1 REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION} on ${OPENSSL_INCLUDE_DIR}")
    if (NOT (${OPENSSL_VERSION_MAJOR} EQUAL 1 AND ${OPENSSL_VERSION_MINOR} EQUAL 1))
    	message(FATAL_ERROR "Required OpenSSL version 1.1, apparently got ${OPENSSL_VERSION}")
    endif ()
else()
	message(FATAL_ERROR "OpenSSL 1.1 was not found")
endif()

# Get wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base adv xrc)
include(${wxWidgets_USE_FILE})

file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ICPApp.cpp)
include_directories(${COMMON_INCLUDES})
add_library(openicp_no_main_lib STATIC ${SOURCES})

# Configure our desired binary
add_executable(openicp ${CMAKE_CURRENT_SOURCE_DIR}/src/ICPApp.cpp)
target_link_libraries(openicp openicp_no_main_lib)
target_link_libraries(openicp ${wxWidgets_LIBRARIES})
target_link_libraries(openicp ${OPENSSL_CRYPTO_LIBRARIES})
set_target_properties(openicp PROPERTIES BUNDLE TRUE)

# This will help with testing

# Add non-code install_files
file(COPY src/ui.xrc DESTINATION ${CMAKE_BINARY_DIR})

# Test stuff
find_package(GTest)
if (GTEST_FOUND)
    enable_testing()
    include_directories(${COMMON_INCLUDES})
    file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
    add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} --output-on-failure)
    add_custom_target(build_and_test_verbose ${CMAKE_CTEST_COMMAND} -V)
    foreach(_test_file ${TEST_SRC_FILES})
        get_filename_component(_test_name ${_test_file} NAME_WE)
        add_executable(${_test_name} ${_test_file})
        target_link_libraries(${_test_name} gtest gtest_main openicp_no_main_lib ${CMAKE_THREAD_LIBS_INIT} ${wxWidgets_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARIES})
        add_test(${_test_name} bin/${_test_name})
        set_tests_properties(${_test_name} PROPERTIES TIMEOUT 5)
        add_dependencies(build_and_test ${_test_name})
        add_dependencies(build_and_test_verbose ${_test_name})
    endforeach()
else ()
    message(STATUS "Could NOT find Google Test, testing will be disabled")
endif()

# Add `make run`
add_custom_target(run
    COMMAND openicp
    DEPENDS openicp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
