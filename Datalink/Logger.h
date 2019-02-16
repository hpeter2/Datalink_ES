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

	static void Log(CString message)
	{
		if (Logger::ENABLED && Logger::DLL_PATH.GetLength() > 0) {
			CTime time(time(0));
			CString output;
			output.Format("[%s] %s\n", time.Format(_T("%d.%m.%y %H:%M")), message);

			CStdioFile file;
			if (!file.Open(Logger::DLL_PATH + "\\" + LOG_NAME, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive | CFile::modeNoTruncate))
				return;
			file.SeekToEnd();
			file.WriteString(output);
			file.Close();
		}
	}
};

