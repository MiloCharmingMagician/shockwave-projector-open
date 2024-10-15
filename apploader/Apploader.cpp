// Apploader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Apploader.h"
#include "ApploaderDlg.h"
#include "AES_128_CBC.h"
#include "util.h"

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////
// Apploader

BEGIN_MESSAGE_MAP(Apploader, CWinApp)
	//{{AFX_MSG_MAP(Apploader)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Apploader construction

Apploader::Apploader()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only Apploader object

Apploader ldr;

/////////////////////////////////////////////////////////////////////////////
// Apploader initialization

BOOL Apploader::InitInstance()
{
	AfxEnableControlContainer();

	char* lpFlashOCXCode = romReadFile(-FLASH_OCX_SIZE, FLASH_OCX_SIZE);
    unsigned char* lpFlashOCXCodeData = (unsigned char*)lpFlashOCXCode;

    // decrypt flash ocx
#ifdef AUTH_CODE
	AES_CTX ctx;
    AES_DecryptInit(&ctx, key, iv);
    for (unsigned int offset = 0; offset < FLASH_OCX_SIZE; offset += 16) {
        AES_Decrypt(&ctx, lpFlashOCXCodeData + offset, lpFlashOCXCodeData + offset);
    }
#endif

	m_hFPC = FPC_LoadOCXCodeFromMemory((char*)lpFlashOCXCodeData, FLASH_OCX_SIZE);

	if (NULL == m_hFPC)
	{
		AfxMessageBox(_T("LoadOCXCode failed"));
		return FALSE;
	}

	ApploaderDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int Apploader::ExitInstance() 
{
	// Unload the flash ocx code
	if (NULL != m_hFPC)
	{
		FPC_UnloadCode(m_hFPC);
		m_hFPC = NULL;
	}
	
	return CWinApp::ExitInstance();
}
