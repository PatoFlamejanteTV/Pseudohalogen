//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Pseudohalogen.rc
//

#include "stuff.h"
#include <windows.h>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

#define IDI_ICON1                       101

// https://stackoverflow.com/a/72448544/26411616
#define IDI_BATTERY_IMAGE               102

BOOL CreateTrayIcon();
BOOL ShowTrayIconBalloon(LPCTSTR pszTitle, LPCTSTR pszText, UINT unTimeout, DWORD dwInfoFlags);

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        102
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
