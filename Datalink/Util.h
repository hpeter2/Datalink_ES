#pragma once
#include <EuroScopePlugIn.h>
#include "Defines.h"
#include "HoppieConn.h"

class CUtil
{
private:

public:
	int		buttonList;
	bool	configOpen;
	CRect	listRect;
	CString currentDir;

	CHoppieConn hoppie;

	CUtil();
	virtual ~CUtil();

	int FindNoCase(LPCTSTR pszString, LPCTSTR pszSearch);
};

