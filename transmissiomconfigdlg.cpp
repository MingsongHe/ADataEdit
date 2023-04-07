// TransmissiomConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADataEdit.h"
#include "TransmissiomConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransmissiomConfigDlg dialog


CTransmissiomConfigDlg::CTransmissiomConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransmissiomConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransmissiomConfigDlg)
	m_BandRate = _T("");
	m_Parity = _T("");
	m_WordLength = _T("");
	m_StopBits = _T("");
	m_CodeType = _T("");
	m_ComPortNo = _T("");
	m_AutoXonXoff = _T("");
	m_InputControlMode = _T("");
	m_OutputControlMode = _T("");
	m_InputStartString = _T("");
	m_InputEndString = _T("");
	m_OutputStartString = _T("");
	m_OutputEndString = _T("");
	m_OutputSendDelay = 0;
	m_InputTimeOut = 0;
	//}}AFX_DATA_INIT
}


void CTransmissiomConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransmissiomConfigDlg)
	DDX_CBString(pDX, IDC_COMBO1, m_BandRate);
	DDX_CBString(pDX, IDC_COMBO2, m_Parity);
	DDX_CBString(pDX, IDC_COMBO3, m_WordLength);
	DDX_CBString(pDX, IDC_COMBO4, m_StopBits);
	DDX_CBString(pDX, IDC_COMBO5, m_CodeType);
	DDX_CBString(pDX, IDC_COMBO6, m_ComPortNo);
	DDX_CBString(pDX, IDC_COMBO7, m_AutoXonXoff);
	DDX_CBString(pDX, IDC_COMBO8, m_InputControlMode);
	DDX_CBString(pDX, IDC_COMBO9, m_OutputControlMode);
	DDX_Text(pDX, IDC_EDIT1, m_InputStartString);
	DDX_Text(pDX, IDC_EDIT2, m_InputEndString);
	DDX_Text(pDX, IDC_EDIT4, m_OutputStartString);
	DDX_Text(pDX, IDC_EDIT5, m_OutputEndString);
	DDX_Text(pDX, IDC_EDIT6, m_OutputSendDelay);
	DDV_MinMaxInt(pDX, m_OutputSendDelay, 0, 1000);
	DDX_Text(pDX, IDC_EDIT3, m_InputTimeOut);
	DDV_MinMaxInt(pDX, m_InputTimeOut, 0, 180);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransmissiomConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CTransmissiomConfigDlg)
	ON_BN_CLICKED(IDC_OK, OnClickOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransmissiomConfigDlg message handlers

BOOL CTransmissiomConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(0);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransmissiomConfigDlg::OnOK() 
{
	// TODO: Add extra validation here
//	UpdateData(1);
//	CDialog::OnOK();
}

void CTransmissiomConfigDlg::OnClickOk() 
{
	UpdateData(1);
	CDialog::OnOK();
}
