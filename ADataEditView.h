// ADataEditView.h : interface of the CADataEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADATAEDITVIEW_H__EE42D7BA_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
#define AFX_ADATAEDITVIEW_H__EE42D7BA_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_

#define SETFORMATETC(fe, cf, asp, td, med, li)   \
	((fe).cfFormat=cf, \
	 (fe).dwAspect=asp, \
	 (fe).ptd=td, \
	 (fe).tymed=med, \
	 (fe).lindex=li)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommunicationWorking;

class CADataEditView : public CView
{
private:
	CCommunicationWorking* m_pDlg;

protected: // create from serialization only
	CADataEditView();
	DECLARE_DYNCREATE(CADataEditView)
/*
    struct m_undo
	{
    CString EditString;
	CString EndEditString;
    int EditLineNo;
	int TotalPasteLine;
	int CursorX;
	int CursorY;
	int cmdcode;
	};

	struct m_undo undo[500];
*/
    CUIntArray Undocmdcode;
	CUIntArray UndoTotalPasteLine;
	CUIntArray UndoEditLineNo;
	CStringArray UndoEditString;
    CStringArray UndoEndEditString;

	int m_undocount;

    CPen ALinePen,VLinePen,AHLinePen,T1LinePen,T2LinePen,XLinePen,GridLinePen;

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
	
	int EditLineNo,m_SelectLine,m_SelectLine2,LastEditLine/*,TotalPasteLine*/;
	int m_GoToLineNo;
	CString EditString,EndEditString;

	int saveCurrentLine,saveLHeight, saveCWidth;

	CDC memDC0/*,memDC1,memDC2*/;
	BOOL PreparememDC,B_PrepareChartData,DrawXYLine;
	int maxX,maxY,n;

	bool fCapture,DataCapture,fBoxing,b_FindCapture,QuickDraw;
	CPoint ptAnchor,ptAnchor2, ptOld;

	unsigned long VLineColor,ALineColor,AHLineColor,T1LineColor,T2LineColor;
	unsigned long TitleTextColor,XTextColor,YTextColor;
	unsigned long XLineColor,YLineColor,GridLineColor;
    unsigned long BackGroundColor,TextColor,LineNoColor;
	BOOL b_LineNo,b_AttachChart; 

	CString m_InputString,m_OutputString;
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

//	BOOL   m_vpoXable,m_vpoYable;
//    int m_vpoX,m_vpoY,m_vpeX,m_vpeY;
//	double DrawV[10000],DrawA[10000],DrawAH[10000],DrawT1[10000],DrawT2[10000];
//	double MinTime,MaxTime;
//    double TimeapartmV,VapartmV,AapartmA,AHapartmAH;
//    int Timeapartm,Vapartm,Aapartm,AHapartm,k2;
//	double	m_XScale;
//	double	m_YScale;
//	double DispScaleX;
//	double DispScaleY;

//	CString FileTypeCode;

//	int OffsetX,OffsetY;
//	int Ge;
//	double Gg,Gh,GP16,GT,Gx,Gy,upx,upy,lowx,lowy,startx,starty,endx,endy,
//		  dstartx,dstarty,dendx,dendy,Gi,Gj,centx,centy,Circler;
//	CString Gs1,Gs2,G4,G5,NCFileName;
//	CString s_startx,s_starty,s_centx,s_centy,s_Circler,s_Diameter,s_GT,s_R;

//	BOOL NCDrawRectCapture;
	BOOL Inch;
//	int XMarkQty,YMarkQty;
//	float maxXvalue,minXvalue,maxYvalue,minYvalue;
//    double XMarkValue,YMarkValue,NCDrawScale,NcDrawScale;
//	bool /*b_MoveAble,*/b_PanRealtimeAble;


	int memDC0OffSet;
//	double maxXvalue,minXvalue,maxYvalue,minYvalue;

	CPen *oldPen;

// Attributes
public:
	CADataEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADataEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CADataEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CFont m_font;
	LOGFONT m_lf;
// Generated message map functions
protected:
	afx_msg void OnUpdateCaretPos(CCmdUI* pCmdUI);
    afx_msg void OnSelchangeCombo1();                      //响应CBN_SELCHANGE消息的函数
    afx_msg void OnEditchangeCombo1();                     //响应CBN_EDITCHANGE消息的函数

	//{{AFX_MSG(CADataEditView)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnViewLineno();
	afx_msg void OnUpdateViewLineno(CCmdUI* pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditInsertafile();
	afx_msg void OnUpdateEditInsertafile(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditInsertaline();
	afx_msg void OnUpdateEditInsertaline(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEditSetfont();
	afx_msg void OnUpdateEditSetfont(CCmdUI* pCmdUI);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnEditGoto();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditSetcolor();
	afx_msg void OnTransmissiomConfigdevice();
	afx_msg void OnUpdateTransmissiomConfigdevice(CCmdUI* pCmdUI);
	afx_msg void OnTransmissiomSendout();
	afx_msg void OnTransmissiomStop();
	afx_msg void OnUpdateTransmissiomStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransmissiomSendout(CCmdUI* pCmdUI);
	afx_msg void OnTransmissiomReceivein();
	afx_msg void OnUpdateTransmissiomReceivein(CCmdUI* pCmdUI);
	afx_msg void OnViewAttachchart();
	afx_msg void OnUpdateViewAttachchart(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONRedrawView();
	afx_msg void OnUpdateBUTTONRedrawView(CCmdUI* pCmdUI);
	afx_msg void OnViewInch();
	afx_msg void OnUpdateViewInch(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditGotofilebottom();
	afx_msg void OnEditGotofiletop();
	afx_msg void OnUpdateEditGotofiletop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditGotofilebottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditGoto(CCmdUI* pCmdUI);
	afx_msg void OnEditDeletealine();
	afx_msg void OnUpdateEditDeletealine(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnGoodbye(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	void GotoFileBottom();
	void GotoFileTop();
	void AdjScrollRange();
	void GoToSpecialLine(int SpecialLine,int StartLine);
	void PrepareUndo(int inccount);
	void ReferenceLine();
	void DrawChartFunc();
	void DrawChartMemDC();
	void PrepareChartData();
	void TransmissionConfig();
//	COleDataSource* SaveDib();
//	BOOL DoPasteDib(COleDataObject* pDataObject);
	COleDataSource* SaveText();
	BOOL DoPasteText(COleDataObject* pDataObject);
	void KeepCursorXPos(int i);
	void StringSave();
	void DeleteLine();
	void StringLoad();
	void AddEmptyLine();
	void PrepareMemDC();

};

#ifndef _DEBUG  // debug version in ADataEditView.cpp
inline CADataEditDoc* CADataEditView::GetDocument()
   { return (CADataEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADATAEDITVIEW_H__EE42D7BA_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
