#if !defined(AFX_TRANSMISSIOMCONFIGDLG_H__A8D30DE0_BF4C_11D3_A676_84594ED49D43__INCLUDED_)
#define AFX_TRANSMISSIOMCONFIGDLG_H__A8D30DE0_BF4C_11D3_A676_84594ED49D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransmissiomConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransmissiomConfigDlg dialog

class CTransmissiomConfigDlg : public CDialog
{
// Construction
public:
	CTransmissiomConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransmissiomConfigDlg)
	enum { IDD = IDD_ConfigDevice };
	CString	m_BandRate;
	CString	m_Parity;
	CString	m_WordLength;
	CString	m_StopBits;
	CString	m_CodeType;
	CString	m_ComPortNo;
	CString	m_AutoXonXoff;
	CString	m_InputControlMode;
	CString	m_OutputControlMode;
	CString	m_InputStartString;
	CString	m_InputEndString;
	CString	m_OutputStartString;
	CString	m_OutputEndString;
	int		m_OutputSendDelay;
	int		m_InputTimeOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransmissiomConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransmissiomConfigDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSMISSIOMCONFIGDLG_H__A8D30DE0_BF4C_11D3_A676_84594ED49D43__INCLUDED_)
