#pragma once
#include "stdafx.h"


static TCHAR* LOG_NAME = _T("datalink.log");

class Logger
{
public:
	static bool ENABLED;
	static CString DLL_PATH;

public:
	static void Init(bool enabled, CString dll_path)
	{
		ENABLED = enabled;
		DLL_PATH = dll_path;
	}


	static CString GetCurrentDir()
	{
		TCHAR tmpT[MAX_PATH] = _T("");
		CString tempC = "";

		DWORD len = GetModuleFileNameA(AfxGetInstanceHandle(), tmpT, MAX_PATH);
		if (len == 0 || len >= MAX_PATH) strcpy(tmpT, "C:\\");

		tempC = tmpT;
		int pos = tempC.ReverseFind('\\');

		if (pos > -1)
			tempC.Delete(pos + 1, tempC.GetLength() - (pos + 1));
		return tempC;
	}


	static void Log(CString message)
	{
		if (Logger::ENABLED && Logger::DLL_PATH.GetLength() > 0) {
			CTime time(time(0));
			CString output;
			output.Format("[%s] %s\n", time.Format(_T("%d.%m.%y %H:%M")), message);

			CStdioFile file;
			file.Open(Logger::DLL_PATH + "\\" + LOG_NAME, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive | CFile::modeNoTruncate);
			file.SeekToEnd();
			file.WriteString(output);
			file.Close();
		}
	}
};

