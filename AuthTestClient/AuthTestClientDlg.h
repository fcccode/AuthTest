
// AuthTestClientDlg.h : header file
//

#pragma once


// CAuthTestClientDlg dialog
class CAuthTestClientDlg : public CDialogEx
{
// Construction
public:
	CAuthTestClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTHTESTCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	static UINT CAuthTestClientDlg::WorkerThreadNoOutput(LPVOID _param);
	static UINT CAuthTestClientDlg::WorkerThreadVerbose(LPVOID _param);
	static void CAuthTestClientDlg::SetBasic();

	//static void CAuthTestDlg::PrintOutput(BOOL fVerbose, CString StrTemp,LPVOID _param, ClientConn * pclient);

	//struct with params to WorkerThread
	typedef struct THREADSTRUCT
	{
		CAuthTestClientDlg * _this;
		int		iIndex;
		WCHAR	szServerName[255];
		int		iPort;
		WCHAR	szTargetName[255];
		WCHAR	szPackageName[40];
		TestType TestType;
	} THREADSTRUCT;

	afx_msg void OnBnClickedNooutput();
	afx_msg void OnBnClickedVerbose();
	afx_msg void OnSelchangeTabctrl(NMHDR *pNMHDR, LRESULT *pResult);

	CEdit		m_ServerName;
	CEdit		m_Port;
	CEdit		m_TargetName;
	CComboBox	m_PackageName;
	CTabCtrl	m_tabctrl;
	CButton		m_Basic;
	CButton		m_Advanced;
	CListBox	m_ListBox;

};
