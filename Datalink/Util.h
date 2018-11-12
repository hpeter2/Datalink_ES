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

	CHoppieConn hoppie;

	CUtil();
	virtual ~CUtil();
};

