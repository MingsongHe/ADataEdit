#if !defined(AFX_TEXTCOLORDLG_H__F8EA1AA0_09EC_11D3_8073_B05BA152C323__INCLUDED_)
#define AFX_TEXTCOLORDLG_H__F8EA1AA0_09EC_11D3_8073_B05BA152C323__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextColorDlg dialog

class CTextColorDlg : public CDialog
{
// Construction
public:
	CTextColorDlg(CWnd* pParent = NULL);   // standard constructor
    unsigned long BackGroundColor,TextColor,LineNoColor;

// Dialog Data
	//{{AFX_DATA(CTextColorDlg)
	enum { IDD = IDD_TextColorDlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextColorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnClickOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTCOLORDLG_H__F8EA1AA0_09EC_11D3_8073_B05BA152C323__INCLUDED_)
