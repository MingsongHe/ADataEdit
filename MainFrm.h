// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EE42D7B6_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
#define AFX_MAINFRM_H__EE42D7B6_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IDC_FINCOMBO 100
      class CComplexToolBar : public CToolBar
      {
	  public:
      CComboBox m_combobox1;

      BOOL CreateComboBox(int nIndex);
      }; 

#define ID_INDICATOR_PROGRESS 100
      class CComplexStatusBar : public CStatusBar
      {
      public:
      CProgressCtrl m_Progress;
      int m_nProgressPane;
      BOOL CreateProgressCtrl(int nPane);

      afx_msg void OnSize(UINT nType, int cx, int cy);
      DECLARE_MESSAGE_MAP()
      };

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
    CComplexStatusBar m_wndStatusBar;
	CComplexToolBar m_wndToolBar;

protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nDatePaneNo;
	int m_nTimePaneNo;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
//	CStatusBar  m_wndStatusBar;       //Becuse add CComplexStatusBar
//	CToolBar    m_wndToolBar;         //Becuse add CComplexToolBar

// Generated message map functions
protected:
	CDialogBar m_wndPapDialogBar;
	afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EE42D7B6_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
