// CommunicationWorking.cpp : implementation file
//

#include "stdafx.h"
#include "ADataEdit.h"
#include "CommunicationWorking.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommunicationWorking dialog


CCommunicationWorking::CCommunicationWorking(CWnd* pParent /*=NULL*/)
	: CDialog(CCommunicationWorking::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommunicationWorking)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pView = NULL;
}

CCommunicationWorking::CCommunicationWorking(CView* pView) // modeless constructor
{
	m_pView = pView;
}

BOOL CCommunicationWorking::Create()
{
	return CDialog::Create(CCommunicationWorking::IDD);
}

void CCommunicationWorking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommunicationWorking)
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommunicationWorking, CDialog)
	//{{AFX_MSG_MAP(CCommunicationWorking)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommunicationWorking message handlers

BEGIN_EVENTSINK_MAP(CCommunicationWorking, CDialog)
    //{{AFX_EVENTSINK_MAP(CCommunicationWorking)
	ON_EVENT(CCommunicationWorking, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCommunicationWorking::OnOnCommMscomm1() 
{
	if(m_Comm1.GetCommEvent()==2)
	 {
     m_input1 = m_Comm1.GetInput();
     m_input2=m_input1;
//	 ASSERT(m_input2.vt == VT_BSTR);
     str = m_input2.bstrVal;
//	 TRACE("%s\n", str);
     m_InputString = str;
//	 if(str == '\n')
	 m_pView->PostMessage(WM_GOODBYE, IDOK);
	}

	if(m_Comm1.GetCommEvent()==1)
	{
	m_pView->PostMessage(WM_GOODBYE, IDOK);
	}

//	if(m_Comm1.GetCommEvent()==7)
//	{
//	m_pView->PostMessage(WM_GOODBYE, IDOK);
//	}
}

void CCommunicationWorking::Output()
{
   if( !m_Comm1.GetPortOpen() )
    m_Comm1.SetPortOpen(TRUE);

    m_Comm1.SetOutput(COleVariant(m_OutputString));
}

void CCommunicationWorking::Input()
{
   if( !m_Comm1.GetPortOpen() )
     m_Comm1.SetPortOpen(TRUE);
}

/*
void CCommunicationWorking::ReadInput()
{
     VARIANT m_input1;
     COleVariant m_input2;
     CString str;

LOOP:	if(m_Comm1.GetCommEvent()==2)
	 {

     m_input1=m_Comm1.GetInput();
     m_input2=m_input1;
//	 ASSERT(m_input2.vt == VT_BSTR);
     str =m_input2.bstrVal;
//	 TRACE("%s\n", str);
     m_InputString = str;
	 m_pView->PostMessage(WM_GOODBYE, IDOK);
	}
	goto LOOP;
}
*/

BOOL CCommunicationWorking::OnCommand(WPARAM wParam, LPARAM lParam) 
{
      if(SW_MINIMIZE)
      ShowWindow (SW_HIDE); 	
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CCommunicationWorking::OnInitDialog() 
{
	CDialog::OnInitDialog();
    PostMessage(WM_COMMAND, MAKEWPARAM(SW_MINIMIZE,0), 0); 		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommunicationWorking::OnOK() 
{

}

void CCommunicationWorking::OnDestroy() 
{
	if( m_Comm1.GetPortOpen() )
	  {
		m_Comm1.SetRTSEnable(FALSE);
		m_Comm1.SetDTREnable(FALSE);
		m_Comm1.SetPortOpen(FALSE);		
	  }	
	CDialog::OnDestroy();
}
