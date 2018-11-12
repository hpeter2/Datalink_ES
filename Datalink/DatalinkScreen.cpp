#include "stdafx.h"
#include "DatalinkScreen.h"


CDatalinkScreen::CDatalinkScreen() :	util(S::getUtilInstance())
{
	Logger::Log("SYSTEM: CDatalinkScreen()");

	// default values
	xOffset = 0;
	yOffset = 0;
	buttonHighlight = -1;
	buttonDown = -1;
	util.buttonList = -1;
	util.hoppie.selectedItem = -1;
	

	hidden = false;
	listOpen = false;
	util.configOpen = false;
	once = false;


	HINSTANCE hInstance = AfxGetInstanceHandle();

	br_frame.CreateSolidBrush(COLOR_FRAME);
	br_frameHighlight.CreateSolidBrush(COLOR_FRAME_HIGHLIGHT);

	b_header[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_HEADER), IMAGE_BITMAP, 0, 0, 0);
	b_header[L_ON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_HEADER_CONNECTED), IMAGE_BITMAP, 0, 0, 0);
	b_header[L_ERR].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_HEADER_ERROR), IMAGE_BITMAP, 0, 0, 0);

	b_data.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_DATA), IMAGE_BITMAP, 0, 0, 0);
	b_aircraft.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_AIRCRAFT), IMAGE_BITMAP, 0, 0, 0);
	b_aircraftSelected.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_AIRCRAFT_SELECTED), IMAGE_BITMAP, 0, 0, 0);
	b_aircraftClear.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_AIRCRAFT_CLEAR), IMAGE_BITMAP, 0, 0, 0);

	b_btn1[L_LOGON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN1_LOG), IMAGE_BITMAP, 0, 0, 0);
	b_btn1[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN1_OFF), IMAGE_BITMAP, 0, 0, 0);
	b_btn1[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN1), IMAGE_BITMAP, 0, 0, 0);
	b_btn1[L_DCL].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN1_DCL), IMAGE_BITMAP, 0, 0, 0);

	//b_btn2[0].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN2_LOG_OFF), IMAGE_BITMAP, 0, 0, 0);
	b_btn2[L_LOGON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN2_LOG), IMAGE_BITMAP, 0, 0, 0);
	b_btn2[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN2_OFF), IMAGE_BITMAP, 0, 0, 0);
	b_btn2[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN2), IMAGE_BITMAP, 0, 0, 0);
	b_btn2[L_DCL].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN2_DCL), IMAGE_BITMAP, 0, 0, 0);

	b_btn3[L_LOGON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN3_LOG), IMAGE_BITMAP, 0, 0, 0);
	b_btn3[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN3_OFF), IMAGE_BITMAP, 0, 0, 0);
	b_btn3[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN3), IMAGE_BITMAP, 0, 0, 0);
	b_btn3[L_DCL].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN3_DCL), IMAGE_BITMAP, 0, 0, 0);

	b_btn4[L_LOGON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN4_LOG), IMAGE_BITMAP, 0, 0, 0);
	b_btn4[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN4_OFF), IMAGE_BITMAP, 0, 0, 0);
	b_btn4[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN4), IMAGE_BITMAP, 0, 0, 0);
	b_btn4[L_DCL].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN4_DCL), IMAGE_BITMAP, 0, 0, 0);

	b_btn5[L_LOGON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN5_LOG), IMAGE_BITMAP, 0, 0, 0);
	b_btn5[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN5_CLEAR), IMAGE_BITMAP, 0, 0, 0);
	b_btn5[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN5_CLEAR), IMAGE_BITMAP, 0, 0, 0);
	b_btn5[L_DCL].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN5_DCL), IMAGE_BITMAP, 0, 0, 0);

	b_btn6[L_LOGON].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN6_LOG), IMAGE_BITMAP, 0, 0, 0);
	b_btn6[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN6_OFF), IMAGE_BITMAP, 0, 0, 0);
	b_btn6[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN6), IMAGE_BITMAP, 0, 0, 0);
	b_btn6[L_DCL].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BTN6_DCL), IMAGE_BITMAP, 0, 0, 0);

	b_lvl[L_EX].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_LVL_EX), IMAGE_BITMAP, 0, 0, 0);
	b_lvl[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_LVL), IMAGE_BITMAP, 0, 0, 0);
	b_lvl[L_RPLY].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_LVL_RPLY), IMAGE_BITMAP, 0, 0, 0);

	b_route[L_EX].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_ROUTE_EX), IMAGE_BITMAP, 0, 0, 0);
	b_route[L_DEF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_ROUTE), IMAGE_BITMAP, 0, 0, 0);
	b_route[L_RPLY].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_ROUTE_RPLY), IMAGE_BITMAP, 0, 0, 0);

	b_ssr.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_SSR), IMAGE_BITMAP, 0, 0, 0);
	//b_ssr[L_OFF].m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_SSR_STOP), IMAGE_BITMAP, 0, 0, 0);

	b_mike.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_MIKE), IMAGE_BITMAP, 0, 0, 0);
	b_vci.m_hObject = LoadImage(hInstance, MAKEINTRESOURCE(IDB_VCI), IMAGE_BITMAP, 0, 0, 0);

}


CDatalinkScreen::~CDatalinkScreen()
{
	Logger::Log("SYSTEM: ~CDatalinkScreen()");
	delete rSub;
	delete rAc;
}


//---HighlightButton------------------------------------------------
void	CDatalinkScreen::HighlightButton(CDC * pDC, const CRect & DisplayArea)
{
	CPen	highlight_pen(PS_SOLID, 0, COLOR_BUTTON_HIGHLIGHT);
	CPen*   orig_pen = pDC->SelectObject(&highlight_pen);

	//Draw outer Frame Line (Black)
	pDC->MoveTo(DisplayArea.left, DisplayArea.bottom);
	pDC->LineTo(DisplayArea.left, DisplayArea.top);
	pDC->LineTo(DisplayArea.right, DisplayArea.top);
	pDC->LineTo(DisplayArea.right, DisplayArea.bottom);
	pDC->LineTo(DisplayArea.left, DisplayArea.bottom);

	//Restore
	pDC->SelectObject(orig_pen);
}


//---HighlightDown------------------------------------------------
void	CDatalinkScreen::HighlightDown(CDC * pDC, const CRect & DisplayArea)
{
	CPen	highlight_pen_blue(PS_SOLID, 0, COLOR_BLUE),
			highlight_pen_frame(PS_SOLID, 0, COLOR_FRAME_HIGHLIGHT);
	CPen*   orig_pen = pDC->SelectObject(&highlight_pen_blue);

	pDC->MoveTo(DisplayArea.left + 1, DisplayArea.bottom - 2);
	pDC->LineTo(DisplayArea.left + 1, DisplayArea.top + 1);
	pDC->LineTo(DisplayArea.right - 1, DisplayArea.top + 1);

	pDC->SelectObject(&highlight_pen_frame);
	pDC->MoveTo(DisplayArea.left + 1, DisplayArea.bottom - 1);
	pDC->LineTo(DisplayArea.left + 1, DisplayArea.bottom - 1);
	pDC->MoveTo(DisplayArea.right - 1, DisplayArea.top + 1);
	pDC->LineTo(DisplayArea.right - 2, DisplayArea.top + 1);

	//Restore
	pDC->SelectObject(orig_pen);
}


/////////////////////////////////////////////////////////////////////////////
// EuroScopePlugIn message handlers
//
//---OnAsrContentLoaded--------------------------------------------
void    CDatalinkScreen::OnAsrContentLoaded(bool Loaded)
{

}


//---OnAsrContentToBeSaved------------------------------------------
void    CDatalinkScreen::OnAsrContentToBeSaved(void) 
{

}


//---OnRefresh------------------------------------------------------
void    CDatalinkScreen::OnRefresh(HDC hDC, int Phase) 
{
	// Only in first phase && Don't Draw, if Window hidden
	if (Phase != EuroScopePlugIn::REFRESH_PHASE_AFTER_LISTS || hidden)
		return;

	// If no Item or an Deleted Item is Selected, select last One by default.
	if (util.hoppie.selectedItem == -1) {
		if (util.hoppie.hoppieList.GetCount() > 0)
			util.hoppie.selectedItem = util.hoppie.hoppieList.GetCount() - 1;
	}
	else if (util.hoppie.selectedItem >= util.hoppie.hoppieList.GetCount()) {
		if (util.hoppie.hoppieList.GetCount() > 0)
			util.hoppie.selectedItem = util.hoppie.hoppieList.GetCount() - 1;
		else
			util.hoppie.selectedItem = -1;
	}

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//  I am using MFC, so load the DC in to MFC structure and Attach it
	//------------------------------------------------------------------
	CDC		dc;
	CDC		*mdc = new CDC;

	dc.Attach(hDC);
	mdc->CreateCompatibleDC(&dc);

	//------------------------------------------------------------------
	//  Load Fonts && Black Pen && Backup current Font & Pen
	//------------------------------------------------------------------
	CFont	*orig_font, data_font, button_font, buttonDotted_font;
	CPen	*orig_pen, black_pen(0, 0, COLOR_BLACK);

	data_font.CreatePointFont(120, "Datalink Data", &dc);
	button_font.CreatePointFont(120, "Datalink Button", &dc);
	buttonDotted_font.CreatePointFont(120, "Datalink Button Dotted", &dc);

	orig_font = dc.SelectObject(&data_font);
	orig_pen = dc.SelectObject(&black_pen);


	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//  Set Frame Area to x & y (loaded or default Value)
	//------------------------------------------------------------------
	rDataLink = GetRadarArea();

	if (util.hoppie.y > rDataLink.top)
		rDataLink.top = util.hoppie.y;

	if (util.hoppie.x > rDataLink.left)
		rDataLink.left = util.hoppie.x;

	rDataLink.right = rDataLink.left + 411;

	//------------------------------------------------------------------
	//  Set Header Frame Area & Draw Header Bitmap
	//------------------------------------------------------------------
	rSub[0].SetRect(rDataLink.left + 1, rDataLink.top + 1, rDataLink.left + 23, rDataLink.top + 23); //Iconify
	rSub[1].SetRect(rDataLink.left + 24, rDataLink.top + 1, rDataLink.right - 24, rDataLink.top + 23); //Header
	rSub[2].SetRect(rDataLink.right - 23, rDataLink.top + 1, rDataLink.right - 1, rDataLink.top + 23); //Close

	//------------------------------------------------------------------
	//  Register Frame as Object to detect Mouse leaving other Areas (OnOver)
	//  If a Submenu is Open, extend the Frame to surround it too
	if (util.hoppie.iconify) {
		//------------------------------------------------------------------
		//  Nothing below Header is created. Draw Line around Header only (Black)
		//------------------------------------------------------------------
		//------------------------------------------------------------------
		rDataLink.bottom = rSub[0].bottom;
		rDataLink.SetRect(rDataLink.left - 10, rDataLink.top - 10, rDataLink.right + 10, rDataLink.bottom + 10);
		AddScreenObject(FRAME, "DATALINK_FRAME", rDataLink, false, NULL);
		rDataLink.SetRect(rDataLink.left + 10, rDataLink.top + 10, rDataLink.right - 10, rDataLink.bottom - 10);

		// Draw outer Frame Line (Black)
		dc.MoveTo(rDataLink.TopLeft());
		dc.LineTo(rDataLink.left, rDataLink.bottom);
		dc.LineTo(rDataLink.right - 1, rDataLink.bottom);
		dc.LineTo(rDataLink.right - 1, rDataLink.top);
		dc.LineTo(rDataLink.TopLeft());
	}
	else {
		//------------------------------------------------------------------
		//  Set Frame bottom (needed for later Calculations) & Take AC List into Account
		//  1 Row will always be displayed in AC List, even if List is empty
		//------------------------------------------------------------------
		if (util.hoppie.hoppieList.GetCount() > 0)
			rDataLink.bottom = rDataLink[0].bottom + 7 + util.hoppie.hoppieList.GetCount() * 22 + 125;
		else
			rDataLink.bottom = rDataLink[0].bottom + 7 + 22 + 125;

		//------------------------------------------------------------------
		//  Register Frame as Object to detect Mouse leaving other Areas (OnOver)
		//  If a Submenu is Open, extend the Frame to surround it too
		//------------------------------------------------------------------
		if (util.buttonList == -1) {
			rDataLink.SetRect(rDataLink.left - 10, rDataLink.top - 10, rDataLink.right + 10, rDataLink.bottom + 10);
			AddScreenObject(FRAME, "DATALINK_FRAME", rDataLink, false, NULL);
			rDataLink.SetRect(rDataLink.left + 10, rDataLink.top + 10, rDataLink.right - 10, rDataLink.bottom - 10);
		}
		else {
			rDataLink.SetRect(rDataLink.left - 10, rDataLink.top - 10, rDataLink.right + 10, rDataLink.bottom + 191);
			AddScreenObject(FRAME, "DATALINK_FRAME", rDataLink, false, NULL);
			rDataLink.SetRect(rDataLink.left + 10, rDataLink.top + 10, rDataLink.right - 10, rDataLink.bottom - 191);
		}


		//------------------------------------------------------------------
		//  Draw AC List
		//  
		//------------------------------------------------------------------

		int iMax = 0;

		
		// Draw AC List TOP
		rSub[3].SetRect(rDataLink.left + 1, rSub[2].bottom, rDataLink.right - 1, rSub[2].bottom + 3);
		dc.FillRect(&rSub[3], &br_frameHighlight);

		dc.MoveTo(rDataLink.left, rSub[3].top);
		dc.LineTo(rDataLink.left, rSub[3].bottom);
		dc.MoveTo(rDataLink.right - 1, rSub[3].top);
		dc.LineTo(rDataLink.right - 1, rSub[3].bottom);


		// If AC List is empty, draw 1 empty Row
		if (util.hoppie.hoppieList.GetCount() > 0)
			iMax = util.hoppie.hoppieList.GetCount();
		else
			iMax = 1;


		// Create AC List Rows
		for (int i = 0; i < iMax; ++i)
		{
			if (util.hoppie.hoppieList.GetCount() != 0)
			{
				if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected != 5)
				{
					// Current Row
					rSub[3].SetRect(rSub[3].left, rSub[3].bottom, rSub[3].right, rSub[3].bottom + 22);


					//------------------------------------------------------------------
					//  If AC List is empty, draw an Row without Data
					//  If Current Row is selected, draw a highlighted Row
					//------------------------------------------------------------------


					if (i == util.hoppie.selectedItem)
						mdc->SelectObject(b_aircraftSelected);
					else
						mdc->SelectObject(b_aircraft);

					// Actual Drawing && Register Current Row 
					dc.BitBlt(rDataLink.left, rSub[3].top, rDataLink.right, 22, mdc, 0, 0, SRCCOPY);
					AddScreenObject(ITEM_AIRCRAFT + i, "DATALINK_AIRCRAFT" + i, rSub[3], false, NULL);


					//------------------------------------------------------------------
					//  Fill Current Row with Data
					//  If AC hasn't answered to Open Message yet, highlight its Name
					//  Dont execute, if AC List is empty
					//------------------------------------------------------------------
					if (util.hoppie.hoppieList.GetCount() != 0)
					{
						if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelTimer >= 120)
						{
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelTimer = 0;
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelATCId = "";
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Level.Insert(2, "NRPLY/\0");
						}
						if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteTimer >= 120)
						{
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteTimer = 0;
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteATCId = "";
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Route.Insert(2, "NRPLY/\0");
						}
						if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRTimer >= 120)
						{
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRTimer = 0;
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRATCId = "";
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSR.Insert(2, "NRPLY/\0");
						}
						if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceTimer >= 120)
						{
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceTimer = 0;
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceATCId = "";
							util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Voice.Insert(2, "NRPLY/\0");
						}

						if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected == 0 || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected == 4)
							dc.SetTextColor(COLOR_ERROR); //CONN LOSS

						else if (i == util.hoppie.selectedItem && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected == 2)
							dc.SetTextColor(COLOR_FRAME_HIGHLIGHT); //FIX: OTHER COLOR ON LOGOFF REQUEST

						else if (i != util.hoppie.selectedItem && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected == 2)
							dc.SetTextColor(COLOR_FRAME); //FIX: OTHER COLOR ON LOGOFF REQUEST

						else if ((util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelATCId != "" && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelTimer >= 30) || (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteATCId != "" && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteTimer >= 30) || (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRATCId != "" && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRTimer >= 30) || (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceATCId != "" && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceTimer >= 30))
							dc.SetTextColor(COLOR_ERROR); //UNANSWERED AC MESSAGE

						else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelId != "" || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteId != "" || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRId != "" || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceId != "")
							dc.SetTextColor(COLOR_GREEN); //UNANSWERED AC MESSAGE

						else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_LevelATCId != "" || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_RouteATCId != "" || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_SSRATCId != "" || util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_VoiceATCId != "")
							dc.SetTextColor(COLOR_GREEN); //UNANSWERED ATC MESSAGE

						else if (i == util.hoppie.selectedItem)
							dc.SetTextColor(COLOR_WHITE);
						else
							dc.SetTextColor(COLOR_BLUE_HIGHLIGHT);


						// Actual Text Drawing
						rSub[3].top += 2;
						rSub[3].left += 5;


						if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Connected == 6) {
							dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign.GetBuffer(0), -1, rSub[3], DT_SINGLELINE | DT_VCENTER | DT_LEFT, NULL);
						}
						else
							dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(i)).m_Callsign.GetBuffer(0), -1, rSub[3], DT_SINGLELINE | DT_VCENTER | DT_LEFT, NULL);
						rSub[3].left -= 5;
						rSub[3].top -= 2;
					}
				}
			}
			else
			{
				// Current Row
				rSub[3].SetRect(rSub[3].left, rSub[3].bottom, rSub[3].right, rSub[3].bottom + 22);

				mdc->SelectObject(b_aircraftClear);
				// Actual Drawing && Register Current Row 
				dc.BitBlt(rDataLink.left, rSub[3].top, rDataLink.right, 22, mdc, 0, 0, SRCCOPY);
				AddScreenObject(ITEM_AIRCRAFT + i, "DATALINK_AIRCRAFT" + i, rSub[3], false, NULL);
			}
		}


		// Draw AC List BOTTOM
		rSub[3].SetRect(rDataLink.left + 1, rSub[3].bottom, rDataLink.right - 1, rSub[3].bottom + 3);
		dc.FillRect(&rSub[3], &br_frameHighlight);

		dc.MoveTo(rDataLink.left, rSub[3].top);
		dc.LineTo(rDataLink.left, rSub[3].bottom);
		dc.MoveTo(rDataLink.right - 1, rSub[3].top);
		dc.LineTo(rDataLink.right - 1, rSub[3].bottom);


		// Create next Rect's based on rSub[3] (AC List)
		rSub[10].SetRect(rDataLink.left + 1, rSub[3].bottom, rDataLink.right - 1, rSub[3].bottom + 100);	//DATA FRAME

		rSub[4].SetRect(rDataLink.left, rDataLink.bottom - 26, rDataLink.left + 59, rDataLink.bottom - 2); //LVL
		rSub[5].SetRect(rSub[4].right + 2, rSub[4].top, rSub[4].right + 60, rSub[4].bottom); //ROUTE
		rSub[6].SetRect(rSub[5].right + 2, rSub[5].top, rSub[5].right + 60, rSub[5].bottom); //CONT
		rSub[7].SetRect(rSub[6].right + 2, rSub[6].top, rSub[6].right + 60, rSub[6].bottom); //SSR
		rSub[8].SetRect(rSub[7].right + 2, rSub[7].top, rSub[7].right + 109, rSub[7].bottom); //RST/STANDBY
		rSub[9].SetRect(rSub[8].right + 2, rSub[8].top, rDataLink.right, rSub[8].bottom);	//MIKE


		// Draw Bottom Bitmap (Data Frame && Buttons)
		mdc->SelectObject(b_data);
		dc.BitBlt(rDataLink.left, rSub[10].top, rDataLink.right, 101, mdc, 0, 0, SRCCOPY);


		if (util.hoppie.selectedItem > -1)
		{
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected == 3)
			{
				mdc->SelectObject(b_btn1[L_LOGON]);
				dc.BitBlt(rSub[4].left, rSub[4].top, rSub[4].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn2[L_LOGON]);
				dc.BitBlt(rSub[5].left, rSub[5].top, rSub[5].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn3[L_LOGON]);
				dc.BitBlt(rSub[6].left, rSub[6].top, rSub[6].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn4[L_LOGON]);
				dc.BitBlt(rSub[7].left, rSub[7].top, rSub[7].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn5[L_LOGON]);
				dc.BitBlt(rSub[8].left, rSub[8].top, rSub[8].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn6[L_LOGON]);
				dc.BitBlt(rSub[9].left, rSub[9].top, rSub[9].right, 26, mdc, 0, 0, SRCCOPY);
			}
			else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected == 6)
			{
				mdc->SelectObject(b_btn1[L_DCL]);
				dc.BitBlt(rSub[4].left, rSub[4].top, rSub[4].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn2[L_DCL]);
				dc.BitBlt(rSub[5].left, rSub[5].top, rSub[5].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn3[L_DCL]);
				dc.BitBlt(rSub[6].left, rSub[6].top, rSub[6].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn4[L_DCL]);
				dc.BitBlt(rSub[7].left, rSub[7].top, rSub[7].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn5[L_DCL]);
				dc.BitBlt(rSub[8].left, rSub[8].top, rSub[8].right, 26, mdc, 0, 0, SRCCOPY);

				mdc->SelectObject(b_btn6[L_DCL]);
				dc.BitBlt(rSub[9].left, rSub[9].top, rSub[9].right, 26, mdc, 0, 0, SRCCOPY);
			}
			else
			{
				if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelATCId != "")
					mdc->SelectObject(b_btn1[L_OFF]);
				else
					mdc->SelectObject(b_btn1[L_DEF]);

				dc.BitBlt(rSub[4].left, rSub[4].top, rSub[4].right, 26, mdc, 0, 0, SRCCOPY);


				if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteATCId != "")
					mdc->SelectObject(b_btn2[L_OFF]);
				else
					mdc->SelectObject(b_btn2[L_DEF]);

				dc.BitBlt(rSub[5].left, rSub[5].top, rSub[5].right, 26, mdc, 0, 0, SRCCOPY);


				if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId != "")
					mdc->SelectObject(b_btn3[L_OFF]);
				else
					mdc->SelectObject(b_btn3[L_DEF]);

				dc.BitBlt(rSub[6].left, rSub[6].top, rSub[6].right, 26, mdc, 0, 0, SRCCOPY);


				if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRATCId != "")
					mdc->SelectObject(b_btn4[L_OFF]);
				else
					mdc->SelectObject(b_btn4[L_DEF]);

				dc.BitBlt(rSub[7].left, rSub[7].top, rSub[7].right, 26, mdc, 0, 0, SRCCOPY);


				mdc->SelectObject(b_btn5[L_DEF]);
				dc.BitBlt(rSub[8].left, rSub[8].top, rSub[8].right, 26, mdc, 0, 0, SRCCOPY);


				mdc->SelectObject(b_btn6[L_DEF]);

				dc.BitBlt(rSub[9].left, rSub[9].top, rSub[9].right, 26, mdc, 0, 0, SRCCOPY);
			}
		}
		else
		{
			mdc->SelectObject(b_btn1[L_OFF]);
			dc.BitBlt(rSub[4].left, rSub[4].top, rSub[4].right, 26, mdc, 0, 0, SRCCOPY);
			mdc->SelectObject(b_btn2[L_OFF]);
			dc.BitBlt(rSub[5].left, rSub[5].top, rSub[5].right, 26, mdc, 0, 0, SRCCOPY);
			mdc->SelectObject(b_btn3[L_OFF]);
			dc.BitBlt(rSub[6].left, rSub[6].top, rSub[6].right, 26, mdc, 0, 0, SRCCOPY);
			mdc->SelectObject(b_btn4[L_OFF]);
			dc.BitBlt(rSub[7].left, rSub[7].top, rSub[7].right, 26, mdc, 0, 0, SRCCOPY);
			mdc->SelectObject(b_btn5[L_OFF]);
			dc.BitBlt(rSub[8].left, rSub[8].top, rSub[8].right, 26, mdc, 0, 0, SRCCOPY);
			mdc->SelectObject(b_btn6[L_OFF]);
			dc.BitBlt(rSub[9].left, rSub[9].top, rSub[9].right, 26, mdc, 0, 0, SRCCOPY);
		}



		rSub[4].left += 2;
		rSub[4].top += 1;
		rSub[4].bottom -= 1;
		rSub[5].left += 1;
		rSub[5].top += 1;
		rSub[5].bottom -= 1;
		rSub[6].left += 1;
		rSub[6].top += 1;
		rSub[6].bottom -= 1;
		rSub[7].left += 1;
		rSub[7].top += 1;
		rSub[7].bottom -= 1;
		rSub[8].left += 1;
		rSub[8].top += 1;
		rSub[8].bottom -= 1;
		rSub[9].left += 1;
		rSub[9].top += 1;
		rSub[9].bottom -= 1;
		rSub[9].right -= 2;

		//------------------------------------------------------------------
		//  Fill Data Frame with Data, if an Aircraft is selected (i.e. the List is not empty)
		//------------------------------------------------------------------
		if (util.hoppie.selectedItem != -1)
		{
			// CALLSIGN
			dc.SetTextColor(COLOR_BLUE_HIGHLIGHT);


			rSub[10].top += 6;
			rSub[10].left += 5;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected == 6) {
				dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);
			}
			else
				dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);


			// TEXT AFTER CALLSIGN 
			rSub[10].left += strlen(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign) * 9 + 9;

			if (util.hoppie.error != "")
				data[0] = util.hoppie.error;
			else if (util.hoppie.data.GetCount() > 0)
				data[0] = util.hoppie.data.GetHead();
			else if (util.buttonList == BUTTON_LVL)
				data[0] = "LVL";
			else if (util.buttonList == BUTTON_ROUTE)
				data[0] = "ROUTE";
			else if (util.buttonList == BUTTON_VCI)
				data[0] = "VCI";
			else if (util.buttonList == BUTTON_SSR)
				data[0] = "SSR";
			else if (util.buttonList == BUTTON_RST)
				data[0] = "RST";
			else if (util.buttonList == BUTTON_MIKE)
				data[0] = "MIKE";
			else if (util.hoppie.popupList == BUTTON_CLIMB)
				data[0] = "CLIMB";
			else if (util.hoppie.popupList == BUTTON_DESCEND)
				data[0] = "DESCEND";
			else if (util.hoppie.popupList == BUTTON_MAINTN)
				data[0] = "MAINTAIN";
			else if (util.hoppie.popupList == BUTTON_FLYHDG)
				data[0] = "FLY HDG";
			else if (util.hoppie.popupList == BUTTON_CONTHDG)
				data[0] = "CONT PRSTN HDG";
			else if (util.hoppie.popupList == BUTTON_DCTTO)
				data[0] = "DCT TO";
			else if (util.hoppie.popupList == BUTTON_TURNLDEG)
				data[0] = "DEG L";
			else if (util.hoppie.popupList == BUTTON_TURNRDEG)
				data[0] = "DEG R";
			else if (util.hoppie.popupList == BUTTON_CNTCT)
				data[0] = "CNTCT";
			else if (util.hoppie.popupList == BUTTON_PDC || util.hoppie.popupList == BUTTON_DCL_DCL)
				data[0] = "PDC";

			dc.DrawTextEx(data[0].GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);


			// LEVEL
			rSub[10].top += 17;
			rSub[10].left = rDataLink.left + 8;


			data[1] = "L ";

			dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);


			// ROUTE
			rSub[10].top += 20;
			dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);


			// VOICE
			rSub[10].top += 20;
			dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);


			// INFO
			rSub[10].top += 20;
			dc.DrawTextEx(util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSR.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);

			rSub[10].left -= 5 - 2;
			rSub[10].top -= 6 - 17 - 20 - 20 - 20;
		}
		else if (util.hoppie.error != "")
		{
			dc.SetTextColor(COLOR_BLUE_HIGHLIGHT);

			rSub[10].top += 6;
			rSub[10].left += 5;

			dc.DrawTextEx(util.hoppie.error.GetBuffer(0), -1, rSub[10], DT_SINGLELINE | DT_TOP | DT_LEFT, NULL);
		}
	}

	// Header
	if (!util.hoppie.hoppieConnected && util.hoppie.error == "")
		mdc->SelectObject(b_header[L_DEF]);
	else if (util.hoppie.hoppieConnected == 1)
		mdc->SelectObject(b_header[L_ON]);
	else
		mdc->SelectObject(b_header[L_ERR]);
	dc.BitBlt(rDataLink.left, rDataLink.top, rDataLink.right, 23, mdc, 0, 0, SRCCOPY);

	// Register Interactable Items HEADER
	AddScreenObject(BUTTON_ICONIFY, "DATALINK_ICONIFY", rSub[0], true, NULL);
	AddScreenObject(AREA_HEADER, "DATALINK_HEADER", rSub[1], true, NULL);
	AddScreenObject(BUTTON_CLOSE, "DATALINK_CLOSE", rSub[2], false, NULL);

	// Highlight Header Button, if MouseOver (Outside of !iconify)
	if ((buttonHighlight == BUTTON_ICONIFY || buttonHighlight == BUTTON_CLOSE) && util.buttonList == -1) {
		if (buttonHighlight == BUTTON_ICONIFY)
			HighlightButton(&dc, rSub[0]);
		else if (buttonHighlight == BUTTON_CLOSE)
			HighlightButton(&dc, rSub[2]);
	}


	// Data Frame
	rSub[10].SetRect(rDataLink.left + 1, rSub[3].bottom, rDataLink.right - 1, rSub[3].bottom + 100);	//DATA FRAME
	AddScreenObject(AREA_DATA, "DATALINK_DATA_FRAME", rSub[10], false, NULL);




	//------------------------------------------------------------------
	//  LOWER BUTTONS
	//  Don't Register them, if a Submenu is displayed over them
	//------------------------------------------------------------------

	if (util.hoppie.selectedItem != -1)
	{
		if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected == 3)
		{
			AddScreenObject(BUTTON_ACC, "DATALINK_LVL", rSub[4], false, NULL);
			AddScreenObject(BUTTON_SBY, "DATALINK_ROUTE", rSub[5], false, NULL);
			AddScreenObject(BUTTON_UNA, "DATALINK_CONT", rSub[6], false, NULL);
			AddScreenObject(BUTTON_UDT, "DATALINK_SSR", rSub[7], false, NULL);
			AddScreenObject(BUTTON_UDA, "DATALINK_RST", rSub[8], false, NULL);

			util.buttonList = -1;
		}
		else if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected == 6)
		{
			//AddScreenObject(BUTTON_DCL_DCL, "DATALINK_LVL", rSub[4], false, NULL);
			//AddScreenObject(BUTTON_DCL_UNA, "DATALINK_ROUTE", rSub[5], false, NULL);

			util.buttonList = -1;
		}
		else
		{
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelATCId == "")
				AddScreenObject(BUTTON_LVL, "DATALINK_LVL", rSub[4], false, NULL);

			if (util.buttonList != BUTTON_LVL && util.buttonList != BUTTON_LVL_EX && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteATCId == "")
				AddScreenObject(BUTTON_ROUTE, "DATALINK_ROUTE", rSub[5], false, NULL);
			if (util.buttonList != BUTTON_ROUTE && util.buttonList != BUTTON_ROUTE_EX && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId == "")
				AddScreenObject(BUTTON_VCI, "DATALINK_CONT", rSub[6], false, NULL);
			if (util.buttonList != BUTTON_VCI && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRATCId == "")
				AddScreenObject(BUTTON_SSR, "DATALINK_SSR", rSub[7], false, NULL);
			//if (util.buttonList != BUTTON_SSR && util.buttonList != BUTTON_MIKE) 
			//	AddScreenObject(BUTTON_RST, "DATALINK_RST", rSub[8], false, NULL);

			AddScreenObject(BUTTON_MIKE, "DATALINK_MIKE", rSub[9], false, NULL);
		}
	}
	else
	{
		/*
		AddScreenObject(BUTTON_LVL, "DATALINK_LVL", rSub[4], false, NULL);
		if (buttonList != BUTTON_LVL && buttonList < BUTTON_CLIMB && buttonList > BUTTON_MINROC && buttonList != BUTTON_LVL_EX) AddScreenObject(BUTTON_ROUTE, "DATALINK_ROUTE", rSub[5], false, NULL);
		if (buttonList != BUTTON_ROUTE) AddScreenObject(BUTTON_VCI, "DATALINK_CONT", rSub[6], false, NULL);
		if (buttonList != BUTTON_VCI && buttonList < BUTTON_CONTHDG && buttonList > BUTTON_TURNRDEG) AddScreenObject(BUTTON_SSR, "DATALINK_SSR", rSub[7], false, NULL);
		if (buttonList != BUTTON_SSR && buttonList != BUTTON_MIKE) AddScreenObject(BUTTON_RST, "DATALINK_RST", rSub[8], false, NULL);
		if (buttonList != BUTTON_RST) AddScreenObject(BUTTON_MIKE, "DATALINK_MIKE", rSub[9], false, NULL);

		AddScreenObject(BUTTON_LVL, "DATALINK_LVL", rSub[4], false, NULL);
		AddScreenObject(BUTTON_ROUTE, "DATALINK_ROUTE", rSub[5], false, NULL);
		AddScreenObject(BUTTON_VCI, "DATALINK_CONT", rSub[6], false, NULL);
		AddScreenObject(BUTTON_SSR, "DATALINK_SSR", rSub[7], false, NULL);
		AddScreenObject(BUTTON_RST, "DATALINK_RST", rSub[8], false, NULL);
		AddScreenObject(BUTTON_MIKE, "DATALINK_MIKE", rSub[9], false, NULL);
		*/
	}

	//------------------------------------------------------------------
	//  Create Submenu, if a Button got Clicked
	//------------------------------------------------------------------
	if ((util.buttonList > -1 && util.buttonList <= BUTTON_MIKE) || util.buttonList >= BUTTON_LVL_EX)
	{
		util.listRect.top = rSub[4].top;
		util.listRect.bottom = rSub[4].bottom + 181;

		if (util.buttonList == BUTTON_LVL)
		{
			util.listRect.left = rSub[5].left;
			util.listRect.right = rSub[5].left + 105;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId != "")
				mdc->SelectObject(b_lvl[L_RPLY]);
			else
				mdc->SelectObject(b_lvl[L_DEF]);
			
		}
		else if (util.buttonList == BUTTON_LVL_EX)
		{
			util.listRect.left = rSub[5].left;
			util.listRect.right = rSub[5].left + 105;

			mdc->SelectObject(b_lvl[L_EX]);

		}
		else if (util.buttonList == BUTTON_ROUTE_EX)
		{
			util.listRect.left = rSub[5].left;
			util.listRect.right = rSub[5].left + 105;


			mdc->SelectObject(b_route[L_EX]);


		}
		else if (util.buttonList == BUTTON_ROUTE)
		{
			util.listRect.left = rSub[6].left;
			util.listRect.right = rSub[6].left + 105;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				mdc->SelectObject(b_route[L_RPLY]);
			else
				mdc->SelectObject(b_route[L_DEF]);
		}
		else if (util.buttonList == BUTTON_VCI)
		{
			util.listRect.left = rSub[7].left;
			util.listRect.right = rSub[7].left + 105;

			mdc->SelectObject(b_vci);
		}
		else if (util.buttonList == BUTTON_SSR)
		{
			util.listRect.left = rSub[8].left;
			util.listRect.right = rSub[8].left + 105;

			mdc->SelectObject(b_ssr);
		}
		else if (util.buttonList == BUTTON_RST)
		{
			/*
			util.listRect.left = rSub[9].left;
			util.listRect.right = rSub[9].left + 105;

			mdc->SelectObject(b_route[1]);
			*/
		}
		else if (util.buttonList == BUTTON_MIKE)
		{
			util.listRect.left = rSub[8].left;
			util.listRect.right = rSub[8].left + 105;

			mdc->SelectObject(b_mike);
		}
		else
			mdc->SelectObject(CBitmap());

		// Draw the actual Submenu
		dc.BitBlt(util.listRect.left, util.listRect.top, util.listRect.right, util.listRect.bottom, mdc, 0, 0, SRCCOPY);
		listOpen = true;


		// Register the individual Submenu Buttons
		util.listRect.top += 1;
		util.listRect.bottom = util.listRect.top + 27;

		if (util.buttonList == BUTTON_LVL)
		{
			AddScreenObject(BUTTON_CLIMB, "DATALINK_LVL", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_CLIMB || buttonDown == BUTTON_CLIMB) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_DESCEND, "DATALINK_LVL", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_DESCEND || buttonDown == BUTTON_DESCEND) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_MAINTN, "DATALINK_LVL", util.listRect, false, NULL);


			if (buttonHighlight == BUTTON_MAINTN || buttonDown == BUTTON_MAINTN) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId != "")
				AddScreenObject(BUTTON_LVL_SBY, "DATALINK_LVL", util.listRect, false, NULL);

			//AddScreenObject(BUTTON_MAXROC, "DATALINK_LVL", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_MAXROC || buttonDown == BUTTON_MAXROC || buttonHighlight == BUTTON_LVL_SBY || buttonDown == BUTTON_LVL_SBY) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId != "")
				AddScreenObject(BUTTON_LVL_UNA, "DATALINK_LVL", util.listRect, false, NULL);

			//AddScreenObject(BUTTON_MINROC, "DATALINK_LVL", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_MINROC || buttonDown == BUTTON_MINROC || buttonHighlight == BUTTON_LVL_UNA || buttonDown == BUTTON_LVL_UNA) rSub[0] = util.listRect;

			// "EXECUTE"
			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			//AddScreenObject(BUTTON_EXECUTE, "DATALINK_LVL", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_EXECUTE) rSub[0] = util.listRect;
		}
		else if (util.buttonList == BUTTON_LVL_EX)
		{

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			// "EXECUTE"
			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_EXECUTE, "DATALINK_LVL", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_EXECUTE) rSub[0] = util.listRect;
		}
		else if (util.buttonList == BUTTON_ROUTE)
		{
			AddScreenObject(BUTTON_CONTHDG, "DATALINK_ROUTE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_CONTHDG || buttonDown == BUTTON_CONTHDG) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_FLYHDG, "DATALINK_ROUTE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_FLYHDG || buttonDown == BUTTON_FLYHDG) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_DCTTO, "DATALINK_ROUTE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_DCTTO || buttonDown == BUTTON_DCTTO) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				AddScreenObject(BUTTON_ROUTE_SBY, "DATALINK_ROUTE", util.listRect, false, NULL);
			else
				AddScreenObject(BUTTON_TURNLDEG, "DATALINK_ROUTE", util.listRect, false, NULL);

			if (buttonHighlight == BUTTON_TURNLDEG || buttonDown == BUTTON_TURNLDEG || buttonHighlight == BUTTON_ROUTE_SBY || buttonDown == BUTTON_ROUTE_SBY) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				AddScreenObject(BUTTON_ROUTE_UNA, "DATALINK_ROUTE", util.listRect, false, NULL);
			else
				AddScreenObject(BUTTON_TURNRDEG, "DATALINK_ROUTE", util.listRect, false, NULL);

			if (buttonHighlight == BUTTON_TURNRDEG || buttonDown == BUTTON_TURNRDEG || buttonHighlight == BUTTON_ROUTE_UNA || buttonDown == BUTTON_ROUTE_UNA) rSub[0] = util.listRect;

			// "EXECUTE"
			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			//AddScreenObject(BUTTON_EXECUTE, "DATALINK_ROUTE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_EXECUTE) rSub[0] = util.listRect;
		}
		else if (util.buttonList == BUTTON_ROUTE_EX)
		{

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;

			// "EXECUTE"
			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_EXECUTE, "DATALINK_ROUTE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_EXECUTE) rSub[0] = util.listRect;
		}
		else if (util.buttonList == BUTTON_VCI)
		{
			//AddScreenObject(BUTTON_DIM, "DATALINK_VCI", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_DIM || buttonDown == BUTTON_DIM) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			//AddScreenObject(BUTTON_BRIGHT, "DATALINK_VCI", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_BRIGHT || buttonDown == BUTTON_BRIGHT) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_CNTCT, "DATALINK_VCI", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_CNTCT || buttonDown == BUTTON_CNTCT) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_LOGOFF, "DATALINK_VCI", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_LOGOFF || buttonDown == BUTTON_LOGOFF) rSub[0] = util.listRect;

		}
		else if (util.buttonList == BUTTON_SSR)
		{
			AddScreenObject(BUTTON_NSSR, "DATALINK_SSR", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_NSSR || buttonDown == BUTTON_NSSR) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_SQIDENT, "DATALINK_SSR", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_SQIDENT || buttonDown == BUTTON_SQIDENT) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			//AddScreenObject(BUTTON_PDC, "DATALINK_SSR", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_PDC || buttonDown == BUTTON_PDC) rSub[0] = util.listRect;

		}
		else if (util.buttonList == BUTTON_RST)
		{

		}
		else if (util.buttonList == BUTTON_MIKE)
		{
			AddScreenObject(BUTTON_MIKECURR, "DATALINK_MIKE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_MIKECURR || buttonDown == BUTTON_MIKECURR) rSub[0] = util.listRect;

			util.listRect.top = util.listRect.bottom + 3;
			util.listRect.bottom = util.listRect.top + 27;
			AddScreenObject(BUTTON_MIKEALL, "DATALINK_MIKE", util.listRect, false, NULL);
			if (buttonHighlight == BUTTON_MIKEALL || buttonDown == BUTTON_MIKEALL) rSub[0] = util.listRect;
		}





		// Highlight Submenu Button, if MouseOver or MouseDown
		if (buttonHighlight >= BUTTON_EXECUTE && buttonHighlight < 50)
			HighlightButton(&dc, rSub[0]);
		if (buttonDown >= BUTTON_EXECUTE && buttonDown < 50)
			HighlightDown(&dc, rSub[0]);

	} //buttonlist > -1


	// Highlight Mainmenu, if MouseOver
	if (buttonHighlight >= BUTTON_LVL && buttonHighlight < 50 && util.buttonList == -1)
	{
		if (buttonHighlight == BUTTON_LVL || buttonHighlight == BUTTON_ACC)
			rSub[0] = rSub[4];
		else if (buttonHighlight == BUTTON_ROUTE || buttonHighlight == BUTTON_SBY)
			rSub[0] = rSub[5];
		else if (buttonHighlight == BUTTON_VCI || buttonHighlight == BUTTON_UNA)
			rSub[0] = rSub[6];
		else if (buttonHighlight == BUTTON_SSR || buttonHighlight == BUTTON_UDT)
			rSub[0] = rSub[7];
		else if (buttonHighlight == BUTTON_RST || buttonHighlight == BUTTON_UDA)
			rSub[0] = rSub[8];
		else if (buttonHighlight == BUTTON_MIKE)
			rSub[0] = rSub[9];

		HighlightButton(&dc, rSub[0]);
	}


	// Highlight Mainmenu Button, if MouseDown
	if (buttonDown >= BUTTON_LVL && buttonDown < 50 && util.buttonList == -1)
	{
		if (buttonDown == BUTTON_LVL || buttonDown == BUTTON_ACC)
			rSub[0] = rSub[4];
		else if (buttonDown == BUTTON_ROUTE || buttonDown == BUTTON_SBY)
			rSub[0] = rSub[5];
		else if (buttonDown == BUTTON_VCI || buttonDown == BUTTON_UNA)
			rSub[0] = rSub[6];
		else if (buttonDown == BUTTON_SSR || buttonDown == BUTTON_UDT)
			rSub[0] = rSub[7];
		else if (buttonDown == BUTTON_RST || buttonDown == BUTTON_UDA)
			rSub[0] = rSub[8];
		else if (buttonDown == BUTTON_MIKE)
			rSub[0] = rSub[9];

		HighlightDown(&dc, rSub[0]);
	}

	//------------------------------------------------------------------
	//  Restore Font & Pen && Detach Object
	//------------------------------------------------------------------

	dc.SelectObject(orig_font);
	dc.SelectObject(orig_pen);

	dc.Detach();
	delete mdc;
}


//---OnCompileCommand-----------------------------------------------
bool    CDatalinkScreen::OnCompileCommand(const char * sCommandLine)
{
	CString command(sCommandLine);
	command.MakeUpper();

	// if CPDLC command
	if (strncmp(command, ".DATALINK", 9) == 0) {
		if (command.GetLength() != 6 && command.GetLength() != 9)
			return false;
		hidden = !hidden;
		return true;
	}
	else
		return false;
}


//---OnOverScreenObject-----------------------------------------
void    CDatalinkScreen::OnOverScreenObject(int ObjectType, const char * sObjectId, POINT Pt, RECT Area) 
{
	if (ObjectType >= BUTTON_EXECUTE && ObjectType < 50 && util.buttonList > -1) {
		buttonHighlight = ObjectType;
		RequestRefresh();
	}
	else if ((ObjectType == BUTTON_ICONIFY || ObjectType == BUTTON_CLOSE) && !listOpen) {
		buttonHighlight = ObjectType;
		RequestRefresh();
	}
	else if ((ObjectType == BUTTON_LVL || ObjectType == BUTTON_ROUTE || ObjectType == BUTTON_VCI ||
		ObjectType == BUTTON_SSR || ObjectType == BUTTON_RST || ObjectType == BUTTON_MIKE ||
		ObjectType == BUTTON_ACC || ObjectType == BUTTON_SBY || ObjectType == BUTTON_UNA ||
		ObjectType == BUTTON_UDT || ObjectType == BUTTON_UDA) && !listOpen) {
		buttonHighlight = ObjectType;
		RequestRefresh();
	}
	else if ((ObjectType == FRAME || ObjectType == AREA_DATA || ObjectType == AREA_HEADER)) {
		buttonHighlight = -1;
		RequestRefresh();
	}
}


//---OnButtonDownScreenObject-----------------------------------------
void    CDatalinkScreen::OnButtonDownScreenObject(int ObjectType, const char * sObjectId, POINT Pt, RECT Area, int Button) 
{
	if ((ObjectType == BUTTON_LVL || ObjectType == BUTTON_ROUTE || ObjectType == BUTTON_VCI ||
		ObjectType == BUTTON_SSR || ObjectType == BUTTON_MIKE ||
		ObjectType == BUTTON_ACC || ObjectType == BUTTON_SBY || ObjectType == BUTTON_UNA ||
		ObjectType == BUTTON_UDT || ObjectType == BUTTON_UDA) && util.buttonList == -1 && util.hoppie.selectedItem > -1) {
		buttonDown = ObjectType;
		RequestRefresh();
	}
	else if ((ObjectType >= BUTTON_EXECUTE && ObjectType < 50) && ObjectType != BUTTON_AUTO && ObjectType != BUTTON_EXECUTE && ObjectType != BUTTON_MAXROC && ObjectType != BUTTON_MINROC) {
		buttonDown = ObjectType;
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_EXECUTE && (util.buttonList == BUTTON_LVL_EX || util.buttonList == BUTTON_ROUTE_EX)) {
		buttonDown = ObjectType;
		RequestRefresh();
	}
}


//---OnButtonUpScreenObject-----------------------------------------
void    CDatalinkScreen::OnButtonUpScreenObject(int ObjectType, const char * sObjectId, POINT Pt, RECT Area, int Button) 
{
	if ((ObjectType == BUTTON_LVL || ObjectType == BUTTON_ROUTE || ObjectType == BUTTON_VCI ||
		ObjectType == BUTTON_SSR || ObjectType == BUTTON_MIKE) && util.buttonList == -1 && util.hoppie.selectedItem > -1)
	{
		buttonDown = -1;
		buttonHighlight = -1;

		util.buttonList = ObjectType;

		//SetCursorPos(Area.right + 20, Area.bottom + 80);

		RequestRefresh();
	}
	else if (ObjectType == BUTTON_SBY && util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Logon == -1)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		return;
	}
	else if ((ObjectType == BUTTON_ACC || ObjectType == BUTTON_SBY || ObjectType == BUTTON_UNA ||
		ObjectType == BUTTON_UDT || ObjectType == BUTTON_UDA) && util.buttonList == -1)
	{
		CString msg, answer;
		buttonDown = -1;
		buttonHighlight = -1;
		int pos;

		switch (ObjectType)
		{
		case BUTTON_ACC:msg = "ACC/"; answer = "LOGON ACCEPTED"; util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected = 1; break;
		case BUTTON_SBY:msg = "SBY/"; answer = "STANDBY"; break;
		case BUTTON_UNA:msg = "UNA/"; answer = "UNABLE"; util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected = 2; break;
		case BUTTON_UDT:msg = "UDT/"; answer = "UNABLE DUE TO TRAFFIC"; util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected = 2; break;
		case BUTTON_UDA:msg = "UDA/"; answer = "UNABLE DUE TO AIRSPACE"; util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected = 2; break;
		}

		if (ObjectType != BUTTON_SBY)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Logon = 1;

			if ((pos = util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Find("SBY/")) > -1)
				util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Delete(pos, 4);
		}
		else
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Logon = -1;
		}

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Insert(2, msg);


		msg.Format("/data2/%d/%s/NE/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId, answer);
		util.hoppie.cpdlcCounter++;
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

		//if (ObjectType == BUTTON_ACC)
		//{
		//	msg.Format("/data2/%d//NE/%s", hoppie.cpdlcCounter, hoppie.callsign);
		//	hoppie.cpdlcCounter++;
		//	util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);
		//}

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId = "";
		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);

		RequestRefresh();
	}
	else if (ObjectType == BUTTON_SQIDENT)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;

		CString msg, answer;

		POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign);

		if (pos != NULL)
		{
			data[5] = "";

			msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "SQUAWK IDENT" + data[5]);
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSR.Insert(2, "SQWK IDENT" + data[5] + '/');

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRATCId.Format("%d", util.hoppie.cpdlcCounter);

			util.hoppie.cpdlcCounter++;

		}

		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_NSSR)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;

		CString msg, answer;

		POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign);

		if (pos != NULL)
		{
			data[5] = util.hoppie.m_VinicityAcList.GetAt(pos).m_Squawk;

			msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "SQUAWK " + data[5]);
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSR.Insert(2, "SQWK " + data[5] + '/');

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRATCId.Format("%d", util.hoppie.cpdlcCounter);

			util.hoppie.cpdlcCounter++;
		}

		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();

	}
	else if (ObjectType == BUTTON_LOGOFF)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;

		CString msg, answer;

		POSITION pos = util.hoppie._SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign);

		if (pos != NULL)
		{
			data[5] = "";

			msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "LOGOFF" + data[5]);
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Insert(2, "LOGOFF" + data[5] + '/');

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelATCId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteATCId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_SSRATCId = "";

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected = 2;

			util.hoppie.cpdlcCounter++;
		}

		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();

	}
	else if (ObjectType == BUTTON_PDC || ObjectType == BUTTON_DCL_DCL)
	{
		/*
		if (strlen(data[5]) <= 0)
		{
			buttonList = ObjectType;
			return;
		}

		buttonDown = -1;
		buttonHighlight = -1;
		buttonList = -1;
		listOpen = false;
		hoppie.popupList = -1;

		CString msg, answer;

		POSITION pos = _SelectAcFromVinicityList(CONTROLLER_LIST, data[5]);

		if (pos != NULL)
		{
			data[5].Format(" @FREQ: @%.3f ", hoppie.controller.GetAt(pos).freq);
		}
		else
		{
			data[5] = " @\0";
		}

		pos = _SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign);

		if (pos != NULL)
		{
			CString atis;
			CString	server = _T("www.hoppie.nl"),
				base = _T("/acars/system/connect.html"),
				URI;
			DWORD	dwRet;
			URI.Format("%s?type=inforeq&logon=%s&from=%s&to=%s&packet=vatatis %s", base, hoppie.logonCode, hoppie.callsign, hoppie.callsign, m_VinicityAcList.GetAt(pos).m_Origin);
			CInternetSession session;

			try {
				CHttpConnection *pConnection = session.GetHttpConnection(server);
				CHttpFile *pFile = pConnection->OpenRequest(NULL, URI);
				pFile->SendRequest();
				pFile->QueryInfoStatusCode(dwRet);

				if (dwRet != HTTP_STATUS_OK)
				{
					hoppie.error.Format("%d", (int)dwRet);
					session.Close();
					atis = "\0";
				}
				pFile->ReadString(hoppie.error);
				session.Close();

				if (hoppie.error.MakeUpper().Find("NO ATIS AVAILABLE") == -1)
				{
					atis.Format(" ATIS: %s\0", "A");

				}
				else {
					atis = "\0";
				}

				delete pConnection;
				delete pFile;
			}
			catch (CInternetException*)
			{
				//hoppie.writeLog("SYSTEM: Exception->Wilco.Handoff.Logoff()");
				atis = "\0";
			}

			//msg.Format("/data2/%d//WU/%s%s%s%s%s%s%s%s%s%s", hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign, " CLRD TO @",
			//		   m_VinicityAcList.GetAt(pos).m_Destination, "@ OFF @", m_VinicityAcList.GetAt(pos).m_Runway, "@ VIA @", m_VinicityAcList.GetAt(pos).m_SID, " @ SQUAWK @",
			//		   m_VinicityAcList.GetAt(pos).m_Squawk, data[5]);
			if (ObjectType == BUTTON_DCL_DCL)
			msg.Format("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", "DEPARTURE CLEARANCE 001",
						CTime::GetCurrentTime().FormatGmt(" @%H%MZ %d%b%Y"),
						" @FROM: ", m_VinicityAcList.GetAt(pos).m_Origin,
						" @", m_VinicityAcList.GetAt(pos).m_Callsign,
						" @CLRD TO: ", m_VinicityAcList.GetAt(pos).m_Destination,
						" @RWY: ", m_VinicityAcList.GetAt(pos).m_Runway, "  SID: ", m_VinicityAcList.GetAt(pos).m_SID,
						" @SQK: ", m_VinicityAcList.GetAt(pos).m_Squawk,
						data[5], atis,
						" @STARTUP APPROVED");
			else
				msg.Format("/data2/%d//WU/%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", hoppie.cpdlcCounter, "DEPARTURE CLEARANCE 001",
				CTime::GetCurrentTime().FormatGmt(" @%H%MZ %d%b%Y"),
				" @FROM: ", m_VinicityAcList.GetAt(pos).m_Origin,
				" @", m_VinicityAcList.GetAt(pos).m_Callsign,
				" @CLRD TO: ", m_VinicityAcList.GetAt(pos).m_Destination,
				" @RWY: ", m_VinicityAcList.GetAt(pos).m_Runway, "  SID: ", m_VinicityAcList.GetAt(pos).m_SID,
				" @SQK: ", m_VinicityAcList.GetAt(pos).m_Squawk,
				data[5], atis,
				" @STARTUP APPROVED");

			//format.Format("%s RCD RECEIVED @REQUEST BEING PROCESSED @STANDBY", sCallsign);
			//hoppieMsg(MSG_SEND, MSG_TELEX, sCallsign, format);

			data[5].Format("DCL|%s|%s|%s/", m_VinicityAcList.GetAt(pos).m_Destination, m_VinicityAcList.GetAt(pos).m_SID, m_VinicityAcList.GetAt(pos).m_Squawk);
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Insert(2, data[5]);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId.Format("%d", hoppie.cpdlcCounter);

			hoppie.cpdlcCounter++;
		}

		data[0] = "";
		data[5] = "";

		char* tmp = new char[10];
		_itoa(hoppie.cpdlcCounter, tmp, 10);
		hoppie.setConfVal("counter", tmp);
		delete[] tmp;

		RequestRefresh();
		*/
	}
	else if (ObjectType == BUTTON_DCL_DCL)
	{
		/*
		if (strlen(data[5]) <= 0)
		{
			buttonList = BUTTON_PDC;
			return;
		}

		buttonDown = -1;
		buttonHighlight = -1;
		buttonList = -1;
		listOpen = false;
		hoppie.popupList = -1;

		CString msg, answer;

		POSITION pos = _SelectAcFromVinicityList(CONTROLLER_LIST, data[5]);

		if (pos != NULL)
		{
			data[5].Format(" @ NEXT FREQ @%.3f", hoppie.controller.GetAt(pos).freq);
		}
		else
		{
			data[5] = "@ \0";
		}

		pos = _SelectAcFromVinicityList(VICINITY_LIST, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign);

		if (pos != NULL)
		{

			msg.Format("/data2/%d//WU/%s%s%s%s%s%s%s%s%s%s", hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Callsign, " CLRD TO @",
				m_VinicityAcList.GetAt(pos).m_Destination, "@ OFF @", m_VinicityAcList.GetAt(pos).m_Runway, "@ VIA @", m_VinicityAcList.GetAt(pos).m_SID, " @ SQUAWK @",
				m_VinicityAcList.GetAt(pos).m_Squawk, data[5]);
			msg = "Test";

			data[5].Format("PDC|%s|%s|%s/", m_VinicityAcList.GetAt(pos).m_Destination, m_VinicityAcList.GetAt(pos).m_SID, m_VinicityAcList.GetAt(pos).m_Squawk);
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Insert(2, data[5]);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId.Format("%d", hoppie.cpdlcCounter);

			hoppie.cpdlcCounter++;
		}

		data[0] = "";
		data[5] = "";

		char* tmp = new char[10];
		_itoa(hoppie.cpdlcCounter, tmp, 10);
		hoppie.setConfVal("counter", tmp);
		delete[] tmp;

		RequestRefresh();
		*/
	}
	else if (ObjectType == BUTTON_CNTCT)
	{
		if (strlen(data[5]) <= 0)
		{
			util.buttonList = BUTTON_CNTCT;
			return;
		}

		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;

		CString msg, answer;

		POSITION pos = util.hoppie._SelectAcFromVinicityList(CONTROLLER_LIST, data[5]);
		if (pos != NULL)
		{
			if (util.hoppie.controller.GetAt(pos).facility == 1 || util.hoppie.controller.GetAt(pos).facility == 6)
			{
				// LON_CTR
				if (strlen(util.hoppie.controller.GetAt(pos).callsign) == 7)
				{
					if (util.hoppie.controller.GetAt(pos).callsign.Mid(0, 3).Find("_") < 0)
					{
						data[5] = util.hoppie.controller.GetAt(pos).callsign.Mid(0, 3);
					}
				}
				// EURM_CTR
				else if (strlen(util.hoppie.controller.GetAt(pos).callsign) == 8)
				{
					if (util.hoppie.controller.GetAt(pos).callsign.Mid(0, 4).Find("_") < 0)
					{
						data[5] = util.hoppie.controller.GetAt(pos).callsign.Mid(0, 4);
					}
				}
				// LON_C_CTR
				else if (strlen(util.hoppie.controller.GetAt(pos).callsign) == 9)
				{
					if (util.hoppie.controller.GetAt(pos).callsign.Mid(0, 3).Find("_") < 0)
					{
						//LONC
						data[5].Format("%s%s", util.hoppie.controller.GetAt(pos).callsign.Mid(0, 3), util.hoppie.controller.GetAt(pos).callsign.Mid(4, 1));
					}
				}
				// EDWW_A_CTR  LON_SC_CTR
				else if (strlen(util.hoppie.controller.GetAt(pos).callsign) == 10)
				{
					if (util.hoppie.controller.GetAt(pos).callsign.Mid(0, 4).Find("_") < 0)
					{
						// EDWA
						data[5].Format("%s%s", util.hoppie.controller.GetAt(pos).callsign.Mid(0, 3), util.hoppie.controller.GetAt(pos).callsign.Mid(5, 1));
					}
					else
					{
						// LONS
						data[5].Format("%s%s", util.hoppie.controller.GetAt(pos).callsign.Mid(0, 3), util.hoppie.controller.GetAt(pos).callsign.Mid(4, 1));
					}
				}
			}
			else if (util.hoppie.controller.GetAt(pos).facility == 5)
			{
				// EBBR_APP
				if (strlen(util.hoppie.controller.GetAt(pos).callsign) == 8)
				{
					data[5].Format("%s%s", util.hoppie.controller.GetAt(pos).callsign.Mid(0, 2), util.hoppie.controller.GetAt(pos).callsign.Mid(3, 1));
				}
				// EDDF_F_APP
				else if (strlen(util.hoppie.controller.GetAt(pos).callsign) == 10)
				{
					data[5].Format("%s%s%s", util.hoppie.controller.GetAt(pos).callsign.Mid(0, 2), util.hoppie.controller.GetAt(pos).callsign.Mid(3, 1), util.hoppie.controller.GetAt(pos).callsign.Mid(5, 1));
				}
			}

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_NextStation = data[5];

			if (strlen(util.hoppie.controller.GetAt(pos).spokenCallsign) > 0)
			{
				int start = 0;
				CString tmp1 = util.hoppie.controller.GetAt(pos).spokenCallsign.Tokenize(_T(" "), start);
				CString tmp2 = util.hoppie.controller.GetAt(pos).spokenCallsign.Tokenize(_T(" "), start);

				data[5].AppendFormat(" %s @%s %.3f MHZ", tmp1, tmp2, util.hoppie.controller.GetAt(pos).freq);
			}
			else
			{
				data[5].AppendFormat(" @%.3f MHZ", util.hoppie.controller.GetAt(pos).freq);
			}

			msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "CONTACT " + data[5]);

			data[5].Format("%.3f", util.hoppie.controller.GetAt(pos).freq);
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Insert(2, "CNTCT " + data[5] + '/');

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId = "";
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId.Format("%d", util.hoppie.cpdlcCounter);

			util.hoppie.cpdlcCounter++;
		}

		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_MIKECURR)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;

		CString msg, answer;

		if (util.hoppie.controllerMyself.valid)
			data[5].Format(" @%.3f", util.hoppie.controllerMyself.freq);
		else
			data[5] = "\0";

		msg.Format("/data2/%d//NE/%s", util.hoppie.cpdlcCounter, "CHECK STUCK MICROPHONE" + data[5]);
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Voice.Insert(2, "CHK STUCK MIC/");

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);

		util.hoppie.cpdlcCounter++;
		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_MIKEALL)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;

		CString msg, answer;

		if (util.hoppie.controllerMyself.valid)
			data[5].Format(" @%.3f", util.hoppie.controllerMyself.freq);
		else
			data[5] = "\0";

		msg.Format("/data2/%d//NE/%s", util.hoppie.cpdlcCounter, "CHECK STUCK MICROPHONE" + data[5]);

		POSITION pos = util.hoppie.hoppieList.GetHeadPosition();

		for (int i = 0; i < util.hoppie.hoppieList.GetCount(); ++i)
		{
			util.hoppie.hoppieList.GetAt(pos).m_Voice.Insert(2, "CHK STUCK MIC/");
			util.hoppie.hoppieList.GetAt(pos).m_Relay->AddTail(msg);

			util.hoppie.cpdlcCounter++;

			util.hoppie.hoppieList.GetNext(pos);
		}

		data[0] = "";
		data[5] = "";

		RequestRefresh();
	}
	else if (ObjectType == BUTTON_LOGOFF)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;


		CString msg;

		msg.Format("/data2/%d//N/%s", util.hoppie.cpdlcCounter, "LOGOFF\0");
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.Insert(2, "LOGOFF/");

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);


		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Connected = 2;
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceId = "";
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_VoiceATCId = "";
		util.hoppie.cpdlcCounter++;
		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_LVL_SBY || ObjectType == BUTTON_ROUTE_SBY)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;


		CString msg;

		if (ObjectType == BUTTON_LVL_SBY)
		{
			msg.Format("/data2/%d/%s/N/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId, "STANDBY\0");
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.Insert(2, "SBY/");
		}
		else
		{
			msg.Format("/data2/%d/%s/N/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "STANDBY\0");
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "SBY/");
		}
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);


		util.hoppie.cpdlcCounter++;
		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_LVL_UNA || ObjectType == BUTTON_ROUTE_UNA)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;
		util.hoppie.popupList = -1;


		CString msg;

		if (ObjectType == BUTTON_LVL_UNA)
		{
			msg.Format("/data2/%d/%s/N/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId, "UNABLE\0");
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.Insert(2, "UNA/");
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId = "";
		}
		else
		{
			msg.Format("/data2/%d/%s/N/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "UNABLE\0");
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "UNA/");
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId = "";
		}
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);


		util.hoppie.cpdlcCounter++;
		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if ((ObjectType >= BUTTON_EXECUTE && ObjectType < 50) && ObjectType != BUTTON_AUTO && ObjectType != BUTTON_EXECUTE && ObjectType != BUTTON_MAXROC && ObjectType != BUTTON_MINROC)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = ObjectType;
		util.listRect.SetRect(Area.left, Area.top, Area.right, Area.bottom);

		RequestRefresh();
	}
	else if (ObjectType == BUTTON_EXECUTE && util.buttonList == BUTTON_LVL_EX)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;

		// TODO: SEND MESSAGE

		CString msg, answer;

		util.hoppie.popupList = -1;


		if (data[0].Find("CLIMB") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.Insert(2, "CLMB " + data[5] + '/');

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId, "CLIMB TO FL" + data[5]);
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "CLIMB TO FL" + data[5]);

		}
		else if (data[0].Find("DESCEND") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.Insert(2, "DESC " + data[5] + '/');
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId, "DESCEND TO FL" + data[5]);
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "DESCEND TO FL" + data[5]);

		}
		else if (data[0].Find("MAINTAIN") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Level.Insert(2, "MAINTN " + data[5] + '/');

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId, "MAINTAIN FL" + data[5]);
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "MAINTAIN FL" + data[5]);

		}

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RelayLvl = atoi(data[5]);

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelId = "";
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_LevelATCId.Format("%d", util.hoppie.cpdlcCounter);
		util.hoppie.cpdlcCounter++;
		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_EXECUTE && util.buttonList == BUTTON_ROUTE_EX)
	{
		buttonDown = -1;
		buttonHighlight = -1;
		util.buttonList = -1;
		listOpen = false;

		// TODO: SEND MESSAGE

		CString msg, answer;

		util.hoppie.popupList = -1;


		if (data[0].Find("DCT") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "DCT TO " + data[5] + '/');

			POSITION pos;
			if ((pos = util.hoppie._SelectFixFromList(data[5])) != NULL)
			{
				int lat = (int)((util.hoppie.waypoint.GetAt(pos).position.m_Latitude - (int)util.hoppie.waypoint.GetAt(pos).position.m_Latitude) * 1000000);
				int lng = (int)((util.hoppie.waypoint.GetAt(pos).position.m_Longitude - (int)util.hoppie.waypoint.GetAt(pos).position.m_Longitude) * 1000000);
				CString str = " @";

				str.AppendFormat("%d %d %dN %d %d %dE", (int)util.hoppie.waypoint.GetAt(pos).position.m_Latitude, (int)((lat * 60) / 1000000), ((((lat * 60) - (((lat * 60) / 1000000) * 1000000)) * 60) / 1000000),
					(int)util.hoppie.waypoint.GetAt(pos).position.m_Longitude, (int)((lng * 60) / 1000000), ((((lng * 60) - (((lng * 60) / 1000000) * 1000000)) * 60) / 1000000));

				data[5].Append(str);
			}

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "PROCEED DIRECT TO " + data[5]);
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "PROCEED DIRECT TO " + data[5]);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RelayDct = data[5];
		}
		else if (data[0].Find("FLY") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "FLY HDG " + data[5] + '/');
			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "FLY HEADING " + data[5]);
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "FLY HEADING " + data[5]);

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RelayHdg = atoi(data[5]);
		}
		else if (data[0].Find("CONT") > -1)
		{
			util.hoppie.popupList = -1;

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "CONT PRSNT HDG" + data[5] + '/');
			//util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "CONT PRSNT HDG" + '/');

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "CONTINUE ON PRESENT\nHEADING");
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "CONTINUE ON PRESENT\nHEADING");

			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RelayHdg = atoi(data[5]);
		}
		else if (data[0].Find("DEG L") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "DEG L " + data[5] + '/');

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "TURN LEFT " + data[5] + " DEGREES");
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "TURN LEFT " + data[5] + " DEGREES");

			//util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RelayHdg = atoi(data[5]);
		}
		else if (data[0].Find("DEG R") > -1)
		{
			util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Route.Insert(2, "DEG R " + data[5] + '/');

			if (util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId != "")
				msg.Format("/data2/%d/%s/WU/%s", util.hoppie.cpdlcCounter, util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId, "TURN RIGHT " + data[5] + " DEGREES");
			else
				msg.Format("/data2/%d//WU/%s", util.hoppie.cpdlcCounter, "TURN RIGHT " + data[5] + " DEGREES");

			//util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RelayHdg = atoi(data[5]);
		}

		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_Relay->AddTail(msg);


		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteId = "";
		util.hoppie.hoppieList.GetAt(util.hoppie.hoppieList.FindIndex(util.hoppie.selectedItem)).m_RouteATCId.Format("%d", util.hoppie.cpdlcCounter);
		util.hoppie.cpdlcCounter++;
		data[0] = "";
		data[5] = "";

		util.hoppie.SetConfInt("counter", util.hoppie.cpdlcCounter);
		RequestRefresh();
	}
}


//---OnClickScreenObject-----------------------------------------
void    CDatalinkScreen::OnClickScreenObject(int ObjectType, const char * sObjectId, POINT Pt, RECT Area, int Button) 
{
	if (ObjectType == BUTTON_ICONIFY) {
		if (listOpen) {
			listOpen = false;
			util.buttonList = -1;
			data[0] = "";
			util.hoppie.popupList = -1;
		}
		else {
			if (Button == BUTTON_RIGHT) {
				if (util.configOpen)
					util.configOpen = false;
				else {
					util.configOpen = true;
					util.listRect.SetRect(Area.right, Area.top, Area.right + 50, Area.bottom);
				}
			}
			else if (Button == BUTTON_LEFT) {
				if (util.hoppie.iconify)
					util.hoppie.iconify = false;
				else
					util.hoppie.iconify = true;
				util.hoppie.SetConfInt("iconify", util.hoppie.iconify);

				listOpen = false;
				util.configOpen = false;
				util.buttonList = -1;
			}
		}
		RequestRefresh();
	}
	else if (ObjectType == BUTTON_CLOSE && Button == BUTTON_LEFT) {
		if (listOpen) {
			listOpen = false;
			util.buttonList = -1;
			data[0] = "";
			util.hoppie.popupList = -1;
		}
		else {
			hidden = true;
			listOpen = false;
			util.configOpen = false;
			util.buttonList = -1;
			buttonHighlight = -1;
		}

		RequestRefresh();
	}
	else if (ObjectType == BUTTON_CLOSE && Button == BUTTON_RIGHT)
	{
		if (listOpen) {
			listOpen = false;
			util.buttonList = -1;
			data[0] = "";
			util.hoppie.popupList = -1;
		}
		else {
			CString format;
			if (util.hoppie.hoppieConnected) {
				util.hoppie.hoppieConnected = false;
				format.Format("%s: Disconnect", util.hoppie.callsign);
				Logger::Log(format);
			}
			else if (util.hoppie.callsign == "") {
				GetPlugIn()->DisplayUserMessage("Datalink", "DataLink", "NO CS SPECIFIED", false, true, true, true, false);
				format.Format("SYSTEM: Connect (NOCS)");
				Logger::Log(format);
			}
			else {
				format.Format("%s: Connect", util.hoppie.callsign);
				Logger::Log(format);
				util.hoppie.HoppiePing();
			}
		}
		RequestRefresh();
	}
	else if (ObjectType >= ITEM_AIRCRAFT) {
		util.hoppie.selectedItem = ObjectType - ITEM_AIRCRAFT;
	}
	else if (ObjectType == BUTTON_LVL || ObjectType == BUTTON_ROUTE || ObjectType == BUTTON_VCI ||
		ObjectType == BUTTON_SSR || ObjectType == BUTTON_RST || ObjectType == BUTTON_MIKE)
	{
		if (listOpen) {
			listOpen = false;
			util.buttonList = -1;
			data[0] = "";
			util.hoppie.popupList = -1;
		}
		util.configOpen = false;
	}
	else if (ObjectType == BUTTON_AUTO || ObjectType == BUTTON_EXECUTE || ObjectType == BUTTON_MAXROC || ObjectType == BUTTON_MINROC)
	{

	}
	else if (ObjectType == AREA_HEADER || ObjectType == AREA_DATA || ObjectType == FRAME)
	{
		listOpen = false;
		util.configOpen = false;
		util.buttonList = -1;
		data[0] = "";
		util.hoppie.popupList = -1;
	}
}


//---OnMoveScreenObject-----------------------------------------
void	CDatalinkScreen::OnMoveScreenObject(int ObjectType, const char * sObjectId, POINT Pt, RECT Area, bool Released) 
{
	CString str;

	if (ObjectType == AREA_HEADER)
	{
		xOffset = Pt.x - Area.left + 24;
		yOffset = Pt.y - Area.top + 1;

		util.hoppie.x = Pt.x - xOffset;
		util.hoppie.y = Pt.y - yOffset;

		util.hoppie.SetConfInt("x", util.hoppie.x);
		util.hoppie.SetConfInt("y", util.hoppie.y);
	}
	else if (ObjectType == BUTTON_ICONIFY)
	{
		xOffset = Pt.x - Area.left + 1;
		yOffset = Pt.y - Area.top + 1;

		util.hoppie.x = Pt.x - xOffset;
		util.hoppie.y = Pt.y - yOffset;

		util.hoppie.SetConfInt("x", util.hoppie.x);
		util.hoppie.SetConfInt("y", util.hoppie.y);
	}

	RequestRefresh();
}


//---OnFunctionCall-----------------------------------------
void    CDatalinkScreen::OnFunctionCall(int FunctionId, const char * sItemString, POINT Pt, RECT Area) 
{
	if (util.hoppie.popupList > -1) {
		listOpen = false;
		util.configOpen = false;

		data[5] = sItemString;
		data[5].Remove(' ');
		data[0] += ' ' + data[5];

		if (util.hoppie.popupList == BUTTON_CLIMB || util.hoppie.popupList == BUTTON_DESCEND || util.hoppie.popupList == BUTTON_MAINTN)
			util.buttonList = BUTTON_LVL_EX;
		else if (util.hoppie.popupList == BUTTON_FLYHDG || util.hoppie.popupList == BUTTON_DCTTO ||
			util.hoppie.popupList == BUTTON_CONTHDG || util.hoppie.popupList == BUTTON_TURNLDEG ||
			util.hoppie.popupList == BUTTON_TURNRDEG)
			util.buttonList = BUTTON_ROUTE_EX;
		else if (util.hoppie.popupList == BUTTON_CNTCT || util.hoppie.popupList == BUTTON_PDC || util.hoppie.popupList == BUTTON_DCL_DCL) {
			POINT pnt; pnt.x = 0, pnt.y = 0;
			RECT  rct; rct.bottom = 0, rct.left = 0; rct.right = 0, rct.top = 0;
			OnButtonUpScreenObject(util.hoppie.popupList, "", pnt, rct, 1);
		}

		util.hoppie.popupList = -1;
	}
}
