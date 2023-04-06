#if !defined(AFX_INSERTFILEDIALOG_H__01B392E0_FF09_11D2_8073_D83209FD3422__INCLUDED_)
#define AFX_INSERTFILEDIALOG_H__01B392E0_FF09_11D2_8073_D83209FD3422__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertFileDialog dialog

class CInsertFileDialog : public CFileDialog
{
public:
	CString m_strFilename;
// Construction
public:
	CInsertFileDialog(/*CWnd* pParent = NULL);   // standard constructor*/
                      BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		              LPCTSTR lpszDefExt = NULL,
		              LPCTSTR lpszFileName = NULL,
		              DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		              LPCTSTR lpszFilter = NULL,
		              CWnd* pParentWnd = NULL);
// Dialog Data
	//{{AFX_DATA(CInsertFileDialog)
	enum { IDD = IDD_INSERTFILE };
	BOOL	m_Detail;
	float	m_DetailValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertFileDialog)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void LoadDataFile();

	// Generated message map functions
	//{{AFX_MSG(CInsertFileDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButton1();
	afx_msg void OnCheck2();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DraftMemDC();
	void PerpareDraftData();
	BOOL PreparememDC;

	CPen RLinePen,OLinePen;

	CPtrArray *lines;
	CString FileTypeCode;

	double DrawA[10000];
	double MinTime,MaxTime;
	double Timeapartm,TimeapartmV,AapartmA;
    int Aapartm;
	double	m_XScale;
	double	m_YScale;

	int OffsetX,OffsetY;
	int Ge,n;
	double Gg,Gh,Gx,Gy,upx,upy,lowx,lowy,startx,starty,endx,endy,
		  dstartx,dstarty,dendx,dendy,Gi,Gj,centx,centy,Circler;
	CString Gs1,Gs2,LastFileName;
//	CString s_startx,s_starty,s_centx,s_centy,s_Circler,s_Diameter,s_GT,s_R;

	float maxXvalue,minXvalue,maxYvalue,minYvalue;
    double XMarkValue,YMarkValue,NCDrawScale,NcDrawScale;

	void PrepareMemDC();
	CPtrArray *GetLines()	{ return lines; }
	CDC memDC1;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTFILEDIALOG_H__01B392E0_FF09_11D2_8073_D83209FD3422__INCLUDED_)
