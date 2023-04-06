// ChartPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ChartPropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartPropertySheet

IMPLEMENT_DYNAMIC(CChartPropertySheet, CPropertySheet)

CChartPropertySheet::CChartPropertySheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);
}

CChartPropertySheet::~CChartPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CChartPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CChartPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChartPropertySheet message handlers


