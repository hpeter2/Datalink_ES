#include "stdafx.h"
#include "OccAircraft.h"


COccAircraft::COccAircraft()
{
}


COccAircraft::COccAircraft(CString callsign, CString acType, CString origin, CString destination, CString deptime, CString runway, CString sid, CString squawk,
	int flightlevel, int speed, int atcFlightlevel, int heading, CString direct, CString nextstation, bool assumed, int sectorEntry)
{
	m_Callsign = callsign;
	m_ACType = acType;
	m_Origin = origin;
	m_Destination = destination;
	m_Runway = runway;
	m_SID = sid;
	m_Squawk = squawk;
	m_DepTime = deptime;
	m_Flightlevel = flightlevel;
	m_ATCSpeed = speed;
	m_ATCFlightlevel = atcFlightlevel;
	m_ATCHeading = heading;
	m_ATCDirect = direct;
	m_NextStation = nextstation;
	m_assumed = assumed;
	m_SectorEntry = sectorEntry;
}


COccAircraft::~COccAircraft()
{
}
