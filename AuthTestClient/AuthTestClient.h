
// AuthTestClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAuthTestClientApp:
// See AuthTestClient.cpp for the implementation of this class
//

class CAuthTestClientApp : public CWinApp
{
public:
	CAuthTestClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAuthTestClientApp theApp;
