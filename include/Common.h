#pragma once
#define UNICODE
#define _UNICODE
#include "Version.h"

// See: https://stackoverflow.com/questions/24119388/openssl-fails-to-build-with-mingw-does-not-give-a-valid-preprocessing-token?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
#if defined(OPENSSL_SYS_WINDOWS)
	#include <windows.h>
	#undef X509_NAME
	#undef X509_EXTENSIONS
	#undef X509_CERT_PAIR
	#undef PKCS7_ISSUER_AND_SERIAL
	#undef OCSP_REQUEST
	#undef OCSP_RESPONSE
#endif

#ifndef __FILENAME__
	#define __FILENAME__ __FILE__
#endif
#define RETURN_AND_PRINT(x) cout << __FILENAME__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << " -> " << #x << endl; return x

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define OK 0

#define NOTEBOOK_HEADER_HEIGHT 70
#define MIN_NOTEBOOK_WIDTH 700
#define MIN_NOTEBOOK_HEIGHT 200

#define SHA256_RAW_LEN 32

#define ERR_NOT_IMPLEMENTED -1
#define ERR_UNKOWN -2

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/xrc/xmlres.h"
#include <libICP++.h>
#include <vector>
#include <string>
#include <map>

#ifdef __WIN32__
	#include <openssl/bio.h>
#endif

using std::vector;
using std::map;
using std::cout;
using std::endl;

typedef unsigned long x509_hash;