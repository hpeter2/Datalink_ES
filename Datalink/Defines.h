#pragma once
#include <EuroScopePlugIn.h>
#include "Logger.h"


#define MY_PLUGIN_NAME      "Datalink Plugin"
#define MY_PLUGIN_VERSION   "2.0.0.2"
#define MY_PLUGIN_DEVELOPER "Hendrik Peter"
#define MY_PLUGIN_COPYRIGHT "Free to be distributed"
#define MY_PLUGIN_VIEW      "Standard ES radar screen"


struct Wpn
{
	const char* name;
	EuroScopePlugIn::CPosition position;
};

struct xController
{
	CString callsign;
	CString spokenCallsign;
	int facility;
	double freq;
	bool valid;
};

struct yController
{
	CString callsign;
	CString spokenCallsign;
};

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

const COLORREF	COLOR_BLACK = RGB(1, 1, 1); //Window Framing
const COLORREF	COLOR_WHITE = RGB(255, 254, 255); //Header Button Framing
const COLORREF	COLOR_ERROR = RGB(137, 19, 19); //
const COLORREF	COLOR_GREEN = RGB(155, 255, 148); //Response Pending Color
const COLORREF	COLOR_BLUE = RGB(14, 1, 54);	  //Header & Button Inner-Background
const COLORREF	COLOR_BLUE_HIGHLIGHT = RGB(145, 180, 203); //Default Data Text Color
const COLORREF	COLOR_BUTTON = RGB(165, 165, 165); // Header Text & Button Symbol & Text Color
const COLORREF	COLOR_BUTTON_HIGHLIGHT = RGB(210, 193, 49); //
const COLORREF	COLOR_FRAME = RGB(42, 42, 42); //Frame Background & Selected AC Background
const COLORREF	COLOR_FRAME_HIGHLIGHT = RGB(74, 75, 74); //AC List Border & Button Outer-Background & Non-Selected AC Background


const int		L_DEF = 0;
const int		L_OFF = 1;
const int		L_EX = 1;
const int		L_ON = 1;
const int		L_LOGON = 2;
const int		L_ERR = 2;
const int		L_RPLY = 2;
const int		L_DCL = 3;

const int		FRAME = 499;
const int		ITEM_AIRCRAFT = 500;
const int		AREA_HEADER = 0;
const int		AREA_AIRCRAFT = 1;
const int		AREA_DATA = 2;

const int		BUTTON_ICONIFY = 3;
const int		BUTTON_CLOSE = 4;
const int		BUTTON_LVL = 5;
const int		BUTTON_ROUTE = 6;
const int		BUTTON_VCI = 7;
const int		BUTTON_SSR = 8;
const int		BUTTON_RST = 9;
const int		BUTTON_MIKE = 10;
const int		BUTTON_EXECUTE = 11;
const int		BUTTON_CLIMB = 12;
const int		BUTTON_DESCEND = 13;
const int		BUTTON_MAINTN = 14;
const int		BUTTON_MAXROC = 15;
const int		BUTTON_MINROC = 16;
const int		BUTTON_CONTHDG = 17;
const int		BUTTON_FLYHDG = 18;
const int		BUTTON_DCTTO = 19;
const int		BUTTON_TURNLDEG = 20;
const int		BUTTON_TURNRDEG = 21;
const int		BUTTON_ACC = 22;
const int		BUTTON_SBY = 23;
const int		BUTTON_UNA = 24;
const int		BUTTON_UDT = 25;
const int		BUTTON_UDA = 26;
const int		BUTTON_NSSR = 27;
const int		BUTTON_SQIDENT = 28;
const int		BUTTON_AUTO = 29;
const int		BUTTON_MIKECURR = 30;
const int		BUTTON_MIKEALL = 31;
const int		BUTTON_DIM = 32;
const int		BUTTON_BRIGHT = 33;
const int		BUTTON_CNTCT = 34;
const int		BUTTON_LOGOFF = 35;
const int		BUTTON_LVL_SBY = 36;
const int		BUTTON_LVL_UNA = 37;
const int		BUTTON_ROUTE_SBY = 38;
const int		BUTTON_ROUTE_UNA = 39;
const int		BUTTON_PDC = 40;
const int		BUTTON_DCL_DCL = 41;
const int		BUTTON_DCL_UNA = 42;

const int		BUTTON_LVL_EX = 50;
const int		BUTTON_ROUTE_EX = 51;

//const   int     BUTTON_LEFT = 1;
//const   int     BUTTON_MIDDLE = 2;
//const   int     BUTTON_RIGHT = 3;

const   int		MSG_TELEX = 0;
const   int		MSG_CPDLC = 1;
const   int		MSG_ADSC = 2;
const   int		MSG_POLL = 3;
const   int		MSG_PEK = 4;
const   int		MSG_PING = 5;
const   bool	MSG_SEND = false;
const   bool	MSG_RECEIVE = true;

const   int		VICINITY_LIST = 1;
const   int		HOPPIE_LIST = 2;
const   int		CONTROLLER_LIST = 3;
const   int		SPOKEN_LIST = 4;
