#pragma once
#include <EuroScopePlugIn.h>
#include "Defines.h"
#include "DatalinkScreen.h"
#include "Util.h"
#include "S.h"

using namespace std;
using namespace EuroScopePlugIn;


class CDatalinkPlugin : public CDialog,
						public EuroScopePlugIn::CPlugIn
{
private:
	CUtil	&util;
	
	CString	m_status;
	int		m_port;
	int		m_lastSend;

	int		m_cycle;


public:
	//---CDatalinkPlugin--------------------------------------
	CDatalinkPlugin ();

	//---~CDatalinkPlugin-------------------------------------
	virtual ~CDatalinkPlugin ();


protected:
	void initCallsigns();
	void initWPN();

	CString generateCallsign(CString callsign);

	/////////////////////////////////////////////////////////////////////////////
	// EuroScopePlugIn message handlers
	//
	//---OnRadarScreenCreated------------------------------------------
	virtual EuroScopePlugIn::CRadarScreen * OnRadarScreenCreated (const char * sDisplayName,
																  bool NeedRadarContent,
																  bool GeoReferenced,
																  bool CanBeSaved,
																  bool CanBeCreated);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------

	
	//---OnGetTagItem-------------------------------------
	virtual void	OnGetTagItem (EuroScopePlugIn::CFlightPlan FlightPlan, EuroScopePlugIn::CRadarTarget RadarTarget, int ItemCode,
								  int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnRadarTargetPositionUpdate-------------------------------------
	virtual void    OnRadarTargetPositionUpdate (EuroScopePlugIn::CRadarTarget RadarTarget);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnFlightPlanDisconnect-------------------------------------
	virtual void    OnFlightPlanDisconnect (EuroScopePlugIn::CFlightPlan FlightPlan);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnFlightPlanFlightPlanDataUpdate-------------------------------------
	virtual void    OnFlightPlanFlightPlanDataUpdate (EuroScopePlugIn::CFlightPlan FlightPlan);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnFlightPlanControllerAssignedDataUpdate-------------------------------------
	virtual void    OnFlightPlanControllerAssignedDataUpdate (EuroScopePlugIn::CFlightPlan FlightPlan, int DataType);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnFlightPlanControllerAssignedDataUpdate-------------------------------------
	virtual void    OnControllerDisconnect (EuroScopePlugIn::CController Controller);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnFlightPlanControllerAssignedDataUpdate-------------------------------------
	virtual void	OnControllerPositionUpdate (EuroScopePlugIn::CController Controller);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnCompileCommand-------------------------------------
	virtual bool    OnCompileCommand (const char * sCommandLine);
	//------------------------------------------------------------------
	//  The command compiler.
	//------------------------------------------------------------------


	//---OnTimer-------------------------------------
	virtual void    OnTimer (int Counter);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnFunctionCall-----------------------------------------
	virtual void    OnFunctionCall (int FunctionId, const char * sItemString, POINT Pt, RECT Area);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------

};

