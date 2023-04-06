// AChartEditView.cpp : implementation file
//

#include "stdafx.h"
#include "ADataEdit.h"

#include "ADataEditDoc.h"
#include "AChartEditView.h"

#include "math.h"
#include "cdib.h"
#include "ChartPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAChartEditView

IMPLEMENT_DYNCREATE(CAChartEditView, CView)

BEGIN_MESSAGE_MAP(CAChartEditView, CView)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_CARET,OnUpdateCaretPos)

	//{{AFX_MSG_MAP(CAChartEditView)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CHART_SETTING, OnChartSetting)
	ON_COMMAND(ID_CHART_EDIT_COPY, OnChartEditCopy)
	ON_UPDATE_COMMAND_UI(ID_CHART_EDIT_COPY, OnUpdateChartEditCopy)
	ON_COMMAND(ID_CHART_EDIT_PASTE, OnChartEditPaste)
	ON_COMMAND(ID_CHART_EDIT_CUT, OnChartEditCut)
	ON_UPDATE_COMMAND_UI(ID_CHART_EDIT_CUT, OnUpdateChartEditCut)
	ON_COMMAND(ID_CHART_SAVEAS, OnChartSaveas)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BUTTONZoomIn, OnBUTTONZoomIn)
	ON_UPDATE_COMMAND_UI(ID_BUTTONZoomIn, OnUpdateBUTTONZoomIn)
	ON_COMMAND(ID_BUTTONZoomOut, OnBUTTONZoomOut)
	ON_UPDATE_COMMAND_UI(ID_BUTTONZoomOut, OnUpdateBUTTONZoomOut)
	ON_COMMAND(ID_BUTTONZoomAll, OnBUTTONZoomAll)
	ON_UPDATE_COMMAND_UI(ID_BUTTONZoomAll, OnUpdateBUTTONZoomAll)
	ON_COMMAND(ID_BUTTONChartToDown, OnBUTTONChartToDown)
	ON_COMMAND(ID_BUTTONChartToUp, OnBUTTONChartToUp)
	ON_COMMAND(ID_BUTTONChartToL, OnBUTTONChartToL)
	ON_UPDATE_COMMAND_UI(ID_BUTTONChartToL, OnUpdateBUTTONChartToL)
	ON_UPDATE_COMMAND_UI(ID_BUTTONChartToDown, OnUpdateBUTTONChartToDown)
	ON_UPDATE_COMMAND_UI(ID_BUTTONChartToUp, OnUpdateBUTTONChartToUp)
	ON_COMMAND(ID_BUTTONChartToR, OnBUTTONChartToR)
	ON_UPDATE_COMMAND_UI(ID_BUTTONChartToR, OnUpdateBUTTONChartToR)
	ON_COMMAND(ID_BUTTONZoomInW, OnBUTTONZoomInW)
	ON_UPDATE_COMMAND_UI(ID_BUTTONZoomInW, OnUpdateBUTTONZoomInW)
	ON_COMMAND(ID_BUTTON32820, OnButton32820)
	ON_UPDATE_COMMAND_UI(ID_BUTTON32820, OnUpdateButton32820)
	ON_COMMAND(ID_BUTTONQUICKDRAW, OnButtonquickdraw)
	ON_UPDATE_COMMAND_UI(ID_BUTTONQUICKDRAW, OnUpdateButtonquickdraw)
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAChartEditView::CAChartEditView()
{
//	AfxOleInit();

	EditLineNo = 0;
	LastEditLine = 2;

//	maxX=GetSystemMetrics(SM_CXFULLSCREEN);
//	maxY=GetSystemMetrics(SM_CYFULLSCREEN);

	maxX=GetSystemMetrics(SM_CXSCREEN);
	maxY=GetSystemMetrics(SM_CYSCREEN);

	DispScaleX = ((maxX*100)/1024)/100.0;
	DispScaleY = ((maxY*100)/768)/100.0;

	Timeapartm = Vapartm = Aapartm = AHapartm = 1;
	TimeapartmV = VapartmV = AapartmA = AHapartmAH = 1;
	
	PreparememDC = FALSE;
	PrepareChartData = FALSE;
	DrawXYLine = FALSE;
	FileTypeCode.Empty();

	b_Break = FALSE;

	fCapture = FALSE;
	fBoxing = FALSE;
    DataCapture = FALSE;
    DataBoxing = FALSE;
	b_FindCapture = FALSE;
	m_HandMoveAble = FALSE;
	QuickDraw = FALSE;
	NCDrawRectCapture = FALSE;

	GP16 = 0.0;
	GT = 0.0;
	Gx = 0.0;
	Gy = 0.0;
	startx = 0.0;
	starty = 0.0;
	centx = 999.9;
	centy = 999.9;
	Circler = 999.9;
	Angle = 0.0;

	maxXvalue = -10000.0;
	minXvalue = 10000.0;
	maxYvalue = -10000.0;
	minYvalue = 10000.0;

	G4 = '*';
	G5 = '*';
	s_startx.Empty();
	s_starty.Empty();
	s_centx.Empty();
	s_centy.Empty();
	s_Circler.Empty();
	s_Diameter.Empty();
	s_R.Empty();
	s_GT.Empty();
//	LastEditLine = 2;
	NCDrawScale = 1.0;
//	NCDrawRectCapture = FALSE;
	NCFileName.Empty();
/*
	BYTE buf;
	CFile file("c:\\cddyV3.0\\ADataEdit.ind",CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	
	ar >> m_SelectV >> m_SelectA;
	ar >> m_SelectAH >> m_SelectT1 >> m_SelectT2;
	ar >> m_TitleText >> m_XText >> m_YText >> m_RadioLineType;
	ar >> buf >> buf;
	ar >> VLineColor >> ALineColor >> AHLineColor >> T1LineColor >> T2LineColor;
	ar >> TitleTextColor >> XTextColor >> YTextColor;
	ar >> XLineColor >> YLineColor >> GridLineColor;
	ar >> BackGroundColor >> TextColor >> LineNoColor;
	ar >> m_GoToLineNo;
	ar >> buf >> buf;
	ar >> m_BandRate;
	ar >> m_Parity;
	ar >> m_WordLength;
	ar >> m_StopBits;
	ar >> m_CodeType;
	ar >> m_ComPortNo;
	ar >> m_AutoXonXoff;
	ar >> buf >> buf;
	ar >> m_InputControlMode;
	ar >> m_OutputControlMode;
	ar >> m_InputStartString;
	ar >> m_InputEndString;
	ar >> m_OutputStartString;
	ar >> m_OutputEndString;
	ar >> m_OutputSendDelay;
	ar >> m_InputTimeOut;
	ar.Close();
	file.Close();
*/
	CWinApp* pApp = AfxGetApp();

	m_SelectV = pApp->GetProfileInt("Settings","m_SelectV",0);
	m_SelectA = pApp->GetProfileInt("Settings","m_SelectA",1);
	m_SelectAH = pApp->GetProfileInt("Settings","m_SelectAH",0);
	m_SelectT1 = pApp->GetProfileInt("Settings","m_SelectT1",0);
	m_SelectT2 = pApp->GetProfileInt("Settings","m_SelectT2",0);
	m_TitleText = pApp->GetProfileString("Settings","m_TitleText","Time - A");
	m_XText = pApp->GetProfileString("Settings","m_XText","Time");
	m_YText = pApp->GetProfileString("Settings","m_YText","A");
	m_RadioLineType = pApp->GetProfileInt("Settings","m_RadioLineType",2);

	VLineColor = pApp->GetProfileInt("Settings","VLineColor",32768);
	ALineColor = pApp->GetProfileInt("Settings","ALineColor",16711680);
	AHLineColor = pApp->GetProfileInt("Settings","AHLineColor",128);
	T1LineColor = pApp->GetProfileInt("Settings","T1LineColor",32768);
	T2LineColor = pApp->GetProfileInt("Settings","T2LineColor",32768);
	TitleTextColor = pApp->GetProfileInt("Settings","TitleTextColor",32768);
	XTextColor = pApp->GetProfileInt("Settings","XTextColor",33023);
	YTextColor = pApp->GetProfileInt("Settings","YTextColor",32768);
	XLineColor = pApp->GetProfileInt("Settings","XLineColor",32768);
	YLineColor = pApp->GetProfileInt("Settings","YLineColor",32768);
	GridLineColor = pApp->GetProfileInt("Settings","GridLineColor",33023);

	m_vpoX = 0;
    m_vpoY = 0;
	m_XScale = 1.6;
	m_YScale = 1.6;

	T2LineColor = (RGB(255,0,255));
	
	ALinePen.CreatePen(PS_INSIDEFRAME,0.1,ALineColor);
	VLinePen.CreatePen(PS_INSIDEFRAME,0.1,VLineColor);
	AHLinePen.CreatePen(PS_INSIDEFRAME,0.1,AHLineColor);
	T1LinePen.CreatePen(PS_INSIDEFRAME,0.1,T1LineColor);
	T2LinePen.CreatePen(PS_INSIDEFRAME,0.1,T2LineColor);
	XLinePen.CreatePen(PS_INSIDEFRAME,0.1,XLineColor);
	if(m_RadioLineType == 0){GridLinePen.CreatePen(PS_INSIDEFRAME,0.1,GridLineColor);}
	if(m_RadioLineType == 2){GridLinePen.CreatePen(PS_DOT,0.1,GridLineColor);}
	if(m_RadioLineType == 1){GridLinePen.CreatePen(PS_INSIDEFRAME,0.1,GridLineColor);}
}

void CAChartEditView::OnDestroy() 
{
	CView::OnDestroy();
/*	CFile file("c:\\cddyV3.0\\ADataEdit.ind",CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	ar << m_SelectV << m_SelectA;
	ar << m_SelectAH << m_SelectT1 << m_SelectT2 << m_TitleText;
	ar << m_XText << m_YText << m_RadioLineType;
	ar << '\r' << '\n';
	ar << VLineColor << ALineColor << AHLineColor << T1LineColor << T2LineColor;
	ar << TitleTextColor << XTextColor << YTextColor;
	ar << XLineColor << YLineColor << GridLineColor;
	ar << BackGroundColor << TextColor << LineNoColor;
	ar << m_GoToLineNo;
	ar << '\r' << '\n';
	ar << m_BandRate;
	ar << m_Parity;
	ar << m_WordLength;
	ar << m_StopBits;
	ar << m_CodeType;
	ar << m_ComPortNo;
	ar << m_AutoXonXoff;
	ar << '\r' << '\n';
	ar << m_InputControlMode;
	ar << m_OutputControlMode;
	ar << m_InputStartString;
	ar << m_InputEndString;
	ar << m_OutputStartString;
	ar << m_OutputEndString;
	ar << m_OutputSendDelay;
	ar << m_InputTimeOut;
	ar.Close();
	file.Close();
*/
	
		CWinApp* pApp = AfxGetApp();

	pApp->WriteProfileInt("Settings","m_SelectV",m_SelectV);
	pApp->WriteProfileInt("Settings","m_SelectA",m_SelectA);
	pApp->WriteProfileInt("Settings","m_SelectAH",m_SelectAH);
	pApp->WriteProfileInt("Settings","m_SelectT1",m_SelectT1);
	pApp->WriteProfileInt("Settings","m_SelectT2",m_SelectT2);
	pApp->WriteProfileString("Settings","m_TitleText",m_TitleText);
	pApp->WriteProfileString("Settings","m_XText",m_XText);
	pApp->WriteProfileString("Settings","m_YText",m_YText);
	pApp->WriteProfileInt("Settings","m_RadioLineType",m_RadioLineType);

	pApp->WriteProfileInt("Settings","VLineColor",VLineColor);
	pApp->WriteProfileInt("Settings","ALineColor",ALineColor);
	pApp->WriteProfileInt("Settings","AHLineColor",AHLineColor);
	pApp->WriteProfileInt("Settings","T1LineColor",T1LineColor);
	pApp->WriteProfileInt("Settings","T2LineColor",T2LineColor);
	pApp->WriteProfileInt("Settings","TitleTextColor",TitleTextColor);
	pApp->WriteProfileInt("Settings","XTextColor",XTextColor);
	pApp->WriteProfileInt("Settings","YTextColor",YTextColor);
	pApp->WriteProfileInt("Settings","XLineColor",XLineColor);
	pApp->WriteProfileInt("Settings","YLineColor",YLineColor);
	pApp->WriteProfileInt("Settings","GridLineColor",GridLineColor);

/*
	pApp->WriteProfileInt("Settings","BackGroundColor",BackGroundColor);
	pApp->WriteProfileInt("Settings","TextColor",TextColor);
	pApp->WriteProfileInt("Settings","LineNoColor",LineNoColor);
	pApp->WriteProfileInt("Settings","m_GoToLineNo",m_GoToLineNo);

	pApp->WriteProfileString("Settings","m_BandRate",m_BandRate);
	pApp->WriteProfileString("Settings","m_Parity",m_Parity);
	pApp->WriteProfileString("Settings","m_WordLength",m_WordLength);
	pApp->WriteProfileString("Settings","m_StopBits",m_StopBits);
	pApp->WriteProfileString("Settings","m_CodeType",m_CodeType);
	pApp->WriteProfileString("Settings","m_ComPortNo",m_ComPortNo);
	pApp->WriteProfileString("Settings","m_AutoXonXoff",m_AutoXonXoff);
	pApp->WriteProfileString("Settings","m_InputControlMode",m_InputControlMode);
	pApp->WriteProfileString("Settings","m_OutputControlMode",m_OutputControlMode);
	pApp->WriteProfileString("Settings","m_InputStartString",m_InputStartString);
	pApp->WriteProfileString("Settings","m_InputEndString",m_InputEndString);
	pApp->WriteProfileString("Settings","m_OutputStartString",m_OutputStartString);
	pApp->WriteProfileString("Settings","m_OutputEndString",m_OutputEndString);
	pApp->WriteProfileInt("Settings","m_InputTimeOut",m_InputTimeOut);
	pApp->WriteProfileInt("Settings","m_OutputSendDelay",m_OutputSendDelay);
	pApp->WriteProfileInt("Settings","b_AttachChart",b_AttachChart);
*/
}

CAChartEditView::~CAChartEditView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAChartEditView drawing

CADataEditDoc* CAChartEditView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADataEditDoc)));
	return (CADataEditDoc*)m_pDocument;
}

void CAChartEditView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();

    HICON hIcon=AfxGetApp() ->LoadIcon(IDI_ICON1);
	ASSERT(hIcon); 
    AfxGetMainWnd() ->SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon); 

    m_TextEditCopyEnable = pDoc->m_TextEditCopyEnable;

	PrepareChartData = FALSE;
	DrawXYLine = FALSE;
	FileTypeCode.Empty();

	if(PreparememDC == TRUE)
	memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);

		GP16 = 0.0;
	GT = 0.0;
	Gx = 0.0;
	Gy = 0.0;
	startx = 0.0;
	starty = 0.0;
	centx = 999.9;
	centy = 999.9;
	Circler = 999.9;

	maxXvalue = -10000.0;
	minXvalue = 10000.0;
	maxYvalue = -10000.0;
	minYvalue = 10000.0;

	G4 = '*';
	G5 = '*';
	s_startx.Empty();
	s_starty.Empty();
	s_centx.Empty();
	s_centy.Empty();
	s_Circler.Empty();
	s_Diameter.Empty();
	s_R.Empty();
	s_GT.Empty();
	LastEditLine = 2;
	EditLineNo = 0;
	NCDrawScale = 1.0;
//	NCDrawRectCapture = FALSE;
	NCFileName.Empty();

	m_vpoX = 0;
    m_vpoY = 0;
	m_XScale = 1.6;
	m_YScale = 1.6;

	Invalidate(0);
}

void CAChartEditView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnPrepareDC(pDC, pInfo);
}

BOOL CAChartEditView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	
	return CView::OnPreparePrinting(pInfo);
}

void CAChartEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnBeginPrinting(pDC, pInfo);
}

void CAChartEditView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnPrint(pDC, pInfo);
}

void CAChartEditView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnEndPrinting(pDC, pInfo);
}


void CAChartEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CAChartEditView diagnostics

#ifdef _DEBUG
void CAChartEditView::AssertValid() const
{
	CView::AssertValid();
}

void CAChartEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAChartEditView message handlers

void CAChartEditView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

      if(PreparememDC == FALSE)
	  {
		PrepareMemDC();
	   if(m_TextEditCopyEnable == TRUE)
	   {
		OnPrepareChartData();
	    DrawChartMemDC();
	   }
	  }

	  if(m_TextEditCopyEnable == TRUE)
	  {
		{
 	    OnPrepareChartData();
	    DrawChartMemDC();
		}
        dc.StretchBlt(0,0,maxX,maxY,&memDC1,0,0,maxX,maxY,SRCCOPY);
	  }
	// Do not call CView::OnPaint() for painting messages
}

void CAChartEditView::PrepareMemDC()
{
	CClientDC DC(this);
	CBitmap m_bmp1;
	
	m_bmp1.CreateCompatibleBitmap(&DC,maxX,maxY);
	memDC1.CreateCompatibleDC(&DC);
	memDC1.SelectObject(&m_bmp1);

	memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);

	PreparememDC = TRUE;
}

void CAChartEditView::DrawChartMemDC()
{
          if((DrawXYLine == FALSE)||(LastEditLine >= EditLineNo))
		  {
            CString s;
			int PoxX,PoxY;
			int NetX,NetY;

			memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);

			if(m_HandMoveAble ==0)AfxGetApp()->BeginWaitCursor();

			if(FileTypeCode == 'R')
		   {
			if (m_RadioLineType == 1)
			{
				NetX = 4;
				NetY = 4;
			}
			else 
			{
				NetX = 450.0*DispScaleX*m_XScale;
				NetY = 250.0*DispScaleY*m_YScale;
			}
			memDC1.SetTextColor(XLineColor);
			memDC1.SelectObject(&GridLinePen);
		
			int w;
            for (w = 0; w < Timeapartm +1; w++)
			{
				PoxX = 450*(DispScaleX*m_XScale*w)/Timeapartm;
			  if(PoxX>=0.0)
			  {
				memDC1.MoveTo(m_vpoX + 130 + PoxX,m_vpoY+(504*DispScaleY));
				memDC1.LineTo(m_vpoX + 130 + PoxX,m_vpoY+(504*DispScaleY)-NetY);
				
				s.Format("  %4.1f",(TimeapartmV*w));
				memDC1.TextOut(m_vpoX + 105 + PoxX,m_vpoY+(506*DispScaleY),s);
			  }
			}

            for (w = 1; w <  Aapartm +1; w++)
			{
				PoxY = 250*(DispScaleY*m_YScale*w)/ Aapartm;
			  if(PoxY>=0.0)
			  {
				memDC1.MoveTo(m_vpoX + 130 , m_vpoY +(504*DispScaleY) - PoxY);
				memDC1.LineTo(m_vpoX + 130 + NetX , m_vpoY +(504*DispScaleY) - PoxY);
				
				s.Format("  %4.1f",(AapartmA*w));
				memDC1.TextOut(m_vpoX + 80 , m_vpoY +490*DispScaleY - PoxY,s);
			  }
			}

			memDC1.SelectObject(&XLinePen);
            memDC1.MoveTo(441.0*DispScaleX*m_XScale+m_vpoX+160,m_vpoY+(502*DispScaleY));
			memDC1.LineTo(450.0*DispScaleX*m_XScale+m_vpoX+160,m_vpoY+(504*DispScaleY));
			memDC1.LineTo(441.0*DispScaleX*m_XScale+m_vpoX+160,m_vpoY+(506*DispScaleY));

			memDC1.MoveTo(450.0*DispScaleX*m_XScale+m_vpoX+160,m_vpoY+(504*DispScaleY));
			memDC1.LineTo(m_vpoX + 130,m_vpoY+(504*DispScaleY));                            //H.L
			memDC1.LineTo(m_vpoX + 130,m_vpoY+(504*DispScaleY)-270.0*DispScaleY*m_YScale);  //V.L

            memDC1.LineTo(m_vpoX + 128,(m_vpoY+(504*DispScaleY)-270.0*DispScaleY*m_YScale)+17);
            memDC1.LineTo(m_vpoX + 130,m_vpoY+(504*DispScaleY)-270.0*DispScaleY*m_YScale);
			memDC1.LineTo(m_vpoX + 132,(m_vpoY+(504*DispScaleY)-270.0*DispScaleY*m_YScale)+17);

			memDC1.SetTextColor(TitleTextColor);
			memDC1.TextOut (290.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+526*DispScaleY,m_TitleText);
			memDC1.SetTextColor(XTextColor);
			memDC1.TextOut (450.0*DispScaleX*m_XScale+m_vpoX+160,m_vpoY+486*DispScaleY,m_XText);
			memDC1.TextOut (70.0*DispScaleX+m_vpoX,(m_vpoY+(504*DispScaleY)-270.0*DispScaleY*m_YScale)-30,m_YText);
		  }

		  if(FileTypeCode =='O')
		  {
			memDC1.SetTextColor(XTextColor);
			CString s;
            int i,j;
			float RealXMarkValue,RealYMarkValue;

			RealXMarkValue = XMarkValue;
			RealYMarkValue = YMarkValue;

            if(minXvalue < 0)
			RealXMarkValue = -1.0 * XMarkValue;
			if(minYvalue < 0)
			RealYMarkValue = -1.0 * YMarkValue;
/*		
			s.Format("XMarkQty = %2i",XMarkQty);
			memDC1.TextOut(600,25,s,strlen(s));

            s.Format("XMarkValue = %6.3f",XMarkValue);
			memDC1.TextOut(600,40,s,strlen(s));

			s.Format("RealXMarkValue = %7.3f",RealXMarkValue);
			memDC1.TextOut(600,55,s,strlen(s));
*/
			j = 0;
			if(RealXMarkValue<0)
			{
			while(j*RealXMarkValue > minXvalue)
			{
				j++;
			}
			}

			for(i = 0; i <= (XMarkQty + 1); i++)
			{
			memDC1.MoveTo((j*RealXMarkValue + XMarkValue * i) * m_XScale * NCDrawScale + m_vpoX + (maxX/2 - OffsetX),117);
            memDC1.LineTo((j*RealXMarkValue + XMarkValue * i) * m_XScale * NCDrawScale + m_vpoX + (maxX/2 - OffsetX),125);
			if(Inch)
            s.Format("%4.2f",(j*RealXMarkValue + XMarkValue * i)/25.4);
			else
			s.Format("%4.1f",j*RealXMarkValue + XMarkValue * i);
            memDC1.TextOut((j*RealXMarkValue + XMarkValue * i) * m_XScale * NCDrawScale + m_vpoX + (maxX/2 - OffsetX),103,s,strlen(s));
			}
            
			j = 0;
			if(RealYMarkValue<0)
			{
			while(j*RealYMarkValue > minYvalue)
			{
				j++;
			}
			}

			for(i = 0; i <= (YMarkQty + 1); i++)
			{
			memDC1.MoveTo(42,-(j*RealYMarkValue+YMarkValue*i)*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY) + m_vpoY);
            memDC1.LineTo(50,-(j*RealYMarkValue+YMarkValue*i)*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY) + m_vpoY);
            if(Inch)
            s.Format("%4.2f",(j*RealYMarkValue + YMarkValue*i)/25.4);
			else
			s.Format("%4.1f",j*RealYMarkValue + YMarkValue*i);
            memDC1.TextOut(3,-(j*RealYMarkValue+YMarkValue*i)*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY) + m_vpoY-8,s,strlen(s));
			}
		  }

           DrawXYLine = TRUE;
		  }
		    DrawChartFunc();
		    if(m_HandMoveAble ==0)
			AfxGetApp()->EndWaitCursor();
}

void CAChartEditView::OnLButtonDown(UINT nFlags, CPoint point) 
{
		if(fBoxing)
		{
			fBoxing = FALSE;
			Invalidate(0);	
		}
		SetCapture();
		fCapture = TRUE;
//	    fBoxing = FALSE;
		ptAnchor = GetMessagePos();
        ptAnchor2 = point;
		ptOld = ptAnchor;
			
	CView::OnLButtonDown(nFlags, point);
}

void CAChartEditView::OnMouseMove(UINT nFlags, CPoint point) 
{
		MPointX = point.x;
		MPointY = point.y;
      if (fCapture)
	  {
        if (m_HandMoveAble ==0)
		{
			CPoint ptNow = GetMessagePos();
			CDC dcScreen;
			dcScreen.CreateDC("DISPLAY", NULL, NULL, NULL);
			dcScreen.SetROP2(R2_NOT);
			dcScreen.SelectStockObject(NULL_BRUSH);
			dcScreen.Rectangle(CRect(ptOld, ptAnchor));
			dcScreen.Rectangle(CRect(ptAnchor, ptNow));
			ptOld = ptNow;
			if(ptAnchor != ptOld)
			fBoxing = TRUE;
			HCURSOR hcur = AfxGetApp () ->LoadCursor (IDC_CURSOR1);
		    SetCursor (hcur); 
		}
		 if((m_HandMoveAble ==1)&&(!QuickDraw))
		 {
	        HCURSOR hcur = AfxGetApp () ->LoadCursor(IDC_HandCURSOR);
		    SetCursor (hcur);
            m_vpoX += point.x - ptAnchor2.x;
            m_vpoY += point.y - ptAnchor2.y;
            ptAnchor2 = point;

			Invalidate(0);
		 }
	  }

	CView::OnMouseMove(nFlags, point);
}

void CAChartEditView::OnLButtonUp(UINT nFlags, CPoint point) 
{
        ReleaseCapture();
		fCapture = FALSE;
//	    fBoxing = FALSE;		
	    CView::OnLButtonUp(nFlags, point);
}

void CAChartEditView::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	    pCmdUI->Enable(TRUE);
 
	    CString str,s1,s2,s3;
        if(FileTypeCode == 'R')
		{
        s1.Format("X: %5.1f     ",(MPointX*1.0-130.0-m_vpoX)/((450.0*DispScaleX*m_XScale)/(Timeapartm*TimeapartmV)));
   		s2.Format(" Y: %5.1f     ",-(MPointY*1.0-(504*DispScaleY)-m_vpoY)/((250/(AapartmA*Aapartm))*DispScaleY*m_YScale));
		}
        if((FileTypeCode == 'O')||(FileTypeCode == ':'))
		{
		 if(Inch)
		 {
        s1.Format("X: %6.4f  ",((MPointX - m_vpoX - (maxX/2 - OffsetX))/m_XScale * NCDrawScale)/25.4);
	    s2.Format(" Y: %6.4f  ",-((MPointY*1.0 - (maxY/2 - 85 + OffsetY) - m_vpoY)/m_XScale * NCDrawScale)/25.4);
		 }
		 else
		 {
        s1.Format("X: %6.3f  ",((MPointX - m_vpoX - (maxX/2 - OffsetX))/m_XScale * NCDrawScale));
	    s2.Format(" Y: %6.3f  ",-(MPointY*1.0 - (maxY/2 - 85 + OffsetY) - m_vpoY)/m_XScale * NCDrawScale);
		 }
		 }
		s3.Format(" S: %4.1f",m_XScale);
		str = s1 + s2 + s3;

	    pCmdUI->SetText(str);
}

void CAChartEditView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
		CMenu  PopUpMenu2;
//		m_ptDataEditPopUpMenu = point;
//		ScreenToClient(&m_ptDataEditPopUpMenu);
		PopUpMenu2.LoadMenu(IDR_MENU2);
		CMenu* pPopup = PopUpMenu2.GetSubMenu(0);
		pPopup->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON,
			point.x,point.y,this);	
}

void CAChartEditView::OnProperties()
{
	// TODO: The property sheet attached to your project
	// via this function is not hooked up to any message
	// handler.  In order to actually use the property sheet,
	// you will need to associate this function with a control
	// in your project such as a menu item or tool bar button.

	CChartPropertySheet propSheet;

    propSheet.m_Page1.m_XScale = m_XScale;
	propSheet.m_Page1.m_YScale = m_YScale;
	propSheet.m_Page1.m_SelectV = m_SelectV;
	propSheet.m_Page1.m_SelectA = m_SelectA;
	propSheet.m_Page1.m_SelectAH = m_SelectAH;
//	propSheet.m_Page1.m_SelectT1 = m_SelectT1;
//	propSheet.m_Page1.m_SelectT2 = m_SelectT2;
	propSheet.m_Page2.m_TitleText = m_TitleText;
	propSheet.m_Page2.m_XText = m_XText;
	propSheet.m_Page2.m_YText = m_YText;
	propSheet.m_Page3.m_Radio = m_RadioLineType;
	
	propSheet.m_Page1.VLineColor = VLineColor;
	propSheet.m_Page1.ALineColor =ALineColor;
	propSheet.m_Page1.AHLineColor = AHLineColor;
	propSheet.m_Page1.T1LineColor = T1LineColor;
	propSheet.m_Page1.T2LineColor = T2LineColor;
	
	propSheet.m_Page2.TitleTextColor = TitleTextColor;
	propSheet.m_Page2.XTextColor = XTextColor;
	propSheet.m_Page2.YTextColor = YTextColor;
	
	propSheet.m_Page3.XLineColor = XLineColor;
	propSheet.m_Page3.YLineColor = YLineColor;
	propSheet.m_Page3.GridLineColor = GridLineColor;

	if(propSheet.DoModal() == IDOK)
	{
        m_XScale = propSheet.m_Page1.m_XScale;
		m_YScale = propSheet.m_Page1.m_YScale;
		m_SelectV = propSheet.m_Page1.m_SelectV;
		m_SelectA = propSheet.m_Page1.m_SelectA;
		m_SelectAH = propSheet.m_Page1.m_SelectAH;
//		m_SelectT1 = propSheet.m_Page1.m_SelectT1;
//		m_SelectT2 = propSheet.m_Page1.m_SelectT2;
		m_TitleText = propSheet.m_Page2.m_TitleText;
		m_XText = propSheet.m_Page2.m_XText;
		m_YText = propSheet.m_Page2.m_YText;
		m_RadioLineType = propSheet.m_Page3.m_Radio;
		
		VLineColor = propSheet.m_Page1.VLineColor;
		ALineColor = propSheet.m_Page1.ALineColor;
		AHLineColor = propSheet.m_Page1.AHLineColor;
		T1LineColor = propSheet.m_Page1.T1LineColor;
		T2LineColor = propSheet.m_Page1.T2LineColor;
		
		TitleTextColor = propSheet.m_Page2.TitleTextColor;
		XTextColor = propSheet.m_Page2.XTextColor;
		YTextColor = propSheet.m_Page2.YTextColor;
		
		XLineColor = propSheet.m_Page3.XLineColor;
		YLineColor = propSheet.m_Page3.YLineColor;
		GridLineColor = propSheet.m_Page3.GridLineColor;
		
		ALinePen.DeleteObject();
        VLinePen.DeleteObject();
		AHLinePen.DeleteObject();
        T1LinePen.DeleteObject();
		T2LinePen.DeleteObject();
        XLinePen.DeleteObject();
        GridLinePen.DeleteObject();
		
		ALinePen.CreatePen(PS_INSIDEFRAME,0.1,ALineColor);
        VLinePen.CreatePen(PS_INSIDEFRAME,0.1,VLineColor);
		AHLinePen.CreatePen(PS_INSIDEFRAME,0.1,AHLineColor);
        T2LinePen.CreatePen(PS_INSIDEFRAME,0.1,T2LineColor);
        XLinePen.CreatePen(PS_INSIDEFRAME,0.1,XLineColor);
		if(m_RadioLineType == 0){GridLinePen.CreatePen(PS_INSIDEFRAME,0.1,GridLineColor);}
        if(m_RadioLineType == 2){GridLinePen.CreatePen(PS_DOT,0.1,GridLineColor);}
        if(m_RadioLineType == 1){GridLinePen.CreatePen(PS_INSIDEFRAME,0.1,GridLineColor);}

    	Invalidate(0);	
	}

	// This is where you would retrieve information from the property
	// sheet if propSheet.DoModal() returned IDOK.  We aren't doing
	// anything for simplicity.
}

void CAChartEditView::OnChartSetting() 
{
    OnProperties();	
}

BOOL CAChartEditView::DoPasteDib(COleDataObject *pDataObject)
{
    // update command user interface should keep us out of 
	//  here if not CF_DIB
    if (!pDataObject->IsDataAvailable(CF_DIB)) {
        TRACE("CF_DIB format is unavailable\n");
        return FALSE;
    }
    CADataEditDoc* pDoc = GetDocument();
    // Seems to be MOVEABLE memory, so we must use GlobalLock!
    //  (hDib != lpDib) GetGlobalData copies the memory, so we can
    //  hang onto it until we delete the CDib.
    HGLOBAL hDib = pDataObject->GetGlobalData(CF_DIB);
    ASSERT(hDib != NULL);
    LPVOID lpDib = ::GlobalLock(hDib);
    ASSERT(lpDib != NULL);
    pDoc->m_dib.AttachMemory(lpDib, TRUE, hDib);
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
    return TRUE;
}

COleDataSource* CAChartEditView::SaveDib()
{
	CDib& dib = GetDocument()->m_dib;
	if (dib.GetSizeImage() > 0)
	{
        COleDataSource* pSource = new COleDataSource();
        int nHeaderSize = dib.GetSizeHeader();
        int nImageSize = dib.GetSizeImage();
        HGLOBAL hHeader = ::GlobalAlloc(GMEM_SHARE,
            nHeaderSize + nImageSize);
        LPVOID pHeader = ::GlobalLock(hHeader);
        ASSERT(pHeader != NULL);
        LPVOID pImage = (LPBYTE) pHeader + nHeaderSize;
        memcpy(pHeader, dib.m_lpBMIH, nHeaderSize); 
        memcpy(pImage, dib.m_lpImage, nImageSize);
        // Receiver is supposed to free the global memory 
        ::GlobalUnlock(hHeader);
        pSource->CacheGlobalData(CF_DIB, hHeader);
        return pSource;
	}
    return NULL;
}

void CAChartEditView::OnChartEditCopy() 
{
	if (fBoxing)
	{
		CDC dcScreen;
		dcScreen.CreateDC("DISPLAY", NULL, NULL, NULL);
		
		int nWidth = abs(ptOld.x - ptAnchor.x)-2;
		int nHeight = abs(ptOld.y - ptAnchor.y)-2;
		
		CPoint ptUpperLeft(min(ptAnchor.x, ptOld.x), min(ptAnchor.y, ptOld.y));
		
		//		CClientDC dc(this);
		//		dc.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x, ptUpperLeft.y, SRCCOPY) ;
		
		CDC dcMem;
		CBitmap bmp;
		
		dcMem.CreateCompatibleDC(&dcScreen);
		bmp.CreateCompatibleBitmap(&dcScreen, nWidth, nHeight);
		CBitmap* pOldBitmap = dcMem.SelectObject(&bmp);
		
		dcMem.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x+1, ptUpperLeft.y+1, SRCCOPY) ;
		OpenClipboard();
		EmptyClipboard();
		SetClipboardData(CF_BITMAP, HBITMAP(bmp));
		CloseClipboard();
		
		fBoxing = FALSE;	
		//      ptOld = ptAnchor;		
		Invalidate(0);
	}			
}

void CAChartEditView::OnUpdateChartEditCopy(CCmdUI* pCmdUI) 
{
         pCmdUI->Enable(fBoxing);	
}

void CAChartEditView::OnChartEditPaste() 
{
		CDC dcScreen;
		dcScreen.CreateDC("DISPLAY", NULL, NULL, NULL);
		
		int nWidth = abs(ptOld.x - ptAnchor.x)-2;
		int nHeight = abs(ptOld.y - ptAnchor.y)-2;
		
		CPoint ptUpperLeft(min(ptAnchor.x, ptOld.x), min(ptAnchor.y, ptOld.y));
		CBitmap bmp;
		
		dcMem2.CreateCompatibleDC(&dcScreen);
		bmp.CreateCompatibleBitmap(&dcScreen, nWidth, nHeight);
		CBitmap* pOldBitmap = dcMem2.SelectObject(&bmp);
		
		dcMem2.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x+1, ptUpperLeft.y+1, SRCCOPY) ;
		Invalidate(0);	
}

void CAChartEditView::OnChartEditCut() 
{
	  	if (fBoxing)
		{
			CDC dcScreen;
			dcScreen.CreateDC("DISPLAY", NULL, NULL, NULL);
			
			int nWidth = abs(ptOld.x - ptAnchor.x)-2;
			int nHeight = abs(ptOld.y - ptAnchor.y)-2;
			
			CPoint ptUpperLeft(min(ptAnchor.x, ptOld.x), min(ptAnchor.y, ptOld.y));
			
			CDC dcMem;
			CBitmap bmp;
			
			dcMem.CreateCompatibleDC(&dcScreen);
			bmp.CreateCompatibleBitmap(&dcScreen, nWidth, nHeight);
			CBitmap* pOldBitmap = dcMem.SelectObject(&bmp);
			
			dcMem.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x+1, ptUpperLeft.y+1, SRCCOPY) ;
			OpenClipboard();
			EmptyClipboard();
			SetClipboardData(CF_BITMAP, HBITMAP(bmp));
			CloseClipboard();
			
			dcScreen.PatBlt(min(ptAnchor.x, ptOld.x),min(ptAnchor.y, ptOld.y),nWidth+2,nHeight+2,WHITENESS);
			
			fBoxing = FALSE;		
		}		    
}

void CAChartEditView::OnUpdateChartEditCut(CCmdUI* pCmdUI) 
{
             pCmdUI->Enable(fBoxing);	
}

void CAChartEditView::OnChartSaveas() 
{
	CDC dcScreen;
	dcScreen.CreateDC("DISPLAY", NULL, NULL, NULL);
	
	int nWidth,nHeight;
    CPoint ptUpperLeft;
	CDC dcMem;
	CBitmap bmp;

	if(fBoxing)
	{
	nWidth = abs(ptOld.x - ptAnchor.x)-2;
	nHeight = abs(ptOld.y - ptAnchor.y)-2;
	
	ptUpperLeft = (min(ptAnchor.x, ptOld.x), min(ptAnchor.y, ptOld.y));
	//		CClientDC dc(this);
	//		dc.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x, ptUpperLeft.y, SRCCOPY) ;
		
	dcMem.CreateCompatibleDC(&dcScreen);
	bmp.CreateCompatibleBitmap(&dcScreen, nWidth, nHeight);
	CBitmap* pOldBitmap = dcMem.SelectObject(&bmp);
	
	dcMem.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x+1, ptUpperLeft.y+1, SRCCOPY) ;
	}

	else
	{
    nWidth = maxX;
    nHeight = maxY;
    ptUpperLeft = (0,0);
	//		CClientDC dc(this);
	//		dc.BitBlt(0, 0, nWidth, nHeight, &dcScreen, ptUpperLeft.x, ptUpperLeft.y, SRCCOPY) ;
	
	dcMem.CreateCompatibleDC(&dcScreen);
	bmp.CreateCompatibleBitmap(&dcScreen, nWidth, nHeight);
	CBitmap* pOldBitmap = dcMem.SelectObject(&bmp);
	
	dcMem.BitBlt(0, 0, nWidth, nHeight, &memDC1, ptUpperLeft.x+1, ptUpperLeft.y+1, SRCCOPY) ;
	}

	OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, HBITMAP(bmp));
	CloseClipboard();
	
    CADataEditDoc* pDoc = GetDocument();
    COleDataObject dataObject;
    VERIFY(dataObject.AttachClipboard());
    DoPasteDib(&dataObject);
	//	CClientDC dc(this);
	//  pDoc->m_dib.UsePalette(&dc);
	//  pDoc->SetModifiedFlag();
	//  pDoc->UpdateAllViews(NULL);
	pDoc->MenuID = "BMPFile";
	
	CDib& dib = GetDocument()->m_dib;
	CFileDialog dlg(FALSE, "bmp", "*.bmp");
	if (dlg.DoModal() != IDOK) return;
	
	BeginWaitCursor();
	dib.CopyToMapFile(dlg.GetPathName());
	EndWaitCursor();	
}

void CAChartEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	Invalidate(0);
	CView::OnLButtonDblClk(nFlags, point);
}

void CAChartEditView::OnBUTTONZoomIn() 
{
	if(FileTypeCode == 'R')
	{
	m_XScale = m_XScale + 0.1;
	m_YScale = m_YScale + 0.1;
	}
	if((FileTypeCode == 'O')||(FileTypeCode == ':'))
	{
    m_XScale = m_XScale + m_XScale*0.1;
	m_YScale = m_YScale + m_YScale*0.1;
	}
	Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONZoomIn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((( m_XScale < 19.9)&&(!QuickDraw))||FileTypeCode == 'O');
}

void CAChartEditView::OnBUTTONZoomOut() 
{
	if(FileTypeCode == 'R')
	{
    m_XScale = m_XScale - 0.1;
	m_YScale = m_YScale - 0.1;
	}
	if((FileTypeCode == 'O')||(FileTypeCode == ':'))
	{
	m_XScale = m_XScale - m_XScale*0.1;
	m_YScale = m_YScale - m_YScale*0.1;
	}
	Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONZoomOut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((( m_XScale > 0.55)&&(!QuickDraw))||FileTypeCode == 'O');	
}

void CAChartEditView::OnBUTTONZoomAll() 
{
    if(FileTypeCode == 'R')
	{
	m_XScale = 1.6;
	m_YScale = 1.6;
	m_vpoX = 0;
	m_vpoY = 0;
	}
	if((FileTypeCode == 'O')||(FileTypeCode == ':'))
	{
	PrepareChartData = FALSE;
    m_vpoY = m_vpoX = 0;
	}
	Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONZoomAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((((m_XScale != 1.0)||(m_vpoX != 0)||(m_vpoY != 0))&&(!QuickDraw))||FileTypeCode == 'O');
}

void CAChartEditView::OnBUTTONChartToDown() 
{
		m_vpoY = m_vpoY + 50;
		Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONChartToDown(CCmdUI* pCmdUI) 
{
	    pCmdUI->Enable((m_vpoY<(718*m_XScale))&&(!QuickDraw));
}

void CAChartEditView::OnBUTTONChartToUp() 
{
		m_vpoY = m_vpoY - 50;
		Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONChartToUp(CCmdUI* pCmdUI) 
{
	    pCmdUI->Enable((m_vpoY>(-718*m_XScale))&&(!QuickDraw));
}

void CAChartEditView::OnBUTTONChartToL() 
{
		m_vpoX = m_vpoX - 50;
		Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONChartToL(CCmdUI* pCmdUI) 
{
	    pCmdUI->Enable((m_vpoX>(-974*m_XScale))&&(!QuickDraw));
}

void CAChartEditView::OnBUTTONChartToR() 
{
		m_vpoX = m_vpoX + 50;
		Invalidate(0);		
}

void CAChartEditView::OnUpdateBUTTONChartToR(CCmdUI* pCmdUI) 
{
	    pCmdUI->Enable((m_vpoX<(974*m_XScale))&&(!QuickDraw));
}

void CAChartEditView::OnBUTTONZoomInW() 
{
	fBoxing = FALSE;
	m_XScale = (maxX*1.0/(abs(abs(ptOld.x) - abs(ptAnchor.x))))*1.00;
	m_YScale = (maxY*1.0/(abs(abs(ptOld.y) - abs(ptAnchor.y))))*1.00;
	
	m_XScale = m_YScale = min(m_XScale,m_YScale);
	
	m_vpoX = -(ptAnchor.x-10);
	m_vpoY = (ptAnchor.y);
	Invalidate(0);	
}

void CAChartEditView::OnUpdateBUTTONZoomInW(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((fBoxing)&&(!QuickDraw));
}

void CAChartEditView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	        CADataEditDoc* pDoc = GetDocument();
		    CPtrArray *l = pDoc->GetLines();
		    ASSERT_VALID(pDoc);

	        EditLineNo = pDoc->EditLineNo;
			Inch = pDoc->Inch;
			m_TextEditCopyEnable = pDoc->m_TextEditCopyEnable;
//			if(QuickDraw==1)
//			QuickDraw = pDoc->QuickDraw;
//			OnBUTTONZoomAll();
			Invalidate(0);
}

void CAChartEditView::OnButton32820() 
{
     m_HandMoveAble ^=1;
}

void CAChartEditView::OnUpdateButton32820(CCmdUI* pCmdUI) 
{
     pCmdUI->SetCheck((m_HandMoveAble)&&(!QuickDraw));	
}

void CAChartEditView::DrawChartFunc()
{
            CADataEditDoc* pDoc = GetDocument();
		    CPtrArray *l = pDoc->GetLines();
		    ASSERT_VALID(pDoc);

          memDC1.SetBkMode(TRANSPARENT);

        if(PrepareChartData)
			{
              if(FileTypeCode == 'R')
			  {
                CString Vs,As,AHs,T1s,T2s;
                CString TimeH = "000";
	            CString TimeM = "00";
	            CString TimeS = "00";
	            double DrawV = 0.0f;
	            double DrawA = 0.0f;
	            double DrawAH = 0.0f;
	            double DrawTime = 0.0f;
				CString s;

		if(!(EditLineNo > LastEditLine))
		{
            LastEditLine = 1;
		}

			for (int k = LastEditLine; (k < EditLineNo)&&(k <(l->GetSize()-2)) ; k++)
			{						    
			LastEditLine = EditLineNo;
			CString *line = (CString *) l->GetAt(k+1);
            s = *line;
	        if(s.GetLength() < 56)
			{
				b_Break = TRUE;
				goto NextPoint1;
			}

			if (m_SelectV == TRUE)
			{
            Vs = s.Mid( 17, 5 );
	         DrawV = atof(Vs);
			}
	        
			if (m_SelectA == TRUE)
			{
	        As = s.Mid( 24, 5 );
	        DrawA = atof(As);
			}		
	        
			if (m_SelectAH == TRUE)
			{
            AHs = s.Mid( 31, 5 );
	        DrawAH = atof(AHs);
			}	   

		
		    TimeH=s.Mid(6 ,3 );
		    TimeM=s.Mid(10,2 );
		    TimeS=s.Mid(13,2 );

            DrawTime = atoi(TimeH)*60.0 + atoi(TimeM) + atof(TimeS)/60.0;
		
		    memDC1.SelectObject(&ALinePen);

           if((k==1)||(b_Break))
		   {
            memDC1.MoveTo(m_vpoX + 130 + (DrawTime-MinTime)*(450.0*DispScaleX*m_XScale)/(Timeapartm*TimeapartmV),m_vpoY+(504*DispScaleY)-(DrawA)*(250/(AapartmA*Aapartm))*DispScaleY*m_YScale);
		    b_Break = false;
		   }
		    memDC1.LineTo(m_vpoX + 130 + (DrawTime-MinTime)*(450.0*DispScaleX*m_XScale)/(Timeapartm*TimeapartmV),m_vpoY+(504*DispScaleY)-(DrawA)*(250/(AapartmA*Aapartm))*DispScaleY*m_YScale);
            NextPoint1:;
			}         
		}

         if((FileTypeCode == 'O')||(FileTypeCode == ':'))          //NC File Draw Chart Func
		{
		    AfxGetApp()->BeginWaitCursor();

		    if(LastEditLine >= EditLineNo)
			{
                LastEditLine = 1;
//				memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);
			}

			for (int k = LastEditLine; k < EditLineNo ; k++)
			{
				LastEditLine = EditLineNo;
				CString *line = (CString *) l->GetAt(k+1);
				Gs1 = *line;
                Gs2.Empty();

                if(Gs1.Find("G10P16R")!=-1)
				{
                for( Ge = Gs1.Find('R')+1; Ge < Gs1.Find('\r'); Ge++)
				  {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				  }
					GP16 = atof(Gs2);
					s_R.Format("%4.3f",GP16);
					Gs2.Empty();
				}

				if(Gs1.Find("G4")!=-1)
				{
                G4 = Gs1.GetAt(Gs1.Find("G4")+2);
				}

				if(Gs1.Find("G5")!=-1)
				{
                G5 = Gs1.GetAt(Gs1.Find("G5")+2);
				}

				if(Gs1.Find('T')!=-1)
				{
                for( Ge = Gs1.Find('T')+1; Ge < Gs1.Find('\r'); Ge++)
				  {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				  }
					GT = atof(Gs2);
					s_GT.Format("%5.3f",GT);
					Gs2.Empty();
				}

                if(Gs1.Find("1D")!=-1)
				{
                oldPen = memDC1.SelectObject(&VLinePen);
				}
				if(Gs1.Find("2D")!=-1)
				{
                oldPen = memDC1.SelectObject(&ALinePen);
				}
				if(Gs1.Find("3D")!=-1)
				{
                oldPen = memDC1.SelectObject(&AHLinePen);
				}
				if(Gs1.Find("4D")!=-1)
				{
                oldPen = memDC1.SelectObject(&T2LinePen);
				}

				if((Gs1.Find("G92")!=-1)||(Gs1.Find("G90G54G0")!=-1))
				{
				  for( Ge = Gs1.Find('X')+1; Ge < Gs1.Find('\r'); Ge++)
				  {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				  }
					startx = atof(Gs2);
					Gs2.Empty();
				 for( Ge = Gs1.Find('Y')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					starty = atof(Gs2);	
					Gs2.Empty();
					memDC1.MoveTo(m_vpoX+startx * m_XScale * NCDrawScale + (maxX/2 - OffsetX),-starty * m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY);
					if(Inch)
					{
					s_startx.Format("%7.4f",startx/25.4);
				    s_starty.Format("%7.4f",starty/25.4);
					}
					else
					{
					s_startx.Format("%7.3f",startx);
				    s_starty.Format("%7.3f",starty);
					}
					s_centx.Empty();
	                s_centy.Empty();
	                s_Circler.Empty();
				}

				if(Gs1.Find("G00")!=-1)
				{
				  for( Ge = Gs1.Find('X')+1; Ge < Gs1.Find('\r'); Ge++)
				  {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				  }
					startx = atof(Gs2);
					Gs2.Empty();
				 for( Ge = Gs1.Find('Y')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					starty = atof(Gs2);	
					Gs2.Empty();
					oldPen = memDC1.SelectObject(&GridLinePen);
					memDC1.LineTo(m_vpoX+startx * m_XScale * NCDrawScale + (maxX/2 - OffsetX),-starty * m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY);
				    memDC1.SelectObject(oldPen);
					if(Inch)
					{
					s_startx.Format("%7.4f",startx/25.4);
				    s_starty.Format("%7.4f",starty/25.4);
					}
					else
					{
					s_startx.Format("%7.3f",startx);
				    s_starty.Format("%7.3f",starty);
					}
					s_centx.Empty();
	                s_centy.Empty();
	                s_Circler.Empty();
				}
				
				if((Gs1.Find("G01"))>=0)
				{
				 for( Ge = Gs1.Find('X')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
				 	Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					Gx = (atof(Gs2));
					Gs2.Empty();
				 for( Ge = Gs1.Find('Y')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					Gy = (atof(Gs2));
					Gs2.Empty();

					Angle = 180.0 + atan2((starty-Gy),(startx-Gx))*(180.0/3.14159);
					if(Angle >= 360.0)
					Angle = Angle - 360.0;

					startx = Gx;
					starty = Gy;
					
					memDC1.LineTo(m_vpoX+Gx * m_XScale * NCDrawScale + (maxX/2 - OffsetX),-Gy * m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY);
					if(Inch)
					{
					s_startx.Format("%7.4f",startx/25.4);
				    s_starty.Format("%7.4f",starty/25.4);
					}
					else
					{
					s_startx.Format("%7.3f",startx);
				    s_starty.Format("%7.3f",starty);
					}
				    s_centx.Empty();
	                s_centy.Empty();
	                s_Circler.Empty();
                    s_Diameter.Empty();
//					b_MoveAble = true;
				}
				 			
				 if((Gs1.Find("G03")>=0)||(Gs1.Find("G02")>=0))
				 {
				   if(Gs1.Find('X')!=-1)
				   {
					 Gs2.Empty();
					 for( Ge = Gs1.Find('X') + 1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 endx = atof(Gs2);
					 Gs2.Empty();
				   }
					 else endx = 0.0;
					
				   if(Gs1.Find('Y')!=-1)
				   {
					 Gs2.Empty();
					 for( Ge = Gs1.Find('Y') + 1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 endy = atof(Gs2);
					 Gs2.Empty();
				   }
					 else endy = 0.0;
					
					if(Gs1.Find('I')!=-1)
					{
					 Gs2.Empty();
					 for( Ge = Gs1.Find('I')+1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 Gi = (atof(Gs2))/1000.0;
					 Gs2.Empty();
					}
					 else Gi = 0.0;
					
					if(Gs1.Find('J')!=-1)
					{
					 Gs2.Empty();
					 for( Ge = Gs1.Find('J')+1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 Gj = (atof(Gs2))/1000.0;
					 Gs2.Empty();
					}
					else Gj = 0.0;
					
					
					centx = startx + Gi ;
					centy = starty + Gj ;
					Circler = sqrt((Gi*Gi) + (Gj*Gj));
					upx = (centx - Circler);
					upy = (centy + Circler);
					lowx = (centx + Circler);
					lowy = (centy - Circler);
					
					if((Gi==0.0)||(Gj==0.0))
					{
					 dstartx = startx;
					 dstarty = starty;
					 dendx = endx;
					 dendy = endy;
					}
					else
					{
					 if((Gi<0.0)&&(Gj<0.0)&&(Gi==Gj))                //first zero
					 {
					  dstartx = lowx;
					  dstarty = upy;
					 }
						
					 if((Gi<0.0)&&(Gj<0.0)&&(Gi<Gj))                 //  <45
					 {
						 dstartx = lowx;
						 dstarty = centy + Gj*Circler/Gi;
					 }
					 
					 if((Gi<0.0)&&(Gj<0.0)&&(Gi>Gj))                 //  >45
					 {
						 dstartx = centx + Gi*Circler/Gj;
						 dstarty = upy;
					 }
					 
					 if((Gi>0.0)&&(Gj<0.0)&&(Gi==-Gj))               //secend zero  
					 {
						 dstartx = upx;
						 dstarty = upy;
					 }
					 
					 if((Gi>0.0)&&(Gj<0.0)&&(-Gi>Gj))
					 {
						 dstartx = upx;
						 dstarty = centy - Gj*Circler/Gi;
					 }
					 
					 if((Gi>0.0)&&(Gj<0.0)&&(-Gi<Gj))
					 {
						 dstartx = centx + Gi*Circler/Gj;
						 dstarty = upy;
					 }
					 
					 if((Gi>0.0)&&(Gj>0.0)&&(Gi==Gj))             //3th zero
					 {
						 dstartx = upx;
						 dstarty = lowy;
					 }
					 
					 if((Gi>0.0)&&(Gj>0.0)&&(Gi>Gj))
					 {
						 dstartx = upx;
						 dstarty = centy - Gj*Circler/Gi;
					 }
					 
					 if((Gi>0.0)&&(Gj>0.0)&&(Gi<Gj))
					 {
						 dstartx = centx - Gi*Circler/Gj;
						 dstarty = lowy;
					 }
					 
					 if((Gi<0.0)&&(Gj>0.0)&&(Gi==-Gj))               //4th zero  
					 {
						 dstartx = lowx;
						 dstarty = lowy;
					 }
					 
					 if((Gi<0.0)&&(Gj>0.0)&&(-Gi>Gj))
					 {
						 dstartx = lowx;
						 dstarty = centy + Gj*Circler/Gi;
					 }
					 
					 if((Gi<0.0)&&(Gj>0.0)&&(-Gi<Gj))
					 {
						 dstartx = centx - Gi*Circler/Gj;
						 dstarty = lowy;
					 }
					 
					 if((endx-centx==0.0)||(endy-centy==0.0))
					 {
						 dendx = endx;
						 dendy = endy;
					 }
					 else
					 {
						 if((endx-centx>0.0)&&(endy-centy>0.0)&&((endx-centx)==(endy-centy)))                //first zero
						 {
							 dendx = lowx;
							 dendy = upy;
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy>0.0)&&((endx-centx)>(endy-centy)))              //  <45
						 {
							 dendx = lowx;
							 dendy = centy + (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy>0.0)&&((endx-centx)<(endy-centy)))              //  >45
						 {
							 dendx = centx + (endx-centx)*Circler/(endy-centy);
							 dendy = upy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy>0.0)&&((endx-centx)==-(endy-centy)))               //secend zero  
						 {
							 dendx = upx;
							 dendy = upy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy>0.0)&&(-(endx-centx)>(endy-centy)))
						 {
							 dendx = upx;
							 dendy = centy - (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy>0.0)&&(-(endx-centx)<(endy-centy)))
						 {
							 dendx = centx + (endx-centx)*Circler/(endy-centy);
							 dendy = upy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy<0.0)&&((endx-centx)==(endy-centy)))             //3th zero
						 {
							 dendx = upx;
							 dendy = lowy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy<0.0)&&((endx-centx)<(endy-centy)))
						 {
							 dendx = upx;
							 dendy = centy - (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy<0.0)&&((endx-centx)>(endy-centy)))
						 {
							 dendx = centx - (endx-centx)*Circler/(endy-centy);
							 dendy = lowy;
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy<0.0)&&((endx-centx)==-(endy-centy)))               //4th zero  
						 {
							 dendx = lowx;
							 dendy = lowy;
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy<0.0)&&((endx-centx)>-(endy-centy)))
						 {
							 dendx = lowx;
							 dendy = centy + (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy<0.0)&&((endx-centx)<-(endy-centy)))
						 {
							 dendx = centx - (endx-centx)*Circler/(endy-centy);
							 dendy = lowy;
						 }
					 } 
				  }
				  
				  if(Gs1.Find("G02")!=-1)
				  {
					  Gg = dendx;
					  Gh = dendy;
					  dendx = dstartx;
					  dendy = dstarty;
					  dstartx = Gg;
					  dstarty = Gh;
				  }

				  memDC1.Arc(m_vpoX+upx * m_XScale * NCDrawScale + (maxX/2 - OffsetX),-upy * m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY,m_vpoX+lowx*m_XScale * NCDrawScale + (maxX/2 - OffsetX),
					         -lowy*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY,m_vpoX+dstartx*m_XScale * NCDrawScale + (maxX/2 - OffsetX),
					         -dstarty*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY,m_vpoX+dendx*m_XScale * NCDrawScale + (maxX/2 - OffsetX),-dendy*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY);
				  memDC1.MoveTo(m_vpoX+endx*m_XScale * NCDrawScale + (maxX/2 - OffsetX),-endy*m_XScale * NCDrawScale + (maxY/2 - 85 + OffsetY)+m_vpoY);
				  
                 if(Inch)
				 {
				  s_centx.Format("%7.4f",centx/25.4);
				  s_centy.Format("%7.4f",centy/25.4);
				 }
				 else
				 { 
				  s_centx.Format("%7.3f",centx);
				  s_centy.Format("%7.3f",centy);
				 }

				  startx = endx;
				  starty = endy;
				 if(Inch)
				 {
				  s_startx.Format("%7.4f",startx/25.4);
				  s_starty.Format("%7.4f",starty/25.4);
				 }
			     else
				 {
				  s_startx.Format("%7.3f",startx);
				  s_starty.Format("%7.3f",starty);
				 }
                 if(Inch)
				 {
				  s_Circler.Format("%7.4f",Circler/25.4);
				  s_Diameter.Format("%7.4f",Circler/12.7);
				 }
				 else
				 {
				  s_Circler.Format("%6.3f",Circler);
                  s_Diameter.Format("%6.3f",Circler*2.0);
				 }
//				  b_MoveAble = true;
//				  memDC1.SelectObject(oldPen);
				}
				  }
				  memDC1.SetTextColor(XTextColor);
				  memDC1.PatBlt(0,0,630,96,WHITENESS);
			      memDC1.TextOut(50,2,"End Point                 Cent Point                   Radius/Diameter                 Angular",94);
		          memDC1.TextOut(50,55,"Offset",6);
				  memDC1.TextOut(50,73,"Taper",5);

				  memDC1.SetTextColor(TitleTextColor);
				  CString s3;

				  memDC1.TextOut(90,20,"X: "+s_startx);
				  memDC1.TextOut(90,37,"Y: "+s_starty);
				  
				  memDC1.TextOut(230,20,"X: "+s_centx);
				  memDC1.TextOut(230,37,"Y: "+s_centy);

				  memDC1.TextOut(380,20,"R: "+s_Circler);
				  memDC1.TextOut(380,37,"D:"+s_Diameter);

				  s_Angle.Format("%6.3f",Angle);
				  memDC1.TextOut(520,20,"A: "+s_Angle);

				  memDC1.TextOut(230,55,"Dir. G4"+ G4,8);
				  memDC1.TextOut(120,55,"R:"+s_R);				  
				  memDC1.TextOut(230,73,"Dir. G5"+ G5,8);
				  if (G5 == '0')
				  {
				  GT = 0.0;
				  s_GT.Empty();
				  }
				  memDC1.TextOut(120,73,"T:"+s_GT);
				  
//                s3.Format("%4.1f",NCDrawScale);
//				  memDC0.TextOut(750,540,"              ",14);
//				  memDC0.TextOut(750,540,"Scale:"+s3);
		AfxGetApp()->EndWaitCursor();
		}

	}
}

void CAChartEditView::OnButtonquickdraw() 
{
		QuickDraw ^=1;
		if(QuickDraw==TRUE)
		SetTimer(1,100,NULL);
        else
		KillTimer(1);
}

void CAChartEditView::OnUpdateButtonquickdraw(CCmdUI* pCmdUI) 
{
       	pCmdUI->SetCheck(QuickDraw);
}

void CAChartEditView::OnTimer(UINT nIDEvent) 
{
	CADataEditDoc *pDoc = GetDocument();
	if(EditLineNo < n-2)
	{
		if(QuickDraw==FALSE)
		KillTimer(1);

		pDoc->UpdateAllViews(NULL);
	}
    else
	{
		KillTimer(1);
		QuickDraw = false;
	}
	CView::OnTimer(nIDEvent);
}

BOOL CAChartEditView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
//       HCURSOR hcur = AfxGetApp () ->LoadCursor (IDC_CURSOR1);
//  	 SetCursor (hcur);	
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CAChartEditView::OnPrepareChartData()
{
        CADataEditDoc *pDoc = GetDocument();
        CPtrArray *l = pDoc->GetLines();	 

	    ASSERT_VALID(pDoc);

	 	CString *line = (CString *) l->GetAt(1);
	    CString FileTypeString = *line;

	    n = l->GetSize();

	    FileTypeCode = FileTypeString.GetAt(0);

  if((PrepareChartData==FALSE)/*||(LastEditLine > EditLineNo)*/)
  {
   if((FileTypeCode == 'R')&&(n>3))
   {
	 CString Totals;
     CString Vs,As,AHs,T1s,T2s;
     CString TimeHmins = "000";
     CString TimeHmaxs = "000";
	 CString TimeMmins = "00";
	 CString TimeMmaxs = "00";
	 CString TimeSmins = "00";
	 CString TimeSmaxs = "00";
	 double DrawMaxV = 0.0f;
	 double DrawMaxA = 0.0f;
	 double DrawMaxAH = 0.0f;
	 int VIndex,AIndex,AHIndex,T1Index,T2Index;
     double DrawMaxVs,DrawMaxAs,DrawMaxAHs;
	 int o,p;
	 
	 n = l->GetSize();

	 for (int i = 2; i < n-3; i++)
	 {
	    CString *line = (CString *) l->GetAt(i);
	    Totals = *line;
		if(Totals.GetLength() < 56)
		{
		DrawV[i] = 0.0;
		DrawA[i] = 0.0;
		DrawAH[i] = 0.0;
		goto end;
		}
	   if (m_SelectV == TRUE)
	   {
       Vs = Totals.Mid( 17, 5 );
	   DrawV[i] = atof(Vs);
	     if (DrawMaxV < DrawV[i])
		     DrawMaxV = DrawV[i];
	   }
	   if (m_SelectA == TRUE)
	   {
	   As = Totals.Mid( 24, 5 );
	   DrawA[i] = atof(As);
	     if (DrawMaxA < DrawA[i])
		     DrawMaxA = DrawA[i];
	   }		
	   if (m_SelectAH == TRUE)
	   {
       AHs = Totals.Mid( 31, 5 );
	   DrawAH[i] = atof(AHs);
	     if (DrawMaxAH < DrawAH[i])
		     DrawMaxAH = DrawAH[i];
	   }	   
end:
	   ;
	 }
       DrawMaxVs = DrawMaxV;
       VIndex = log10(DrawMaxV);
	   DrawMaxAs = DrawMaxA;
       AIndex = log10(DrawMaxA);
	   DrawMaxAHs = DrawMaxAH;
       AHIndex = log10(DrawMaxAH);

	   DrawMaxVs = DrawMaxVs/pow(10,VIndex);
	   DrawMaxAs = DrawMaxAs/pow(10,AIndex);
	   DrawMaxAHs = DrawMaxAHs/pow(10,AHIndex);

       Vapartm = DrawMaxVs *2;
       Vapartm += 1;
       VapartmV = 0.5;
	 for ( p = 0; p < VIndex; p++)
	   {
	   VapartmV = VapartmV*10.0;
	   }

       Aapartm = DrawMaxAs *2;
       Aapartm += 1;
       AapartmA = 0.5;
	 for ( p = 0; p < AIndex; p++)
	   {
	   AapartmA = AapartmA*10.0;
	   }

	   AHapartm = DrawMaxAHs *2;
       AHapartm += 1;
       AHapartmAH = 0.5;
	 for ( p = 0; p < AHIndex; p++)
	   {
	   AHapartmAH = AHapartmAH*10.0;
	   }
	 
	    CString *line = (CString *) l->GetAt(2);
	    Totals = *line;		

		TimeHmins=Totals.Mid(6 ,3 );

		TimeMmins=Totals.Mid(10,2 );

		TimeSmins=Totals.Mid(13,2 );
	    
		line= (CString *) l->GetAt(n-2);
	    Totals = *line;
		
		TimeHmaxs=Totals.Mid(6 ,3 );

		TimeMmaxs=Totals.Mid(10,2 );

		TimeSmaxs=Totals.Mid(13,2 );

	    double DrawTime,DrawTimes;
	    MinTime = atoi(TimeHmins)*60.0 + atoi(TimeMmins) + atof(TimeSmins)/60.0;
        MaxTime = atoi(TimeHmaxs)*60.0 + atoi(TimeMmaxs) + atof(TimeSmaxs)/60.0;

        DrawTime = MaxTime - MinTime;
        
	    int TimeIndex;
	    DrawTimes = DrawTime;
        TimeIndex = log10(DrawTime);

       for (int u = 0; u < TimeIndex; u++)
	   {
	   DrawTimes = DrawTimes/10;
	   }
       Timeapartm = DrawTimes *2;
       Timeapartm = Timeapartm + 1;
       TimeapartmV = 0.5;
	   for (int v = 0; v < TimeIndex; v++)
	   {
	   TimeapartmV = TimeapartmV*10;
	   }
      }

	 if(((FileTypeCode == 'O')||(FileTypeCode == ':'))&&(n>9))             //NC File PrepareChartData
	 {                          
		CString s,s2;
		int e,
		double x,y;

			for (int k = 2; k < n-2; k++)
			{						    
			CString *line = (CString *) l->GetAt(k+1);
            s = *line;
            
        	if((s.Find('X'))>=0)
				{
				s2.Empty();
				for( e = s.Find('X')+1; e < s.Find('\r'); e++)
				{
					s2 = s2 + s.GetAt(e);
				}
                x = (atof(s2));
				s2.Empty();
				}
				else x = 0.0;

				if((s.Find('Y'))>=0)
				{
				s2.Empty();
				for( e = s.Find('Y')+1; e < s.Find('\r'); e++)
				{
					s2 = s2 + s.GetAt(e);
				}
				y = (atof(s2));
				s2.Empty();
				}
				else y = 0.0;
				
					if (maxXvalue < x)
						maxXvalue = x;
					if (minXvalue > x)
						minXvalue = x;
					if (maxYvalue < y)
						maxYvalue = y;
					if (minYvalue > y)
						minYvalue = y;
       					s.Empty();
			}

			m_XScale = (min(maxX/(maxXvalue - minXvalue) , maxY/(maxYvalue - minYvalue)))*0.55;

		    OffsetX = m_XScale*(maxXvalue + minXvalue)/2.0 + 200;
			OffsetY = m_XScale*(maxYvalue + minYvalue)/2.0 + 80;

	    int o,X1stBitValue,Y1stBitValue;
	    float XCoverValue,YCoverValue;

        XCoverValue = maxXvalue - minXvalue;
        YCoverValue = maxYvalue - minYvalue;

        XIndex = int(log10(abs(XCoverValue)));
        YIndex = int(log10(abs(YCoverValue)));

        X1stBitValue = int(XCoverValue);
	   for ( o = 0; o < XIndex; o++)
	   {
	    X1stBitValue = X1stBitValue/10;
	   }
 
        Y1stBitValue = int(YCoverValue);
	   for ( o = 0; o < YIndex; o++)
	   {
	    Y1stBitValue = Y1stBitValue/10;//Pow(60,RIDIO)
	   }

        XMarkQty = X1stBitValue * 2 + 1;
		XMarkValue = 0.5;
       for ( o = 0; o < XIndex; o++)
	   {
        XMarkValue = XMarkValue * 10.0;
	   }

	    YMarkQty = Y1stBitValue * 2 + 1;
		YMarkValue = 0.5;
       for ( o = 0; o < YIndex; o++)
	   {
        YMarkValue = YMarkValue * 10.0;
	   }

	   if(XMarkQty > 10)
		{
       XMarkQty = XMarkQty/2 + 1;
       XMarkValue = XMarkValue*2.0;
		}
	   if(YMarkQty > 10)
		{
       YMarkQty = YMarkQty/2 + 1;
       YMarkValue = YMarkValue*2.0;
		}
	 }
	   PrepareChartData = TRUE; 
     }
}
