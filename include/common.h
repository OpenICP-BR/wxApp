#pragma once

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define NOTEBOOK_HEADER_HEIGHT 70
#define MIN_NOTEBOOK_WIDTH 700
#define MIN_NOTEBOOK_HEIGHT 200

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/xrc/xmlres.h"