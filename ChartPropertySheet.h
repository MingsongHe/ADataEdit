// ChartPropertySheet.h : header file
//
// This class defines custom modal property sheet 
// CChartPropertySheet.
 
#ifndef __CHARTPROPERTYSHEET_H__
#define __CHARTPROPERTYSHEET_H__

#include "ChartPropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CChartPropertySheet

class CChartPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CChartPropertySheet)

// Construction
public:
	CChartPropertySheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CChartPropertyPage1 m_Page1;
	CChartPropertyPage2 m_Page2;
	CChartPropertyPage3 m_Page3;
	CChartPropertyPage4 m_Page4;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChartPropertySheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CChartPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __CHARTPROPERTYSHEET_H__
