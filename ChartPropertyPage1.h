// ChartPropertyPage1.h : header file
//

#ifndef __CHARTPROPERTYPAGE1_H__
#define __CHARTPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage1 dialog

class CChartPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CChartPropertyPage1)

// Construction
public:
	CChartPropertyPage1();
	~CChartPropertyPage1();

	unsigned long VLineColor,ALineColor,AHLineColor,T1LineColor,T2LineColor;
// Dialog Data
	//{{AFX_DATA(CChartPropertyPage1)
	enum { IDD = IDD_PROPPAGE1 };
	BOOL	m_SelectV;
	BOOL	m_SelectA;
	BOOL	m_SelectAH;
	double	m_XScale;
	double	m_YScale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChartPropertyPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChartPropertyPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage2 dialog

class CChartPropertyPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CChartPropertyPage2)

// Construction
public:
	CChartPropertyPage2();
	~CChartPropertyPage2();

	unsigned long TitleTextColor,XTextColor,YTextColor;

// Dialog Data
	//{{AFX_DATA(CChartPropertyPage2)
	enum { IDD = IDD_PROPPAGE2 };
	CString	m_TitleText;
	CString	m_XText;
	CString	m_YText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChartPropertyPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChartPropertyPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage3 dialog

class CChartPropertyPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CChartPropertyPage3)

// Construction
public:
	CChartPropertyPage3();
	~CChartPropertyPage3();
	unsigned long XLineColor,YLineColor,GridLineColor;
// Dialog Data
	//{{AFX_DATA(CChartPropertyPage3)
	enum { IDD = IDD_PROPPAGE3 };
	int		m_Radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChartPropertyPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChartPropertyPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CChartPropertyPage4 dialog

class CChartPropertyPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CChartPropertyPage4)

// Construction
public:
	CChartPropertyPage4();
	~CChartPropertyPage4();

// Dialog Data
	//{{AFX_DATA(CChartPropertyPage4)
	enum { IDD = IDD_PROPPAGE4 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChartPropertyPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChartPropertyPage4)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __CHARTPROPERTYPAGE1_H__
