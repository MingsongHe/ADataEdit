// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ADataEdit.h"

#include "ADataEditDoc.h"
#include "ADataEditView.h"
#include "AChartEditView.h"

#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_PAPDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_PAPDIALOGBAR, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_CARET,     // carte  position  pane
	
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

		CRect rect;
//设置组合框的宽度，四个参数依次为控件在工具条中的索引号、ID号、风格、宽度
        m_wndToolBar.SetButtonInfo(9, IDC_COMBOX, TBBS_SEPARATOR, 160 );
//得到组合框的位置
        m_wndToolBar.GetItemRect(9, &rect);
//设置组合框的高度
        rect.bottom += 100; //COMBO HEIGHT;
//创建组合框，四个参数依次为窗口风格、组合框位置、父窗口、ID号
      if(!m_wndToolBar.m_combobox1.Create 
        (CBS_DROPDOWN|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL ,rect, &m_wndToolBar, 
         IDC_COMBOX))
        return -1;
//在组合框中加入字符串

      m_wndToolBar.m_combobox1.AddString("NULL");


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	    m_wndStatusBar.CreateProgressCtrl(1); //在第二个窗格创建进度条
 
        m_wndStatusBar.m_Progress.SetRange(0,100);
		m_wndStatusBar.m_Progress.SetStep(2);
        m_wndStatusBar.m_Progress.SetPos(0);

	// CG: The following block was inserted by 'Status Bar' component.//For date and time
	{
		// Find out the size of the static variable 'indicators' defined
		// by AppWizard and copy it
		int nOrigSize = sizeof(indicators) / sizeof(UINT);

		UINT* pIndicators = new UINT[nOrigSize + 2];
		memcpy(pIndicators, indicators, sizeof(indicators));

		// Call the Status Bar Component's status bar creation function
		if (!InitStatusBar(pIndicators, nOrigSize, 60))
		{
			TRACE0("Failed to initialize Status Bar\n");
			return -1;
		}
		delete[] pIndicators;
	}

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "Pap Dialog Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_PAPDIALOGBAR
	//   5. Assign the item a Caption: Pap Dialog Bar

	// TODO: Change the value of CG_ID_VIEW_PAPDIALOGBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndPapDialogBar
		if (!m_wndPapDialogBar.Create(this, CG_IDD_PAPDIALOGBAR,
			CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_PAPDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndPapDialogBar\n");
			return -1;		// fail to create
		}

		m_wndPapDialogBar.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndPapDialogBar);

	}

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

      BEGIN_MESSAGE_MAP(CComplexStatusBar, CStatusBar)
      ON_WM_SIZE()
      END_MESSAGE_MAP()

      //参数nPane是窗格的索引，函数将在该窗格内创建进度条控件
 BOOL CComplexStatusBar::CreateProgressCtrl(int nPane)
      {
      if(m_Progress.GetSafeHwnd()) //防止重复创建
      return FALSE;

      //设置该窗格的宽度为200
      SetPaneInfo(nPane,GetItemID(nPane),SBPS_NORMAL,200);
      CRect rect(0,0,1,1);
      if(!m_Progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect,this,
      ID_INDICATOR_PROGRESS))
      return FALSE;
      m_nProgressPane=nPane;
      return TRUE;
      }

 void CComplexStatusBar::OnSize(UINT nType, int cx, int cy) 
      {
      CStatusBar::OnSize(nType, cx, cy);
      if(m_Progress.GetSafeHwnd()==NULL) return;

      CRect rect;
      GetItemRect(m_nProgressPane,&rect);
      m_Progress.MoveWindow(rect); //调整控件的位置和尺寸
      }

//BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
/*	CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,               // TODO: adjust the number of rows, columns
		CSize(10, 10),      // TODO: adjust the minimum pane size
		pContext);
}
*/

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
    VERIFY(m_wndSplitter.CreateStatic(this, 1, 2));
    VERIFY(m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CADataEditView),
                                    CSize(330, 768), pContext));
    VERIFY(m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CAChartEditView),
                                    CSize(100, 768), pContext));
    return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateDate(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strDate = time.Format(_T("%x"));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strDate);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current date
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nDatePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nDatePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strDate);
	pCmdUI->Enable(TRUE);

}

void CMainFrame::OnUpdateTime(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%X"));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strTime);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current time
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nTimePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nTimePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strTime);
	pCmdUI->Enable(TRUE);

}

BOOL CMainFrame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Create an index for the DATE pane
	m_nDatePaneNo = nSize++;
	pIndicators[m_nDatePaneNo] = ID_INDICATOR_DATE;
	// Create an index for the TIME pane
	m_nTimePaneNo = nSize++;
	nSeconds = 1;
	pIndicators[m_nTimePaneNo] = ID_INDICATOR_TIME;

	// TODO: Select an appropriate time interval for updating
	// the status bar when idling.
	m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

	return m_wndStatusBar.SetIndicators(pIndicators, nSize);
}

