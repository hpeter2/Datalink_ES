#include "stdafx.h"
#include "Util.h"


CUtil::CUtil()
{
	Logger::Init(true, Logger::GetCurrentDir());
	Logger::Log("SYSTEM: CUtil()");
}


CUtil::~CUtil()
{
	Logger::Log("SYSTEM: ~CUtil()");
}
