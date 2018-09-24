cmake_minimum_required(VERSION 3.6)
project(openicpbr CXX)

# Set some basic variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_PREFIX /usr)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

message(STATUS "CXX_FLAGS=${CXX_FLAGS}")
if (CXX_FLAGS)
	set(CMAKE_CXX_FLAGS "${CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/src/,,$(abspath $<))\"'")
	message(STATUS "Using user CXX_FLAGS...")
else()
	set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -pedantic -Wall -Wextra -Wundef -Wshadow -Wunreachable-code -Wfloat-equal -Werror  -g -fPIC -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/src/,,$(abspath $<))\"'")
	message(STATUS "Using default CXX_FLAGS...")
endif()
message(STATUS "CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

# Set some paths for our custom tools
set(TOOL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools/")
if (APPLE)
	set(TOOL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools/osx/")
elseif(MINGW OR WIN32)
	set(TOOL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools/win/")
elseif(UNIX)
	set(TOOL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools/linux/")
endif()

# Get wxWidgets
set(wxWidgets_USE_UNICODE true)
set(wxWidgets_USE_STATIC false)
set(wxWidgets_USE_DEBUG false)
if (MINGW)
	set(wxWidgets_CONFIGURATION mswu)
endif()
message(STATUS "Looking for wxWidgets...")
SET(wxWidgets_USE_LIBS base core adv xrc)
find_package(wxWidgets REQUIRED net core base adv xrc)
message(STATUS "Using wxWidgets ${wxWidgets_VERSION} on ${wxWidgets_USE_FILE}")
include(${wxWidgets_USE_FILE})
message(STATUS "Using wxWidgets ${wxWidgets_VERSION} on ${wxWidgets_INCLUDE_DIRS}")
message(STATUS "Using wxWidgets libraries ${wxWidgets_LIBRARIES}")

file(GLOB SOURCES "src/*.cpp")
include_directories(${COMMON_INCLUDES})
# Configure our desired binary
if (APPLE)
	set(MACOSX_BUNDLE_BUNDLE_NAME "OpenICP-BR")
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.github.gjvnq.openicp_br")
	set(MACOSX_BUNDLE_ICON_FILE logo.icns)
	set(MACOSX_BUNDLE_INFO_PLIST res/Info.plist)
	set(MACOSX_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/openicp.app/Contents/")
	add_executable(openicp MACOSX_BUNDLE "${SOURCES}")
elseif(MINGW)
	set(CMAKE_RC_COMPILER_INIT windres)
	ENABLE_LANGUAGE(RC)
	SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> --use-temp-file <FLAGS> -O coff <DEFINES> -I <INCLUDES> -i <SOURCE> -o <OBJECT>")
	add_definitions(-DwxUSE_NO_MANIFEST=1)
	add_executable(openicp "${SOURCES}" "${CMAKE_CURRENT_SOURCE_DIR}/res/win-res.rc")
else()
	add_executable(openicp "${SOURCES}")
endif()
add_library(ICP++ STATIC IMPORTED)
set_target_properties(ICP++ PROPERTIES
	IMPORTED_LOCATION "$ENV{GOPATH}/src/github.com/OpenICP-BR/libICP/c-wrapper/libICP++.a"
	INTERFACE_INCLUDE_DIRECTORIES "$ENV{GOPATH}/src/github.com/OpenICP-BR/libICP/c-wrapper/"
)
target_link_libraries(openicp ICP++)
target_link_libraries(openicp ${wxWidgets_LIBRARIES})
if (MINGW)
	#link_directories("/c/wxWidgets-3.0.4/lib/gcc_dll/")
	target_link_libraries(openicp "ws2_32")
	add_library(wxmsw30u_xrc STATIC IMPORTED)
	set_target_properties(wxmsw30u_xrc PROPERTIES
		IMPORTED_LOCATION "/c/wxWidgets-3.0.4/lib/gcc_dll/libwxmsw30u_xrc.a"
	)
	target_link_libraries(openicp "-LC:/wxWidgets-3.0.4/lib/gcc_dll/ -lwxmsw30u_xrc -lwxmsw30u_adv -lwxmsw30u_core -lwxbase30u")
endif()
if (APPLE)
	target_link_libraries(openicp "-framework CoreFoundation -framework Security")
endif()


# Add non-code install_files
if(MINGW)
	add_custom_command(
		TARGET openicp
		POST_BUILD
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/res/"
		COMMAND ${TOOL_DIR}/copy_dll.sh "${CMAKE_BINARY_DIR}/"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	# Add `make run`
	add_custom_target(run
		# This below line ensures we always run with the most up to date res files
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/res/"
		COMMAND ${TOOL_DIR}/copy_dll.sh "${CMAKE_BINARY_DIR}/"
		COMMAND ${CMAKE_BINARY_DIR}/openicp.exe
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
	# Allow us to easily generate a .exe installer for distribution
	add_custom_target(installer
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/res/"
		COMMAND ${TOOL_DIR}/copy_dll.sh "${CMAKE_BINARY_DIR}/"
		COMMAND makensis "${CMAKE_CURRENT_SOURCE_DIR}/res/installer.nsi"
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
elseif(APPLE)
	add_custom_command(
		TARGET openicp
		POST_BUILD
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${MACOSX_PACKAGE_LOCATION}/Resources"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	# Allow us to easily generate a .dmg file for distribution
	add_custom_target(dmg
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${MACOSX_PACKAGE_LOCATION}/Resources"
		COMMAND ${TOOL_DIR}/fix_dylibs.sh
		COMMAND ${TOOL_DIR}/make_dmg.sh
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	# Add `make run`
	add_custom_target(run
		# This below line ensures we always run with the most up to date res files
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${MACOSX_PACKAGE_LOCATION}/Resources"
		COMMAND "${MACOSX_PACKAGE_LOCATION}/MacOS/openicp"
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
	# Add `make run-valgrind`
	add_custom_target(run-valgrind
		# This below line ensures we always run with the most up to date res files
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${MACOSX_PACKAGE_LOCATION}/Resources"
		COMMAND valgrind -v --leak-check=full "${MACOSX_PACKAGE_LOCATION}/MacOS/openicp"
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
elseif(UNIX)
	add_custom_command(
		TARGET openicp
		POST_BUILD
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/res/"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	install(TARGETS openicp RUNTIME DESTINATION bin/)
	install(DIRECTORY "${CMAKE_BINARY_DIR}/res/CAs/" DESTINATION share/openicpbr/CAs)
	install(FILES "${CMAKE_SOURCE_DIR}/res/ui.xrc" DESTINATION share/openicpbr/)
	install(FILES "${CMAKE_SOURCE_DIR}/res/github.gjvnq.openicpbr.desktop" DESTINATION share/applications/)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo.svg" DESTINATION share/icons/hicolor/scalable/apps RENAME github.gjvnq.openicpbr.svg)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo-16.png" DESTINATION share/icons/hicolor/16x16/apps RENAME github.gjvnq.openicpbr.png)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo-32.png" DESTINATION share/icons/hicolor/32x32/apps RENAME github.gjvnq.openicpbr.png)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo-48.png" DESTINATION share/icons/hicolor/48x48/apps RENAME github.gjvnq.openicpbr.png)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo-64.png" DESTINATION share/icons/hicolor/64x64/apps RENAME github.gjvnq.openicpbr.png)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo-128.png" DESTINATION share/icons/hicolor/128x128/apps RENAME github.gjvnq.openicpbr.png)
	install(FILES "${CMAKE_SOURCE_DIR}/res/logo-256.png" DESTINATION share/icons/hicolor/256x256/apps RENAME github.gjvnq.openicpbr.png)
	# Generate .tar.gz distribution files easily
	add_custom_target(tgz
		COMMAND make install DESTDIR=${CMAKE_BINARY_DIR}/install/
		COMMAND ${TOOL_DIR}/make_tgz.sh "${CMAKE_BINARY_DIR}/install/" "${CMAKE_BINARY_DIR}"
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	# Add `make run`
	add_custom_target(run
		# This below line ensures we always run with the most up to date res files
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/res/"
		COMMAND ${CMAKE_BINARY_DIR}/openicp
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
	# Add `make run-valgrind`
	add_custom_target(run-valgrind
		# This below line ensures we always run with the most up to date res files
		COMMAND ${TOOL_DIR}/copy_res.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/res/"
		COMMAND valgrind -v --leak-check=full ${CMAKE_BINARY_DIR}/openicp
		DEPENDS openicp
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)
endif()
