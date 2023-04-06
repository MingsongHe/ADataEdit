#if !defined(AFX_ACHARTEDITVIEW_H__EE42D7C3_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
#define AFX_ACHARTEDITVIEW_H__EE42D7C3_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AChartEditView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAChartEditView view

class CAChartEditView : public CView
{
protected:
	CAChartEditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAChartEditView)

protected:

	CPen ALinePen,VLinePen,AHLinePen,T1LinePen,T2LinePen,XLinePen,GridLinePen;
    CPen *oldPen;

	double	m_XScale;
	double	m_YScale;
	BOOL m_SelectV;
	BOOL m_SelectA;
	BOOL m_SelectAH;
	BOOL m_SelectT1;
	BOOL m_SelectT2;
	BOOL b_Break;
    CString	m_TitleText;
	CString	m_XText;
	CString	m_YText;
	int	m_RadioLineType;		  
    CString EditPasteString,EditCopyString;
	CString MenuID;
	CFont *ourFont;
	int cWidth,lHeight,currentLine,margin,CursorY,CursorX;
	CRect printerRect;
	BOOL m_TextEditPasteEnable,m_TextEditCopyEnable;
	
	int EditLineNo,m_SelectLine,m_SelectLine2,LastEditLine;
	int m_GoToLineNo;
	CString EditString,EndEditString;

	int saveCurrentLine,saveLHeight, saveCWidth;

	CDC memDC1;
	BOOL PreparememDC,PrepareChartData,DrawXYLine;
	int maxX,maxY;
	double DispScaleX;
	double DispScaleY;
	
	BOOL   m_vpoXable,m_vpoYable;
    int m_vpoX,m_vpoY,m_vpeX,m_vpeY;
	double DrawV[10000],DrawA[10000],DrawAH[10000],DrawT1[10000],DrawT2[10000];
	double MinTime,MaxTime;
    double TimeapartmV,VapartmV,AapartmA,AHapartmAH;
    int Timeapartm,Vapartm,Aapartm,AHapartm,n,k2;
	int OffsetX,OffsetY;

	bool fCapture,DataCapture,fBoxing,DataBoxing,b_FindCapture,m_HandMoveAble,QuickDraw,NCDrawRectCapture;
	CPoint ptAnchor,ptAnchor2, ptOld;
	int MPointX,MPointY;
	
	CDC dcMem2;

	unsigned long VLineColor,ALineColor,AHLineColor,T1LineColor,T2LineColor;
	unsigned long TitleTextColor,XTextColor,YTextColor;
	unsigned long XLineColor,YLineColor,GridLineColor;
    unsigned long BackGroundColor,TextColor,LineNoColor;
	bool b_LineNo; 

//	CString m_InputString,m_OutputString;
	int OutputLinei;
	int m_Communication;

	CString m_Combo1Text;
	int i_ProgressStep;

	CMapStringToString map1;
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

	CString FileTypeCode;

//	int OffsetX,OffsetY;
	int Ge;
	double Gg,Gh,GP16,GT,Gx,Gy,upx,upy,lowx,lowy,startx,starty,endx,endy,
		  dstartx,dstarty,dendx,dendy,Gi,Gj,centx,centy,Circler,Angle;
	CString Gs1,Gs2,G4,G5,NCFileName;
	CString s_startx,s_starty,s_centx,s_centy,s_Circler,s_Diameter,s_Angle,s_GT,s_R;

	BOOL Inch;
	int XMarkQty,YMarkQty,XIndex,YIndex;
	float maxXvalue,minXvalue,maxYvalue,minYvalue;
    double XMarkValue,YMarkValue,NCDrawScale,NcDrawScale;
	bool /*b_MoveAble,*/b_PanRealtimeAble;
   
// Attributes
public:

// Operations
public:
	void OnProperties();
	CADataEditDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAChartEditView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAChartEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void DrawChartMemDC();
	void PrepareMemDC();

	afx_msg void OnUpdateCaretPos(CCmdUI* pCmdUI);  
	//{{AFX_MSG(CAChartEditView)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnChartSetting();
	afx_msg void OnChartEditCopy();
	afx_msg void OnUpdateChartEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnChartEditPaste();
	afx_msg void OnChartEditCut();
	afx_msg void OnUpdateChartEditCut(CCmdUI* pCmdUI);
	afx_msg void OnChartSaveas();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBUTTONZoomIn();
	afx_msg void OnUpdateBUTTONZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONZoomOut();
	afx_msg void OnUpdateBUTTONZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONZoomAll();
	afx_msg void OnUpdateBUTTONZoomAll(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONChartToDown();
	afx_msg void OnBUTTONChartToUp();
	afx_msg void OnBUTTONChartToL();
	afx_msg void OnUpdateBUTTONChartToL(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBUTTONChartToDown(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBUTTONChartToUp(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONChartToR();
	afx_msg void OnUpdateBUTTONChartToR(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONZoomInW();
	afx_msg void OnUpdateBUTTONZoomInW(CCmdUI* pCmdUI);
	afx_msg void OnButton32820();
	afx_msg void OnUpdateButton32820(CCmdUI* pCmdUI);
	afx_msg void OnButtonquickdraw();
	afx_msg void OnUpdateButtonquickdraw(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnPrepareChartData();
	void DrawChartFunc();
	COleDataSource* SaveDib();
	BOOL DoPasteDib(COleDataObject* pDataObject);
};

#ifndef _DEBUG  // debug version in ADataEditView.cpp
inline CADataEditDoc* CADataEditView::GetDocument()
   { return (CADataEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACHARTEDITVIEW_H__EE42D7C3_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
