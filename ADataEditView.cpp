// ADataEditView.cpp : implementation of the CADataEditView class
//

#include "stdafx.h"
#include "ADataEdit.h"

#include "ADataEditDoc.h"
#include "ADataEditView.h"

//#include "math.h"
//#include "cdib.h"

#include "GoToDLG.h"
#include "TextColorDlg.h"
#include "TransmissiomConfigDlg.h"
#include "CommunicationWorking.h"
#include "InsertFileDialog.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADataEditView

IMPLEMENT_DYNCREATE(CADataEditView, CView)

BEGIN_MESSAGE_MAP(CADataEditView, CView)
ON_MESSAGE(WM_GOODBYE, OnGoodbye)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_CARET,OnUpdateCaretPos)
ON_CBN_SELCHANGE(IDC_COMBOX, OnSelchangeCombo1)
ON_CBN_EDITCHANGE(IDC_COMBOX, OnEditchangeCombo1)

	//{{AFX_MSG_MAP(CADataEditView)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_LINENO, OnViewLineno)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINENO, OnUpdateViewLineno)
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_INSERTAFILE, OnEditInsertafile)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERTAFILE, OnUpdateEditInsertafile)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_INSERTALINE, OnEditInsertaline)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERTALINE, OnUpdateEditInsertaline)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_SETFONT, OnEditSetfont)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SETFONT, OnUpdateEditSetfont)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CONTEXTMENU()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_COMMAND(ID_EDIT_GOTO, OnEditGoto)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_SETCOLOR, OnEditSetcolor)
	ON_COMMAND(ID_TRANSMISSIOM_CONFIGDEVICE, OnTransmissiomConfigdevice)
	ON_UPDATE_COMMAND_UI(ID_TRANSMISSIOM_CONFIGDEVICE, OnUpdateTransmissiomConfigdevice)
	ON_COMMAND(ID_TRANSMISSIOM_SENDOUT, OnTransmissiomSendout)
	ON_COMMAND(ID_TRANSMISSIOM_STOP, OnTransmissiomStop)
	ON_UPDATE_COMMAND_UI(ID_TRANSMISSIOM_STOP, OnUpdateTransmissiomStop)
	ON_UPDATE_COMMAND_UI(ID_TRANSMISSIOM_SENDOUT, OnUpdateTransmissiomSendout)
	ON_COMMAND(ID_TRANSMISSIOM_RECEIVEIN, OnTransmissiomReceivein)
	ON_UPDATE_COMMAND_UI(ID_TRANSMISSIOM_RECEIVEIN, OnUpdateTransmissiomReceivein)
	ON_COMMAND(ID_VIEW_ATTACHCHART, OnViewAttachchart)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ATTACHCHART, OnUpdateViewAttachchart)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_BUTTONRedrawView, OnBUTTONRedrawView)
	ON_UPDATE_COMMAND_UI(ID_BUTTONRedrawView, OnUpdateBUTTONRedrawView)
	ON_COMMAND(ID_VIEW_INCH, OnViewInch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INCH, OnUpdateViewInch)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_GOTOFILEBOTTOM, OnEditGotofilebottom)
	ON_COMMAND(ID_EDIT_GOTOFILETOP, OnEditGotofiletop)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GOTOFILETOP, OnUpdateEditGotofiletop)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GOTOFILEBOTTOM, OnUpdateEditGotofilebottom)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GOTO, OnUpdateEditGoto)
	ON_COMMAND(ID_EDIT_DELETEALINE, OnEditDeletealine)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETEALINE, OnUpdateEditDeletealine)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADataEditView construction/destruction

CADataEditView::CADataEditView()
{
	// TODO: add construction code here
	AfxOleInit();

	m_undocount = 1;
	Undocmdcode.Add(0);
	UndoTotalPasteLine.Add(0);
	UndoEditLineNo.Add(1);
	UndoEditString.Add("!!!!!!!!!!!!!!!!");
    UndoEndEditString.Add("!!!!!!!!!!!!!!!!!");

	m_pDlg = new CCommunicationWorking(this);

	MenuID = "DataFile";
	currentLine = 0;
	n = 0;
    memDC0OffSet = 0;
	margin = 0;
	CursorY = 0;
    CursorX = 0;
	EditLineNo = 0;
	LastEditLine = 2;
//	TotalPasteLine = 0;

//	DispScaleX = ((maxX*100)/640)/100.0;
//	DispScaleY = ((maxY*100)/480)/100.0;

//	Timeapartm = Vapartm = Aapartm = AHapartm = 1;
//	TimeapartmV = VapartmV = AapartmA = AHapartmAH = 1;
//	m_vpoX = 0;
//  m_vpoY = 0;
//	m_XScale = 1.0;
//	m_YScale = 1.0;

	m_SelectLine = m_SelectLine2 = 0;
	m_TextEditCopyEnable = FALSE;
    m_TextEditPasteEnable = FALSE;
	i_ProgressStep = 1;
	b_Break = FALSE;

	EditString.Empty();
	EndEditString.Empty();
	
	PreparememDC = FALSE;
//	B_PrepareChartData = FALSE;
//	DrawXYLine = FALSE;
//	FileTypeCode.Empty();
//	b_LineNo = TRUE;

    DataCapture = FALSE;
	b_FindCapture = FALSE;
	
	m_Communication = 0;

	maxX=GetSystemMetrics(SM_CXSCREEN);
	maxY=GetSystemMetrics(SM_CYSCREEN);

	Inch = FALSE;
//	GP16 = 0.0;
//	GT = 0.0;
//	Gx = 0.0;
//	Gy = 0.0;
//	startx = 0.0;
//	starty = 0.0;
//	centx = 999.9;
//	centy = 999.9;
//	Circler = 999.9;

//	maxXvalue = -10000.0;
//	minXvalue = 10000.0;
//	maxYvalue = -10000.0;
//	minYvalue = 10000.0;

//	G4 = '*';
//	G5 = '*';
//	s_startx.Empty();
//	s_starty.Empty();
//	s_centx.Empty();
//	s_centy.Empty();
//	s_Circler.Empty();
//	s_Diameter.Empty();
//	s_R.Empty();
//	s_GT.Empty();
////	LastEditLine = 2;
//	NCDrawScale = 1.0;
//	NCDrawRectCapture = FALSE;
//	NCFileName.Empty();
	
	map1.SetAt("EVEN","e");
	map1.SetAt("ODD","o");
	map1.SetAt("NONE","n");
	map1.SetAt("COM1","1");
	map1.SetAt("COM2","2");
	map1.SetAt("COM3","3");
	map1.SetAt("COM4","4");
	map1.SetAt("ON","1");
    map1.SetAt("OFF","0");
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
	ar >> b_AttachChart;
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
	XTextColor = pApp->GetProfileInt("Settings","XTextColor",32768);
	YTextColor = pApp->GetProfileInt("Settings","YTextColor",32768);
	XLineColor = pApp->GetProfileInt("Settings","XLineColor",32768);
	YLineColor = pApp->GetProfileInt("Settings","YLineColor",32768);
	GridLineColor = pApp->GetProfileInt("Settings","GridLineColor",33023);

	BackGroundColor = pApp->GetProfileInt("Settings","BackGroundColor",16777215);
	TextColor = pApp->GetProfileInt("Settings","TextColor",0);
	LineNoColor = pApp->GetProfileInt("Settings","LineNoColor",255);
	m_GoToLineNo = pApp->GetProfileInt("Settings","m_GoToLineNo",1);

	m_BandRate = pApp->GetProfileString("Settings","m_BandRate","9600");
	m_Parity = pApp->GetProfileString("Settings","m_Parity","EVEN");
	m_WordLength = pApp->GetProfileString("Settings","m_WordLength","7");
	m_StopBits = pApp->GetProfileString("Settings","m_StopBits","1");
	m_CodeType = pApp->GetProfileString("Settings","m_CodeType","ASCII");
	m_ComPortNo = pApp->GetProfileString("Settings","m_ComPortNo","COM2");
	m_AutoXonXoff = pApp->GetProfileString("Settings","m_AutoXonXoff","ON");
	m_InputControlMode = pApp->GetProfileString("Settings","m_InputControlMode","MASTER");
	m_OutputControlMode = pApp->GetProfileString("Settings","m_OutputControlMode","SLAVE");
	m_InputStartString = pApp->GetProfileString("Settings","m_InputStartString","%");
	m_InputEndString = pApp->GetProfileString("Settings","m_InputEndString","%");
	m_OutputStartString = pApp->GetProfileString("Settings","m_OutputStartString","%");
	m_OutputEndString = pApp->GetProfileString("Settings","m_OutputEndString","%");
	m_InputTimeOut = pApp->GetProfileInt("Settings","m_InputTimeOut",60);
	m_OutputSendDelay = pApp->GetProfileInt("Settings","m_OutputSendDelay",60);
	b_AttachChart = pApp->GetProfileInt("Settings","b_AttachChart",1);

	b_AttachChart = false;         //Becouse attach 1 memDC is too slowly

//	T2LineColor = (RGB(255,0,255));
	
//	ALinePen.CreatePen(PS_INSIDEFRAME,0.1,ALineColor);
//	VLinePen.CreatePen(PS_INSIDEFRAME,0.1,VLineColor);
//	AHLinePen.CreatePen(PS_INSIDEFRAME,0.1,AHLineColor);
//	T1LinePen.CreatePen(PS_INSIDEFRAME,0.1,T1LineColor);
//	T2LinePen.CreatePen(PS_INSIDEFRAME,0.1,T2LineColor);
//	XLinePen.CreatePen(PS_INSIDEFRAME,0.1,XLineColor);
//	if(m_RadioLineType == 0){GridLinePen.CreatePen(PS_INSIDEFRAME,0.1,GridLineColor);}
//	if(m_RadioLineType == 2){GridLinePen.CreatePen(PS_DOT,0.1,GridLineColor);}
//	if(m_RadioLineType == 1){GridLinePen.CreatePen(PS_INSIDEFRAME,0.1,GridLineColor);}
}

void CADataEditView::OnDestroy() 
{
	CView::OnDestroy();	
	// TODO: Add your message handler code here
/*
	CFile file("c:\\cddyV3.0\\ADataEdit.ind",CFile::modeWrite);
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
	ar << b_AttachChart;
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

}

CADataEditView::~CADataEditView()
{
	delete m_pDlg;
}

BOOL CADataEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CADataEditView drawing

void CADataEditView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_Communication == 0)
	{
		if (pInfo != NULL)
		{
			if (currentLine < GetDocument()->GetLines()->GetSize())
			{
				TRACE1("currentLine = %d, continuing printing\n", currentLine);
				pInfo->m_bContinuePrinting = TRUE;
			}
			else
			{
				TRACE1("currentLine = %d, terminating printing\n", currentLine);
				pInfo->m_bContinuePrinting = FALSE;
			}
		}		
	}		
	CView::OnPrepareDC(pDC, pInfo);
}

void CADataEditView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();

    m_TextEditCopyEnable = pDoc->m_TextEditCopyEnable;
	MenuID = "DataFile";

	Undocmdcode.RemoveAll();
	UndoTotalPasteLine.RemoveAll();
	UndoEditLineNo.RemoveAll();
	UndoEditString.RemoveAll();
    UndoEndEditString.RemoveAll();


	m_undocount = 1;
	Undocmdcode.Add(0);
	UndoTotalPasteLine.Add(0);
	UndoEditLineNo.Add(1);
	UndoEditString.Add("!!!!!!!!!!!!!!!!");
    UndoEndEditString.Add("!!!!!!!!!!!!!!!!!");

	currentLine = 0;

	margin = 0;
	memDC0OffSet = 0;
	CursorY = 0;
    CursorX = 0;
	EditLineNo = 0;
	LastEditLine = 2;
	m_SelectLine = m_SelectLine2 = 0;
//	m_TextEditCopyEnable = FALSE;
    m_TextEditPasteEnable = FALSE;
	i_ProgressStep = 1;
	EditString.Empty();
	EndEditString.Empty();

	B_PrepareChartData = FALSE;
	DrawXYLine = FALSE;
//	FileTypeCode.Empty();
	b_LineNo = TRUE;

    DataCapture = FALSE;
	b_FindCapture = FALSE;
	
	m_Communication = 0;

	SetScrollRange(SB_VERT, 0, l->GetSize());
	SetScrollPos(SB_VERT, 0);
	SetScrollRange(SB_HORZ, 0, pDoc->GetMaxLineLength());
	SetScrollPos(SB_HORZ, 0);
	
//	ourFont = new CFont();
/*	m_font.CreateFont(20,10, 0,800,FW_NORMAL, FALSE, FALSE,
		FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_TT_ALWAYS,
		DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");
		*/
/*	m_font.CreateFont(20, 0, 0, 0, 400, FALSE, FALSE, 0,
                        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_SWISS, "Arial");
*/	
	CDC *pDC = GetDC();
	CFont *oldFont = pDC->SelectObject(&m_font);
	
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	lHeight = tm.tmHeight + tm.tmExternalLeading;
	cWidth = tm.tmAveCharWidth;
	
	pDC->SelectObject(&oldFont);
	
//	if(PreparememDC == TRUE)
//    memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);

	B_PrepareChartData = FALSE;
	
//	GP16 = 0.0;
//	GT = 0.0;
//	Gx = 0.0;
//	Gy = 0.0;
//	startx = 0.0;
//	starty = 0.0;
//	centx = 999.9;
//	centy = 999.9;
//	Circler = 999.9;

//	maxXvalue = -10000.0;
//	minXvalue = 10000.0;
//	maxYvalue = -10000.0;
//	minYvalue = 10000.0;

	Invalidate(0);

//    CView::OnInitialUpdate();	
}

void CADataEditView::OnDraw(CDC* pDC)
{
	CADataEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CPtrArray *l = pDoc->GetLines();
	
		CFont *oldFont;
		CRect clientRect;
		
		oldFont = pDC->SelectObject(&m_font);
		
		int y = 0;
		
		if (pDC->IsPrinting())
			clientRect = printerRect;
		else
			GetClientRect(&clientRect);
		
		for (int i = currentLine; i < l->GetSize(); i++)
		{
			CString *line = (CString *) l->GetAt(i);
			if (line->GetLength() - 2 > margin)
				pDC->TextOut(450, y+20, line->Mid(margin), line->GetLength() - margin - 2);
			char m_str[6];    
			wsprintf(m_str,"%d",i+1);
			pDC->TextOut(100,y+20,m_str,strlen(m_str));
			y += lHeight;
			if (y > clientRect.Height()-40)
				break;
		}
		pDC->SelectObject(oldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CADataEditView printing

BOOL CADataEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation

		CADataEditDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CPtrArray *l = pDoc->GetLines();
		pInfo->SetMaxPage((l->GetSize()/57)+1);
	
	return DoPreparePrinting(pInfo);
}

void CADataEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
	CFont *oldFont = pDC->SelectObject(&m_font);
	saveLHeight = lHeight;
	saveCWidth = cWidth;
	
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	lHeight = tm.tmHeight + tm.tmExternalLeading;
	cWidth = tm.tmAveCharWidth;
	saveCurrentLine = currentLine;
	currentLine = 0;
	pDC->SelectObject(oldFont);
}

void CADataEditView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	pInfo->m_rectDraw.InflateRect(0, -lHeight);
	printerRect = pInfo->m_rectDraw;
	int linesPerPage = (printerRect.Height() / lHeight) - 1;
	currentLine = linesPerPage * (pInfo->m_nCurPage -1);
	TRACE2("Printing page %d, starting with line %d\n", pInfo->m_nCurPage, currentLine);
	CView::OnPrint(pDC, pInfo);
	CString footer;
	CFont *oldFont;
	footer.Format("    File %s    ", GetDocument()->GetPathName());
	oldFont = pDC->SelectObject(&m_font);
	pDC->TextOut(160, pInfo->m_rectDraw.Height() + lHeight, footer);
	pDC->SelectObject(oldFont);		

	CView::OnPrint(pDC, pInfo);
}


void CADataEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	lHeight = saveLHeight;
	cWidth = saveCWidth;
	currentLine = saveCurrentLine;
}

/////////////////////////////////////////////////////////////////////////////
// CADataEditView diagnostics

#ifdef _DEBUG
void CADataEditView::AssertValid() const
{
	CView::AssertValid();
}

void CADataEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CADataEditDoc* CADataEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADataEditDoc)));
	return (CADataEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADataEditView message handlers


void CADataEditView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	    if(!PreparememDC)
		{
		PrepareMemDC();
		/*
		if((m_TextEditCopyEnable)&&(b_AttachChart))
		{
		PrepareChartData();
	    DrawChartMemDC();
		}
		*/
		}
		/*
		if((m_TextEditCopyEnable)&&(b_AttachChart))
		{
        PrepareChartData();
	    DrawChartMemDC();
		}
		*/
		CADataEditDoc* pDoc = GetDocument();
		CPtrArray *l = pDoc->GetLines();
		ASSERT_VALID(pDoc);
		
		CRect clientRect;
		if (dc.IsPrinting())
			clientRect = printerRect;
		else
			GetClientRect(&clientRect);
		
		CFont *oldFont;
		oldFont = memDC0.SelectObject(&m_font);
		
//		memDC0.PatBlt(0,0,maxX,maxY,WHITENESS);
		
		CBrush BackGroundBrush;
		BackGroundBrush.CreateSolidBrush(BackGroundColor);
		memDC0.SelectObject(&BackGroundBrush);
		memDC0.PatBlt(0,0,maxX,maxY,PATCOPY);
		
		int y = 0;
			
		
		if(m_Communication == 1)                      //Communication send out
		{
			for (int i = currentLine; i < OutputLinei; i++)
			{
				CString *line = (CString *) l->GetAt(i);
				if (line->GetLength() - 2 >=  margin)
					memDC0.TextOut(60, y, line->Mid(margin, line->GetLength() - margin -2));
				
				y += lHeight;
				if (y >= clientRect.Height())
					break;
			}
			
//			memDC0.SetTextColor(TextColor);
//			memDC0.SetBkColor(BackGroundColor);
			char m_str[7];
			y = 0;
			for (int i2 = currentLine; i2 < OutputLinei ; i2++)
			{
				
				wsprintf(m_str,"%d",i2+1);
				memDC0.TextOut(5,y,m_str,strlen(m_str));
				
				y += lHeight;
				if (y >= clientRect.Height())
					break;
			}
		}
		
		if(m_Communication == 2)               //Communication Recive in
		{

			int n3 = l->GetSize();
			for (int i = currentLine; i < n3; i++)
			{
				CString *line = (CString *) l->GetAt(i);
				if (line->GetLength() - 2 >=  margin)
					memDC0.TextOut(60, y, line->Mid(margin, line->GetLength() - margin -2));
				
				y += lHeight;
				if (y >= clientRect.Height())
					break;
			}
			
//			memDC0.SetTextColor(TextColor);
//			memDC0.SetBkColor(BackGroundColor);
			char m_str[7];
			y = 0;
			for (int i2 = currentLine; i2 < n3 ; i2++)
			{
				
				wsprintf(m_str,"%d",i2+1);
				memDC0.TextOut(5,y,m_str,strlen(m_str));
				
				y += lHeight;
				if (y >= clientRect.Height())
					break;
			}
		}
		
		if(m_Communication == 0)                       //Communication stop
		{
		pDoc->EditLineNo = EditLineNo;
		pDoc->LastEditLine = LastEditLine;
        pDoc->QuickDraw = QuickDraw;
		pDoc->Inch = Inch;
		pDoc->UpdateAllViews(this);

            CString s;

			memDC0.SetTextColor(TextColor);
//			memDC0.SetBkColor(BackGroundColor);
			int n = l->GetSize();
			for (int i = currentLine; i < n; i++)
			{
				CString *line = (CString *) l->GetAt(i);
				if (line->GetLength() - 2 >=  margin)
					memDC0.TextOut(60, y, line->Mid(margin, line->GetLength() - margin -2));
				
				y += lHeight;
				if (y >= clientRect.Height())
					break;
			}
			if(b_LineNo==TRUE)                                   //Display Line No.
			{
				memDC0.SetTextColor(LineNoColor);
//				memDC0.SetBkColor(BackGroundColor);
				char m_str[7];
				y = 0;
				for (int i2 = currentLine; i2 < n; i2++)
				{
					
					wsprintf(m_str,"%d",i2+1);
					memDC0.TextOut(5,y,m_str,strlen(m_str));
					
					y += lHeight;
					if (y >= clientRect.Height())
						break;
				}
			}
			CBrush BlackBrush;
            BlackBrush.CreateSolidBrush(RGB(0,255,255));
            memDC0.SelectObject(&BlackBrush);
            CSize size;
			size = memDC0.GetTextExtent(EditString,strlen(EditString));
			if((b_FindCapture == FALSE )&&(m_SelectLine ==0))
			{
				memDC0.PatBlt(59+size.cx-10*margin,CursorY,2,lHeight,PATINVERT);
			}
            CursorX = 59 + size.cx - 10*margin;
			
			/*		if(!CaretCreated)
            {
			TEXTMETRIC textmetric;
			dc.GetTextMetrics(&textmetric);
			CreateSolidCaret(textmetric.tmAveCharWidth/2,textmetric.tmHeight);
			CaretPosition.x = CaretPosition.y = 0;
			SetCaretPos(CaretPosition);
			ShowCaret();
			CaretCreated = true;
			}
			
			  CSize size = dc.GetTextExtent(EditString,strlen(EditString));
			  HideCaret();
			  CaretPosition.x = 45 + size.cx;
			  CaretPosition.y = CursorY;
			  SetCaretPos(CaretPosition);
			  ShowCaret();        
			*/        
			EditCopyString.Empty();
			int j = 0;
			while((m_SelectLine >= 1)&&(DataCapture == TRUE))
			{
				CString *EditLineL = (CString *) l->GetAt(EditLineNo+j);
				s = *EditLineL;
				EditCopyString = EditCopyString + s;
				memDC0.PatBlt(59,CursorY+j*lHeight,(memDC0.GetTextExtent(s,strlen(s))).cx-5,lHeight,DSTINVERT);
				j = j +1;
				m_SelectLine = m_SelectLine-1;
				if((EditLineNo+j) >= n){break;}
			}
			if(b_FindCapture == TRUE)
			{
//				b_FindCapture = FALSE;
				memDC0.PatBlt(CursorX,CursorY,(memDC0.GetTextExtent(m_Combo1Text,strlen(m_Combo1Text))).cx,lHeight,DSTINVERT);
			}			
		}
		memDC0.SelectObject(oldFont);
/*
        if((FileTypeCode == 'R')&&(b_AttachChart))
		{
		memDC0.StretchBlt(500,200,520,480,&memDC1,50,0,maxX-50,maxY,SRCAND/*INVERT*//*);*/
//		}

/*
		if((FileTypeCode == 'O')&&(b_AttachChart))
		{
//			int NetY;
			memDC0.TextOut(595,190,"Y",1);
			memDC0.TextOut(966,510,"X",1);
			memDC0.MoveTo(588,200);
			memDC0.LineTo(590,190);
			memDC0.LineTo(592,200);
			memDC0.MoveTo(590,190);
			memDC0.LineTo(590,530);
			memDC0.LineTo(980,530);
			memDC0.LineTo(970,528);
			memDC0.MoveTo(970,532);
			memDC0.LineTo(980,530);

			      memDC0.TextOut(550,34,"End Point                 Cent Point                   Radius",61);
		          memDC0.TextOut(550,94,"Offset",6);
				  memDC0.TextOut(550,134,"Taper",5);

				  memDC0.SetTextColor(TextColor);
				  CString s3;

				  memDC0.TextOut(560,50,"              ",14);
				  memDC0.TextOut(560,50,"X:"+s_startx);

				  memDC0.TextOut(560,70,"              ",14);
				  memDC0.TextOut(560,70,"Y:"+s_starty);
				  

                  memDC0.TextOut(690,50,"              ",14);
				  memDC0.TextOut(690,50,"X:"+s_centx);

				  memDC0.TextOut(690,70,"              ",14);
				  memDC0.TextOut(690,70,"Y:"+s_centy);

                  memDC0.TextOut(830,50,"              ",14);
				  memDC0.TextOut(830,50,"R:"+s_Circler);
  
				  memDC0.TextOut(830,70,"              ",14);
				  memDC0.TextOut(830,70,"D:"+s_Diameter);

				  memDC0.TextOut(690,110,"Dir. G4"+ G4,8);
				  memDC0.TextOut(560,110,"             ",13);
				  memDC0.TextOut(560,110,"R:"+s_R);
				  
				  memDC0.TextOut(690,150,"Dir. G5"+ G5,8);
				  if (G5 == '0')
				  {
				  GT = 0.0;
				  s_GT.Empty();
				  }
				  memDC0.TextOut(560,150,"             ",13);
				  memDC0.TextOut(560,150,"T:"+s_GT);
				  
                  s3.Format("%4.1f",NCDrawScale);
				  memDC0.TextOut(750,540,"              ",14);
				  memDC0.TextOut(750,540,"Scale:"+s3);

//				  memDC0.BitBlt(600,200,900,480,&memDC2,0,0,SRCINVERT);
                  memDC0.StretchBlt(600,190,1000,740,&memDC1,0,0,maxX,maxY,SRCAND/*INVERT*//*);*/

//		}
		dc.BitBlt(0,0,maxX,maxY,&memDC0,memDC0OffSet,0,SRCCOPY);

	// Do not call CView::OnPaint() for painting messages
}

void CADataEditView::OnViewLineno() 
{
	b_LineNo = !b_LineNo;
	Invalidate(0);	
}

void CADataEditView::OnUpdateViewLineno(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(b_LineNo);		
}

void CADataEditView::PrepareMemDC()
{
	CClientDC DC(this);
	CBitmap m_bmp0/*,m_bmp1,m_bmp2*/;
	
	m_bmp0.CreateCompatibleBitmap(&DC,maxX,maxY);
	memDC0.CreateCompatibleDC(&DC);
	memDC0.SelectObject(&m_bmp0);

//	memDC0.SetTextColor(TextColor);
	memDC0.SetBkColor(BackGroundColor);
/*
	m_bmp1.CreateCompatibleBitmap(&DC,360,320);
	memDC1.CreateCompatibleDC(&DC);
    memDC1.SelectObject(&m_bmp1);
    memDC1.PatBlt(0,0,360,320,WHITENESS);
*/
/*
	m_bmp1.CreateCompatibleBitmap(&DC,maxX,maxY);
	memDC1.CreateCompatibleDC(&DC);
    memDC1.SelectObject(&m_bmp1);
    memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);
*/
/*
	m_bmp2.CreateCompatibleBitmap(&DC,360,320);
	memDC2.CreateCompatibleDC(&DC);
    memDC2.SelectObject(&m_bmp2);
    memDC2.PatBlt(0,0,360,320,WHITENESS);
*/
	PreparememDC = TRUE;
}

void CADataEditView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	    CADataEditDoc *pDoc = GetDocument();
		CPtrArray *l = pDoc->GetLines();
		CString s;

	if (m_Communication == 0)
	{
		
		if(l->GetSize() <= 1){AddEmptyLine();}
	
		if (nChar == '\b')              //Return Key
		{
			if (EditString.GetLength() == 0)
			{
				if(EditLineNo >= 1)
				{  
					

					StringLoad();

					s = EndEditString;
					DeleteLine();
					OnKeyDown(VK_UP,1,NULL);
					StringLoad();
					EditString = EndEditString;
					EndEditString = s;

				if(Undocmdcode.GetAt(m_undocount-1) != 2)
					{
					PrepareUndo(1);
                    Undocmdcode.Add(3);
					}

					goto NEXT0;
				}
				goto NEXT0;
			}
//			if(Undocmdcode.GetAt(m_undocount-1) != 2)
			{
			PrepareUndo(1);
			Undocmdcode.Add(1);
			}
			EditString = EditString.Left(EditString.GetLength()-1);
			goto NEXT0;
		}

		if((nChar != '\r')&&(nChar != '\b'))
		{
		PrepareUndo(1);
		Undocmdcode.Add(1);
		EditString += nChar;
		}
NEXT0:
		if (nChar == '\r')         //Enter Key
	  {
		  if(EditLineNo +1 == l->GetSize()){pDoc->lines->Add(new CString(s));}
		  if(Undocmdcode.GetAt(m_undocount-1) != 3)
		  {
		  PrepareUndo(1);
		  Undocmdcode.Add(2);
		  }
		  s = EndEditString;
		  EndEditString.Empty();
		  StringSave();
		  OnKeyDown(VK_DOWN,1,NULL);
		  OnEditInsertaline();
		  EndEditString = s;
	  }
      StringSave();
	}
	
	
	Invalidate(0);	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CADataEditView::AddEmptyLine()
{
	CString s;
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
	pDoc->lines->Add(new CString(s));
	
	EndEditString.Empty();
	StringSave();
	StringLoad();
	m_TextEditCopyEnable = TRUE;
	MenuID="DataFile";
}

void CADataEditView::DeleteLine()
{
    CADataEditDoc *pDoc = GetDocument();	
    pDoc->lines->RemoveAt(EditLineNo);
	CPtrArray *l = pDoc->GetLines();
    OnKeyDown(VK_UP,1,NULL);
    OnKeyDown(VK_DOWN,1,NULL);
	
	CString s;
	if(EditLineNo  == l->GetSize()){OnKeyDown(VK_UP,1,NULL);}
    if(l->GetSize() == 1){AddEmptyLine();} 
	Invalidate(0);
}

void CADataEditView::StringLoad()
{
    CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    CString *EditLineL = (CString *) l->GetAt(EditLineNo);
	EndEditString = *EditLineL;
	EndEditString = EndEditString.Left(EndEditString.GetLength()-2);
	EditString.Empty();
}

void CADataEditView::StringSave()
{
    CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    CString *EditLineS = (CString *) l->GetAt(EditLineNo);
    *EditLineS = EditString + EndEditString + '\r' + '\n';
}

void CADataEditView::OnEditInsertafile() 
{
	int i = EditLineNo;
	int TotalPasteLine = 0;
	BYTE buf;
	CString s1,s2;
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
	
	HICON hIcon=AfxGetApp() ->LoadIcon(IDI_ICON1);
	
	/*    CFileDialog dlg(TRUE);
	BOOL bRet = CFileDialog::OnInitDialog();
	if (bRet == TRUE) {
	GetParent()->GetDlgItem(IDOK)->SetWindowText("Delete");
	}
	return bRet;
	if (dlg.DoModal() == IDOK)
	{
	CFile file(dlg.GetPathName(),CFile::modeRead);*/
	
//	CInsertFileDialog dlgFile(TRUE, "*.dat","*.dat",0,"*.dat",NULL);
	CInsertFileDialog dlgFile(FALSE ,"dat",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"*.dat|*.dat|*.nc|*.nc|*.*|*.*|",NULL);
	CString strMessage;
	int nModal = dlgFile.DoModal();

/*	if ((nModal == IDCANCEL) && (dlgFile.m_bDeleteAll)) {
	strMessage.Format(
	"Are you sure you want to delete all %s files?",
	dlgFile.m_strFilename);
	if (AfxMessageBox(strMessage, MB_YESNO) == IDYES) {
	HANDLE h;
	WIN32_FIND_DATA fData;
	while((h = ::FindFirstFile(dlgFile.m_strFilename, &fData))
	!= (HANDLE) 0xFFFFFFFF) { // no MFC equivalent
				if (::DeleteFile(fData.cFileName) == FALSE) {
				strMessage.Format("Unable to delete file %s\n",
				fData.cFileName);
				AfxMessageBox(strMessage);
				break;
				}
				}
				}
}*/
	/*else*/ 
	if (nModal == IDOK) 
	{
	CString strSingleFilename = dlgFile.GetPathName();
	strMessage.Format("Are you sure you want to insert %s?", strSingleFilename);
	if (AfxMessageBox(strMessage, MB_YESNO) == IDYES) 
	{
		PrepareUndo(1);
		Undocmdcode.Add(11);

		CFile file(dlgFile.GetPathName(),CFile::modeRead);
		CArchive ar(&file,CArchive::load);
		
		while (1)
		{
			try {
				ar >> buf;
			}
			catch (CArchiveException *e)
			{
				if (e->m_cause != CArchiveException::endOfFile)
				{
					TRACE0("Unknown exception loading file!\n");
					throw;
				} else
				{
					TRACE0("End of file reached...\n");
					e->Delete();
				}
				break;
			}
			s2 += buf;   
			if (buf == '\n')
			{
				pDoc->lines->InsertAt(i,new CString(s1),1);
				pDoc->lines->SetAt(i, new CString(s2));
				i++;
				TotalPasteLine++;
				s2.Empty();
			}
		}
		StringLoad();
		EndEditString.Empty();
		
	}

        UndoTotalPasteLine.SetAt(m_undocount-1,TotalPasteLine);
    
		AdjScrollRange();

  	    Invalidate(0);
	}	
}

void CADataEditView::OnUpdateEditInsertafile(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_TextEditCopyEnable);	
}


void CADataEditView::OnEditInsertaline() 
{
    CString s;
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    if(EditLineNo < l->GetSize()){pDoc->lines->InsertAt(EditLineNo,new CString(s),1);}
	if(EditLineNo == l->GetSize()){pDoc->lines->Add(new CString(s));}
	StringLoad();
    EndEditString.Empty(); 
	Invalidate(0);
}

void CADataEditView::OnUpdateEditInsertaline(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_TextEditCopyEnable);		
}

void CADataEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    
	if(l->GetSize() <= 1){AddEmptyLine();} 
	
    CRect clientRect;
    GetClientRect(&clientRect);
	
		switch (nChar)
		{
		case VK_UP:                   //ARROW UP

			if (EditLineNo>=1)
			{
				if ( CursorY  == 0 )
				{
					currentLine -= 1;
					EditLineNo = EditLineNo - 1;
				}
				else 
				{
					EditLineNo = EditLineNo - 1;
					CursorY -= lHeight;
				}
			}
			StringLoad();
			
			KeepCursorXPos(CursorX);
			
			break;
			
		case VK_DOWN:                  //ARROW DOWN

			if (EditLineNo < l->GetSize()-1)
			{
				if (CursorY < clientRect.Height()-2*lHeight)
				{
					EditLineNo = EditLineNo + 1;
					CursorY += lHeight;
				}
				else
				{
					currentLine +=1;
					EditLineNo = EditLineNo + 1;
				}
				StringLoad();
				
				KeepCursorXPos(CursorX);
				
			}
			break;
			
		case VK_LEFT:                   //ARROW LEFT
			if ((EditString.GetLength()-1)>=0)
			{
				EndEditString.MakeReverse();
				EndEditString += EditString.GetAt(EditString.GetLength()-1);
				EndEditString.MakeReverse();
				EditString = EditString.Left(EditString.GetLength()-1);
				StringSave();
				if ((EditString.GetLength()<memDC0OffSet/cWidth)&&memDC0OffSet>0)
				{
					memDC0OffSet = memDC0OffSet - 60;
				}
			}
			break;
			
		case VK_RIGHT:                    //ARROW RIGHT
			if ((EndEditString.GetLength()-1)>=0)
			{
				EditString += EndEditString.GetAt(0);
				EndEditString = EndEditString.Right(EndEditString.GetLength()-1);
				StringSave();
				if (EditString.GetLength()>(clientRect.Width() + memDC0OffSet -60)/cWidth)
				{
					memDC0OffSet = memDC0OffSet + 60;
				}
				}
			break;

		case VK_DELETE:
			if((EndEditString.GetLength()>0)&&m_SelectLine2 == 0)
			{
				PrepareUndo(1);
				Undocmdcode.Add(1);

				EndEditString = EndEditString.Right(EndEditString.GetLength()-1);
				StringSave();
			}

			if(m_SelectLine2 >= 1)
			{
			while(m_SelectLine2 > 0)
			{
			    DeleteLine();
			    m_SelectLine2 = m_SelectLine2 - 1;
			}
		        m_undocount = m_undocount + 1;
		        Undocmdcode.Add(10);
		        UndoTotalPasteLine.Add(0);
	            UndoEditLineNo.Add(EditLineNo);
	            UndoEditString.Add(EditCopyString);
                UndoEndEditString.Add(EndEditString);

		        AdjScrollRange();
			}
			break;

			//	case VK_INSERT:
			//		OnEditInsertline();
			//		break;
			
		case VK_END:
		    EditString += EndEditString;
			EndEditString.Empty();
            StringSave();
			break;
			
		case VK_HOME:
			EditString += EndEditString;
            EndEditString = EditString;
			EditString.Empty();
            StringSave();
			break;
			
		case VK_PRIOR:
			{
				currentLine -= (clientRect.Height() / lHeight);
				EditLineNo -= (clientRect.Height() / lHeight);
				if (currentLine < 0)
				{
					currentLine = 0;
					EditLineNo = 0;
					CursorY = 0;
				}
				StringLoad();
				
				KeepCursorXPos(CursorX);
			}
			break;
			
		case VK_NEXT:
			if (( EditLineNo + (clientRect.Height() / lHeight)) < l->GetSize())
			{
				currentLine += (clientRect.Height() / lHeight);
				EditLineNo += (clientRect.Height() / lHeight);
				
//				if (currentLine > l->GetSize()-1)
//				{
//					currentLine = l->GetSize()-1;
//					EditLineNo = currentLine;
//					CursorY = 0;
//				}
			}
			else
			{
				GotoFileBottom();
			}
				StringLoad();
				KeepCursorXPos(CursorX);
			break;
		}
        SetScrollPos(SB_VERT, EditLineNo);
		Invalidate(0);
		
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CADataEditView::KeepCursorXPos(int i)
{
	i = i + memDC0OffSet;
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    
	CFont *oldFont;
	oldFont = memDC0.SelectObject(&m_font);
	
	while((i - (59+(memDC0.GetTextExtent(EditString,strlen(EditString))).cx-10*margin) > 1)
		&&(EditLineNo < l->GetSize()-2)&&((EndEditString.GetLength()-1) >= 0))
	{OnKeyDown(VK_RIGHT,1,NULL);}
	
	while(((59+(memDC0.GetTextExtent(EditString,strlen(EditString))).cx-10*margin - i) > 1)
		&&(EditLineNo < l->GetSize()-2)&&((EditString.GetLength()-1) >= 0))
	{OnKeyDown(VK_LEFT,1,NULL);}
	
	memDC0.SelectObject(oldFont);
}


void CADataEditView::OnLButtonDown(UINT nFlags, CPoint point) //Flags tell you if 'control' or 'shaft' key press together
{                                                             //So MK_CONTROL,MK_SHAFT,MK_RBUTTON
	b_FindCapture = FALSE;
	if (m_Communication == 0)
	{
        CADataEditDoc *pDoc = GetDocument();
		CPtrArray *l = pDoc->GetLines();
		while(point.y - CursorY >= 15)
		{
			if(EditLineNo == l->GetSize()-1){break;}
			OnKeyDown(VK_DOWN,1,NULL);
		}
		
        while(point.y - CursorY <= -1)
		{OnKeyDown(VK_UP,1,NULL);}
		
		KeepCursorXPos(point.x);
		
		DataCapture = TRUE;
	}	
	CView::OnLButtonDown(nFlags, point);
}

void CADataEditView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_Communication == 0)
	{
		DataCapture = FALSE;
		m_SelectLine = 0;
	}	
	CView::OnLButtonUp(nFlags, point);
}

void CADataEditView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((m_Communication == 0)&&(DataCapture == TRUE))
	{
		m_SelectLine2 = m_SelectLine = (point.y-CursorY)/lHeight;
		Invalidate(0);
	}	
	CView::OnMouseMove(nFlags, point);
}

void CADataEditView::OnEditSetfont() 
{
	CFontDialog dlg(&m_lf,CF_SCREENFONTS);
	if(dlg.DoModal() == IDOK)
	{
		m_font.DeleteObject();
		if(m_font.CreateFontIndirect(&m_lf))
		{
			//				memDC0.SelectObject(&m_font);
			//				RecalcLayout();
			
			CDC *pDC = GetDC();
			CFont *oldFont = pDC->SelectObject(&m_font);
			
			TEXTMETRIC tm;
			pDC->GetTextMetrics(&tm);
			lHeight = tm.tmHeight + tm.tmExternalLeading;
			cWidth = tm.tmAveCharWidth;
			
			EditString.Empty();
			EndEditString.Empty();
			currentLine = 0;
			margin = 0;
			CursorY = 0;
			CursorX = 0;
			EditLineNo = 0;
			m_SelectLine = m_SelectLine2 = 0;
			//	            m_TextEditCopyEnable = FALSE;
			//              m_TextEditPasteEnable = FALSE;
			StringLoad();
			KeepCursorXPos(CursorX);
			
			Invalidate(0);
		}
	}	
}

void CADataEditView::OnUpdateEditSetfont(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(m_TextEditCopyEnable);	
}

void CADataEditView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(m_Communication == 0)
	{
//		CADataEditDoc *pDoc = GetDocument();
//		CPtrArray *l = pDoc->GetLines();
		
		CRect clientRect;
		GetClientRect(&clientRect);
		
		switch (nSBCode)
		{
		case SB_LINELEFT:
			if (memDC0OffSet > 0)
			{
//				margin--;
//          	OnKeyDown(VK_LEFT,1,NULL);
				memDC0OffSet = memDC0OffSet - 10;
			}
			break;
			
		case SB_LINERIGHT:
            if (memDC0OffSet < clientRect.Width()+80)
			{
//				margin++;
//          	OnKeyDown(VK_RIGHT,1,NULL);
				memDC0OffSet = memDC0OffSet + 10;
			}
			break;
			
			/*	case SB_RIGHT:
			margin = pDoc->GetMaxLineLength();
			break;
			
			  case SB_LEFT:
			  margin = 0;
			break;*/
			
		case SB_PAGELEFT:
//			margin -= (clientRect.Width() / cWidth);
//			if (margin < 0)
//				margin = 0;
			if (memDC0OffSet > 100)
			{
				memDC0OffSet = memDC0OffSet - 100;
			}
			else
			{memDC0OffSet = 0;}
			break;
			
		case SB_PAGERIGHT:
//			margin += (clientRect.Width() / cWidth);
//			if (margin > pDoc->GetMaxLineLength())
//				margin = pDoc->GetMaxLineLength();
            if (memDC0OffSet < clientRect.Width()+80)
			{
				memDC0OffSet = memDC0OffSet + 100;
			}
			break;
			
//		case SB_THUMBPOSITION:
//		case SB_THUMBTRACK:
//			margin = nPos;
//			if (margin < 0)
//				margin = 0;
//			if (margin > pDoc->GetMaxLineLength())
//				margin = pDoc->GetMaxLineLength();
//			break;
		}
		SetScrollPos(SB_HORZ, memDC0OffSet/cWidth);
		Invalidate(0);
	}	
	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CADataEditView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if(m_Communication == 0)
	{
		CADataEditDoc *pDoc = GetDocument();
		CPtrArray *l = pDoc->GetLines();
		
		CRect clientRect;
		GetClientRect(&clientRect);
		
		switch (nSBCode)
		{
		case SB_LINEUP:
            if (EditLineNo>=1)
			{
				if ( CursorY  == 0 )
				{
					currentLine -= 1;
					EditLineNo = EditLineNo - 1;
				}
				else 
				{
					EditLineNo = EditLineNo - 1;
					CursorY -= lHeight;
				}
			}
			StringLoad();
			KeepCursorXPos(CursorX);
			break;
			
		case SB_LINEDOWN:

			if (EditLineNo < l->GetSize()-1)
			{
				if (CursorY < clientRect.Height()-2*lHeight)
				{
					EditLineNo = EditLineNo + 1;
					CursorY += lHeight;
				}
				else
				{
					currentLine +=1;
					EditLineNo = EditLineNo + 1;
				}
				StringLoad();
				
				KeepCursorXPos(CursorX);				
			}
			break;
			
/*			
		case SB_BOTTOM:
			OnKeyDown(VK_END,1,NULL);
			break;
			
		case SB_TOP:
			OnKeyDown(VK_HOME,1,NULL);
			break;
*/			
		case SB_PAGEUP:
				currentLine -= (clientRect.Height() / lHeight);
				EditLineNo -= (clientRect.Height() / lHeight);
				if (currentLine < 0)
				{
					currentLine = 0;
					EditLineNo = 0;
					CursorY = 0;
				}
				StringLoad();
				
				KeepCursorXPos(CursorX);
			break;
			
        case SB_PAGEDOWN:
            if (( EditLineNo + (clientRect.Height() / lHeight)) < l->GetSize())
			{
				currentLine += (clientRect.Height() / lHeight);
				EditLineNo += (clientRect.Height() / lHeight);
				
				if (currentLine > l->GetSize()-1)
				{
					currentLine = l->GetSize()-1;
					EditLineNo = currentLine;
					CursorY = 0;
				}
				StringLoad();
				KeepCursorXPos(CursorX);
			}
			break;
/*			
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			if (nPos < 0)
				nPos = 0;
			if (nPos > l->GetSize()-1)
				nPos = l->GetSize()-1;
			currentLine = nPos;
			EditLineNo = currentLine;
			CursorY  = 0;
			StringLoad();
			break;
*/
		}
		SetScrollPos(SB_VERT, EditLineNo);
		
		Invalidate(0);
	}	
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CADataEditView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (m_Communication == 0)
	{
		CMenu  PopUpMenu1;
//		m_ptDataEditPopUpMenu = point;
//		ScreenToClient(&m_ptDataEditPopUpMenu);
		PopUpMenu1.LoadMenu(IDR_MENU1);
		CMenu* pPopup = PopUpMenu1.GetSubMenu(0);
		pPopup->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON,
			point.x,point.y,this);	  
	}	

	if ((m_Communication == 1)||(m_Communication == 2))
	{
		CMenu  PopUpMenu3;
		CPoint m_ptDataEditPopUpMenu = point;
		ScreenToClient(&m_ptDataEditPopUpMenu);
		PopUpMenu3.LoadMenu(IDR_MENU3);
		CMenu* pPopup = PopUpMenu3.GetSubMenu(0);
		pPopup->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON,
			point.x-50,point.y-25,this);
	}		
}

BOOL CADataEditView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
 
		HCURSOR hcur = AfxGetApp () ->LoadStandardCursor (IDC_IBEAM);
		SetCursor (hcur); 
		return TRUE; 
	
	    return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CADataEditView::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	   CADataEditDoc *pDoc = GetDocument();
	   CPtrArray *l = pDoc->GetLines();
	
	   pCmdUI->Enable(TRUE);
	   CString str,s1,s2,s3;

	   str.Format("    Ln %d/%d    Col %d",EditLineNo+1,l->GetSize(),CursorX/10-5);

	   pCmdUI->SetText(str);
}

void CADataEditView::OnSelchangeCombo1() 
{
	   CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
	   frame->m_wndToolBar.m_combobox1.GetLBText(
       frame->m_wndToolBar.m_combobox1.GetCurSel(),m_Combo1Text);
//        OnEditFind();
}

void CADataEditView::OnEditchangeCombo1() 
{
	CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
	
	frame->m_wndToolBar.m_combobox1.GetWindowText(m_Combo1Text);
}

void CADataEditView::OnEditFind() 
{
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
	int m = 0;
	CString s;
	int nn = l->GetSize();
	if(!b_FindCapture)
	{
	OnKeyDown(VK_UP,1,NULL);
	}
	b_FindCapture = FALSE;
	if(EditLineNo == nn-1)
	{
	OnKeyDown(VK_UP,1,NULL);
	}
	m_GoToLineNo = EditLineNo ;
	
start:  for (int i = EditLineNo; i < nn-1; i++)
		{
			OnKeyDown(VK_DOWN,1,NULL);
			m = i;
			m++;
			CString *line = (CString *) l->GetAt(i+1);
			s = *line;
			if(s.Find(m_Combo1Text) != -1)
			{
				b_FindCapture = TRUE;
				KeepCursorXPos(60);
				int j = s.Find(m_Combo1Text);
				while( j > 0)
				{
					OnKeyDown(VK_RIGHT,1,NULL);
					j--;
				}
				m = 0;
				goto nend;
			}			
		}
		if(m < nn-1)
		{
			OnKeyDown(VK_HOME,1,NULL);
//			m = 0;
			goto start;
		}
		if(s.Find(m_Combo1Text) == -1)
		{	
			
            CString strMessage;
			strMessage = "Have no same string.\nAre you sure go to hold point?";           
			if (MessageBox(strMessage,"Finished  find.", MB_ICONQUESTION|MB_YESNO) == IDYES) 
			{
				CRect clientRect;
				GetClientRect(&clientRect);
				int CurrentEditLineNo = EditLineNo;
				/*        while( m_GoToLineNo - CurrentEditLineNo > (clientRect.Height() / lHeight))
				{
				OnKeyDown(VK_NEXT,1,NULL);
				m_GoToLineNo = m_GoToLineNo - (clientRect.Height() / lHeight);
			}*/
				while( CurrentEditLineNo - m_GoToLineNo > (clientRect.Height() / lHeight))
				{
					OnKeyDown(VK_PRIOR,1,NULL);
					m_GoToLineNo = m_GoToLineNo + (clientRect.Height() / lHeight);
				}
				while(CurrentEditLineNo < m_GoToLineNo - 1)
				{
					OnKeyDown(VK_DOWN,1,NULL);
					m_GoToLineNo = m_GoToLineNo - 1;
				}
				while(CurrentEditLineNo > m_GoToLineNo - 1)
				{
					OnKeyDown(VK_UP,1,NULL);
					m_GoToLineNo = m_GoToLineNo + 1;
				}
			}
		}
nend:    SetScrollPos(SB_VERT, EditLineNo);
		
		CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
        frame->m_wndToolBar.m_combobox1.InsertString(0,m_Combo1Text);
		Invalidate(0);		
}

void CADataEditView::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	    pCmdUI->Enable(!m_Combo1Text.IsEmpty());	
}

void CADataEditView::OnEditGoto() 
{	
	int m_GoToLineNoBackup;
	
star:	CGoToDLG dlg;
        dlg.m_GoToLineNo = m_GoToLineNo;
		if (dlg.DoModal() == IDOK)	 
		{
			int CurrentEditLineNo = EditLineNo;
			m_GoToLineNo = dlg.m_GoToLineNo;
			m_GoToLineNoBackup = m_GoToLineNo;
			
			CADataEditDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			CPtrArray *l = pDoc->GetLines();
			n = l->GetSize();
			
			if(m_GoToLineNo > n)
			{
				CString strMessage;
				strMessage.Format("Maximum Line Number is %d.  \nAre you sure go to end?",n);           
				if (MessageBox(strMessage,"Too Big Line Number.", MB_ICONQUESTION|MB_YESNO) == IDYES) 
				{
					OnKeyDown(VK_END,1,NULL);
				}
				else goto star;
			}
			else
			{
				GoToSpecialLine(m_GoToLineNo, CurrentEditLineNo);
			}
		}
        KeepCursorXPos(60);
        SetScrollPos(SB_VERT, EditLineNo);
		m_GoToLineNo = m_GoToLineNoBackup;	
}

void CADataEditView::OnUpdateEditGoto(CCmdUI* pCmdUI) 
{
            pCmdUI->Enable(m_TextEditCopyEnable);		
}


BOOL CADataEditView::DoPasteText(COleDataObject *pDataObject)
{
	   STGMEDIUM stg;
	   FORMATETC fmt;
	   //uptata command UI shoud keep us out of here if not CF_TEXT
	   if (!pDataObject->IsDataAvailable(CF_TEXT))
	   {
		   TRACE("CF_TEXT format is unvailable\n");
		   return FALSE;
	   }
	   //Memory is MOVEABLE, so we must us GlobalLock!
	   SETFORMATETC(fmt,CF_TEXT,DVASPECT_CONTENT,NULL,TYMED_HGLOBAL,-1);
	   VERIFY(pDataObject->GetData(CF_TEXT,&stg,&fmt));
	   HGLOBAL hText = stg.hGlobal;
       EditPasteString = (LPSTR)::GlobalLock(hText);
	   ::GlobalUnlock(hText);
	   return TRUE;
}

COleDataSource* CADataEditView::SaveText()
{
	   if(!EditCopyString.IsEmpty())
	   {
		   COleDataSource* pSource = new COleDataSource();
		   int nTextSize = EditCopyString.GetLength() + 1;
		   HGLOBAL hText = ::GlobalAlloc(GMEM_SHARE, nTextSize);
		   LPSTR pText = (LPSTR) ::GlobalLock(hText);
		   ASSERT(pText);
		   strcpy(pText,EditCopyString);
		   ::GlobalUnlock(hText);
		   pSource->CacheGlobalData(CF_TEXT,hText);

		   return pSource;
	   }
       return NULL;
}

void CADataEditView::OnEditCopy() 
{
    if(m_Communication == 0)
	{
		
	/*	CAEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    CString *EditLineL = (CString *) l->GetAt(EditLineNo);
	EditCopyString = *EditLineL;
	
	  HGLOBAL hData;
	  LPVOID pData;
	  
		OpenClipboard();
		EmptyClipboard();
		hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE,
		strlen(EditCopyString) + 1);
		pData = GlobalLock(hData);
		strcpy((LPSTR)pData, EditCopyString);
		GlobalUnlock(hData);
		SetClipboardData(CF_TEXT, hData);
		CloseClipboard();
		m_TextEditPasteEnable = TRUE;*/
		
		COleDataSource* pSource = SaveText();
		if(pSource){
			pSource->SetClipboard();
			m_TextEditPasteEnable = TRUE;
		}
	}		
}

void CADataEditView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!EditCopyString.IsEmpty());	
}

void CADataEditView::OnEditCut() 
{
    if(m_Communication == 0)
	{
		OnEditCopy();
		
		while(m_SelectLine2 > 0)
		{
			DeleteLine();
			m_SelectLine2 = m_SelectLine2 - 1;
		}
		   m_undocount = m_undocount + 1;
		   Undocmdcode.Add(10);
		   UndoTotalPasteLine.Add(0);
	       UndoEditLineNo.Add(EditLineNo);
	       UndoEditString.Add(EditCopyString);
           UndoEndEditString.Add(EndEditString);

		   AdjScrollRange();

		Invalidate(0);
	}	
}

void CADataEditView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!EditCopyString.IsEmpty());	
}


void CADataEditView::OnEditPaste() 
{
	  int TotalPasteLine = 0;

//      if(Undocmdcode.GetAt(m_undocount-1) != 2)
//		{
		  PrepareUndo(1);
		  Undocmdcode.Add(11);
//		}
	      
		if(m_TextEditCopyEnable == FALSE)
		{
			OnChar('\r',1,NULL);
			OnChar('\b',1,NULL);
	//		m_TextEditCopyEnable = TRUE;
		}
		/*  HANDLE hData;
		LPVOID pData;
		char *pszData;
		
		  if (!IsClipboardFormatAvailable(CF_TEXT)) return;
		  OpenClipboard();
		  hData = GetClipboardData(CF_TEXT);
		  pData = GlobalLock(hData);
		  if (pszData)
		  {
		  free(pszData);
		  pszData = NULL;
		  }
		  pszData = malloc(strlen(pData) + 1);
		  strcpy(pszData, (LPSTR)pData);
		  GlobalUnlock(hData);
		  CloseClipboard();
		  for (int i=0; i < strlen(pszData); i++)
		  {    
		  EditPasteString += pszData[i] ;
	}*/
		
		COleDataObject dataObject;
		VERIFY(dataObject.AttachClipboard());
		DoPasteText(&dataObject);
		//dataObject released
		
		CADataEditDoc *pDoc = GetDocument();
		CPtrArray *l = pDoc->GetLines();
        
		CString s;
		while(EditPasteString.GetLength()>0)
		{
			if (EditPasteString.GetAt(0) == '\n')
			{
				s += EditPasteString.GetAt(0);
				pDoc->lines->InsertAt(EditLineNo,new CString(s),1);
				StringLoad();
				EndEditString.Empty();
				OnKeyDown(VK_DOWN,1,NULL);
				TotalPasteLine++;
				if(EditPasteString.GetLength()>1)
				{
					EditPasteString = EditPasteString.Right(EditPasteString.GetLength()-1);
				}
				s.Empty();
			}
			s += EditPasteString.GetAt(0);
			EditPasteString = EditPasteString.Right(EditPasteString.GetLength()-1);
		}
		if(s != '\n')
		{EditString = EditString + s;
		StringSave();}

		UndoTotalPasteLine.SetAt(m_undocount-1,TotalPasteLine);

		AdjScrollRange();

		Invalidate(FALSE);		
}

void CADataEditView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
        pCmdUI->Enable(IsClipboardFormatAvailable(CF_TEXT));	
}

void CADataEditView::OnEditSetcolor() 
{
	   CTextColorDlg dlg;
  	   dlg.BackGroundColor = BackGroundColor;
	   dlg.TextColor = TextColor;
	   dlg.LineNoColor = LineNoColor;
	   if (dlg.DoModal() == IDOK)
	   {
		BackGroundColor = dlg.BackGroundColor;
		TextColor = dlg.TextColor;
		LineNoColor = dlg.LineNoColor;
	   }
	  memDC0.SetBkColor(BackGroundColor);
	  Invalidate(0);	
}

void CADataEditView::OnTransmissiomConfigdevice() 
{
	CTransmissiomConfigDlg dlg;
	
	dlg.m_BandRate = m_BandRate;
	dlg.m_Parity = m_Parity;
	dlg.m_WordLength = m_WordLength;
	dlg.m_StopBits = m_StopBits;
	dlg.m_CodeType = m_CodeType;
	dlg.m_ComPortNo = m_ComPortNo;
	dlg.m_AutoXonXoff = m_AutoXonXoff;
	dlg.m_InputControlMode = m_InputControlMode;
	dlg.m_OutputControlMode = m_OutputControlMode;
	dlg.m_InputStartString = m_InputStartString;
	dlg.m_InputEndString = m_InputEndString;
	dlg.m_OutputStartString = m_OutputStartString;
	dlg.m_OutputEndString = m_OutputEndString;
	dlg.m_OutputSendDelay = m_OutputSendDelay;
	dlg.m_InputTimeOut = m_InputTimeOut;
	
	if (dlg.DoModal() == IDOK)
	{
        m_BandRate = dlg.m_BandRate;
		m_Parity = dlg.m_Parity;
		m_WordLength = dlg.m_WordLength;
		m_StopBits = dlg.m_StopBits;
		m_CodeType = dlg.m_CodeType;
		m_ComPortNo = dlg.m_ComPortNo;
		m_AutoXonXoff = dlg.m_AutoXonXoff;
		m_InputControlMode = dlg.m_InputControlMode;
		m_OutputControlMode = dlg.m_OutputControlMode;
		m_InputStartString = dlg.m_InputStartString;
		m_InputEndString = dlg.m_InputEndString;
		m_OutputStartString = dlg.m_OutputStartString;
		m_OutputEndString = dlg.m_OutputEndString;
		m_OutputSendDelay = dlg.m_OutputSendDelay;
		m_InputTimeOut = dlg.m_InputTimeOut;
	}			
}

void CADataEditView::OnUpdateTransmissiomConfigdevice(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Communication == 0);	
}

void CADataEditView::OnTransmissiomSendout() 
{

	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
    OutputLinei =0;
	if (m_pDlg->GetSafeHwnd() == 0)
	{
		m_pDlg->Create(); // displays the modleness dialog window
	}
	  TransmissionConfig();
//      m_pDlg->m_Comm1.SetDTREnable(FALSE);
	  CString *s = (CString *) l->GetAt(OutputLinei);
 	  m_pDlg->m_OutputString = *s;
//	  CString ss;
//	  ss.Format("'%c'",65);
//      m_pDlg->m_OutputString = ss;

	  m_pDlg->Output();
	  
	  CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
      frame->m_wndStatusBar.m_Progress.SetPos(2);
	  
      m_Communication = 1;
      currentLine = 0;
	  memDC0.SetTextColor(LineNoColor);
	  memDC0.SetBkColor(BackGroundColor);
	  Invalidate(0);
}

void CADataEditView::OnUpdateTransmissiomSendout(CCmdUI* pCmdUI) 
{
       pCmdUI->Enable((m_TextEditCopyEnable)&&(m_Communication == 0));	
}

void CADataEditView::OnTransmissiomReceivein() 
{
	m_Communication = 2;
	memDC0.SetTextColor(LineNoColor);
	memDC0.SetBkColor(BackGroundColor);

	if (m_pDlg->GetSafeHwnd() == 0) {
		m_pDlg->Create(); // displays the modleness dialog window
	}
	TransmissionConfig();
	m_pDlg->Input();
	SetTimer(1,200,NULL);	
}

void CADataEditView::OnUpdateTransmissiomReceivein(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_Communication == 0);	
}

void CADataEditView::OnTransmissiomStop() 
{
	if( m_pDlg->m_Comm1.GetPortOpen() )
	  {
		m_pDlg->m_Comm1.SetRTSEnable(FALSE);
		m_pDlg->m_Comm1.SetDTREnable(FALSE);
		m_pDlg->m_Comm1.SetPortOpen(FALSE);		
//		m_pDlg->DestroyWindow();
	  }

       i_ProgressStep = 1;
	   KillTimer(1);

       CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
       frame->m_wndStatusBar.m_Progress.SetPos(0);

	   m_Communication = 0;
	   m_TextEditCopyEnable = TRUE;
    
	   Invalidate(0);
}

void CADataEditView::OnUpdateTransmissiomStop(CCmdUI* pCmdUI) 
{
	   pCmdUI->Enable(m_Communication != 0);	
}

void CADataEditView::TransmissionConfig()
{
	CString s1,s2;
	BOOL found1 = map1.Lookup(m_Parity,s1);
	if (found1 == 0)
	{MessageBox("Not matching value.");}
	BOOL found2 = map1.Lookup(m_ComPortNo,s2);
	if (found2 == 0)
	{MessageBox("Not matching value.");}
	
	m_pDlg->m_Comm1.SetCommPort(atoi( s2 ));
	m_pDlg->m_Comm1.SetSettings(m_BandRate + s1 + m_WordLength + m_StopBits);

}

LRESULT CADataEditView::OnGoodbye(WPARAM wParam, LPARAM lParam)
{
	//	TRACE("CAMonitorView::OnGoodbye %x, %lx\n", wParam, lParam);
	
	CADataEditDoc *pDoc = GetDocument();
	CPtrArray *l = pDoc->GetLines();
	
	if(m_pDlg->m_Comm1.GetCommEvent()==2)         //recieve in
	{
		for(int i = 0; i < m_pDlg->m_InputString.GetLength(); i++)
		{
			
			//  if(l->GetSize()>3)
			//		{
			//		OnKeyDown( VK_DOWN,1,NULL);			
			//		l->SetAt(l->GetSize()-1,new CString(m_InputString));
			//		}
				if(m_pDlg->m_InputString.GetAt(i) == '\n')
				{
				m_InputString.TrimRight();
				m_InputString = m_InputString + '\r' + '\n';
				pDoc->lines->Add(new CString(m_InputString));
				m_InputString.Empty();
				OutputLinei = OutputLinei+1;
				if(l->GetSize()>1)
			//	  m_TextEditCopyEnable = TRUE;
					OnKeyDown( VK_DOWN,1,NULL);
				}
				else
				{
				m_InputString += m_pDlg->m_InputString.GetAt(i);
				}
		}
	}
	
	if(m_pDlg->m_Comm1.GetCommEvent()==1)        //send out
	{
		OutputLinei = OutputLinei+1;
		OnKeyDown( VK_DOWN,1,NULL);
		
		if(OutputLinei < l->GetSize())
		{
			CString *s = (CString *) l->GetAt(OutputLinei);
			m_OutputString = *s;
			
			m_pDlg->m_OutputString = m_OutputString;
			m_pDlg->Output();
		}
		else
		{
            OnTransmissiomStop(); 
		}

        if((OutputLinei  - (l->GetSize()* i_ProgressStep)/50)>(l->GetSize()/50))
		{
			CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
			frame->m_wndStatusBar.m_Progress.StepIt();
			i_ProgressStep ++ ;
		}
	}
		if(m_pDlg->m_Comm1.GetCommEvent()==7)
		{
			OnTransmissiomStop();
		    Invalidate(0);
		}
	return 0L;
}

void CADataEditView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
       if(m_TextEditCopyEnable)
	   {
        OnKeyDown( VK_DOWN,1,NULL);
	    Invalidate(0);		
	   }	
}

void CADataEditView::PrepareChartData()
{
/*
        CADataEditDoc *pDoc = GetDocument();
        CPtrArray *l = pDoc->GetLines();
	    ASSERT_VALID(pDoc);

	    CString *line = (CString *) l->GetAt(1);
	    CString FileTypeString = *line;

	    n = l->GetSize();

	    FileTypeCode = FileTypeString.GetAt(0);

    if((!B_PrepareChartData)||(LastEditLine > EditLineNo))
	{
     if(FileTypeCode =='R')
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
	    int VIndex,AIndex,AHIndex/*,T1Index,T2Index*/;
/*
        double DrawMaxVs,DrawMaxAs,DrawMaxAHs;
	    int p;

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
	    if (DrawMaxV < DrawV[i])DrawMaxV = DrawV[i];
	   }
	    if (m_SelectA == TRUE)
		{
	     As = Totals.Mid( 24, 5 );
	     DrawA[i] = atof(As);
	     if (DrawMaxA < DrawA[i])DrawMaxA = DrawA[i];		     
		}		
	    if (m_SelectAH == TRUE)
		{
         AHs = Totals.Mid( 31, 5 );
	     DrawAH[i] = atof(AHs);
	     if (DrawMaxAH < DrawAH[i])DrawMaxAH = DrawAH[i];	     
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

	if(FileTypeCode == 'O')     //NC File PrepareChartData
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
			if (350/(maxXvalue - minXvalue) >= 300/(maxYvalue - minYvalue))
				NcDrawScale = 300/(maxYvalue - minYvalue);
		   else NcDrawScale = 350/(maxXvalue - minXvalue);
				OffsetX = NcDrawScale*(maxXvalue + minXvalue)/2;
				OffsetY = NcDrawScale*(maxYvalue + minYvalue)/2;

	    int o,XIndex,YIndex,X1stBitValue,Y1stBitValue;
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
	}	
        B_PrepareChartData = TRUE;
    }
*/	   
}

void CADataEditView::DrawChartMemDC()
{
		AfxGetApp()->BeginWaitCursor();

		if((DrawXYLine == FALSE)||(LastEditLine > EditLineNo))
		  {
		ReferenceLine();
		  }
        DrawChartFunc();

		AfxGetApp()->EndWaitCursor();
}

void CADataEditView::DrawChartFunc()
{
/*
          CADataEditDoc* pDoc = GetDocument();
		  CPtrArray *l = pDoc->GetLines();
		  ASSERT_VALID(pDoc);

          if(B_PrepareChartData)
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

		  if(LastEditLine > EditLineNo)
		  {
            LastEditLine = 1;
		  }

		  for (int k = LastEditLine; (k < EditLineNo)&&(k <(l->GetSize()-2)) ; k++)
			{						    
			CString *line = (CString *) l->GetAt(k);
            s = *line;
			LastEditLine = EditLineNo;
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
        memDC1.MoveTo(m_vpoX + 130 + (DrawTime-MinTime)*(450.0*DispScaleX*m_XScale)/(Timeapartm*TimeapartmV),m_vpoY+504-(DrawA)*(250/(AapartmA*Aapartm))*DispScaleY*m_YScale);
		b_Break = FALSE;
		}
		memDC1.LineTo(m_vpoX + 130 + (DrawTime-MinTime)*(450.0*DispScaleX*m_XScale)/(Timeapartm*TimeapartmV),m_vpoY+504-(DrawA)*(250/(AapartmA*Aapartm))*DispScaleY*m_YScale);
        NextPoint1:;
		  }
		}

        if(FileTypeCode=='O')          	 //NC File Draw Chart Func
		{
		    AfxGetApp()->BeginWaitCursor();

		    if(LastEditLine > EditLineNo)
			{
                LastEditLine = 2;
				memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);
			}

			for (int k = LastEditLine; k < EditLineNo ; k++)
			{
				LastEditLine = EditLineNo;
				CString *line = (CString *) l->GetAt(k);
				Gs1 = *line;
                Gs2.Empty();
                
	        if((Gs1.Find('O')!=-1) && k==0)
			{
				  NCFileName.Empty();
                for( Ge = Gs1.Find('O'); Ge < Gs1.Find('\r'); Ge++)
				  {
					NCFileName = NCFileName + Gs1.GetAt(Ge);
				  }
//				b_MoveAble = false;
			}
            else
			{
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

				if((Gs1.Find("G92")!=-1)||(Gs1.Find("G00")!=-1))
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
					memDC1.MoveTo(startx * NcDrawScale * NCDrawScale + (175 - OffsetX),-starty * NcDrawScale * NCDrawScale + (175 + OffsetY));
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
					startx = Gx;
					Gs2.Empty();
				 for( Ge = Gs1.Find('Y')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					Gy = (atof(Gs2));
					starty = Gy;
					Gs2.Empty();
					memDC1.LineTo(Gx * NcDrawScale * NCDrawScale + (175 - OffsetX),-Gy * NcDrawScale * NCDrawScale + (175 + OffsetY));
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

				  memDC1.Arc(upx * NcDrawScale * NCDrawScale + (175 - OffsetX),-upy * NcDrawScale * NCDrawScale + (175 + OffsetY),lowx*NcDrawScale * NCDrawScale + (175 - OffsetX),
					         -lowy*NcDrawScale * NCDrawScale + (175 + OffsetY),dstartx*NcDrawScale * NCDrawScale + (175 - OffsetX),
					         -dstarty*NcDrawScale * NCDrawScale + (175 + OffsetY),dendx*NcDrawScale * NCDrawScale + (175 - OffsetX),-dendy*NcDrawScale * NCDrawScale + (175 + OffsetY));
				  memDC1.MoveTo(endx*NcDrawScale * NCDrawScale + (175 - OffsetX),-endy*NcDrawScale * NCDrawScale + (175 + OffsetY));
				  
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
		AfxGetApp()->EndWaitCursor();
		}
	}
*/
}

void CADataEditView::OnViewAttachchart() 
{
//      b_AttachChart = !b_AttachChart;
//	    Invalidate(0);
}

void CADataEditView::OnUpdateViewAttachchart(CCmdUI* pCmdUI) 
{
		pCmdUI->Enable(m_TextEditCopyEnable&&(n<100));
        pCmdUI->SetCheck(b_AttachChart);
}

void CADataEditView::ReferenceLine()               //XY Lines
{
/*
        if(FileTypeCode == 'R')
		{	        
	        CString s;
			int PoxX,PoxY;

			memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);

            int NetX,NetY;

//			if (m_RadioLineType == 1)
//			{
				NetX = 4;
				NetY = 4;
//			}
//			else 
//			{
//				NetX = 480.0*DispScaleX*m_XScale;
//				NetY = 270.0*DispScaleY*m_YScale;
//			}

			memDC1.SetTextColor(XLineColor);
			memDC1.SelectObject(&GridLinePen);

			int w;
            for (w = 0; w < Timeapartm +1; w++)
			{
				PoxX = 450*(DispScaleX*m_XScale*w)/Timeapartm;
			  if(PoxX>=0.0)
			  {
				memDC1.MoveTo(m_vpoX + 130 + PoxX,m_vpoY+315.0*DispScaleY);
				memDC1.LineTo(m_vpoX + 130 + PoxX,m_vpoY+315.0*DispScaleY-NetY);
				
				s.Format("  %4.1f",(TimeapartmV*w));
				memDC1.TextOut(m_vpoX + 105 + PoxX,m_vpoY+323.0*DispScaleY,s);
			  }
			}

            for (w = 0; w <  Aapartm +1; w++)
			{
				PoxY = 250*(DispScaleY*m_YScale*w)/ Aapartm;
			  if(PoxY>=0.0)
			  {
				memDC1.MoveTo(m_vpoX + 130 , m_vpoY +504 - PoxY);
				memDC1.LineTo(m_vpoX + 130 + NetX , m_vpoY +504 - PoxY);
				
				s.Format("  %4.1f",(AapartmA*w));
				memDC1.TextOut(m_vpoX + 80 , m_vpoY +490 - PoxY,s);
			  }
			}

			memDC1.SelectObject(&XLinePen);
            memDC1.MoveTo(563.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+313.0*DispScaleY);
			memDC1.LineTo(570.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+315.0*DispScaleY);
			memDC1.LineTo(563.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+317.0*DispScaleY);

			memDC1.MoveTo(570.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+315.0*DispScaleY);
			memDC1.LineTo(m_vpoX + 130,m_vpoY+315.0*DispScaleY);                            //H.L
			memDC1.LineTo(m_vpoX + 130,m_vpoY+315.0*DispScaleY-270.0*DispScaleY*m_YScale);  //V.L

            memDC1.LineTo(m_vpoX + 128,(m_vpoY+315.0*DispScaleY-270.0*DispScaleY*m_YScale)+17);
            memDC1.LineTo(m_vpoX + 130,m_vpoY+315.0*DispScaleY-270.0*DispScaleY*m_YScale);
			memDC1.LineTo(m_vpoX + 132,(m_vpoY+315.0*DispScaleY-270.0*DispScaleY*m_YScale)+17);

			memDC1.SetTextColor(TitleTextColor);
			memDC1.TextOut (290.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+335.0*DispScaleY,m_TitleText);
			memDC1.TextOut (560.0*DispScaleX*m_XScale+m_vpoX,m_vpoY+295.0*DispScaleY,m_XText);
			memDC1.TextOut (70.0*DispScaleX+m_vpoX,(m_vpoY+315.0*DispScaleY-270.0*DispScaleY*m_YScale)-30,m_YText);
		
			DrawXYLine =TRUE;
		}
		        if(FileTypeCode == 'O')
		{
		}
*/
}

void CADataEditView::OnEditUndo() 
{     
	       CString s;
           int a,b,TotalPasteLine;

	switch(Undocmdcode.GetAt(m_undocount-1))            
    {                           
		   case 1:
           b = EditLineNo;
		   a = UndoEditLineNo.GetAt(m_undocount-1);
           GoToSpecialLine(a+1,b);
           EditString = UndoEditString.GetAt(m_undocount-1);
		   EndEditString =UndoEndEditString.GetAt(m_undocount-1);
		   StringSave();
		   break;

		   case 2:                                        //for "enter" key
           b = EditLineNo;
		   a = UndoEditLineNo.GetAt(m_undocount-1);
           GoToSpecialLine(a+2,b);
		   OnKeyDown(VK_HOME, 1, NULL);
		   OnChar('\b', 1, NULL);
		   break;

		   case 3:                                          //for "\b'
           b = EditLineNo;
		   a = UndoEditLineNo.GetAt(m_undocount-1);
           GoToSpecialLine(a+1,b);
		   EditString = UndoEditString.GetAt(m_undocount-1);
		   EndEditString = UndoEndEditString.GetAt(m_undocount-1);
		   StringSave();
		   OnChar('\r', 1, NULL);
		   break;

		   case 10:                            //For EditCut
           b = EditLineNo;
		   a = UndoEditLineNo.GetAt(m_undocount-1);
           GoToSpecialLine(a+1,b);
           OnKeyDown(VK_HOME, 1, NULL);

           EditPasteString = UndoEditString.GetAt(m_undocount-1);
		   EndEditString = UndoEndEditString.GetAt(m_undocount-1);
		   while(EditPasteString.GetLength()>0)
		   {
			if (EditPasteString.GetAt(0) == '\n')
			{
				CADataEditDoc *pDoc = GetDocument();
		        CPtrArray *l = pDoc->GetLines();

				s += EditPasteString.GetAt(0);
				pDoc->lines->InsertAt(EditLineNo,new CString(s),1);
				StringLoad();
				EndEditString.Empty();
				OnKeyDown(VK_DOWN,1,NULL);
				if(EditPasteString.GetLength()>1)
				{
					EditPasteString = EditPasteString.Right(EditPasteString.GetLength()-1);
				}
				s.Empty();
			}
			s += EditPasteString.GetAt(0);
			EditPasteString = EditPasteString.Right(EditPasteString.GetLength()-1);
		   }
		    if(s != '\n')
			{EditString = EditString + s;
		    StringSave();}
			OnKeyDown(VK_HOME, 1, NULL);
		    Invalidate(FALSE);
		    break;

		    case 11:                            //for EditPaste
            b = EditLineNo;
		    a = UndoEditLineNo.GetAt(m_undocount-1);
            GoToSpecialLine(a+1,b);
            OnKeyDown(VK_HOME, 1, NULL);

			TotalPasteLine = UndoTotalPasteLine.GetAt(m_undocount-1);

			EditString = UndoEditString.GetAt(m_undocount-1);
		    EndEditString = UndoEndEditString.GetAt(m_undocount-1);
            while(TotalPasteLine > 0)
			{
		    DeleteLine();
            TotalPasteLine--;
			}
			break;
		   
			case 12:
			b = EditLineNo;
		    a = UndoEditLineNo.GetAt(m_undocount-1);
            GoToSpecialLine(a+1,b);
			OnEditInsertaline();
			EditString = UndoEditString.GetAt(m_undocount-1);
			EndEditString = UndoEndEditString.GetAt(m_undocount-1);
			StringSave();
			break;

	}

	if(m_undocount>1)
	{
	m_undocount--;	
    Undocmdcode.RemoveAt(m_undocount);
	UndoTotalPasteLine.RemoveAt(m_undocount);
	UndoEditLineNo.RemoveAt(m_undocount);
	UndoEditString.RemoveAt(m_undocount);
    UndoEndEditString.RemoveAt(m_undocount);
	}
	Invalidate(0);
}

void CADataEditView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	        pCmdUI->Enable((m_undocount>1)&&(EditCopyString.IsEmpty()));
}

void CADataEditView::PrepareUndo(int inccount)
{
	       m_undocount = m_undocount + inccount;

	       UndoTotalPasteLine.Add(0);
	       UndoEditLineNo.Add(EditLineNo);
	       UndoEditString.Add(EditString);
           UndoEndEditString.Add(EndEditString);
}

void CADataEditView::OnBUTTONRedrawView() 
{
		   CADataEditDoc* pDoc = GetDocument();

	       pDoc->EditLineNo = EditLineNo;
		   pDoc->LastEditLine = LastEditLine;
           pDoc->QuickDraw = QuickDraw;
		   pDoc->Inch = Inch;
		   pDoc->m_TextEditCopyEnable = TRUE;
		   pDoc->UpdateAllViews(this);
	       Invalidate(0);
}

void CADataEditView::OnUpdateBUTTONRedrawView(CCmdUI* pCmdUI) 
{
	       pCmdUI->Enable(m_TextEditCopyEnable);
}

void CADataEditView::OnViewInch() 
{
	
           Inch ^= TRUE;

//	       memDC1.PatBlt(0,0,maxX,maxY,WHITENESS);
	       LastEditLine = 0;
//	       DrawChartMemDC();	
	       Invalidate(0);
		   
}

void CADataEditView::OnUpdateViewInch(CCmdUI* pCmdUI) 
{
           pCmdUI->SetCheck(Inch);	
}

void CADataEditView::GoToSpecialLine(int SpecialLine, int StartLine)
{
	         CRect clientRect;
	         GetClientRect(&clientRect);
//	    if(SpecialLine != StartLine)
		{
				while( SpecialLine - StartLine > (clientRect.Height() / lHeight))
				{
					OnKeyDown(VK_NEXT,1,NULL);
					SpecialLine = SpecialLine - (clientRect.Height() / lHeight);
				}
				while( StartLine - SpecialLine > (clientRect.Height() / lHeight))
				{
					OnKeyDown(VK_PRIOR,1,NULL);
					SpecialLine = SpecialLine + (clientRect.Height() / lHeight);
				}
				while(StartLine < SpecialLine - 1)
				{
					OnKeyDown(VK_DOWN,1,NULL);
					SpecialLine = SpecialLine - 1;
				}
				while(StartLine > SpecialLine - 1)
				{
					OnKeyDown(VK_UP,1,NULL);
					SpecialLine = SpecialLine + 1;
				}
		}
}

void CADataEditView::AdjScrollRange()
{
		   CADataEditDoc* pDoc = GetDocument();
		   CPtrArray *l = pDoc->GetLines();
		   ASSERT_VALID(pDoc);
		
	       SetScrollRange(SB_VERT, 0, l->GetSize());
		   SetScrollPos(SB_VERT, EditLineNo);
	       SetScrollRange(SB_HORZ, 0, pDoc->GetMaxLineLength());
	       SetScrollPos(SB_HORZ, 0);
}

void CADataEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	CView::OnLButtonDblClk(nFlags, point);
}

void CADataEditView::GotoFileTop()
{
			CADataEditDoc *pDoc = GetDocument();
			CPtrArray *l = pDoc->GetLines();
    
			if(l->GetSize() <= 1){AddEmptyLine();}

			CRect clientRect;
			GetClientRect(&clientRect);

			currentLine = 0;
			EditLineNo = 0;
			CursorY = 0;
			StringLoad();
			
			KeepCursorXPos(CursorX);

			SetScrollPos(SB_VERT, EditLineNo);

			Invalidate(0);
}

void CADataEditView::GotoFileBottom()
{
	int i;
			CADataEditDoc *pDoc = GetDocument();
			CPtrArray *l = pDoc->GetLines();
    
			if(l->GetSize() <= 1){AddEmptyLine();} 
	
			CRect clientRect;
			GetClientRect(&clientRect);
	
			i = clientRect.Height()/lHeight;

			currentLine = l->GetSize()-1-i;
			EditLineNo = currentLine;
			CursorY = 0;
			StringLoad();
			
			KeepCursorXPos(CursorX);
		for(i;i>0;i--)
		{
			OnKeyDown(VK_DOWN,1,NULL);
		}
			SetScrollPos(SB_VERT, EditLineNo);

			Invalidate(0);
}

void CADataEditView::OnEditGotofilebottom() 
{
			GotoFileBottom();
}

void CADataEditView::OnUpdateEditGotofilebottom(CCmdUI* pCmdUI) 
{
            pCmdUI->Enable(m_TextEditCopyEnable);	
}

void CADataEditView::OnEditGotofiletop() 
{
			GotoFileTop();	
}

void CADataEditView::OnUpdateEditGotofiletop(CCmdUI* pCmdUI) 
{
            pCmdUI->Enable(m_TextEditCopyEnable);	
}

void CADataEditView::OnEditDeletealine() 
{
			PrepareUndo(1);
		    Undocmdcode.Add(12);
			DeleteLine();
}

void CADataEditView::OnUpdateEditDeletealine(CCmdUI* pCmdUI) 
{
            pCmdUI->Enable(m_TextEditCopyEnable);	
}
