#include "stdafx.h"
#include "DatalinkPlugin.h"


bool Logger::ENABLED;
CString Logger::DLL_PATH;


//---CDatalinkPlugin--------------------------------------
CDatalinkPlugin::CDatalinkPlugin () :	CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
										MY_PLUGIN_NAME,
										MY_PLUGIN_VERSION,
										MY_PLUGIN_DEVELOPER,
										MY_PLUGIN_COPYRIGHT),
										util(S::getUtilInstance())
{
#ifdef DEBUG
	DisplayUserMessage("DataLink", "DataLink", "DEBUG VERSION INITIALISED", false, true, true, true, false);
#else
	DisplayUserMessage("DataLink", "DataLink", MY_PLUGIN_VERSION + " INITIALISED", false, true, true, true, false);
#endif
	Logger::Log("SYSTEM: CDatalinkPlugin()");

	CController a = ControllerMyself();//ControllerMyself();
	initCallsigns();
	initWPN();

	// register my own view type
	RegisterDisplayType (MY_PLUGIN_VIEW,
						 false,		// no radar content here
						 false,		// no geo referencing
						 true,		// it can be saved to an ASR file
						 true);		// can be created
}


//---CDatalinkPlugin--------------------------------------
CDatalinkPlugin::~CDatalinkPlugin ()
{
	Logger::Log("SYSTEM: ~CDatalinkPlugin()");
}


void CDatalinkPlugin::initCallsigns()
{
	CStdioFile file;
	CFileException e;
	TCHAR* pszFileName = _T("callsigns.ini");
	CString line;

	if (!file.Open(util.hoppie.currentDir + pszFileName, CFile::modeRead | CFile::shareDenyWrite, &e))
	{
		//TRACE(_T("File could not be opened %d\n"), e.m_cause);

		line.Format("SYSTEM: Unable to read callsigns.ini");
		DisplayUserMessage("DataLink", "DataLink", "ERROR: Unable to read callsigns.ini", false, true, true, true, false);
		Logger::Log(line);
	}
	else
	{
		BOOL dwRead;
		int nTokenPos = 0;

		dwRead = file.ReadString(line);

		while (dwRead)
		{
			if (line[0] != '#' && line.GetLength() > 0)
			{
				yController controller;

				controller.callsign = line.Tokenize(_T(":"), nTokenPos);
				controller.spokenCallsign = line.Tokenize(_T(":"), nTokenPos);

				util.hoppie.spokenList.AddTail(controller);

			}
			nTokenPos = 0;
			dwRead = file.ReadString(line);
		}

		// Close both files
		file.Close();
	}
}


void CDatalinkPlugin::initWPN()
{
	Wpn tmp;
	EuroScopePlugIn::CSectorElement sct = SectorFileElementSelectFirst(EuroScopePlugIn::SECTOR_ELEMENT_VOR);
	tmp.name = sct.GetName();
	sct.GetPosition(&tmp.position, 0);
	util.hoppie.waypoint.AddTail(tmp);

	while (SectorFileElementSelectNext(sct, EuroScopePlugIn::SECTOR_ELEMENT_VOR).IsValid())
	{
		sct = SectorFileElementSelectNext(sct, EuroScopePlugIn::SECTOR_ELEMENT_VOR);
		tmp.name = sct.GetName();
		sct.GetPosition(&tmp.position, 0);
		util.hoppie.waypoint.AddTail(tmp);
	}

	sct = SectorFileElementSelectFirst(EuroScopePlugIn::SECTOR_ELEMENT_NDB);
	tmp.name = sct.GetName();
	sct.GetPosition(&tmp.position, 0);
	util.hoppie.waypoint.AddTail(tmp);

	while (SectorFileElementSelectNext(sct, EuroScopePlugIn::SECTOR_ELEMENT_NDB).IsValid())
	{
		sct = SectorFileElementSelectNext(sct, EuroScopePlugIn::SECTOR_ELEMENT_NDB);
		tmp.name = sct.GetName();
		sct.GetPosition(&tmp.position, 0);
		util.hoppie.waypoint.AddTail(tmp);
	}

	sct = SectorFileElementSelectFirst(EuroScopePlugIn::SECTOR_ELEMENT_FIX);
	tmp.name = sct.GetName();
	sct.GetPosition(&tmp.position, 0);
	util.hoppie.waypoint.AddTail(tmp);

	while (SectorFileElementSelectNext(sct, EuroScopePlugIn::SECTOR_ELEMENT_FIX).IsValid())
	{
		sct = SectorFileElementSelectNext(sct, EuroScopePlugIn::SECTOR_ELEMENT_FIX);
		tmp.name = sct.GetName();
		sct.GetPosition(&tmp.position, 0);
		util.hoppie.waypoint.AddTail(tmp);
	}
}


CString CDatalinkPlugin::generateCallsign(CString callsign) {

	CString temp = "";
	//-----------------------------------------------------------------
	//      the facility of the controller:
	//          1   - FSS - flight service station
	//          2   - DEL - delivery
	//          3   - GND - ground
	//          4   - TWR - tower
	//          5   - APP, DEP - approach, departure
	//          6   - CTR - controller
	//-----------------------------------------------------------------
	if (ControllerMyself().GetFacility() == 1 || ControllerMyself().GetFacility() == 6)
	{
		// LON_CTR
		if (callsign.GetLength() == 7)
		{
			if (callsign.Mid(0, 3).Find("_") < 0)
				return callsign.Mid(0, 3);
		}
		// EURM_CTR
		else if (callsign.GetLength() == 8)
		{
			if (callsign.Mid(0, 4).Find("_") < 0)
				return callsign.Mid(0, 4);
		}
		// LON_C_CTR
		else if (callsign.GetLength() == 9)
		{
			if (callsign.Mid(0, 3).Find("_") < 0)
			{
				//LONC
				temp.Format("%s%s", callsign.Mid(0, 3), callsign.Mid(4, 1));
				return temp;
			}
		}
		// EDWW_A_CTR  LON_SC_CTR
		else if (callsign.GetLength() == 10)
		{
			if (callsign.Mid(0, 4).Find("_") < 0)
			{
				// EDWA
				temp.Format("%s%s", callsign.Mid(0, 3), callsign.Mid(5, 1));
				return temp;
			}
			else
			{
				// LONS
				temp.Format("%s%s", callsign.Mid(0, 3), callsign.Mid(4, 1));
				return temp;
			}
		}
	}

	else if (ControllerMyself().GetFacility() == 5)
	{
		// EBBR_APP
		if (callsign.GetLength() == 8)
		{
			temp.Format("%s%s", callsign.Mid(0, 2), callsign.Mid(3, 1));
			return temp;
		}
		// EDDF_F_APP
		else if (callsign.GetLength() == 10)
		{
			temp.Format("%s%s%s", callsign.Mid(0, 2), callsign.Mid(3, 1), callsign.Mid(5, 1));
			return temp;
		}
	}
	else if (ControllerMyself().GetFacility() >= 2 && ControllerMyself().GetFacility() <= 4)
	{
		return "";
	}
	return "";
}


/////////////////////////////////////////////////////////////////////////////
// EuroScopePlugIn message handlers
//
//---OnRadarScreenCreated----------------------------------------------
EuroScopePlugIn::CRadarScreen * CDatalinkPlugin::OnRadarScreenCreated(const char * sDisplayName,
	bool NeedRadarContent,
	bool GeoReferenced,
	bool CanBeSaved,
	bool CanBeCreated)
{
	return new CDatalinkScreen;
}


//---OnGetTagItem-------------------------------------
void	CDatalinkPlugin::OnGetTagItem (EuroScopePlugIn::CFlightPlan FlightPlan, EuroScopePlugIn::CRadarTarget RadarTarget, int ItemCode,
					  int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize)
{
	const int TAG_COLOR_RGB_DEFINED = 1;
	if (util.buttonList == BUTTON_CLIMB)
		OnTimer(m_lastSend + 1000);

	POSITION pos;
	// only for flight plans
	if (!FlightPlan.IsValid())
		return;

	// get the AC index
	if (ItemCode == 1)
	{
		// If AC not Connected to my Station
		if ((pos = util.hoppie._SelectAcFromVinicityList(HOPPIE_LIST, FlightPlan.GetCallsign())) == NULL) 
		{
			// If AC is in Hoppie List
			if ((pos = util.hoppie.hoppieAcList.Find(FlightPlan.GetCallsign())) != NULL) {
				// Default Available
				*pColorCode = TAG_COLOR_DEFAULT;
				sprintf(sItemString, "•");
			}
			// If AC is not connected to Hoppie Network
			else
				return;
		}
		// If AC Connected to my Station
		else
		{
			// If AC is Timing Out
			if (util.hoppie.hoppieList.GetAt(pos).m_Connected == 0 || util.hoppie.hoppieList.GetAt(pos).m_Connected == 4) {
				*pColorCode = TAG_COLOR_EMERGENCY;
			}
			// Request Logon
			else if (util.hoppie.hoppieList.GetAt(pos).m_Connected == 3 || util.hoppie.hoppieList.GetAt(pos).m_Connected == 5) {
				*pColorCode = TAG_COLOR_INFORMATION;
				sprintf(sItemString, "°");
			}
			// Logoff
			else if (util.hoppie.hoppieList.GetAt(pos).m_Connected == 2) {
				*pColorCode = TAG_COLOR_DEFAULT;
				sprintf(sItemString, "•");
			}
			// If ATC hasn't answered to open AC Message yet
			else if (util.hoppie.hoppieList.GetAt(pos).m_LevelATCId != "" || util.hoppie.hoppieList.GetAt(pos).m_RouteATCId != "" || 
					 util.hoppie.hoppieList.GetAt(pos).m_SSRATCId != "" || util.hoppie.hoppieList.GetAt(pos).m_VoiceATCId != "" ||
					 util.hoppie.hoppieList.GetAt(pos).m_LevelId != "" || util.hoppie.hoppieList.GetAt(pos).m_RouteId != "" || 
					 util.hoppie.hoppieList.GetAt(pos).m_SSRId != "" || util.hoppie.hoppieList.GetAt(pos).m_VoiceId != "")
			{
				*pColorCode = EuroScopePlugIn::TAG_COLOR_INFORMATION;
				sprintf(sItemString, "*");
			}
			// Default Connected
			else {
				*pColorCode = EuroScopePlugIn::TAG_COLOR_DEFAULT;
				sprintf(sItemString, "*");
			}

		}
	}
}


//---OnRadarTargetPositionUpdate-------------------------------------
void    CDatalinkPlugin::OnRadarTargetPositionUpdate (EuroScopePlugIn::CRadarTarget RadarTarget)
{
	if (util.buttonList >= BUTTON_CLIMB && util.buttonList <= BUTTON_AUTO)
		OnTimer(m_lastSend);

	POSITION posx;
	if ((posx = util.hoppie._SelectAcFromVinicityList(HOPPIE_LIST, RadarTarget.GetCallsign())) != NULL)
	{
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayLvl != -1) {
			RadarTarget.GetCorrelatedFlightPlan().GetControllerAssignedData().SetClearedAltitude(util.hoppie.hoppieList.GetAt(posx).m_RelayLvl);
			util.hoppie.hoppieList.GetAt(posx).m_RelayLvl = -1;
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayHdg != -1) {
			RadarTarget.GetCorrelatedFlightPlan().GetControllerAssignedData().SetAssignedHeading(util.hoppie.hoppieList.GetAt(posx).m_RelayHdg);
			util.hoppie.hoppieList.GetAt(posx).m_RelayHdg = -1;
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk.GetLength() > 0) {
			RadarTarget.GetCorrelatedFlightPlan().GetControllerAssignedData().SetSquawk(util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk);
			util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk = "";
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayDct.GetLength() > 0) {
			RadarTarget.GetCorrelatedFlightPlan().GetControllerAssignedData().SetDirectToPointName(util.hoppie.hoppieList.GetAt(posx).m_RelayDct);
			util.hoppie.hoppieList.GetAt(posx).m_RelayDct = "";
		}
	}

	POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, RadarTarget.GetCallsign());
	CFlightPlanData fpData = RadarTarget.GetCorrelatedFlightPlan().GetFlightPlanData();
	CFlightPlanControllerAssignedData CfpData = RadarTarget.GetCorrelatedFlightPlan().GetControllerAssignedData();

	COccAircraft aircraft(RadarTarget.GetCallsign(), fpData.GetAircraftFPType(), fpData.GetOrigin(), fpData.GetDestination(), fpData.GetEstimatedDepartureTime(),
		fpData.GetDepartureRwy(), fpData.GetSidName(), CfpData.GetSquawk(), fpData.GetFinalAltitude(), CfpData.GetAssignedSpeed(),
		CfpData.GetClearedAltitude(), CfpData.GetAssignedHeading(), CfpData.GetDirectToPointName(), RadarTarget.GetCorrelatedFlightPlan().GetCoordinatedNextController(),
		RadarTarget.GetCorrelatedFlightPlan().GetTrackingControllerIsMe(), RadarTarget.GetCorrelatedFlightPlan().GetSectorEntryMinutes());

	//(CString callsign, CString acType, CString origin, CString destination, CString deptime, CString runway, CString sid, CString squawk, 
	// int flightlevel, int speed, int atcFlightlevel, int heading, CString direct, CString nextstation)


	if (pos != NULL)
		util.hoppie.m_VinicityAcList.SetAt(pos, aircraft);
	else
		util.hoppie.m_VinicityAcList.AddTail(aircraft);
}


//---OnFlightPlanDisconnect-------------------------------------
void    CDatalinkPlugin::OnFlightPlanDisconnect (EuroScopePlugIn::CFlightPlan FlightPlan)
{
	if (util.buttonList >= BUTTON_CLIMB && util.buttonList <= BUTTON_AUTO)
		OnTimer(m_lastSend);

	POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, FlightPlan.GetCallsign());

	if (pos != NULL)
	{
		util.hoppie.m_VinicityAcList.RemoveAt(pos);
	}
}


//---OnFlightPlanFlightPlanDataUpdate-------------------------------------
void    CDatalinkPlugin::OnFlightPlanFlightPlanDataUpdate (EuroScopePlugIn::CFlightPlan FlightPlan)
{
	if (util.buttonList >= BUTTON_CLIMB && util.buttonList <= BUTTON_AUTO)
		OnTimer(m_lastSend);

	POSITION posx;
	if ((posx = util.hoppie._SelectAcFromVinicityList(HOPPIE_LIST, FlightPlan.GetCallsign())) != NULL) {
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayLvl != -1) {
			FlightPlan.GetControllerAssignedData().SetClearedAltitude(util.hoppie.hoppieList.GetAt(posx).m_RelayLvl);
			util.hoppie.hoppieList.GetAt(posx).m_RelayLvl = -1;
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayHdg != -1) {
			FlightPlan.GetControllerAssignedData().SetAssignedHeading(util.hoppie.hoppieList.GetAt(posx).m_RelayHdg);
			util.hoppie.hoppieList.GetAt(posx).m_RelayHdg = -1;
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk.GetLength() > 0) {
			FlightPlan.GetControllerAssignedData().SetSquawk(util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk);
			util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk = "";
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayDct.GetLength() > 0) {
			FlightPlan.GetControllerAssignedData().SetDirectToPointName(util.hoppie.hoppieList.GetAt(posx).m_RelayDct);
			util.hoppie.hoppieList.GetAt(posx).m_RelayDct = "";
		}
	}

	POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, FlightPlan.GetCallsign());
	CFlightPlanData fpData = FlightPlan.GetFlightPlanData();
	CFlightPlanControllerAssignedData CfpData = FlightPlan.GetControllerAssignedData();

	COccAircraft aircraft(FlightPlan.GetCallsign(), fpData.GetAircraftFPType(), fpData.GetOrigin(), fpData.GetDestination(), fpData.GetEstimatedDepartureTime(),
		fpData.GetDepartureRwy(), fpData.GetSidName(), CfpData.GetSquawk(), fpData.GetFinalAltitude(), CfpData.GetAssignedSpeed(),
		CfpData.GetClearedAltitude(), CfpData.GetAssignedHeading(), CfpData.GetDirectToPointName(), FlightPlan.GetCoordinatedNextController(),
		FlightPlan.GetTrackingControllerIsMe(), FlightPlan.GetSectorEntryMinutes());

	if (pos != NULL)
		util.hoppie.m_VinicityAcList.SetAt(pos, aircraft);
	else
		util.hoppie.m_VinicityAcList.AddTail(aircraft);
}


//---OnFlightPlanControllerAssignedDataUpdate-------------------------------------
void    CDatalinkPlugin::OnFlightPlanControllerAssignedDataUpdate (EuroScopePlugIn::CFlightPlan FlightPlan, int DataType)
{
	if (util.buttonList >= BUTTON_CLIMB && util.buttonList <= BUTTON_AUTO)
		OnTimer(m_lastSend);

	POSITION posx;
	if ((posx = util.hoppie._SelectAcFromVinicityList(HOPPIE_LIST, FlightPlan.GetCallsign())) != NULL)
	{
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayLvl != -1) {
			FlightPlan.GetControllerAssignedData().SetClearedAltitude(util.hoppie.hoppieList.GetAt(posx).m_RelayLvl);
			util.hoppie.hoppieList.GetAt(posx).m_RelayLvl = -1;
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayHdg != -1) {
			FlightPlan.GetControllerAssignedData().SetAssignedHeading(util.hoppie.hoppieList.GetAt(posx).m_RelayHdg);
			util.hoppie.hoppieList.GetAt(posx).m_RelayHdg = -1;
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk.GetLength() > 0) {
			FlightPlan.GetControllerAssignedData().SetSquawk(util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk);
			util.hoppie.hoppieList.GetAt(posx).m_RelaySquawk = "";
		}
		if (util.hoppie.hoppieList.GetAt(posx).m_RelayDct.GetLength() > 0) {
			FlightPlan.GetControllerAssignedData().SetDirectToPointName(util.hoppie.hoppieList.GetAt(posx).m_RelayDct);
			util.hoppie.hoppieList.GetAt(posx).m_RelayDct = "";
		}
	}

	POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, FlightPlan.GetCallsign());
	CFlightPlanData fpData = FlightPlan.GetFlightPlanData();
	CFlightPlanControllerAssignedData CfpData = FlightPlan.GetControllerAssignedData();

	COccAircraft aircraft(FlightPlan.GetCallsign(), fpData.GetAircraftFPType(), fpData.GetOrigin(), fpData.GetDestination(), fpData.GetEstimatedDepartureTime(),
		fpData.GetDepartureRwy(), fpData.GetSidName(), CfpData.GetSquawk(), fpData.GetFinalAltitude(), CfpData.GetAssignedSpeed(),
		CfpData.GetClearedAltitude(), CfpData.GetAssignedHeading(), CfpData.GetDirectToPointName(), FlightPlan.GetCoordinatedNextController(),
		FlightPlan.GetTrackingControllerIsMe(), FlightPlan.GetSectorEntryMinutes());

	//(CString callsign, CString acType, CString origin, CString destination, CString deptime, CString runway, CString sid, CString squawk, 
	// int flightlevel, int speed, int atcFlightlevel, int heading, CString direct, CString nextstation)
	if (pos != NULL)
		util.hoppie.m_VinicityAcList.SetAt(pos, aircraft);
	else
		util.hoppie.m_VinicityAcList.AddTail(aircraft);
}


//---OnFlightPlanControllerAssignedDataUpdate-------------------------------------
void    CDatalinkPlugin::OnControllerDisconnect (EuroScopePlugIn::CController Controller)
{
	if (strcmp(Controller.GetFullName(), ControllerMyself().GetFullName()) == 0)
		util.hoppie.controllerMyself.valid = false;

	else if (util.hoppie._SelectAcFromVinicityList(CONTROLLER_LIST, Controller.GetCallsign()) != NULL) {
		POSITION pos = util.hoppie._SelectAcFromVinicityList(CONTROLLER_LIST, Controller.GetCallsign());
		util.hoppie.controller.RemoveAt(pos);
	}
}


//---OnFlightPlanControllerAssignedDataUpdate-------------------------------------
void	CDatalinkPlugin::OnControllerPositionUpdate (EuroScopePlugIn::CController Controller)
{
	if (strcmp(Controller.GetFullName(), ControllerMyself().GetFullName()) == 0) {
		util.hoppie.controllerMyself.valid = true;
		util.hoppie.controllerMyself.callsign = Controller.GetCallsign();
		util.hoppie.controllerMyself.freq = Controller.GetPrimaryFrequency();
		util.hoppie.controllerMyself.facility = Controller.GetFacility();
		util.hoppie.controllerMyself.spokenCallsign = "";
	}
	else if (util.hoppie._SelectAcFromVinicityList(CONTROLLER_LIST, Controller.GetCallsign()) != NULL) {
		POSITION pos = util.hoppie._SelectAcFromVinicityList(CONTROLLER_LIST, Controller.GetCallsign());
		util.hoppie.controller.GetAt(pos).callsign = Controller.GetCallsign();
		util.hoppie.controller.GetAt(pos).facility = Controller.GetFacility();
		util.hoppie.controller.GetAt(pos).freq = Controller.GetPrimaryFrequency();
		util.hoppie.controller.GetAt(pos).valid = Controller.IsValid();

		if (util.hoppie._SelectAcFromVinicityList(SPOKEN_LIST, Controller.GetCallsign()) != NULL) {
			POSITION pos2 = util.hoppie._SelectAcFromVinicityList(SPOKEN_LIST, Controller.GetCallsign());
			util.hoppie.controller.GetAt(pos).spokenCallsign = util.hoppie.spokenList.GetAt(pos2).spokenCallsign;
		}
		else
			util.hoppie.controller.GetAt(pos).spokenCallsign = "";
	}
	else if (Controller.IsController()) {
		xController tmp;
		tmp.callsign = Controller.GetCallsign();
		tmp.freq = Controller.GetPrimaryFrequency();
		tmp.valid = Controller.IsValid();
		tmp.facility = Controller.GetFacility();

		if (util.hoppie._SelectAcFromVinicityList(SPOKEN_LIST, Controller.GetCallsign()) != NULL) {
			POSITION pos2 = util.hoppie._SelectAcFromVinicityList(SPOKEN_LIST, Controller.GetCallsign());
			tmp.spokenCallsign = util.hoppie.spokenList.GetAt(pos2).spokenCallsign;
		}
		else
			tmp.spokenCallsign = "";

		util.hoppie.controller.AddTail(tmp);
	}
}


//---OnCompileCommand-------------------------------------
bool    CDatalinkPlugin::OnCompileCommand (const char * sCommandLine)
{
	CString p_call, command(sCommandLine);
	command.MakeUpper();

	// if CPDLC command 
	// 10: .datalink BOR
	// 11: .datalink EDDW

	if (strncmp(command, ".LOGIN", 6) == 0) {
		if (command.GetLength() == 6)
			return false;
		p_call = sCommandLine + 7;
		util.hoppie.logonCode = p_call;
		util.hoppie.SetConfString("logonCode", p_call);
		return true;
	}
	else if (strncmp(command, ".DATALINK", 9) == 0) {
		if (command.GetLength() == 9)
			return false;
		if (command.GetLength() < 13 || command.GetLength() > 14) {
			DisplayUserMessage("Datalink", "DataLink", "No valid Callsign", false, true, true, true, false);
			return true;
		}

		// extract callsign
		p_call = sCommandLine + 10;
		p_call.MakeUpper();

		if (p_call == "NULL" || p_call == "AUTO") {
			util.hoppie.callsign = generateCallsign(ControllerMyself().GetCallsign());
			util.hoppie.csOverride = false;
			util.hoppie.euroscopeConnected = false;
			
			if (util.hoppie.callsign.GetLength() == 0) {
				if (ControllerMyself().GetFacility() >= 2 && ControllerMyself().GetFacility() <= 4) {
					DisplayUserMessage("Datalink", "Datalink", "Datalink Is not designed for Ground Stations", false, true, true, true, false);
					DisplayUserMessage("Datalink", "Datalink", "Set a Callsign via .datalink [CALLSIGN] to use Datalink anyway", false, true, true, true, false);
				}
				else {
					DisplayUserMessage("Datalink", "Datalink", "Your Callsign couldn't be generated", false, true, true, true, false);
					DisplayUserMessage("Datalink", "Datalink", "Set a Callsign via .datalink [CALLSIGN]", false, true, true, true, false);
				}
			}
			else
				DisplayUserMessage("Datalink", "Hoppie Callsign", util.hoppie.callsign, false, true, true, true, false);
		}
		else {
			util.hoppie.callsign = p_call;
			util.hoppie.csOverride = true;
			DisplayUserMessage("Datalink", "Hoppie Callsign", util.hoppie.callsign, false, true, true, true, false);
		}
		return true;
	}
	else if (strncmp(command, ".TELEX", 6) == 0) {
		if (command.GetLength() == 6)
			return false;
		else if (command.GetLength() < 13 || command.GetLength() > 14) {
			DisplayUserMessage("Datalink", "DataLink", "No valid Callsign", false, true, true, true, false);
			return true;
		}

		// extract telex
		p_call = sCommandLine + 7;
		p_call.MakeUpper();

		// TODO: TELEX
		return false;
	}
	else
		return false;
}


//---OnTimer-------------------------------------
void    CDatalinkPlugin::OnTimer (int Counter)
{
	// AC Data: 1/CALLSIGN:ACTYPE:ORIGIN:DEST:DEPTIME:DEPRWY:SID:SQUAWK:FL:ATCSPEED:ATCFL:ATCHDG:DIRECT:NEXTSTAT/
	// 

	//(CString callsign, CString acType, CString origin, CString destination, CString deptime, CString runway, CString sid, CString squawk, 
	// int flightlevel, int speed, int atcFlightlevel, int heading, CString direct, CString nextstation)


	// Update Controller Data
	if (ControllerMyself().IsValid() && ControllerMyself().GetPrimaryFrequency() != util.hoppie.controllerMyself.freq) {
		util.hoppie.controllerMyself.valid = true;
		util.hoppie.controllerMyself.callsign = ControllerMyself().GetCallsign();
		util.hoppie.controllerMyself.freq = ControllerMyself().GetPrimaryFrequency();
	}
	else if (!ControllerMyself().IsValid())
		util.hoppie.controllerMyself.valid = false;

	// Fetch Data
	if (util.hoppie.hoppieConnected && util.hoppie.netClear && m_cycle == 1) {
		util.hoppie.Message(MSG_RECEIVE, MSG_POLL);
		m_cycle = 0;
	}

	// OnClick CLIMB|DESCEND|MAINTAIN
	if (util.buttonList == BUTTON_CLIMB || util.buttonList == BUTTON_DESCEND || util.buttonList == BUTTON_MAINTN) {
		if (util.buttonList == BUTTON_CLIMB) {
			util.hoppie.popupList = BUTTON_CLIMB;
			util.listRect.top += 63;
		}
		else if (util.buttonList == BUTTON_DESCEND) {
			util.hoppie.popupList = BUTTON_DESCEND;
			util.listRect.top += 33;
		}
		else if (util.buttonList == BUTTON_MAINTN) {
			util.hoppie.popupList = BUTTON_MAINTN;
			util.listRect.top -= 55;
		}
		util.buttonList = -1;
		OpenPopupList(util.listRect, "LVL", 1);

		char str[10];
		POSITION pos;
		int selected = 380;
		if ((pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign)) != NULL)
			if (util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCFlightlevel > 90 && util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCFlightlevel < 600)
				selected = util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCFlightlevel;

		for (int i = 59; i > 9; --i) {
			sprintf(str, " %d ", i * 10);
			if (i == selected / 10)
				AddPopupListElement(str, str, 2, true);
			else
				AddPopupListElement(str, str, 2);
		}

		for (int i = 90; i > 5; i -= 5) {
			sprintf(str, " 0%d ", i);
			if (i == selected)
				AddPopupListElement(str, str, 2, true);
			else
				AddPopupListElement(str, str, 2);
		}

		//AddPopupListElement(" FIG ", " FIG ", 2, false, 2, false, true);
	}

	// OnClick FLYHDG
	else if (util.buttonList == BUTTON_FLYHDG) {
		if (util.buttonList == BUTTON_CONTHDG) {
			util.hoppie.popupList = BUTTON_CONTHDG;
			util.listRect.top += 63;
		}
		else if (util.buttonList == BUTTON_FLYHDG) {
			util.hoppie.popupList = BUTTON_FLYHDG;
			util.listRect.top += 33;
		}
		OpenPopupList(util.listRect, "HDG", 1);
		util.buttonList = -1;

		char str[10];
		POSITION pos;
		int selected = 180;
		if ((pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign)) != NULL) {
			if (util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCHeading > 0)
				selected = util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCHeading;
			else
#pragma warning(suppress: 4244)
				selected = (RadarTargetSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetTrackHeading() / 10) * 10;
		}

		for (int i = 36; i > 9; --i) {
			sprintf(str, " %d ", i * 10);
			if (i == selected / 10)
				AddPopupListElement(str, str, 2, true);
			else
				AddPopupListElement(str, str, 2);
		}
		for (int i = 9; i > 0; --i) {
			sprintf(str, " 0%d ", i * 10);
			if (i == selected)
				AddPopupListElement(str, str, 2, true);
			else
				AddPopupListElement(str, str, 2);
		}

		//AddPopupListElement(" FIG ", " FIG ", 2, false, 2, false, true);

	}

	// OnClick TURNLDEG|TURNRDEG
	else if (util.buttonList == BUTTON_TURNLDEG || util.buttonList == BUTTON_TURNRDEG) {
		if (util.buttonList == BUTTON_TURNLDEG) {
			util.hoppie.popupList = BUTTON_TURNLDEG;
			util.listRect.top += 63;
		}
		else if (util.buttonList == BUTTON_TURNRDEG) {
			util.hoppie.popupList = BUTTON_TURNRDEG;
			util.listRect.top += 33;
		}
		OpenPopupList(util.listRect, "DEG", 1);
		util.buttonList = -1;

		char str[10];
		for (int i = 5; i <= 25; i += 5) {
			sprintf(str, " %d ", i);
			AddPopupListElement(str, str, 2);
		}
	}

	// OnClick DCTTO
	else if (util.buttonList == BUTTON_DCTTO) {
		util.hoppie.popupList = BUTTON_DCTTO;
		util.listRect.top -= 55;
		OpenPopupList(util.listRect, "DCT", 1);
		util.buttonList = -1;

		char str[10];
		POSITION pos;
		CString selected = "";
		int i = 0;
		if ((pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign)) != NULL) {
			if (util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCDirect.GetLength() > 0)
				selected = util.hoppie.m_VinicityAcList.GetAt(pos).m_ATCDirect;
			else if (strlen(FlightPlanSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetExitCoordinationPointName()) > 0)
				selected = FlightPlanSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetExitCoordinationPointName();

			if (FlightPlanSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetExtractedRoute().GetPointsCalculatedIndex() > -1)
				i = FlightPlanSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetExtractedRoute().GetPointsCalculatedIndex();


			for (i; i < FlightPlanSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetExtractedRoute().GetPointsNumber(); ++i) {
				strcpy(str, FlightPlanSelect(util.hoppie.m_VinicityAcList.GetAt(pos).m_Callsign).GetExtractedRoute().GetPointName(i));
				if (strcmp(str, selected) == 0)
					AddPopupListElement(str, str, 2, true);
				else
					AddPopupListElement(str, str, 2);
			}
		}

		//AddPopupListElement(" FIG ", " FIG ", 2, false, 2, false, true);
	}

	// OnClick CONTHDG
	else if (util.buttonList == BUTTON_CONTHDG) {
		util.hoppie.popupList = BUTTON_CONTHDG;
		util.buttonList = -1;
	}

	// OnClick CNTCT|PDC
	else if (util.buttonList == BUTTON_CNTCT || util.buttonList == BUTTON_PDC || util.buttonList == BUTTON_DCL_DCL) {
		util.hoppie.popupList = util.buttonList;
		util.listRect.top -= 55;
		OpenPopupList(util.listRect, "CNTCT", 1);
		util.buttonList = -1;

		CString str;
		CString selected = "";
		int i = 0;
		EuroScopePlugIn::CController controller = ControllerSelectFirst();
		for (; controller.IsValid();) {
			if (controller.IsController()) {
				str = controller.GetCallsign();
				if (strcmp(str, selected) == 0)
					AddPopupListElement(str, str, 2, true);
				else
					AddPopupListElement(str, str, 2);
			}
			controller = ControllerSelectNext(controller);
		}
	}

	// If Connected to Vatsim
	if (!util.hoppie.euroscopeConnected && GetConnectionType() >= 1) {
		// As a Controller
		if (ControllerMyself().IsController()) {
			util.hoppie.euroscopeConnected = true;
			bool noConnect = false;
			if (!util.hoppie.csOverride) {
				util.hoppie.callsign = generateCallsign(ControllerMyself().GetCallsign());

				if (util.hoppie.callsign.GetLength() == 0) {
					noConnect = true;

					if (ControllerMyself().GetFacility() >= 2 && ControllerMyself().GetFacility() <= 4) {
						DisplayUserMessage("Datalink", "Datalink", "Datalink Is not designed for Ground Stations", false, true, true, true, false);
						DisplayUserMessage("Datalink", "Datalink", "Set a Callsign via .datalink [CALLSIGN] to use Datalink anyway", false, true, true, true, false);
					}
					else {
						DisplayUserMessage("Datalink", "Datalink", "Your Callsign couldn't be generated", false, true, true, true, false);
						DisplayUserMessage("Datalink", "Datalink", "Set a Callsign via .datalink [CALLSIGN]", false, true, true, true, false);
					}
				}
			}

			if (!noConnect) {
				DisplayUserMessage("Datalink", "Hoppie Callsign", util.hoppie.callsign, false, true, true, true, false);
			}
		}
	}

	// 
	else if (GetConnectionType() == 0 && util.hoppie.euroscopeConnected) {
		//hoppieClear();
		//hoppie.euroscopeConnected = false;
		//hoppie.hoppieConnected = false;
	}

	// Clear AC List if disconnected from Hoppie Net
	if (!util.hoppie.hoppieConnected && util.hoppie.hoppieList.GetCount() > 0) {
		util.hoppie.HoppieClear();
	}

	// AC Send
	for (int i = 0; i < util.hoppie.hoppieList.GetCount(); ++i)
	{
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetCount() > 0)
		{

			for (int j = 0; j < util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetCount(); ++j)
			{
				if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_cooldown == 0)
				{
					if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetHead().MakeUpper().Find("DATA2") > -1)
						util.hoppie.Message(MSG_SEND, MSG_CPDLC, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetHead());
					else
						util.hoppie.Message(MSG_SEND, MSG_TELEX, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetHead());

					util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->RemoveHead();
					util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_cooldown++;
				}
				else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_cooldown == 10)
				{
					if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetHead().MakeUpper().Find("DATA2") > -1)
						util.hoppie.Message(MSG_SEND, MSG_CPDLC, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetHead());
					else
						util.hoppie.Message(MSG_SEND, MSG_TELEX, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->GetHead());

					util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Relay->RemoveHead();
					util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_cooldown = 0;
				}
				else
					util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_cooldown++;
			}//for
		}//if
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelATCId != "")
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelTimer++;
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteATCId != "")
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteTimer++;
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceATCId != "")
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceTimer++;
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRATCId != "")
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRTimer++;

		CFlightPlan FlightPlan = FlightPlanSelect(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign);
		if (FlightPlan.IsValid())
		{
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayLvl != -1) {
				FlightPlan.GetControllerAssignedData().SetClearedAltitude(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayLvl);
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayLvl = -1;
			}
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayHdg != -1) {
				FlightPlan.GetControllerAssignedData().SetAssignedHeading(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayHdg);
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayHdg = -1;
			}
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelaySquawk.GetLength() > 0) {
				FlightPlan.GetControllerAssignedData().SetSquawk(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelaySquawk);
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelaySquawk = "";
			}
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayDct.GetLength() > 0) {
				FlightPlan.GetControllerAssignedData().SetDirectToPointName(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayDct);
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RelayDct = "";
			}
		}
	}//for

	//Next Part Only every 5 seconds
	if ((Counter - m_lastSend) <= 5)
		return;

	int pos;
	POSITION posi;

	// 
	for (int i = 0; i < util.hoppie.hoppieList.GetCount(); ++i) {
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected == 5 && (posi = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign)) != NULL)
			if (util.hoppie.m_VinicityAcList.GetAt(posi).m_SectorEntry < 10)
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected = 3;

		else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Logon == 3)
			if ((pos = util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Voice.Find("REQ LOGON")) > -1) {
				pos -= 4;
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Voice.Delete(pos, 14);
			}

		else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Logon >= 1)
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Logon++;
	}


	// 
	if (util.hoppie.hoppieConnected && m_cycle == 0) {
		util.hoppie.Message(MSG_RECEIVE, MSG_PING);
		m_cycle = 1;
	}

	// 
	if (util.configOpen) {
		//OpenPopupEdit(listRect, 3, "TEST");
		//configOpen = false;
	}

	// Set
	m_lastSend = Counter;
}


//---OnFunctionCall-----------------------------------------
void    CDatalinkPlugin::OnFunctionCall (int FunctionId, const char * sItemString, POINT Pt, RECT Area)
{

}
