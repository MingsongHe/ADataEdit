//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMMUNICATIONWORKING_H__9A2EDF41_143D_11D3_8073_F6FDB9CE3A20__INCLUDED_)
#define AFX_COMMUNICATIONWORKING_H__9A2EDF41_143D_11D3_8073_F6FDB9CE3A20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommunicationWorking.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommunicationWorking dialog
#define WM_GOODBYE WM_USER + 116  //skip over the first five message

class CCommunicationWorking : public CDialog
{
// Construction
private:
	CView* m_pView;
public:
	CCommunicationWorking(CView* pView);//Using the CView class 
	                              //rather than the CddyV2View
	BOOL Create();                //allow the dialog class to

public:
	void ReadInput();
	void Input();
	void Output();

	CCommunicationWorking(CWnd* pParent = NULL);   // standard constructor

    CString m_InputString,m_OutputString,str;;
	VARIANT m_input1;
    COleVariant m_input2;
// Dialog Data
	//{{AFX_DATA(CCommunicationWorking)
	enum { IDD = IDD_COMMWORKONG };
	CMSComm	m_Comm1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunicationWorking)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommunicationWorking)
	afx_msg void OnOnCommMscomm1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMUNICATIONWORKING_H__9A2EDF41_143D_11D3_8073_F6FDB9CE3A20__INCLUDED_)
