// ApploaderDlg.cpp
//

#include "stdafx.h"
#include "Apploader.h"
#include "ApploaderDlg.h"
#include "AES_128_CBC.h"
#include "util.h"

/////////////////////////////////////////////////////////////////////////////
// ApploaderDlg dialog

ApploaderDlg::ApploaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ApploaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ApploaderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ApploaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ApploaderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ApploaderDlg, CDialog)
	//{{AFX_MSG_MAP(ApploaderDlg)
	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ApploaderDlg message handlers

BOOL ApploaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
 
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// FlashPlayerControl creating
	// NOTE: CALL FPC_LoadRegisteredOCX() or FPC_LoadOCXCodeFromMemory() before creating!
	{
		RECT rc;
		GetDlgItem(IDC_STATIC_FPC_PLACE)->GetWindowRect(&rc);
		ScreenToClient(&rc);

		m_hwndFlashPlayerControl = 
			CreateWindow((LPCTSTR)FPC_GetClassAtom(ldr.m_hFPC), 
						 NULL, 
						 WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 
						 rc.left, 
						 rc.top, 
						 rc.right - rc.left, 
						 rc.bottom - rc.top, 
						 m_hWnd, 
						 NULL, 
						 NULL, 
						 NULL);
	}

	// Loading movie from memory
	// can use the message FPCM_PUTMOVIEFROMMEMORY

	unsigned long bootSize = romReadBootSize();
    char* bootFile = romReadFile(-FLASH_OCX_SIZE-bootSize, bootSize);
	unsigned char* bootData = (unsigned char*)bootFile;

#ifdef AUTH_CODE
	// decrypt boot swf
	AES_CTX ctx;
    AES_DecryptInit(&ctx, key, iv);
    for (unsigned int offset = 0; offset < bootSize; offset += 16) {
        AES_Decrypt(&ctx, bootData + offset, bootData + offset);
    }
#endif

	FPCLoadMovieFromMemory(m_hwndFlashPlayerControl, 0, bootData, bootSize);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ApploaderDlg::OnActivate(UINT nState, CWnd* pParent, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pParent, bMinimized);

	if (nState == WA_INACTIVE)
    {
    }
}

void ApploaderDlg::OnPaint() 
{  
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ApploaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
