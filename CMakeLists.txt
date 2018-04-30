cmake_minimum_required(VERSION 3.10)
project(openicpbr)

# Set some basic variables
set(CMAKE_MODULE_PATH cmake/modules/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall -Wextra -pedantic -Wshadow")
set(BUNDLE_EXTENSION ".app")

# Get OpenSSL
find_package(openssl REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
	if (APPLE)
		message(STATUS "On macOS, use: cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl .")
	endif()
	message(FATAL "OpenSSL was not found")
endif()

# Get wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base adv xrc)
include(${wxWidgets_USE_FILE})

# Configure our desired binary 
file(GLOB SOURCES "src/*.cpp")
include_directories(include)
add_executable(openicp ${SOURCES})
target_link_libraries(openicp ${wxWidgets_LIBRARIES})
target_link_libraries(openicp crypto)
set_target_properties(openicp PROPERTIES BUNDLE TRUE)

# Add non-code install_files
file(COPY src/ui.xrc DESTINATION ${CMAKE_BINARY_DIR})

# Add `make run`
add_custom_target(run
    COMMAND openicp
    DEPENDS openicp
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR/bin}
)
