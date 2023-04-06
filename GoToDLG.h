#if !defined(AFX_GOTODLG_H__A3D7DAC0_0627_11D3_8073_BA720B186322__INCLUDED_)
#define AFX_GOTODLG_H__A3D7DAC0_0627_11D3_8073_BA720B186322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoToDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGoToDLG dialog

class CGoToDLG : public CDialog
{
// Construction
public:
	CGoToDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGoToDLG)
	enum { IDD = IDD_GOTODIALOG };
	int		m_GoToLineNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoToDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGoToDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTODLG_H__A3D7DAC0_0627_11D3_8073_BA720B186322__INCLUDED_)
