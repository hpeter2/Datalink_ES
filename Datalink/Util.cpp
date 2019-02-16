#include "stdafx.h"
#include "Util.h"


CUtil::CUtil()
{
	currentDir = GetCurrentDir();
	Logger::Init(true, currentDir);
	Logger::Log("SYSTEM: CUtil()");
}


CUtil::~CUtil()
{
	Logger::Log("SYSTEM: ~CUtil()");
}

int CUtil::FindNoCase(LPCTSTR pszString, LPCTSTR pszSearch)
{
	int lenString = strlen(pszString);
	int lenSearch = strlen(pszSearch);
	if (lenSearch == 0 || lenSearch > lenString)
		return -1;
	for (int i = 0; i < lenString - lenSearch + 1; ++i)
		if (_strnicmp(&pszString[i], pszSearch, lenSearch) == 0)
			return i;
	return -1;
}