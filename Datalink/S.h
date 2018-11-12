#pragma once
//#include "HoppieConn.h"
//#include "HoppieList.h"
//#include "OccAircraft.h"
//#include "DatalinkPlugin.h"
//#include "DatalinkApp.h"
//#include "DatalinkScreen.h"
#include "Util.h"
#include "stdafx.h"

class CDatalinkPlugin;
class CDatalinkScreen;

class S
{
	S() = delete;
	S(S const&) = delete;
	void operator=(S const&) = delete;


public:
	static CUtil& getUtilInstance() 
	{
		static CUtil instance;
		return instance;
	}
	/*static CDatalinkPlugin& getPluginInstance()
	{
		static CDatalinkPlugin instance;
		return instance;
	}*/
	/*static CList <CHoppieList, CHoppieList  &>& getInstance()
	{
		static CList <CHoppieList, CHoppieList  &> instance;
		return instance;
	}*/

	/*
	static int& getListInstance()
	{
		static int instance;
		return instance;
	}
	
	static bool& getConfigInstance()
	{
		static bool instance;
		return instance;
	}
	static CRect& getRectInstance()
	{
		static CRect instance;
		return instance;
	}*/
	/*
	static CHoppieConn& getHoppieInstance()
	{
		static CHoppieConn instance;
		return instance;
	}
	static CList <COccAircraft, COccAircraft &>& getVicinityList()
	{
		static CList <COccAircraft, COccAircraft &> instance;
		return instance;
	}
	*/

	friend CDatalinkPlugin;
	friend CDatalinkScreen;
};
