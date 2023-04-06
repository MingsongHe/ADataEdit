// GoToDLG.cpp : implementation file
//

#include "stdafx.h"
#include "ADataEdit.h"
#include "GoToDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoToDLG dialog


CGoToDLG::CGoToDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGoToDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoToDLG)
	m_GoToLineNo = 1;
	//}}AFX_DATA_INIT
}


void CGoToDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoToDLG)
	DDX_Text(pDX, IDC_EDIT1, m_GoToLineNo);
	DDV_MinMaxInt(pDX, m_GoToLineNo, 1, 99999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGoToDLG, CDialog)
	//{{AFX_MSG_MAP(CGoToDLG)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoToDLG message handlers


BOOL CGoToDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData(false);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGoToDLG::OnOK() 
{		
}

void CGoToDLG::OnOk() 
{
	 CDialog::OnOK();
}

HBRUSH CGoToDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
/*
	CBrush m_hYellowBrush,m_hRedBrush;
		m_hYellowBrush.CreateSolidBrush(RGB(255, 255, 0));
		m_hRedBrush.CreateSolidBrush(RGB(255, 0, 0));

	if (nCtlColor == CTLCOLOR_EDIT) {
        pDC->SetBkColor(RGB(255, 255, 0));  // yellow
		pDC->SetTextColor(RGB(255, 0, 0));  // red
        return m_hYellowBrush;
		return m_hRedBrush;
		}
	if (nCtlColor == CTLCOLOR_STATIC) {
        pDC->SetBkColor(RGB(255, 0, 0));  // red
        return m_hRedBrush;
		}
    if (nCtlColor == CTLCOLOR_DLG) {
        pDC->SetBkColor(RGB(255, 255, 0));    // red
        return m_hRedBrush;
		}
*/	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CGoToDLG::OnPaint() 
{
	/*
	CPaintDC dc(this); // device context for painting
	dc.MoveTo(0,0);
	dc.LineTo(20,30);
	*/
//	CBrush m_hGreenBrush;
//	m_hGreenBrush.CreateSolidBrush(RGB(0, 255, 0));

//    CWnd* pWnd = GetDlgItem(IDC_EDIT1);     // IDC_STATIC1 specified
                                              //  in the dialog editor
//    CDC* pControlDC = pWnd->GetDC();

//    pWnd->Invalidate();
//    pWnd->UpdateWindow();
//    pControlDC->MoveTo(0,0);
//    pControlDC->LineTo(20,30);     
//	  pControlDC->SelectObject(m_hGreenBrush);
//    pControlDC->Rectangle(0, 0, 20, 20);      
//    pWnd->ReleaseDC(pControlDC);
	
	// Do not call CDialog::OnPaint() for painting messages
}
