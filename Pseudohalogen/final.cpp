/*
MIT License

Copyright (c) 2024 UltimateQuack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
        Sleep(100/time);

	    CreateTrayIcon2();
	    ShowTrayIconBalloon2(L"RIP BOZO", L"RIP BOZO", 1, NIIF_WARNING);
        time *= 1.1;
        Sleep(100/time);

        CreateTrayIcon2();
	    ShowTrayIconBalloon2(L"RIP BOZO", L"RIP BOZO", 1, NIIF_ERROR);
        time *= 1.1;
        Sleep(100/time);

	    CreateTrayIcon2();
	    ShowTrayIconBalloon2(L"RIP BOZO", L"RIP BOZO", 1, NIIF_NOSOUND);
        time *= 1.1;
        Sleep(100/time);

        
    }
}