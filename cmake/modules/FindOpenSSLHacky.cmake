# FindOpenSSL (HACKED)
# -----------
#
# Find the OpenSSL encryption library.
#
# Optional COMPONENTS
# ^^^^^^^^^^^^^^^^^^^
#
# This module supports two optional COMPONENTS: ``Crypto`` and ``SSL``.  Both
# components have associated imported targets, as described below.
#
# Imported Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :prop_tgt:`IMPORTED` targets:
#
# ``OpenSSL::SSL``
#   The OpenSSL ``ssl`` library, if found.
# ``OpenSSL::Crypto``
#   The OpenSSL ``crypto`` library, if found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module will set the following variables in your project:
#
# ``OPENSSL_FOUND``
#   System has the OpenSSL library. If no components are requested it only
#   requires the crypto library.
# ``OPENSSL_INCLUDE_DIR``
#   The OpenSSL include directory.
# ``OPENSSL_CRYPTO_LIBRARY``
#   The OpenSSL crypto library.
# ``OPENSSL_SSL_LIBRARY``
#   The OpenSSL SSL library.
# ``OPENSSL_LIBRARIES``
#   All OpenSSL libraries.
# ``OPENSSL_VERSION``
#   This is set to ``$major.$minor.$revision$patch`` (e.g. ``0.9.8s``).
#
# Hints
# ^^^^^
#
# Set ``OPENSSL_ROOT_DIR`` to the root directory of an OpenSSL installation.
# Set ``OPENSSL_USE_STATIC_LIBS`` to ``TRUE`` to look for static libraries.

function(from_hex HEX DEC)
  string(TOUPPER "${HEX}" HEX)
  set(_res 0)
  string(LENGTH "${HEX}" _strlen)

  while (_strlen GREATER 0)
    math(EXPR _res "${_res} * 16")
    string(SUBSTRING "${HEX}" 0 1 NIBBLE)
    string(SUBSTRING "${HEX}" 1 -1 HEX)
    if (NIBBLE STREQUAL "A")
      math(EXPR _res "${_res} + 10")
    elseif (NIBBLE STREQUAL "B")
      math(EXPR _res "${_res} + 11")
    elseif (NIBBLE STREQUAL "C")
      math(EXPR _res "${_res} + 12")
    elseif (NIBBLE STREQUAL "D")
      math(EXPR _res "${_res} + 13")
    elseif (NIBBLE STREQUAL "E")
      math(EXPR _res "${_res} + 14")
    elseif (NIBBLE STREQUAL "F")
      math(EXPR _res "${_res} + 15")
    else()
      math(EXPR _res "${_res} + ${NIBBLE}")
    endif()

    string(LENGTH "${HEX}" _strlen)
  endwhile()

  set(${DEC} ${_res} PARENT_SCOPE)
endfunction()

set(OPENSSL_LIB_EXTENSION CMAKE_FIND_LIBRARY_SUFFIXES)
if(OPENSSL_USE_STATIC_LIBS)
	if(WIN32)
		set(OPENSSL_LIB_EXTENSION .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
	else()
		set(OPENSSL_LIB_EXTENSION .a )
	endif()
endif()

if(MINGW)
	if(NOT DEFINED OPENSSL_ROOT_DIR)
		if(EXISTS "../openssl-1.1.0h/dist/")
			set(OPENSSL_ROOT_DIR "../openssl-1.1.0h/dist/")
		elseif(EXISTS "../openssl/dist/")
			set(OPENSSL_ROOT_DIR "../openssl/dist/")
		elseif(EXISTS "openssl-1.1.0h/dist/")
			set(OPENSSL_ROOT_DIR "openssl-1.1.0h/dist/")
		elseif(EXISTS "openssl/dist/")
			set(OPENSSL_ROOT_DIR "openssl/dist/")
		else()
			message(STATUS "You must set OPENSSL_ROOT_DIR")
		endif()
	else()
		set(OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR})
	endif()
elseif (APPLE)
	if (OPENSSL_USE_STATIC_LIBS)
		set(OPENSSL_LIB_EXTENSION ".a")
	endif()
	message(STATUS "Assuming you installed OpenSSL 1.1 via Homebrew")
	set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
elseif (UNIX)
	if (OPENSSL_USE_STATIC_LIBS)
		set(OPENSSL_LIB_EXTENSION ".a")
	endif()
	message(STATUS "Assuming you installed OpenSSL 1.1 on /usr directly")
	set(OPENSSL_ROOT_DIR "/usr")
endif()

# Adjust some directories
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIBRARIES_DIR "${OPENSSL_ROOT_DIR}/lib")

# Get version number
if(EXISTS "${OPENSSL_INCLUDE_DIR}/openssl/opensslv.h")
	file(STRINGS "${OPENSSL_INCLUDE_DIR}/openssl/opensslv.h" openssl_version_str
	REGEX "^#[\t ]*define[\t ]+OPENSSL_VERSION_NUMBER[\t ]+0x([0-9a-fA-F])+.*")

	if(openssl_version_str)
		# The version number is encoded as 0xMNNFFPPS: major minor fix patch status
		# The status gives if this is a developer or prerelease and is ignored here.
		# Major, minor, and fix directly translate into the version numbers shown in
		# the string. The patch field translates to the single character suffix that
		# indicates the bug fix state, which 00 -> nothing, 01 -> a, 02 -> b and so
		# on.
		string(REGEX REPLACE "^.*OPENSSL_VERSION_NUMBER[\t ]+0x([0-9a-fA-F])([0-9a-fA-F][0-9a-fA-F])([0-9a-fA-F][0-9a-fA-F])([0-9a-fA-F][0-9a-fA-F])([0-9a-fA-F]).*$"
		"\\1;\\2;\\3;\\4;\\5" OPENSSL_VERSION_LIST "${openssl_version_str}")
		list(GET OPENSSL_VERSION_LIST 0 OPENSSL_VERSION_MAJOR)
		list(GET OPENSSL_VERSION_LIST 1 OPENSSL_VERSION_MINOR)
		from_hex("${OPENSSL_VERSION_MINOR}" OPENSSL_VERSION_MINOR)
		list(GET OPENSSL_VERSION_LIST 2 OPENSSL_VERSION_FIX)
		from_hex("${OPENSSL_VERSION_FIX}" OPENSSL_VERSION_FIX)
		list(GET OPENSSL_VERSION_LIST 3 OPENSSL_VERSION_PATCH)

		if (NOT OPENSSL_VERSION_PATCH STREQUAL "00")
			from_hex("${OPENSSL_VERSION_PATCH}" _tmp)
			# 96 is the ASCII code of 'a' minus 1
			math(EXPR OPENSSL_VERSION_PATCH_ASCII "${_tmp} + 96")
			unset(_tmp)
			# Once anyone knows how OpenSSL would call the patch versions beyond 'z'
			# this should be updated to handle that, too. This has not happened yet
			# so it is simply ignored here for now.
			string(ASCII "${OPENSSL_VERSION_PATCH_ASCII}" OPENSSL_VERSION_PATCH_STRING)
		endif ()

		set(OPENSSL_VERSION "${OPENSSL_VERSION_MAJOR}.${OPENSSL_VERSION_MINOR}.${OPENSSL_VERSION_FIX}${OPENSSL_VERSION_PATCH_STRING}")
	endif ()
endif ()

set(OPENSSL_SSL_LIBRARY "${OPENSSL_LIBRARIES_DIR}/libssl${OPENSSL_LIB_EXTENSION}")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_LIBRARIES_DIR}/libcrypto${OPENSSL_LIB_EXTENSION}")
set(OPENSSL_SSL_LIBRARIES ${OPENSSL_SSL_LIBRARY})
set(OPENSSL_CRYPTO_LIBRARIES ${OPENSSL_CRYPTO_LIBRARY})
set(OPENSSL_LIBRARIES ${OPENSSL_SSL_LIBRARY} " " ${OPENSSL_CRYPTO_LIBRARY})

if(DEFINED OPENSSL_VERSION AND EXISTS ${OPENSSL_SSL_LIBRARY} AND EXISTS ${OPENSSL_CRYPTO_LIBRARY})
	set(OPENSSL_FOUND true)
endif()