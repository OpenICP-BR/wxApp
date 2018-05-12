cmake_minimum_required(VERSION 3.6)
project(openicpbr CXX)

# Set some basic variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall -Wextra -pedantic -Wshadow -g")
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(USE_STATIC_WXWIDGETS false)
set(APP_VERSION "0.0.1")

add_definitions(-DUSE_FAKE_ICP_ROOT)

# Get libraries
set(OPENSSL_ROOT_DIR "${CMAKE_SOURCE_DIR}/openssl-1.1.0h/dist/")
set(OPENSSL_CRYPTO_LIBRARIES "${OPENSSL_ROOT_DIR}/lib/libcrypto.a")
include_directories("${OPENSSL_ROOT_DIR}/include/")

message(STATUS "Looking for wxWidgets...")
find_package(wxWidgets REQUIRED COMPONENTS net core base adv xrc)
message(STATUS "Using wxWidgets ${wxWidgets_VERSION} on ${wxWidgets_USE_FILE}")
include(${wxWidgets_USE_FILE})

# Set sources and set our "library" (this is to avoid recompilation for testing)
file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ICPApp.cpp)
include_directories(${COMMON_INCLUDES})
add_library(openicp_no_main_lib STATIC ${SOURCES})
target_link_libraries(openicp_no_main_lib ${wxWidgets_LIBRARIES})
target_link_libraries(openicp_no_main_lib ${OPENSSL_CRYPTO_LIBRARIES})

# Configure our desired binary
if (APPLE)
	set(MACOSX_BUNDLE_BUNDLE_NAME "OpenICP-BR")
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.github.gjvnq.openicp_br")
	set(MACOSX_BUNDLE_ICON_FILE logo.icns)
	set(MACOSX_BUNDLE_INFO_PLIST res/Info.plist)
	set(MACOSX_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/openicp.app/Contents/")
	add_executable(openicp MACOSX_BUNDLE ${CMAKE_CURRENT_SOURCE_DIR}/src/ICPApp.cpp)
else()
	add_executable(openicp ${CMAKE_CURRENT_SOURCE_DIR}/src/ICPApp.cpp)
endif()
target_link_libraries(openicp openicp_no_main_lib)

# Add non-code install_files
file(GLOB CAS_CERTS "res/icp-chain/*.crt")
if (APPLE)
	file(COPY res/logo.icns res/ui.xrc DESTINATION "${MACOSX_PACKAGE_LOCATION}/Resources")
	file(COPY /usr/lib/libc++.1.dylib /usr/local/opt/wxmac/lib/libwx_osx_cocoau_xrc-3.0.dylib /usr/local/opt/wxmac/lib/libwx_osx_cocoau_adv-3.0.dylib /usr/local/opt/wxmac/lib/libwx_baseu-3.0.dylib /usr/local/opt/wxmac/lib/libwx_osx_cocoau_core-3.0.dylib /usr/local/opt/wxmac/lib/libwx_baseu_net-3.0.dylib DESTINATION "${MACOSX_PACKAGE_LOCATION}/MacOS")
	file(MAKE_DIRECTORY "${MACOSX_PACKAGE_LOCATION}/Resources/CAs")
	file(COPY ${CAS_CERTS} DESTINATION "${MACOSX_PACKAGE_LOCATION}/Resources/CAs")
	# Fix all the dylibs
	add_custom_command(TARGET openicp POST_BUILD
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/fix_osx_dylibs.sh
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Fixing dylibs for osx bundle")
	# Allow us to easily generate a .dmg file for distribution
	add_custom_target(dmg
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/make_dmg.sh
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	# Add `make run`
	add_custom_target(run
		COMMAND "${MACOSX_PACKAGE_LOCATION}/MacOS/openicp"
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
else()
	file(COPY res/ui.xrc DESTINATION ${CMAKE_BINARY_DIR})
	file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/cas")
	file(COPY ${CAS_CERTS} DESTINATION "${CMAKE_BINARY_DIR}/cas")
	# Add `make run`
	add_custom_target(run
		COMMAND openicp
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
endif()

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

