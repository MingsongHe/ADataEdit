// ChartPropertyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ChartPropertyPage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChartPropertyPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CChartPropertyPage2, CPropertyPage)
IMPLEMENT_DYNCREATE(CChartPropertyPage3, CPropertyPage)
IMPLEMENT_DYNCREATE(CChartPropertyPage4, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage1 property page

CChartPropertyPage1::CChartPropertyPage1() : CPropertyPage(CChartPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CChartPropertyPage1)
	m_SelectV = FALSE;
	m_SelectA = FALSE;
	m_SelectAH = FALSE;
	m_XScale = 0.0;
	m_YScale = 0.0;
	//}}AFX_DATA_INIT
}

CChartPropertyPage1::~CChartPropertyPage1()
{
}

void CChartPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartPropertyPage1)
	DDX_Check(pDX, IDC_CHECK1, m_SelectV);
	DDX_Check(pDX, IDC_CHECK2, m_SelectA);
	DDX_Check(pDX, IDC_CHECK3, m_SelectAH);
	DDX_Text(pDX, IDC_EDIT1, m_XScale);
	DDV_MinMaxDouble(pDX, m_XScale, 0.2, 2000.);
	DDX_Text(pDX, IDC_EDIT2, m_YScale);
	DDV_MinMaxDouble(pDX, m_YScale, 0.2, 2000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartPropertyPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CChartPropertyPage1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, OnDblclkList4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage2 property page

CChartPropertyPage2::CChartPropertyPage2() : CPropertyPage(CChartPropertyPage2::IDD)
{
	//{{AFX_DATA_INIT(CChartPropertyPage2)
	m_TitleText = _T("");
	m_XText = _T("");
	m_YText = _T("");
	//}}AFX_DATA_INIT
}

CChartPropertyPage2::~CChartPropertyPage2()
{
}

void CChartPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartPropertyPage2)
	DDX_Text(pDX, IDC_EDIT1, m_TitleText);
	DDV_MaxChars(pDX, m_TitleText, 40);
	DDX_Text(pDX, IDC_EDIT7, m_XText);
	DDV_MaxChars(pDX, m_XText, 40);
	DDX_Text(pDX, IDC_EDIT8, m_YText);
	DDV_MaxChars(pDX, m_YText, 40);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartPropertyPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CChartPropertyPage2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, OnDblclkList4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage3 property page

CChartPropertyPage3::CChartPropertyPage3() : CPropertyPage(CChartPropertyPage3::IDD)
{
	//{{AFX_DATA_INIT(CChartPropertyPage3)
	m_Radio = -1;
	//}}AFX_DATA_INIT
}

CChartPropertyPage3::~CChartPropertyPage3()
{
}

void CChartPropertyPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartPropertyPage3)
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartPropertyPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CChartPropertyPage3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage4 property page

CChartPropertyPage4::CChartPropertyPage4() : CPropertyPage(CChartPropertyPage4::IDD)
{
	//{{AFX_DATA_INIT(CChartPropertyPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CChartPropertyPage4::~CChartPropertyPage4()
{
}

void CChartPropertyPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartPropertyPage4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartPropertyPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CChartPropertyPage4)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CChartPropertyPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    CListCtrl* m_List2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	m_List2->SetBkColor(VLineColor);

	CListCtrl* m_List3 = (CListCtrl*)GetDlgItem(IDC_LIST3);
	m_List3->SetBkColor(ALineColor);

	CListCtrl* m_List4 = (CListCtrl*)GetDlgItem(IDC_LIST4);
	m_List4->SetBkColor(AHLineColor);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartPropertyPage1::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 VLineColor=dlg.GetColor();
	 }
	 CListCtrl* m_List2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	 m_List2->SetBkColor(VLineColor);
     m_List2->Invalidate();		
	*pResult = 0;
}

void CChartPropertyPage1::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 ALineColor=dlg.GetColor();
	 }
	 CListCtrl* m_List3 = (CListCtrl*)GetDlgItem(IDC_LIST3);
	 m_List3->SetBkColor(ALineColor);
     m_List3->Invalidate();		
	*pResult = 0;
}

void CChartPropertyPage1::OnDblclkList4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 AHLineColor=dlg.GetColor();
	 }
	 CListCtrl* m_List4 = (CListCtrl*)GetDlgItem(IDC_LIST4);
	 m_List4->SetBkColor(AHLineColor);
     m_List4->Invalidate();		
	*pResult = 0;
}

BOOL CChartPropertyPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

    CListCtrl* m_List1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	m_List1->SetBkColor(TitleTextColor);
	CListCtrl* m_List4 = (CListCtrl*)GetDlgItem(IDC_LIST4);
	m_List4->SetBkColor(XTextColor);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartPropertyPage2::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 TitleTextColor=dlg.GetColor();
	 }
	 CListCtrl* m_List1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	 m_List1->SetBkColor(TitleTextColor);
     m_List1->Invalidate();		
	*pResult = 0;
}

void CChartPropertyPage2::OnDblclkList4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 XTextColor=dlg.GetColor();
	 }
	 CListCtrl* m_List4 = (CListCtrl*)GetDlgItem(IDC_LIST4);
	 m_List4->SetBkColor(XTextColor);
     m_List4->Invalidate();	
	*pResult = 0;
}

BOOL CChartPropertyPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    CListCtrl* m_List1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	m_List1->SetBkColor(XLineColor);

	CListCtrl* m_List2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	m_List2->SetBkColor(GridLineColor);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartPropertyPage3::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 XLineColor=dlg.GetColor();
	 }
	 CListCtrl* m_List1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	 m_List1->SetBkColor(XLineColor);
     m_List1->Invalidate();	
	*pResult = 0;
}

void CChartPropertyPage3::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CColorDialog dlg;
	 if(dlg.DoModal() == IDOK)
	 {
	 GridLineColor=dlg.GetColor();
	 }
	 CListCtrl* m_List2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	 m_List2->SetBkColor(GridLineColor);
     m_List2->Invalidate();	
	*pResult = 0;
}
