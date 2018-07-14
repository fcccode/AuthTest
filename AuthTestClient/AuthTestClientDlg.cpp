
// AuthTestClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AuthTestClient.h"
#include "AuthTestClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//Globals
LONG g_ClientCount = 0;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAuthTestClientDlg dialog



CAuthTestClientDlg::CAuthTestClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTHTESTCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAuthTestClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ServerName, m_ServerName);
	DDX_Control(pDX, IDC_Port, m_Port);
	DDX_Control(pDX, IDC_TargetName, m_TargetName);
	DDX_Control(pDX, IDC_PackageName, m_PackageName);
	DDX_Control(pDX, IDC_Basic, m_Basic);
	DDX_Control(pDX, IDC_Advanced, m_Advanced);
	DDX_Control(pDX, IDC_TabCtrl, m_tabctrl);
	DDX_Control(pDX, IDC_ListBox, m_ListBox);

}

BEGIN_MESSAGE_MAP(CAuthTestClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TabCtrl, &CAuthTestClientDlg::OnSelchangeTabctrl)
	ON_BN_CLICKED(IDC_NoOutput, &CAuthTestClientDlg::OnBnClickedNooutput)
	ON_BN_CLICKED(IDC_Verbose, &CAuthTestClientDlg::OnBnClickedVerbose)
END_MESSAGE_MAP()


// CAuthTestClientDlg message handlers

BOOL CAuthTestClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ServerName.SetWindowTextW(L"win81pro-lmas2");
	m_TargetName.SetWindowTextW(L"leonardo");

	m_Port.SetWindowTextW(L"7010");

	m_PackageName.AddString(L"Negotiate");
	m_PackageName.AddString(L"Kerberos");
	m_PackageName.AddString(L"NTLM");
	m_PackageName.AddString(L"CredSSP");
	m_PackageName.SetCurSel(0);

	m_tabctrl.InsertItem(0, L"No output");
	m_tabctrl.InsertItem(1, L"Verbose");
	m_tabctrl.InsertItem(2, L"Stress Test");

	m_Basic.SetCheck(BST_CHECKED);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAuthTestClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAuthTestClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAuthTestClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAuthTestClientDlg::OnSelchangeTabctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int iSelected = m_tabctrl.GetCurSel();

	switch (iSelected)
	{
	case 0:
		SetBasic();
		break;
	}

	*pResult = 0;
}

void CAuthTestClientDlg::SetBasic()
{

}


void CAuthTestClientDlg::OnBnClickedNooutput()
{
	CString StrTemp;

	//parameters to pass to new thread. The new thread must free this struct
	THREADSTRUCT * _param = new THREADSTRUCT;

	//current instance of CAuthTestDlg
	_param->_this = this;

	//client ID
	_param->iIndex = InterlockedIncrement(&g_ClientCount);

	//Server Name
	m_ServerName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szServerName, StrTemp);

	//Port
	m_Port.GetWindowTextW(StrTemp);
	_param->iPort = _wtoi(StrTemp);

	//Target Name
	m_TargetName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szTargetName, StrTemp);

	//Package Name
	m_PackageName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szPackageName, StrTemp);

	//Test Type
	if (m_Basic.GetCheck() == BST_CHECKED)
	{
		_param->TestType = Basic;
	}
	else
	{
		_param->TestType = Advanced;
	}

	//Create Worker Thread
	AfxBeginThread(WorkerThreadNoOutput, _param);
}


UINT CAuthTestClientDlg::WorkerThreadNoOutput(LPVOID _param)
{
	//cast _param into local Param
	THREADSTRUCT * Param = (THREADSTRUCT *)_param;

	ClientConn * pclient = new ClientConn(
		Param->iIndex,
		Param->szServerName,
		Param->iPort,
		Param->szTargetName,
		Param->szPackageName);

	BOOL bSuccess = false;
	CString StrTemp;

	WCHAR pMessage[200] = {};
	int cbMessage = sizeof(pMessage);

	//
	// Connect to the server
	//
	if (!pclient->Connect())
	{
		StrTemp.Format(L"Test Failed. Error %d at Connect -> %s.\n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	//
	// Send TestType
	//
	if (!pclient->SendTestType(Param->TestType))
	{
		StrTemp.Format(L"Test Failed. Error %d at SendTestType -> %s.\n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}


	//
	// Send Package Name
	//
	if (!pclient->SendPackageName())
	{
		StrTemp.Format(L"Test Failed. Error %d at SendPackageName -> %s.\n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}


	//
	// Authenticate
	//

	if (!pclient->Authenticate())
	{

		//Allow delegating fresh credentials
		if (pclient->dwErrorCode == SEC_E_DELEGATION_POLICY &&
			!_wcsicmp(pclient->pkgInfo->Name, L"CredSSP"))
		{
			StrTemp.Format(L"Test Failed. \nCheck CredSSP delegation policy at Computer Configuration\\Administrative Templates\\System\\Credential Delegation\\Allow delegating fresh credentials. \nAlso make sure the server is elevated.");

			goto cleanup;
		}

		//Allow delegating fresh credentials with NTLM
		if (pclient->dwErrorCode == SEC_E_POLICY_NLTM_ONLY &&
			!_wcsicmp(pclient->pkgInfo->Name, L"CredSSP"))
		{
			StrTemp.Format(L"Test Failed. \nCheck CredSSP delegation policy at Computer Configuration\\Administrative Templates\\System\\Credential Delegation\\Allow delegating fresh credentials with NTLM-only server authentication. \nAlso make sure the server is elevated.");

			goto cleanup;
		}

		StrTemp.Format(L"Test Failed. Error 0x%08x at Authenticate -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	//
	//Obtain the Package selected during authentication
	//
	if (!pclient->GetContextInfo())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at GetContextInfo -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	if (!_wcsicmp(pclient->szPackageName, L"CredSSP"))
	{
		StrTemp.Format(L"Test Success! Package selected: CredSSP over %s\n", pclient->SecPackageInfo.PackageInfo->Name);
	}
	else
	{
		StrTemp.Format(L"Test Success! Package selected: %s\n", pclient->SecPkgNegInfo.PackageInfo->Name);
	}

	//wrap if basic

	if (Param->TestType == Basic)
	{
		bSuccess = true;

		goto cleanup;
	}

	//
	//Obtain the size of signature and the encryption trailer blocks
	//

	if (!pclient->GetContextSizes())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at GetContextSizes -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}


	//
	//Receive an encrypted message from the server and decrypts it
	//

	if (!pclient->SecureReceive(pMessage, cbMessage))
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at SecureReceive -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	//
	//verify if the beginning of the decrypted message matches what we expect
	//

	if (wcsncmp(pMessage, L"The time now is", 15) != NULL)
	{
		StrTemp.Format(L"Test Failed. Decrypted message not recognized. Error 0x%08x at SecureReceive -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	bSuccess = true;

cleanup:

	AfxMessageBox(StrTemp, bSuccess ? MB_ICONINFORMATION : MB_ICONERROR);

	if (pclient)
		delete pclient;

	if (Param)
		delete Param;

	return true;
}




void CAuthTestClientDlg::OnBnClickedVerbose()
{
	CString StrTemp;

	//parameters to pass to new thread. The new thread must free this struct
	THREADSTRUCT * _param = new THREADSTRUCT;

	//current instance of CAuthTestDlg
	_param->_this = this;

	//client ID
	_param->iIndex = InterlockedIncrement(&g_ClientCount);

	//Server Name
	m_ServerName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szServerName, StrTemp);

	//Port
	m_Port.GetWindowTextW(StrTemp);
	_param->iPort = _wtoi(StrTemp);

	//Target Name
	m_TargetName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szTargetName, StrTemp);

	//Package Name
	m_PackageName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szPackageName, StrTemp);

	//Test Type
	if (m_Basic.GetCheck() == BST_CHECKED)
	{
		_param->TestType = Basic;
	}
	else
	{
		_param->TestType = Advanced;
	}

	//Create Worker Thread
	AfxBeginThread(WorkerThreadVerbose, _param);
}


UINT CAuthTestClientDlg::WorkerThreadVerbose(LPVOID _param)
{
	//cast _param into local Param
	THREADSTRUCT * Param = (THREADSTRUCT *)_param;

	ClientConn * pclient = new ClientConn(
		Param->iIndex,
		Param->szServerName,
		Param->iPort,
		Param->szTargetName,
		Param->szPackageName);

	WCHAR pMessage[200] = {};
	int cbMessage = sizeof(pMessage);

	CString StrTemp;
	Param->_this->m_ListBox.ResetContent();

	//
	// Connect to the server
	//
	if (!pclient->Connect())
	{
		StrTemp.Format(L"Test Failed. Error %d at Connect -> %s. Aborting.\n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}
	StrTemp.Format(L"Connected to server: %s\n", pclient->szServerName);
	Param->_this->m_ListBox.AddString(StrTemp);


	//
	// Send TestType
	//
	if (!pclient->SendTestType(Param->TestType))
	{
		StrTemp.Format(L"Test Failed. Error %d at SendTestType -> %s. Aborting.\n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}
	StrTemp.Format(L"TestType sent.\n");
	Param->_this->m_ListBox.AddString(StrTemp);

	//
	// Send Package Name
	//
	if (!pclient->SendPackageName())
	{
		StrTemp.Format(L"Test Failed. Error %d at SendPackageName -> %s. Aborting.\n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}
	StrTemp.Format(L"PackageName sent.\n");
	Param->_this->m_ListBox.AddString(StrTemp);


	//
	// Authenticate
	//

	if (!pclient->Authenticate())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at Authenticate -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_ListBox.AddString(StrTemp);

		//if Allow delegating fresh credentials
		if (pclient->dwErrorCode == SEC_E_DELEGATION_POLICY &&
			!_wcsicmp(pclient->pkgInfo->Name, L"CredSSP"))
		{
			StrTemp.Format(L"Check CredSSP delegation policy at Computer Configuration\\Administrative Templates\\System\\Credential Delegation\\Allow delegating fresh credentials.\n");
		}

		//if Allow delegating fresh credentials with NTLM
		if (pclient->dwErrorCode == SEC_E_POLICY_NLTM_ONLY &&
			!_wcsicmp(pclient->pkgInfo->Name, L"CredSSP"))
		{
			StrTemp.Format(L"Check CredSSP delegation policy at Computer Configuration\\Administrative Templates\\System\\Credential Delegation\\Allow delegating fresh credentials with NTLM-only server authentication.\n");
		}


		goto cleanup;
	}
	StrTemp.Format(L"Authentication Success!\n");
	Param->_this->m_ListBox.AddString(StrTemp);


	//
	//Prints the Package selected during authentication
	//
	if (!pclient->GetContextInfo())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at GetContextInfo -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	if (!_wcsicmp(pclient->szPackageName, L"CredSSP"))
	{
		StrTemp.Format(L"Package selected: CredSSP over %s\n", pclient->SecPackageInfo.PackageInfo->Name);
	}
	else
	{
		StrTemp.Format(L"Package selected: %s\n", pclient->SecPkgNegInfo.PackageInfo->Name);
	}


	//wrap if basic

	if (Param->TestType == Basic)
	{
		StrTemp.Format(L"Test completed successfully!\n");

		goto cleanup;
	}
	else
	{
		Param->_this->m_ListBox.AddString(StrTemp);
	}


	//
	//Obtain the size of signature and the encryption trailer blocks
	//

	if (!pclient->GetContextSizes())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at GetContextSizes -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}
	StrTemp.Format(L"GetContextSizes success");
	Param->_this->m_ListBox.AddString(StrTemp);

	//
	//Receive an encrypted message from the server and decrypts it
	//

	if (!pclient->SecureReceive(pMessage, cbMessage))
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at SecureReceive -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	//
	//verify if the beginning of the decrypted message matches what we expect
	//

	if (wcsncmp(pMessage, L"The time now is", 15) != NULL)
	{
		StrTemp.Format(L"Test Failed. Decrypted message not recognized. Error 0x%08x at %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);

		goto cleanup;
	}

	StrTemp.Format(L"Test completed successfully!\n");

cleanup:

	Param->_this->m_ListBox.AddString(StrTemp);

	if (pclient)
		delete pclient;

	if (Param)
		delete Param;

	return true;
}

