cmake_minimum_required(VERSION 2.8.9)
project(openicpbr)

set(CMAKE_MODULE_PATH cmake/modules/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall -Wextra -pedantic -Wshadow")
set(BUNDLE_EXTENSION ".app")

include_directories(include ${OPENSSL_INCLUDE_DIR})
find_package(wxWidgets REQUIRED COMPONENTS net core base adv xrc)
# find_package(openssl REQUIRED NAMES pem.h)
include(${wxWidgets_USE_FILE})
file(GLOB SOURCES "src/*.cpp")
add_executable(openicp ${SOURCES})
target_link_libraries(openicp ${wxWidgets_LIBRARIES})
target_link_libraries(openicp crypto)
set_target_properties(openicp PROPERTIES BUNDLE TRUE)


add_custom_target(run
    COMMAND openicp
    DEPENDS openicp
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR/bin}
)
