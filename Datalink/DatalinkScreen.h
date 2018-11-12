#pragma once
#include <EuroScopePlugIn.h>
#include "Resource.h"
#include "Defines.h"
#include "Util.h"
#include "S.h"

using namespace std;
using namespace EuroScopePlugIn;

class CDatalinkScreen : public EuroScopePlugIn::CRadarScreen,
						public CDialog
{
private:
	int		xOffset, yOffset, buttonHighlight, buttonDown;
	bool	hidden, listOpen, once;
	CString	data[6];

	CUtil &util;

	CBrush		br_frame, br_frameHighlight;
	CRect		rDataLink, *rSub = new CRect[11], *rAc = new CRect[3];
	CBitmap		b_header[3], b_data, b_aircraft, b_aircraftSelected, b_aircraftClear,
				b_btn1[4], b_btn2[4], b_btn3[4], b_btn4[4], b_btn5[4], b_btn6[4],
				b_lvl[3], b_route[3], b_ssr, b_mike, b_vci;


public:
	CDatalinkScreen ();
	virtual ~CDatalinkScreen();


protected:
	void HighlightButton(CDC * pDC, const CRect & DisplayArea);
	void HighlightDown(CDC * pDC, const CRect & DisplayArea);
	//BOOL HoppieConnect();
	//POSITION    _SelectFixFromList(const char * fix);

	/////////////////////////////////////////////////////////////////////////////
	// EuroScopePlugIn message handlers
	//
	//---OnAsrContentLoaded--------------------------------------------
	virtual void    OnAsrContentLoaded (bool Loaded);
	//------------------------------------------------------------------
	//  When data is fully loaded.
	//------------------------------------------------------------------


	//---OnAsrContentToBeSaved------------------------------------------
	virtual void    OnAsrContentToBeSaved (void);
	//------------------------------------------------------------------
	//  When data is to be saved.
	//------------------------------------------------------------------


	//---OnRefresh------------------------------------------------------
	virtual void    OnRefresh (HDC hDC, int Phase);
	//------------------------------------------------------------------
	//  The screen refresh function.
	//------------------------------------------------------------------


	//---OnCompileCommand-----------------------------------------------
	virtual bool    OnCompileCommand (const char * sCommandLine);
	//------------------------------------------------------------------
	//  The radar command compiler.
	//------------------------------------------------------------------


	//---OnAsrContentToBeClosed-----------------------------------------
	inline virtual void    OnAsrContentToBeClosed (void)
	{
		delete this;
	}


	//---OnOverScreenObject-----------------------------------------
	virtual void    OnOverScreenObject (int ObjectType, const char * sObjectId, POINT Pt, RECT Area);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnButtonDownScreenObject-----------------------------------------
	virtual void    OnButtonDownScreenObject (int ObjectType, const char * sObjectId, POINT Pt, RECT Area, int Button);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnButtonUpScreenObject-----------------------------------------
	virtual void    OnButtonUpScreenObject (int ObjectType, const char * sObjectId, POINT Pt, RECT Area, int Button);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnClickScreenObject-----------------------------------------
	virtual void    OnClickScreenObject (int ObjectType, const char * sObjectId, POINT Pt, RECT Area, int Button);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------


	//---OnMoveScreenObject-----------------------------------------
	virtual void	OnMoveScreenObject (int ObjectType, const char * sObjectId, POINT Pt, RECT Area, bool Released);
	//------------------------------------------------------------------
	//  The screen item mover.
	//------------------------------------------------------------------


	//---OnFunctionCall-----------------------------------------
	virtual void    OnFunctionCall (int FunctionId, const char * sItemString, POINT Pt, RECT Area);
	//------------------------------------------------------------------
	//  
	//------------------------------------------------------------------

};

