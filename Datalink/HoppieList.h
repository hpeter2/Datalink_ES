#pragma once
#include "stdafx.h"


class CHoppieList
{
public:
	CString		m_Callsign = "";
	int			m_Connected = 0, m_Logon = 0;
	int			m_Timeout = 0, m_cooldown = 0;
	CList<CString> *m_Relay;
	CString		m_Level = "L ";
	CString		m_LevelId = "";
	CString		m_LevelATCId = "";
	int			m_LevelTimer = 0;
	CString		m_Route = "R ";
	CString		m_RouteId = "";
	int			m_RouteTimer = 0;
	CString		m_RouteATCId = "";
	CString		m_Voice = "V ";
	CString		m_VoiceId = "";
	CString		m_VoiceATCId = "";
	int			m_VoiceTimer = 0;
	CString		m_SSR = "T ";
	CString		m_SSRId = "";
	CString		m_SSRATCId = "";
	int			m_SSRTimer = 0;
	CString		m_NextStation = "";

	int			m_RelayLvl = -1;
	int			m_RelayHdg = -1;
	CString		m_RelaySquawk = "";
	CString		m_RelayDct = "";

	// Only needed for selectedItem
	int			m_SelectedIdx = -1;

	// m_Connected:
	// 0 : Error
	// 1 : Connected
	// 2 : Request Logoff
	// 3 : Request Logon
	// 4:  Request Logon Error
	// 5:  Aircraft too far away, Standby
	// 6:  PDC via Telex (no Logon)

	// m_Logon:
	// 0 : no Login Answer
	// 1 : Logon Answered
	// 3 : Delete Logon Request from Data Frame
	//-1 : STANDBY


public:
	inline CHoppieList() 
	{
		m_Relay = new CList<CString>();
	}


	inline CHoppieList(CString callsign)
	{
		m_Relay = new CList<CString>();
		m_Callsign = callsign;
	}


	inline CHoppieList(CString callsign, int connected)
	{
		m_Relay = new CList<CString>();
		m_Connected = connected;
		m_Callsign = callsign;
	}

	inline CHoppieList(int selectedIdx)
	{
		m_SelectedIdx = selectedIdx;
	}

	virtual inline ~CHoppieList() 
	{

	}


	inline void SetVal(CString callsign, int connected)
	{
		m_Callsign = callsign;
		m_Connected = connected;
	}

	inline bool IsEmpty()
	{
		return (m_SelectedIdx < 0);
	}

	bool operator== (CHoppieList other)
	{
		return (this->m_Callsign == other.m_Callsign);
	}

	bool operator!= (CHoppieList other)
	{
		return !operator==(other);
	}
};

