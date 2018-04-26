cmake_minimum_required(VERSION 2.8.9)
project(openicpbr)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include_directories(include)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
file(GLOB SOURCES "src/*.cpp")
add_executable(openicp ${SOURCES})
target_link_libraries(openicp ${wxWidgets_LIBRARIES})