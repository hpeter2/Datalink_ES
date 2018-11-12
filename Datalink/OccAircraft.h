#pragma once


class COccAircraft
{
public:
	CString		m_Callsign;
	CString		m_ACType;
	CString		m_Origin;
	CString		m_Destination;
	CString		m_Runway;
	CString		m_SID;
	CString		m_Squawk;
	CString		m_DepTime;
	CString		m_ATCDirect;
	CString		m_NextStation;
	bool		m_assumed;
	int			m_Flightlevel;
	int			m_ATCFlightlevel;
	int			m_ATCHeading;
	int			m_ATCSpeed;
	int			m_SectorEntry;

public:
	COccAircraft();

	COccAircraft(CString callsign, CString acType, CString origin, CString destination, CString deptime, CString runway, CString sid, CString squawk,
				 int flightlevel, int speed, int atcFlightlevel, int heading, CString direct, CString nextstation, bool assumed, int sectorEntry);

	virtual ~COccAircraft();
};
