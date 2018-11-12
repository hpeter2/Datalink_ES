#pragma once
#include <MMSystem.h>
#include "Defines.h"
#include "HoppieList.h"
#include "OccAircraft.h"

class CHoppieConn : public FCHttpRequestManager
{
public:
	int		hoppieConnected, cpdlcCounter, selectedItem, popupList, x, y, iconify, notificationSound, m_mType;
	bool	withPDC, pdcConnected, euroscopeConnected, csOverride, asrLoaded, netClear;
	CString error, logonCode, callsign;
	CString	server = _T("www.hoppie.nl"), base = _T("/acars/system/connect.html");
	CList<CString> data;
	CList <CHoppieList, CHoppieList  &> hoppieList;
	CList <CString> hoppieAcList;
	CList <COccAircraft, COccAircraft &> m_VinicityAcList;            // the ACs in the vincity
	CList <yController> spokenList;
	CList<Wpn> waypoint;
	xController controllerMyself;
	CList<xController> controller;
	CString currentDir;
	CWinApp* pApp;

public:
	CHoppieConn();
	virtual ~CHoppieConn();

	void SetConfString(CString item, CString value);
	void SetConfInt(CString item, int value);
	void HoppieClear();
	bool Message(bool cType, int mType, CString callsign = "", CString msg = "");
	void OnAfterRequestFinish(FCHttpRequest& rTask);
	BOOL HoppiePing();

	POSITION _SelectAcFromVinicityList(int listIdx, const char * sCallsign);
	POSITION _SelectFixFromList(const char * fix);
	//-----------------------------------------------------------------
	//  Parameter :
	//		=>  listIDX		- the List to be searched (1: m_VinicityAcList, 2: hoppieList)
	//      =>  sCallsign   - the AC's callsign
	//
	//  Return :
	//      the position in the list or NULL if not found
	//-----------------------------------------------------------------

};

