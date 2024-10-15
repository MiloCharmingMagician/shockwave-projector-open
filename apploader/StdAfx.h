// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H)
#define AFX_STDAFX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "f_in_box/include/f_in_box.h"

#ifndef DEF_USE_STATIC_LIB
#   ifdef _WIN64
#       pragma comment(lib, "f_in_box/lib/f_in_box64.lib")
#   else
#       pragma comment(lib, "f_in_box/lib/f_in_box.lib")
#   endif // _WIN64
#else
#   ifdef _WIN64
#       pragma comment(lib, "f_in_box/static_lib/f_in_box_staticlib64.lib")
#   else
#       pragma comment(lib, "f_in_box/static_lib/f_in_box_staticlib.lib")
#   endif // _WIN64
#endif // DEF_USE_STATIC_LIB

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H)
