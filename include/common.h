#pragma once

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define NOTEBOOK_HEADER_HEIGHT 70
#define MIN_NOTEBOOK_WIDTH 700
#define MIN_NOTEBOOK_HEIGHT 200

#define ICP_ROOT_V1_SHA1 "70:5D:2B:45:65:C7:04:7A:54:06:94:A7:9A:F7:AB:B8:42:BD:C1:61"
#define ICP_ROOT_V1_LINK "8eee9575.0"
#define ICP_ROOT_V2_SHA1 "A9:82:2E:6C:69:33:C6:3C:14:8C:2D:CA:A4:4A:5C:F1:AA:D2:C4:2E"
#define ICP_ROOT_V2_LINK "1e54e6fa.0"
#define ICP_ROOT_V5_SHA1 "4A:CA:DA:B1:4B:74:BF:4F:BA:7B:AC:E6:4B:91:80:1C:44:B8:CC:66"
#define ICP_ROOT_V5_LINK "a2502f15.0"
#define FAKE_ICP_ROOT_SHA1 "E9:D2:24:55:45:0B:93:AB:7B:88:E0:83:2A:33:5B:ED:0C:03:36:99"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/xrc/xmlres.h"