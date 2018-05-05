cmake_minimum_required(VERSION 3.10)
project(openicpbr)

# Set some basic variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall -Wextra -pedantic -Wshadow -g")

# macOS stuff
if (APPLE)
	set(BUNDLE_EXTENSION ".app")
endif()

# Get OpenSSL
find_package(OpenSSL 1.0 REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION} on ${OPENSSL_INCLUDE_DIR}")
    if (NOT (${OPENSSL_VERSION_MAJOR} EQUAL 1 AND ${OPENSSL_VERSION_MINOR} EQUAL 0))
    	message(FATAL_ERROR "Required OpenSSL version 1.0, got ${OPENSSL_VERSION}")
    endif ()
else()
	message(FATAL_ERROR "OpenSSL 1.0 was not found")
endif()

# Get wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base adv xrc)
include(${wxWidgets_USE_FILE})

# Configure our desired binary 
file(GLOB SOURCES "src/*.cpp")
include_directories(include)
add_executable(openicp ${SOURCES})
target_link_libraries(openicp ${wxWidgets_LIBRARIES})
target_link_libraries(openicp ${OPENSSL_CRYPTO_LIBRARIES})
set_target_properties(openicp PROPERTIES BUNDLE TRUE)

# Add non-code install_files
file(COPY src/ui.xrc DESTINATION ${CMAKE_BINARY_DIR})

# Add `make run`
add_custom_target(run
    COMMAND openicp
    DEPENDS openicp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
