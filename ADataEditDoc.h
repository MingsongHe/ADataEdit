// ADataEditDoc.h : interface of the CADataEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADATAEDITDOC_H__EE42D7B8_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
#define AFX_ADATAEDITDOC_H__EE42D7B8_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_

#include "CDib.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CADataEditDoc : public CDocument
{
protected: // create from serialization only
	CADataEditDoc();
	DECLARE_DYNCREATE(CADataEditDoc)

    CPtrArray *lines;
	int maxLineLength;
// Attributes
public:
    CString StringData;
    CString MenuID;
    BOOL m_TextEditCopyEnable,QuickDraw,Inch;

	int EditLineNo,m_SelectLine,m_SelectLine2,LastEditLine;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADataEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
		
	CDib m_dib;
	CPtrArray *GetLines()	{ return lines; }
	int GetMaxLineLength()	{ return maxLineLength; }

	virtual ~CADataEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CADataEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADATAEDITDOC_H__EE42D7B8_FCAF_11D2_8073_D2EAFCCE9522__INCLUDED_)
