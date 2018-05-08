#pragma once

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define OK 0

#define NOTEBOOK_HEADER_HEIGHT 70
#define MIN_NOTEBOOK_WIDTH 700
#define MIN_NOTEBOOK_HEIGHT 200

#define SHA256_RAW_LEN 32

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/xrc/xmlres.h"

using std::vector;
using std::cout;
using std::endl;

typedef unsigned long x509_hash;