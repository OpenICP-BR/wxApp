#pragma once
#include "Version.h"

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

using std::vector;
using std::map;
using std::cout;
using std::endl;
using namespace ICP;
