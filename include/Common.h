#pragma once
#include "Version.h"


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
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::cout;
using std::endl;

typedef unsigned long x509_hash;