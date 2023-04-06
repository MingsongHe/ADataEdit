// ADataEditDoc.cpp : implementation of the CADataEditDoc class
//

#include "stdafx.h"
#include "ADataEdit.h"

#include "ADataEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADataEditDoc

IMPLEMENT_DYNCREATE(CADataEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CADataEditDoc, CDocument)
	//{{AFX_MSG_MAP(CADataEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADataEditDoc construction/destruction

CADataEditDoc::CADataEditDoc()
{
	// TODO: add one-time construction code here
	lines = NULL;
	maxLineLength = 0;
    m_TextEditCopyEnable = FALSE;
	QuickDraw = 0;
	EditLineNo = 0;
	LastEditLine = 0;
	m_SelectLine = m_SelectLine2 = 0;
	StringData.Empty();
	MenuID.Empty();

	try {
		lines = new CPtrArray();
	}
	catch (CMemoryException *e)
	{
		AfxMessageBox("Can't allocate memory for reading file contents");
		TRACE0("Unable to allocate memory for file contents\n");
		e->Delete();
	}
	TRACE0("Allocated lines array\n");
	
//	EnableAutomation();
	
//	AfxOleLockApp();
}

CADataEditDoc::~CADataEditDoc()
{
//	AfxOleUnlockApp();

	int i = 0;
	if (lines != NULL)
	{
		while (i < lines->GetSize())
			delete (CString *) lines->GetAt(i++);
		    lines->RemoveAll();
		    delete lines;
		    lines = NULL;

	}
	TRACE0("Deleted lines array\n");
}

BOOL CADataEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView(pos);

		if (lines->GetSize()>1)
		{
        pView->OnInitialUpdate();
		}

	StringData.Empty();
	if (lines != NULL)
	{
		int i = 0;
		while (i < lines->GetSize())
			delete (CString *) lines->GetAt(i++);
		    lines->RemoveAll();
	}
	m_TextEditCopyEnable = FALSE;
    MenuID.Empty();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CADataEditDoc serialization

void CADataEditDoc::Serialize(CArchive& ar)
{

	if ( MenuID == "BMPFile" )
	{
		m_dib.Serialize(ar);	
	}
    else
	{
		BYTE buf;
		CString s;

		if (ar.IsStoring())
		{
			for (int i =0; i < lines->GetSize();i++)
			{
				CString *s0 = (CString *) lines->GetAt(i);
				s = *s0;
				for (int j = 0; j < s.GetLength(); j++)
				{
					buf = s.GetAt(j);
                    ar << buf;
				}
			}
		}
		else
		{
//			if ( m_TextEditCopyEnable == TRUE)
			{
				OnNewDocument();
			}
			m_TextEditCopyEnable = TRUE;
			while (1)
			{
				try {
					ar >> buf;
				}
				catch (CArchiveException *e)
				{
					if (e->m_cause != CArchiveException::endOfFile)
					{
						TRACE0("Unknown exception loading file!\n");
						throw;
					} else
					{
						TRACE0("End of file reached...\n");
						e->Delete();
					}
					break;
				}
				s += buf;
				if (buf == '\n')
				{
					try {
						lines->Add(new CString(s));
					}
					catch (CMemoryException *e)
					{
						AfxMessageBox("Not enough memory to load entire file");
						TRACE1("Not enough memory to load entire file; only %d lines loaded\n", lines->GetSize());
						e->Delete();
						break;
					}
					if (maxLineLength < s.GetLength())
						maxLineLength = s.GetLength();
					s.Empty();
				}
			}
#ifdef _DEBUG
			afxDump.SetDepth(1);
			afxDump << lines;
#endif
			
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CADataEditDoc diagnostics

#ifdef _DEBUG
void CADataEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CADataEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADataEditDoc commands
