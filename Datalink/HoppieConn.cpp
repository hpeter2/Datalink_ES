#include "stdafx.h"
#include "HoppieConn.h"


CHoppieConn::CHoppieConn()
{
	hoppieConnected = false;
	cpdlcCounter = 200;
	csOverride = false;
	euroscopeConnected = false;
	pdcConnected = false;
	withPDC = false;
	asrLoaded = false;
	popupList = -1;
	netClear = true;
	error = "";
	logonCode = "";
	callsign = "";
	notificationSound = 1;
	data.RemoveAll();
	currentDir = GetCurrentDir();
	selectedItem = new CHoppieList();
	//int pos = util.currentDir.ReverseFind('\\');

	//if (pos > -1)
		//currentDir.Delete(pos + 1, currentDir.GetLength() - (pos + 1));


	char* tmpStr = new char[1024];

	pApp = AfxGetApp();

	logonCode = pApp->GetProfileString("Config", "logonCode", "");
	if (logonCode == "") pApp->WriteProfileString("Config", "logonCode", "YOUR_LOGON_CODE");

	iconify = pApp->GetProfileInt("Config", "iconify", 0);
	if (iconify == 0) pApp->WriteProfileInt("Config", "iconify", 0);

	x = pApp->GetProfileInt("Config", "x", 200);
	if (x == 200) pApp->WriteProfileInt("Config", "x", 200);

	y = pApp->GetProfileInt("Config", "y", 200);
	if (y == 200) pApp->WriteProfileInt("Config", "y", 200);

	cpdlcCounter = pApp->GetProfileInt("Config", "counter", 1);
	if (cpdlcCounter == 1) pApp->WriteProfileInt("Config", "counter", 1);

	notificationSound = pApp->GetProfileInt("Config", "notificationSound", 1);
	if (notificationSound == 1) pApp->WriteProfileInt("Config", "notificationSound", 1);
}


CHoppieConn::~CHoppieConn()
{
	SetConfString("logonCode", logonCode);
	SetConfInt("iconify", iconify);
	SetConfInt("x", x);
	SetConfInt("y", y);
	SetConfInt("counter", cpdlcCounter++);
	SetConfInt("notificationSound", notificationSound);
	
	delete selectedItem;
	HoppieClear();
}


void CHoppieConn::SetConfString(CString item, CString value)
{
	pApp->WriteProfileString("Config", item, value);
}


void CHoppieConn::SetConfInt(CString item, int value)
{
	pApp->WriteProfileInt("Config", item, value);
}


//---_SelectAcFromVicinityList-----------------------------------------
POSITION CHoppieConn::_SelectAcFromVicinityList(int listIdx, const char * sCallsign)
{
	POSITION    pos;

	if (listIdx == 1)
	{
		// search
		pos = m_VinicityAcList.GetHeadPosition();

		for (int i = 0; i < m_VinicityAcList.GetCount(); ++i)
		{
			// if found
			if (m_VinicityAcList.GetAt(pos).m_Callsign.CompareNoCase(sCallsign) == 0)
				return pos;

			// next
			m_VinicityAcList.GetNext(pos);
		}
	}
	else if (listIdx == 2)
	{
		// search
		pos = hoppieList.GetHeadPosition();

		for (int i = 0; i < hoppieList.GetCount(); ++i)
		{
			// if found
			if (hoppieList.GetAt(pos).m_Callsign.CompareNoCase(sCallsign) == 0)
				return pos;

			// next
			hoppieList.GetNext(pos);
		}
	}
	else if (listIdx == 3)
	{
		// search
		pos = controller.GetHeadPosition();

		for (int i = 0; i < controller.GetCount(); ++i)
		{
			// if found
			if (strcmp(controller.GetAt(pos).callsign, sCallsign) == 0)
				return pos;

			// next
			controller.GetNext(pos);
		}
	}
	else if (listIdx == 4)
	{
		// search
		pos = spokenList.GetHeadPosition();

		for (int i = 0; i < spokenList.GetCount(); ++i)
		{
			// if found
			if (strcmp(spokenList.GetAt(pos).callsign, sCallsign) == 0)
				return pos;
			else if (spokenList.GetAt(pos).callsign.Find("*", 0) != -1)
			{
				CString spokenTmp = spokenList.GetAt(pos).callsign;
				CString reqTemp = sCallsign;

				spokenTmp.Remove('*');

				if (reqTemp.Find(spokenTmp) != -1)
					return pos;
			}

			// next
			controller.GetNext(pos);
		}
	}
	// not found
	return NULL;
}


POSITION CHoppieConn::_SelectFixFromList(const char * fix)
{
	POSITION    pos;


	// search
	pos = waypoint.GetHeadPosition();

	for (int i = 0; i < waypoint.GetCount(); ++i)
	{
		// if found
		if (strcmp(waypoint.GetAt(pos).name, fix) == 0)
			return pos;

		// next
		waypoint.GetNext(pos);
	}

	// not found
	return NULL;
}


void CHoppieConn::HoppieClear()
{
	CString msg;
	for (int i = 0; i < hoppieList.GetCount(); ++i)
	{
		if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected == 1)
		{
			msg.Format("/data2/%d//NE/LOGOFF", cpdlcCounter);
			cpdlcCounter++;
			Message(MSG_SEND, MSG_CPDLC, hoppieList.GetAt(hoppieList.FindIndex(i)).m_Callsign, msg);
			Message(MSG_SEND, MSG_TELEX, hoppieList.GetAt(hoppieList.FindIndex(i)).m_Callsign, "ATC STATION DISCONNECTED FROM NETWORK");
		}
	}
	hoppieConnected = false;
	hoppieList.RemoveAll();

	Logger::Log("SYSTEM: hoppieClear()");
}


bool CHoppieConn::Message(bool cType, int mType, CString cs, CString msg)
{
	netClear = false;

	// Variables:
	CString	URI, strToken, sType = "", format;

	// Select Message Type
	if (cType == MSG_SEND)
		switch (mType)
		{
		case MSG_TELEX: sType = "telex"; break;
		case MSG_CPDLC: sType = "cpdlc"; break;
		case MSG_ADSC: sType = ""; break;
		default: sType = "";
		}
	else if (cType == MSG_RECEIVE)
		switch (mType)
		{
		case MSG_POLL: sType = "poll"; msg = ""; cs = callsign; break;
		case MSG_PEK:  sType = "peek"; msg = ""; cs = callsign; break;
		case MSG_PING: sType = "ping"; msg = "ALL-CALLSIGNS";  cs = callsign; break;
		default: sType = "";
		}

	// Return false, if invalid Type Combination
	if (sType == "")
	{
		error = "WRONG TYPE";
		format.Format("%s >> %s: %s (WRONG TYPE:%s)", callsign, cs, msg, sType);
		Logger::Log(format);
		return false;
	}

	// Create URL String
	// ex.: www.nl/acars/system/connect.html?type=ping&logon=CODE&from=TEST&to=TEST&packet=ALL-CALLSIGNS
	m_mType = mType;
	URI.Format("%s?type=%s&logon=%s&from=%s&to=%s&packet=%s", base, sType, logonCode, callsign, cs, msg);
	AddDownload(_T("http://" + server + base + URI));

	if (mType != MSG_PING && mType != MSG_POLL) {
		format.Format("%s >> %s: %s (%s)", callsign, cs, msg, sType);
		Logger::Log(format);
	}
	return true;
}


void CHoppieConn::OnAfterRequestFinish(FCHttpRequest& rTask)
{
	netClear = true;
	bool bOK = false;

	// Check Response Info
	const HTTP_RESPONSE_INFO &r = rTask.GetResponseInfo();

	if (r.m_status_code == HTTP_STATUS_OK)
	{
		if (r.m_content_length)
		{
			// avoid network broken during downloading
			if (r.m_content_length == rTask.GetTotalReceiveByte())
				bOK = true;
		}
		else
		{
			// no Content-Type field, maybe is a dynamic page, such as PHP, ASP...
			if (r.m_final_read_result)
				bOK = true;
		}
	}
	if (!bOK) {
		m_mType = -1;
		return;
	}

	// Data Received and Complete
	std::string receive_data;
	rTask.PopReceived(receive_data);
	CString strToken = receive_data.c_str();
	strToken.MakeUpper();

	// ... process received data

	// If Message was OK (= no Errors)
	if (strncmp(strToken, "OK", 2) != 0)
	{
		m_mType = -1;
		error = strToken;
		//hoppieConnected = true;
		return;
	}

	// no Errors
	error = "";
	int iStart = 1, found = 0, pos = -1;

	// If Type = PEEK or POLL and Answer not empty
	if ((m_mType == MSG_POLL || m_mType == MSG_PEK) && strToken.GetLength() > 3)
	{
		POSITION posi;
		CString sCallsign, msg, format, responseId = "-1";
		int pos2, messageId = -1;

		// Remove "OK " from String
		strToken = strToken.Mid(3);

		// Clear Inc Data String
		data.RemoveAll();


		// Cut Inc Messages by "}}" 
		for (int i = 0; strToken != ""; ++i)
		{
			for (int j = 0; j < strToken.GetLength() - 1; ++j)
			{
				// If Message end is found ("}}")
				if (!found && strToken[j] == '}' && strToken[j + 1] == '}')
				{
					found = j + 3;
					iStart = 1;
					sCallsign = strToken.Tokenize(" ", iStart);


					// Check, if current Message is a CPDLC message
					// ex.:   TESA cpdlc {/data2/30//Y/REQUEST LOGON}
					if ((pos = strToken.Mid(1, j).Find("CPDLC")) > -1)
					{
						// Get Message ID
						pos = strToken.Mid(1, j).Find("DATA2");
						pos += 7;
						pos2 = strToken.Mid(pos, j).Find("/");
						messageId = atoi(strToken.Mid(pos, pos2));

						pos += pos2 + 1;
						if (strToken[pos] != '/')
						{
							pos2 = strToken.Mid(pos, j).Find("/");
							responseId = strToken.Mid(pos, pos2);
						}

						//LOGOFF
						if ((pos = strToken.Mid(pos, j).Find("LOGOFF")) > -1)
						{
							iconify = false;

							if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
							{
								hoppieList.GetAt(posi).m_Connected = 2;
								hoppieList.GetAt(posi).m_Voice.Insert(2, "LOGOFF/");

								format.Format("%s >> %s: LOGOFF", sCallsign, callsign);
							}
							else
								format.Format("?%s? >> %s: LOGOFF", sCallsign, callsign);

							if (notificationSound)
								PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
						}

						//REQUEST
						else if ((pos = strToken.Mid(pos, j).Find("REQUEST")) > -1)
						{
							iconify = false;

							// LOGON REQUEST
							if ((pos = strToken.Mid(pos, j).Find("LOGON")) > -1)
							{
								// If AC is already Connected
								if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
								{
									// Return "ALREADY CONNECTED"
									Message(MSG_SEND, MSG_TELEX, sCallsign, "ALREADY CONNECTED");

									msg.Format("/data2/%d/%d/NE/LOGON ACCEPTED", cpdlcCounter, messageId);
									cpdlcCounter++;

									Message(MSG_SEND, MSG_CPDLC, sCallsign, msg);


									format.Format("%s >> %s: REQUEST LOGON (ALREADY CONNECTED)", sCallsign, callsign);
								}
								// New AC
								else
								{
									/*
									if (m_VinicityAcList.GetAt(posi).m_SectorEntry >= 10)
									{
										msg.Format("/data2/%d/%d/NE/STANDBY", hoppie.cpdlcCounter, messageId);
										hoppie.cpdlcCounter++;
									
										hoppieMsg(MSG_SEND, MSG_CPDLC, sCallsign, msg);

										CHoppieList aircraft;
										aircraft.setVal(sCallsign, 3);
										aircraft.m_Voice.Append("REQ LOGON/");
										aircraft.m_VoiceId.Format("%d", messageId);
									
										hoppieList.AddTail(aircraft);
									}
									else
									{
									*/
									if ((posi = _SelectAcFromVicinityList(VICINITY_LIST, sCallsign)) != NULL)
									{
										// Add to List and wait for Controller to answer Request
										CHoppieList aircraft;
										aircraft.SetVal(sCallsign, 3);
										aircraft.m_Voice.Append("REQ LOGON/");
										aircraft.m_VoiceId.Format("%d", messageId);

										hoppieList.AddTail(aircraft);
									}
									else
									{
										// Add to List and wait for Controller to answer Request
										CHoppieList aircraft;
										aircraft.SetVal(sCallsign, 3);
										aircraft.m_Voice.Append("REQ LOGON/");
										aircraft.m_VoiceId.Format("%d", messageId);

										hoppieList.AddTail(aircraft);
									}
									format.Format("%s >> %s: REQUEST LOGON", sCallsign, callsign);

									if (notificationSound)
										PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								}
							}//LOGON REQUEST
							// VERTICAL REQUEST
							else if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL && ((pos = strToken.Mid(pos, j).Find("CLIMB")) > -1 || (pos = strToken.Mid(pos, j).Find("DESCEND")) > -1 ||
								(pos = strToken.Mid(pos, j).Find("CLMB")) > -1 || (pos = strToken.Mid(pos, j).Find("DES")) > -1 ||
								(pos = strToken.Mid(pos, j).Find(" FL")) > -1 || (pos = strToken.Mid(pos, j).Find("@FL")) > -1))
							{
								CString altitude;

								// Boeing Format
								if ((pos = strToken.Mid(pos, j).Find("CLIMB")) > -1 || (pos = strToken.Mid(pos, j).Find("DESCEND")) > -1 ||
									(pos = strToken.Mid(pos, j).Find("@FL")) > -1)
								{
									pos = pos + strToken.Mid(pos, j).Find("@") + 1;

									if ((pos2 = strToken.Mid(pos, j).Find("@")) > -1)
										altitude = strToken.Mid(pos, pos2);
									else
										altitude = strToken.Mid(pos, j - pos);

									if (altitude[0] == 'F' && altitude[1] == 'L')
										altitude = altitude.Mid(2);
									else
										altitude = altitude.Mid(0, 3);

									format.Format("%s >> %s: REQUEST FL%s (Boeing)", sCallsign, callsign, altitude);
								}
								// Airbus Format
								else
								{
									pos = pos + strToken.Mid(pos, j).Find(" FL") + 1;

									if ((pos2 = strToken.Mid(pos, j).Find("@")) > -1)
										altitude = strToken.Mid(pos, pos2);
									else
										altitude = strToken.Mid(pos, j - pos);

									if (altitude[0] == 'F' && altitude[1] == 'L')
										altitude = altitude.Mid(2);
									else
										altitude = altitude.Mid(0, 3);

									format.Format("%s >> %s: REQUEST FL%s (Airbus)", sCallsign, callsign, altitude);
								}

								// 
								if (hoppieList.GetAt(posi).m_LevelId != "" || hoppieList.GetAt(posi).m_LevelATCId != "")
								{
									format.Format("%s >> %s: REQUEST FL%s (not clear)", sCallsign, callsign, altitude);
									msg.Format("/data2/%d/%d/NE/UNABLE", cpdlcCounter, messageId);
									cpdlcCounter++;

									Message(MSG_SEND, MSG_CPDLC, sCallsign, msg);

								}
								// Forward Request to Controller
								else if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
								{
									hoppieList.GetAt(posi).m_Level.Insert(2, "RF " + altitude + "/");
									hoppieList.GetAt(posi).m_LevelId.Format("%d", messageId);

									if (notificationSound)
										PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								}
							}
							// DIRECT REQUEST
							else if ((pos = strToken.Mid(pos, j).Find("DIRECT")) > -1 || (pos = strToken.Mid(pos, j).Find("DIR")) > -1)
							{
								CString waypoint;

								// Boeing Format
								if ((pos = strToken.Mid(pos, j).Find("DIRECT")) > -1)
								{
									pos = pos + strToken.Mid(pos, j).Find("@") + 1;

									if ((pos2 = strToken.Mid(pos, j).Find("@")) > -1)
										waypoint = strToken.Mid(pos, pos2);
									else
										waypoint = strToken.Mid(pos, j - pos);

									format.Format("%s >> %s: REQUEST DCT %s (Boeing)", sCallsign, callsign, waypoint);

								}
								// Airbus Format										
								else
								{
									pos = pos + strToken.Mid(pos, j).Find("TO ") + 3;

									if ((pos2 = strToken.Mid(pos, j).Find("@")) > -1)
										waypoint = strToken.Mid(pos, pos2);
									else
										waypoint = strToken.Mid(pos, j - pos);

									format.Format("%s >> %s: REQUEST DCT %s (Airbus)", sCallsign, callsign, waypoint);
								}

								// 
								if (hoppieList.GetAt(posi).m_RouteId != "" || hoppieList.GetAt(posi).m_RouteATCId != "")
								{
									format.Format("%s >> %s: REQUEST DCT %s (not clear)", sCallsign, callsign, waypoint);
									msg.Format("/data2/%d/%d/NE/UNABLE", cpdlcCounter, messageId);
									cpdlcCounter++;

									Message(MSG_SEND, MSG_CPDLC, sCallsign, msg);

								}
								// Forward Request to Controller
								else if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
								{
									hoppieList.GetAt(posi).m_Route.Insert(2, "RD " + waypoint + "/");
									hoppieList.GetAt(posi).m_RouteId.Format("%d", messageId);

									if (notificationSound)
										PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								}
							}
							// Unknown Commands
							else
							{
								// TODO: ADD CPDLC COMMANDS
								msg.Format("/data2/%d/%d/NE/UNABLE", cpdlcCounter, messageId);
								cpdlcCounter++;
								Message(MSG_SEND, MSG_CPDLC, sCallsign, msg);

								Message(MSG_SEND, MSG_TELEX, sCallsign, "MESSAGE NOT SUPPORTED BY THIS ATS UNIT");

								format.Format("%s >> %s: %s (UNAVAILABLE)", sCallsign, callsign, strToken.Mid(pos, j));

							}
						}//REQUEST
						// WILCO RESPONSE
						else if ((pos = strToken.Mid(1, j).Find("WILCO")) > -1)
						{
							iconify = false;

							format.Format("%s >> %s: %s", sCallsign, callsign, strToken.Mid(i, j));

							// Get Callsign
							iStart = 1;
							sCallsign = strToken.Tokenize(" ", iStart);

							// Get Message ID
							messageId = -1;

							pos = strToken.Mid(1, j).Find("DATA2");
							pos += 7;
							pos2 = strToken.Mid(pos, j).Find("/");
							messageId = atoi(strToken.Mid(pos, pos2));

							pos += pos2 + 1;
							if (strToken[pos] != '/')
							{
								pos2 = strToken.Mid(pos, j).Find("/");
								responseId = strToken.Mid(pos, pos2);

								if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
								{
									if (responseId == hoppieList.GetAt(posi).m_LevelATCId)
									{
										hoppieList.GetAt(posi).m_LevelATCId = "";
										hoppieList.GetAt(posi).m_LevelTimer = 0;

										hoppieList.GetAt(posi).m_Level.Insert(2, "WCO/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_RouteATCId)
									{
										hoppieList.GetAt(posi).m_RouteATCId = "";
										hoppieList.GetAt(posi).m_RouteTimer = 0;

										hoppieList.GetAt(posi).m_Route.Insert(2, "WCO/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_SSRATCId)
									{
										hoppieList.GetAt(posi).m_SSRATCId = "";
										hoppieList.GetAt(posi).m_SSRTimer = 0;

										hoppieList.GetAt(posi).m_SSR.Insert(2, "WCO/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_VoiceATCId)
									{
										hoppieList.GetAt(posi).m_VoiceATCId = "";
										hoppieList.GetAt(posi).m_VoiceTimer = 0;

										hoppieList.GetAt(posi).m_Voice.Insert(2, "WCO/");


										CString	URI;
										DWORD	dwRet;

										URI.Format("%s?type=ping&logon=%s&from=%s&to=%s&packet=ALL-CALLSIGNS", base, logonCode, callsign, callsign);
										CInternetSession session;

										try {
											CHttpConnection *pConnection = session.GetHttpConnection(server);

											CHttpFile *pFile = pConnection->OpenRequest(NULL, URI);

											pFile->SendRequest();

											pFile->QueryInfoStatusCode(dwRet);

											if (dwRet != HTTP_STATUS_OK)
											{
												error.Format("%d", (int)dwRet);
												session.Close();
												return;
											}


											pFile->ReadString(error);

											session.Close();

											if (error.MakeUpper().Find("OK") != -1)
											{

												if (error.Find(hoppieList.GetAt(posi).m_NextStation) != -1)
													msg.Format("/data2/%d//NE/%s", cpdlcCounter, "HANDOVER @" + hoppieList.GetAt(posi).m_NextStation);
												else
													msg.Format("/data2/%d//NE/%s", cpdlcCounter, "LOGOFF\0");


												hoppieList.GetAt(posi).m_Relay->AddTail(msg);
												hoppieList.GetAt(posi).m_Connected = 2;
												error = "";
											}
											else {}

											delete pConnection;
											delete pFile;
											return;
										}
										catch (CInternetException*)
										{
											Logger::Log("SYSTEM: Exception->Wilco.Handoff.Logoff()");
											return;
										}
									}//m_VoiceATCId
								}//_SelectAcFromVicinityList
							}//strToken[pos]

							if (notificationSound)
								PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
						}//WILCO
						// UNABLE RESPONSE
						else if ((pos = strToken.Mid(1, j).Find("UNABLE")) > -1)
						{
							iconify = false;
							format.Format("%s >> %s: %s", sCallsign, callsign, strToken.Mid(i, j));

							// Get Callsign
							iStart = 1;
							sCallsign = strToken.Tokenize(" ", iStart);

							// Get Message ID
							messageId = -1;

							pos = strToken.Mid(1, j).Find("DATA2");
							pos += 7;
							pos2 = strToken.Mid(pos, j).Find("/");
							messageId = atoi(strToken.Mid(pos, pos2));

							pos += pos2 + 1;
							if (strToken[pos] != '/')
							{
								pos2 = strToken.Mid(pos, j).Find("/");
								responseId = strToken.Mid(pos, pos2);

								if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
								{
									if (responseId == hoppieList.GetAt(posi).m_LevelATCId)
									{
										hoppieList.GetAt(posi).m_LevelATCId = "";
										hoppieList.GetAt(posi).m_LevelTimer = 0;

										hoppieList.GetAt(posi).m_Level.Insert(2, "UNA/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_RouteATCId)
									{
										hoppieList.GetAt(posi).m_RouteATCId = "";
										hoppieList.GetAt(posi).m_RouteTimer = 0;

										hoppieList.GetAt(posi).m_Route.Insert(2, "UNA/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_SSRATCId)
									{
										hoppieList.GetAt(posi).m_SSRATCId = "";
										hoppieList.GetAt(posi).m_SSRTimer = 0;

										hoppieList.GetAt(posi).m_SSR.Insert(2, "UNA/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_VoiceATCId)
									{
										hoppieList.GetAt(posi).m_VoiceATCId = "";
										hoppieList.GetAt(posi).m_VoiceTimer = 0;

										hoppieList.GetAt(posi).m_Voice.Insert(2, "UNA/");
									}
								}//_SelectAcFromVicinityList
							}//strToken[pos]

							if (notificationSound)
								PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

						}//UNABLE
						// STANDBY RESPONSE
						else if ((pos = strToken.Mid(1, j).Find("STANDBY")) > -1)
						{
							iconify = false;
							format.Format("%s >> %s: %s", sCallsign, callsign, strToken.Mid(i, j));

							// Get Callsign
							iStart = 1;
							sCallsign = strToken.Tokenize(" ", iStart);

							// Get Message ID
							messageId = -1;

							pos = strToken.Mid(1, j).Find("DATA2");
							pos += 7;
							pos2 = strToken.Mid(pos, j).Find("/");
							messageId = atoi(strToken.Mid(pos, pos2));

							pos += pos2 + 1;
							if (strToken[pos] != '/')
							{
								pos2 = strToken.Mid(pos, j).Find("/");
								responseId = strToken.Mid(pos, pos2);

								if ((posi = _SelectAcFromVicinityList(HOPPIE_LIST, sCallsign)) != NULL)
								{
									if (responseId == hoppieList.GetAt(posi).m_LevelATCId)
									{
										hoppieList.GetAt(posi).m_Level.Insert(2, "SBY/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_RouteATCId)
									{
										hoppieList.GetAt(posi).m_Route.Insert(2, "SBY/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_SSRATCId)
									{
										hoppieList.GetAt(posi).m_SSR.Insert(2, "SBY/");
									}
									else if (responseId == hoppieList.GetAt(posi).m_VoiceATCId)
									{
										hoppieList.GetAt(posi).m_Voice.Insert(2, "SBY/");
									}
								}
							}

							if (notificationSound)
								PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

						}//STANDBY
						// if current CPDLC Message isn't recognized, send SERVICE UNAVAILABLE
						else
						{
							// Get Message ID
							messageId = -1;

							pos = strToken.Mid(1, j).Find("DATA2");
							pos += 7;
							pos2 = strToken.Mid(pos, j).Find("/");
							messageId = atoi(strToken.Mid(pos, pos2));

							// Return "SERVICE UNAVAILABLE"
							msg.Format("/data2/%d/%d/NE/UNABLE", cpdlcCounter, messageId);
							cpdlcCounter++;
							Message(MSG_SEND, MSG_CPDLC, sCallsign, msg);

							Message(MSG_SEND, MSG_TELEX, sCallsign, "MESSAGE NOT SUPPORTED BY THIS ATS UNIT");
							format.Format("%s >> %s: %s (UNAVAILABLE)", sCallsign, callsign, strToken.Mid(pos, j));
						}

						Logger::Log(format);
					}//CPDLC
					// PDC
					else if ((pos = strToken.Mid(1, j).Find("PREDEP")) > -1)
					{
						Message(MSG_SEND, MSG_TELEX, sCallsign, "PDC CURRENTLY NOT SUPPORTED BY THIS ATS UNIT");
						format.Format("%s >> %s: %s (PDC UNAVAILABLE)", sCallsign, callsign, strToken.Mid(pos, j));

						Logger::Log(format);
					}
					// TELEX
					else
					{
						CString temp = strToken.Mid(strToken.Mid(1, j).Find("{"), j - 2);
						temp.Remove('}'); temp.Remove('{');

						if (notificationSound)
							PlaySound(_T(currentDir + "notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

						format.Format("%s >> %s: %s (TELEX)", sCallsign, callsign, strToken.Mid(pos, j));

						Logger::Log(format);
					}
				}
			}
			// Remove last processed Message from String and Repeat
			strToken = strToken.Mid(found, strToken.GetLength() - (found));
			found = 0;
		}
	}//if POLL/PEEK DATA


	// If Type = PING and Answer not empty (Hoppie replies with Callsign List)
	else if (m_mType == MSG_PING && strToken.GetLength() > 3)
	{
		// Clear current List containing all Hoppie Aircraft 
		// (Not the Data List used by the Frame; Just a generic List used for comparison and the Tag Item)
		hoppieAcList.RemoveAll();

		// Add Test AC to Datalink List (else it will get Timed out in the actual Data List)
		//hoppieAcList.AddHead("SAS2597");

		// Remove "OK {" from String
		strToken = strToken.Mid(4, strToken.GetLength() - 5);

		// Select first Callsign
		CString sTemp = strToken.Tokenize(" ", iStart);

		// Fill hoppieAcList with Callsigns from Reply (example String: "ok {DLH124 WFP KLM SAS2597}")
		while (sTemp != "") {
			hoppieAcList.AddTail(sTemp);
			sTemp = strToken.Tokenize(" ", iStart);
		}

		// Check, if Aircraft Connected with this Station (in hoppieList) are still in the Hoppie Network (hoppieAcList)
		for (int i = 0; i < hoppieList.GetCount(); ++i)
		{
			// If the AC isn't connected to the Hoppie Network anymore, start the Timeout timer
			// The Aircraft gets removed automatically after 120 seconds (12*10)
			if ((!hoppieAcList.Find(hoppieList.GetAt(hoppieList.FindIndex(i)).m_Callsign)) && hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected != 2 && hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected != 6)
			{
				if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Timeout == 12)
					hoppieList.RemoveAt(hoppieList.FindIndex(i));
				else
				{
					if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected != 3 && hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected != 4 && hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected != 5)
						hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected = 0;
					else
						hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected = 4;

					hoppieList.GetAt(hoppieList.FindIndex(i)).m_Timeout++;
				}
			}
			// If AC sent Logoff Request, keep it in List for 60 seconds, then remove
			else if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected == 2)
			{
				if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Timeout == 6)
					hoppieList.RemoveAt(hoppieList.FindIndex(i));
				else
					hoppieList.GetAt(hoppieList.FindIndex(i)).m_Timeout++;
			}
			// If AC is connected to Hoppie Network (already or again), reset the Timer
			else
			{
				if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected == 0)
					hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected = 1;
				if (hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected == 4)
					hoppieList.GetAt(hoppieList.FindIndex(i)).m_Connected = 3;

				hoppieList.GetAt(hoppieList.FindIndex(i)).m_Timeout = 0;
			}
		}
	}

	//hoppieConnected = true;
	m_mType = -1;
}


BOOL CHoppieConn::HoppiePing()
{
	CString	URI, format;
	DWORD	dwRet;
	CInternetSession session;

	URI.Format("%s?type=ping&logon=%s&from=%s&to=%s", base, logonCode, callsign, callsign);
	
	try {
		CHttpConnection *pConnection = session.GetHttpConnection(server);

		CHttpFile *pFile = pConnection->OpenRequest(NULL, URI);

		pFile->SendRequest();

		pFile->QueryInfoStatusCode(dwRet);

		if (dwRet != HTTP_STATUS_OK)
		{
			error.Format("%d", (int)dwRet);
			session.Close();
			return hoppieConnected = false;
		}


		pFile->ReadString(error);

		session.Close();

		if (strncmp(error.MakeUpper(), "OK", 2) == 0)
		{
			error = "";
			return hoppieConnected = true;
		}
		else
		{
			format.Format("SYSTEM: Connect Failed (%s)", error);
			Logger::Log(format);
			return hoppieConnected = false;
		}

		delete pConnection;
		delete pFile;

		return hoppieConnected = true;
	}
	catch (CInternetException*)
	{
		//session.Close();
		//pEx->ReportError(); //If error, report it in a message box
		Logger::Log("SYSTEM: Exception->HoppieConnect()");
		return hoppieConnected = false;
	}
}
