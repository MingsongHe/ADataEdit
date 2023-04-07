// TextColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADataEdit.h"
#include "TextColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextColorDlg dialog


CTextColorDlg::CTextColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextColorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextColorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextColorDlg, CDialog)
	//{{AFX_MSG_MAP(CTextColorDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	ON_BN_CLICKED(IDC_OK, OnClickOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextColorDlg message handlers

BOOL CTextColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CListCtrl* m_List1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	m_List1->SetBkColor(BackGroundColor);

	CListCtrl* m_List2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	m_List2->SetBkColor(TextColor);

	CListCtrl* m_List3 = (CListCtrl*)GetDlgItem(IDC_LIST3);
	m_List3->SetBkColor(LineNoColor);
//	UpdateData(0);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTextColorDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
     CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 BackGroundColor=dlg.GetColor();
	 }
	 CListCtrl* m_List1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	 m_List1->SetBkColor(BackGroundColor);
     m_List1->Invalidate();	
	
	*pResult = 0;
}

void CTextColorDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 TextColor=dlg.GetColor();
	 }
	 CListCtrl* m_List2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	 m_List2->SetBkColor(TextColor);
     m_List2->Invalidate();		
	*pResult = 0;
}

void CTextColorDlg::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 LineNoColor=dlg.GetColor();
	 }
	 CListCtrl* m_List3 = (CListCtrl*)GetDlgItem(IDC_LIST3);
	 m_List3->SetBkColor(LineNoColor);
     m_List3->Invalidate();		
	*pResult = 0;
}

void CTextColorDlg::OnOK() 
{
     
}

void CTextColorDlg::OnClickOk() 
{
	 UpdateData(1);		
	 CDialog::OnOK();
}
