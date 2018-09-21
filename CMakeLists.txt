cmake_minimum_required(VERSION 3.6)
project(openicpbr CXX)

# Set some basic variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_PREFIX /usr)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall -Wextra -pedantic -Wshadow -g -fPIC -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/src/,,$(abspath $<))\"'")

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
message(STATUS "Looking for wxWidgets...")
find_package(wxWidgets REQUIRED COMPONENTS net core base adv xrc)
message(STATUS "Using wxWidgets ${wxWidgets_VERSION} on ${wxWidgets_USE_FILE}")
include(${wxWidgets_USE_FILE})
message(STATUS "Using wxWidgets ${wxWidgets_VERSION} on ${wxWidgets_INCLUDE_DIRS}")

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
target_link_libraries(openicp ICP++)
target_link_libraries(openicp ${wxWidgets_LIBRARIES})
target_link_libraries(openicp ICP)
if (MINGW)
	target_link_libraries(openicp "ws2_32")
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
endif()
