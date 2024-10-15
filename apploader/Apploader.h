// Apploader.h : main header file for the Flash Projector application
//

#if !defined(AFX_APPLOADER_H)
#define AFX_APPLOADER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// Apploader:
//

class Apploader : public CWinApp
{
public:

	HFPC m_hFPC;

public:
	Apploader();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Apploader)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSample03_StandalonePlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern Apploader ldr;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLOADER_H)
