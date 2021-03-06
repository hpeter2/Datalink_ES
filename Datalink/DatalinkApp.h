// Datalink.h : main header file for the Datalink DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "DatalinkPlugin.h"

// CDatalinkApp
// See Datalink.cpp for the implementation of this class
//
class CDatalinkApp : public CWinApp
{
public:
	CDatalinkApp ();
	virtual ~CDatalinkApp ();

// Overrides
public:
	virtual BOOL InitInstance ();

	DECLARE_MESSAGE_MAP()
};
