// InsertFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ADataEdit.h"
#include "InsertFileDialog.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertFileDialog dialog

/*
CInsertFileDialog::CInsertFileDialog(CWnd* pParent /*=NULL*///)
/*	: CDialog(CInsertFileDialog::IDD, pParent)
*/
CInsertFileDialog::CInsertFileDialog(BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags,
		LPCTSTR lpszFilter, CWnd* pParentWnd)
	: CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName,
		dwFlags, lpszFilter, pParentWnd)
{
	//{{AFX_DATA_INIT(CInsertFileDialog)
	m_Detail = FALSE;
	m_DetailValue = 0.0f;
	//}}AFX_DATA_INIT
		m_ofn.Flags |= OFN_ENABLETEMPLATE;
	    m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_INSERTFILE);
	    m_ofn.lpstrTitle = "   Insert File";
}


void CInsertFileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertFileDialog)
	DDX_Check(pDX, IDC_CHECK2, m_Detail);
	DDX_Text(pDX, IDC_EDIT1, m_DetailValue);
	DDV_MinMaxFloat(pDX, m_DetailValue, 1.e-007f, 1.e+007f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertFileDialog, CDialog)
	//{{AFX_MSG_MAP(CInsertFileDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
//	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertFileDialog message handlers

BOOL CInsertFileDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON hIcon=AfxGetApp() ->LoadIcon(IDI_ICON2);
	
	BOOL bRet = CFileDialog::OnInitDialog();
	if (bRet == TRUE) {
		GetParent()->GetDlgItem(IDOK)->SetWindowText("Insert");
        GetParent()->SetIcon(hIcon, TRUE);
	}

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

    RLinePen.CreatePen(PS_INSIDEFRAME,1,RGB(255,0,0));
	OLinePen.CreatePen(PS_INSIDEFRAME,1,RGB(0,0,255));

	PreparememDC = FALSE;
	LastFileName.Empty();
	
	Gx = 0.0;
	Gy = 0.0;
	startx = 0.0;
	starty = 0.0;
	centx = 999.9;
	centy = 999.9;
	Circler = 999.9;

	NCDrawScale = 1.0;

	maxXvalue = -10000.0;
	minXvalue = 10000.0;
	maxYvalue = -10000.0;
	minYvalue = 10000.0;

	m_Detail = false;
	m_DetailValue = 1.0;

    UpdateData(false);

	return bRet;	
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsertFileDialog::PrepareMemDC()
{
	CClientDC DC(this);
	CBitmap m_bmp1;
	
	m_bmp1.CreateCompatibleBitmap(&DC,640,480);
	memDC1.CreateCompatibleDC(&DC);
	memDC1.SelectObject(&m_bmp1);

	memDC1.PatBlt(0,0,640,480,WHITENESS);

	PreparememDC = TRUE;
}

void CInsertFileDialog::OnPaint() 
{
	    CPaintDC dc(this); // device context for painting

		AfxGetApp()->BeginWaitCursor();

        if(PreparememDC == FALSE)
		{
		  PrepareMemDC();
		}
          m_strFilename = GetPathName();
		  if(LastFileName != m_strFilename)
		  {
          LoadDataFile();

		  PerpareDraftData();

          DraftMemDC();

		  LastFileName = GetPathName();
		  }

		AfxGetApp()->EndWaitCursor();

        dc.StretchBlt(444,46,225,180,&memDC1,0,0,640,480,SRCCOPY);
}

void CInsertFileDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CInsertFileDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
      if(PreparememDC == FALSE)
	  {
		PrepareMemDC();
	  }

	  Gx = 0.0;
	  Gy = 0.0;
	  startx = 0.0;
	  starty = 0.0;
	  centx = 999.9;
	  centy = 999.9;
	  Circler = 999.9;

	  NCDrawScale = 1.0;

	  maxXvalue = -10000.0;
	  minXvalue = 10000.0;
	  maxYvalue = -10000.0;
	  minYvalue = 10000.0;

      memDC1.PatBlt(0,0,640,480,WHITENESS);
      Invalidate(0);	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CInsertFileDialog::LoadDataFile()
{
       BYTE buf;
	   CString s;
	   int i = 0;

	if (lines != NULL)
	{
		while (i < lines->GetSize())
			delete (CString *) lines->GetAt(i++);
		    lines->RemoveAll();
//		    delete lines;
//		    lines = NULL;

	}
		
	   CFile file(GetPathName(),CFile::modeRead);
	   CArchive ar(&file,CArchive::load);
		
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
					s.Empty();
				}
			}

#ifdef _DEBUG
//			afxDump.SetDepth(1);
//			afxDump << lines;
#endif
	    CString *FileTypeString = (CString *)lines->GetAt(1);
		s = *FileTypeString;
	    FileTypeCode = s.GetAt(0);

		n = lines->GetSize();
}

void CInsertFileDialog::PerpareDraftData()
{
	 CPtrArray *l = GetLines();

     if(FileTypeCode =='R')
	 {
	    CString Totals;
        CString As;
        CString TimeHmins = "000";
        CString TimeHmaxs = "000";
	    CString TimeMmins = "00";
	    CString TimeMmaxs = "00";
	    CString TimeSmins = "00";
	    CString TimeSmaxs = "00";

	    double DrawMaxA = 0.0f;

	    int AIndex;
        double DrawMaxAs;
	    int p;

	    for (int i = 2; i < n-3; i++)
		{
	    CString *line = (CString *) l->GetAt(i);
	    Totals = *line;		

		 As = Totals.Mid( 24, 5 );
	     DrawA[i] = atof(As);
	     if (DrawMaxA < DrawA[i])DrawMaxA = DrawA[i];		     	   	  	 
		}

		 DrawMaxAs = DrawMaxA;
         AIndex = log10(DrawMaxA);

	     DrawMaxAs = DrawMaxAs/pow(10,AIndex);

         Aapartm = DrawMaxAs *2;
         Aapartm += 1;
         AapartmA = 0.5;

		 for ( p = 0; p < AIndex; p++)
	   {
	     AapartmA = AapartmA*10.0;
	   }

	 
	     CString *line = (CString *) l->GetAt(2);
	     Totals = *line;		

		 TimeHmins=Totals.Mid(6 ,3 );
		 TimeMmins=Totals.Mid(10,2 );
		 TimeSmins=Totals.Mid(13,2 );
	    
		 line= (CString *) l->GetAt(n-2);
	     Totals = *line;
		
		 TimeHmaxs=Totals.Mid(6 ,3 );
		 TimeMmaxs=Totals.Mid(10,2 );
		 TimeSmaxs=Totals.Mid(13,2 );

	     double DrawTime,DrawTimes;
	     MinTime = atoi(TimeHmins)*60.0 + atoi(TimeMmins) + atof(TimeSmins)/60.0;
         MaxTime = atoi(TimeHmaxs)*60.0 + atoi(TimeMmaxs) + atof(TimeSmaxs)/60.0;

         DrawTime = MaxTime - MinTime;
        
	     int TimeIndex;
	     DrawTimes = DrawTime;
         TimeIndex = log10(DrawTime);

       for (int u = 0; u < TimeIndex; u++)
	   {
	     DrawTimes = DrawTimes/10;
	   }
         Timeapartm = DrawTimes *2;
         Timeapartm = Timeapartm + 1;
         TimeapartmV = 0.5;
	   for (int v = 0; v < TimeIndex; v++)
	   {
	     TimeapartmV = TimeapartmV*10;
	   }	 
	 }

	  if(FileTypeCode == 'O')     //NC File PrepareChartData
	  {
		CString s,s2;
		int e,
		double x,y;

			for (int k = 2; k < n-2; k++)
			{						    
			CString *line = (CString *) l->GetAt(k+1);
            s = *line;
            
        	if(s.Find('X') >= 0)
				{
				s2.Empty();
				for( e = s.Find('X')+1; e < s.Find('\r'); e++)
				{
					s2 = s2 + s.GetAt(e);
				}
                x = (atof(s2));
				s2.Empty();
				}
				else x = 0.0;

				if((s.Find('Y'))>=0)
				{
				s2.Empty();
				for( e = s.Find('Y')+1; e < s.Find('\r'); e++)
				{
					s2 = s2 + s.GetAt(e);
				}
				y = (atof(s2));
				s2.Empty();
				}
				else y = 0.0;
				
					if (maxXvalue < x)
						maxXvalue = x;
					if (minXvalue > x)
						minXvalue = x;
					if (maxYvalue < y)
						maxYvalue = y;
					if (minYvalue > y)
						minYvalue = y;
       					s.Empty();
			}
			NcDrawScale = min((640-50)/(maxXvalue - minXvalue),(480-15)/(maxYvalue - minYvalue));

			OffsetX = NcDrawScale*(maxXvalue + minXvalue)/2;
			OffsetY = NcDrawScale*(maxYvalue + minYvalue)/2;
	  }	
}

void CInsertFileDialog::DraftMemDC()
{
	  if(FileTypeCode == 'R')
		{
            int PoxX,PoxY;
            CString s;
		
			int w;

            for (w = 0; w < Timeapartm ; w++)
			{
			  PoxX = (450*w)/Timeapartm;
			  if(PoxX>=0.0)
			  {
				memDC1.MoveTo(130 + PoxX,385.0);
				memDC1.LineTo(130 + PoxX,385.0-5);
			  }
			}

            for (w = 0; w <  Aapartm +1; w++)
			{
			  PoxY = (250*w)/ Aapartm;
			  if(PoxY>=0.0)
			  {
				memDC1.MoveTo(130 , 385 - PoxY);
				memDC1.LineTo(130 + 5 , 385 - PoxY);
			  }
			}
            
			CPen *oldPen = memDC1.SelectObject(&OLinePen);
            
			memDC1.MoveTo(563,383);
			memDC1.LineTo(570,385);
			memDC1.LineTo(563,387);

			memDC1.MoveTo(570,385);
			memDC1.LineTo(130,385);                        //H.L
			memDC1.LineTo(130,115);                        //V.L

            memDC1.LineTo(128,132);
            memDC1.LineTo(130,115);
			memDC1.LineTo(132,132);

            memDC1.SelectObject(oldPen);
		    CPen *oldPen2 = memDC1.SelectObject(&RLinePen);

                CString As;
                CString TimeH = "000";
	            CString TimeM = "00";
	            CString TimeS = "00";
//	            double DrawV = 0.0f;
	            double DrawA = 0.0f;
//	            double DrawAH = 0.0f;
	            double DrawTime = 0.0f;

                CPtrArray *l = GetLines();
			for (int k = 1; k < n-2 ; k++)
			{						    
			CString *line = (CString *) l->GetAt(k+1);
            s = *line;

/*	        
			if (m_SelectV == TRUE)
			{
            Vs = s.Mid( 17, 5 );
	         DrawV = atof(Vs);
			}		
	        
			if (m_SelectAH == TRUE)
			{
            AHs = s.Mid( 31, 5 );
	        DrawAH = atof(AHs);
			}	   
*/
	        As = s.Mid( 24, 5 );
	        DrawA = atof(As);

		    TimeH=s.Mid(6 ,3 );
		    TimeM=s.Mid(10,2 );
		    TimeS=s.Mid(13,2 );

            DrawTime = atoi(TimeH)*60.0 + atoi(TimeM) + atof(TimeS)/60.0;
		
            if(k==1)
			{
            memDC1.MoveTo(130 + (DrawTime-MinTime)*450.0/(Timeapartm*TimeapartmV),404-(DrawA)*(250/(AapartmA*Aapartm)));
			}
		    memDC1.LineTo(130 + (DrawTime-MinTime)*450.0/(Timeapartm*TimeapartmV),404-(DrawA)*(250/(AapartmA*Aapartm)));
			}

           memDC1.SelectObject(oldPen2);     
	  }

	  if(FileTypeCode == 'O')     //NC File PrepareChartData
	  {
		  CPen *oldPen = memDC1.SelectObject(&OLinePen);

		    CPtrArray *l = GetLines();
			for (int k = 2; k < n-2 ; k++)
			{
				CString *line = (CString *) l->GetAt(k);
				Gs1 = *line;
                Gs2.Empty();
 
				if((Gs1.Find("G92")!=-1)||(Gs1.Find("G00")!=-1)||(Gs1.Find("G90G54G0")!=-1))
				{
				  for( Ge = Gs1.Find('X')+1; Ge < Gs1.Find('\r'); Ge++)
				  {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				  }
					startx = atof(Gs2);
					Gs2.Empty();
				 for( Ge = Gs1.Find('Y')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					starty = atof(Gs2);	
					Gs2.Empty();
					memDC1.MoveTo(startx * NcDrawScale * NCDrawScale + (320 - OffsetX),-starty * NcDrawScale * NCDrawScale + (240 + OffsetY));
				}
				
				if((Gs1.Find("G01"))>=0)
				{
				 for( Ge = Gs1.Find('X')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
				 	Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					Gx = (atof(Gs2));
					startx = Gx;
					Gs2.Empty();
				 for( Ge = Gs1.Find('Y')+1; Ge < Gs1.Find('\r'); Ge++)
				 {
					Gs2 = Gs2 + Gs1.GetAt(Ge);
				 }
					Gy = (atof(Gs2));
					starty = Gy;
					Gs2.Empty();
					memDC1.LineTo(Gx * NcDrawScale * NCDrawScale + (320 - OffsetX),-Gy * NcDrawScale * NCDrawScale + (240 + OffsetY));
				}
				
				 if((Gs1.Find("G03")>=0)||(Gs1.Find("G02")>=0))
				 {
				   if(Gs1.Find('X')!=-1)
				   {
					 Gs2.Empty();
					 for( Ge = Gs1.Find('X') + 1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 endx = atof(Gs2);
					 Gs2.Empty();
				   }
					 else endx = 0.0;
					
				   if(Gs1.Find('Y')!=-1)
				   {
					 Gs2.Empty();
					 for( Ge = Gs1.Find('Y') + 1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 endy = atof(Gs2);
					 Gs2.Empty();
				   }
					 else endy = 0.0;
                    if(m_Detail)
					{
					if(((abs(endx-startx))*NcDrawScale<m_DetailValue)||((abs(endy-starty))*NcDrawScale<m_DetailValue))
					{
					memDC1.LineTo(endx * NcDrawScale * NCDrawScale + (320 - OffsetX),-endy * NcDrawScale * NCDrawScale + (240 + OffsetY));
					startx = endx;
				    starty = endy;
				    goto end;
					}
					}
					if(Gs1.Find('I')!=-1)
					{
					 Gs2.Empty();
					 for( Ge = Gs1.Find('I')+1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 Gi = (atof(Gs2))/1000.0;
					 Gs2.Empty();
					}
					 else Gi = 0.0;
					
					if(Gs1.Find('J')!=-1)
					{
					 Gs2.Empty();
					 for( Ge = Gs1.Find('J')+1; Ge < Gs1.Find('\r'); Ge++)
					 {
					 Gs2 = Gs2 + Gs1.GetAt(Ge);
					 }
					 Gj = (atof(Gs2))/1000.0;
					 Gs2.Empty();
					}
					else Gj = 0.0;
										
					centx = startx + Gi ;
					centy = starty + Gj ;
					Circler = sqrt((Gi*Gi) + (Gj*Gj));
					upx = (centx - Circler);
					upy = (centy + Circler);
					lowx = (centx + Circler);
					lowy = (centy - Circler);
					
					if((Gi==0.0)||(Gj==0.0))
					{
					 dstartx = startx;
					 dstarty = starty;
					 dendx = endx;
					 dendy = endy;
					}
					else
					{
					 if((Gi<0.0)&&(Gj<0.0)&&(Gi==Gj))                //first zero
					 {
					  dstartx = lowx;
					  dstarty = upy;
					 }
						
					 if((Gi<0.0)&&(Gj<0.0)&&(Gi<Gj))                 //  <45
					 {
						 dstartx = lowx;
						 dstarty = centy + Gj*Circler/Gi;
					 }
					 
					 if((Gi<0.0)&&(Gj<0.0)&&(Gi>Gj))                 //  >45
					 {
						 dstartx = centx + Gi*Circler/Gj;
						 dstarty = upy;
					 }
					 
					 if((Gi>0.0)&&(Gj<0.0)&&(Gi==-Gj))               //secend zero  
					 {
						 dstartx = upx;
						 dstarty = upy;
					 }
					 
					 if((Gi>0.0)&&(Gj<0.0)&&(-Gi>Gj))
					 {
						 dstartx = upx;
						 dstarty = centy - Gj*Circler/Gi;
					 }
					 
					 if((Gi>0.0)&&(Gj<0.0)&&(-Gi<Gj))
					 {
						 dstartx = centx + Gi*Circler/Gj;
						 dstarty = upy;
					 }
					 
					 if((Gi>0.0)&&(Gj>0.0)&&(Gi==Gj))             //3th zero
					 {
						 dstartx = upx;
						 dstarty = lowy;
					 }
					 
					 if((Gi>0.0)&&(Gj>0.0)&&(Gi>Gj))
					 {
						 dstartx = upx;
						 dstarty = centy - Gj*Circler/Gi;
					 }
					 
					 if((Gi>0.0)&&(Gj>0.0)&&(Gi<Gj))
					 {
						 dstartx = centx - Gi*Circler/Gj;
						 dstarty = lowy;
					 }
					 
					 if((Gi<0.0)&&(Gj>0.0)&&(Gi==-Gj))               //4th zero  
					 {
						 dstartx = lowx;
						 dstarty = lowy;
					 }
					 
					 if((Gi<0.0)&&(Gj>0.0)&&(-Gi>Gj))
					 {
						 dstartx = lowx;
						 dstarty = centy + Gj*Circler/Gi;
					 }
					 
					 if((Gi<0.0)&&(Gj>0.0)&&(-Gi<Gj))
					 {
						 dstartx = centx - Gi*Circler/Gj;
						 dstarty = lowy;
					 }
					 
					 if((endx-centx==0.0)||(endy-centy==0.0))
					 {
						 dendx = endx;
						 dendy = endy;
					 }
					 else
					 {
						 if((endx-centx>0.0)&&(endy-centy>0.0)&&((endx-centx)==(endy-centy)))                //first zero
						 {
							 dendx = lowx;
							 dendy = upy;
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy>0.0)&&((endx-centx)>(endy-centy)))              //  <45
						 {
							 dendx = lowx;
							 dendy = centy + (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy>0.0)&&((endx-centx)<(endy-centy)))              //  >45
						 {
							 dendx = centx + (endx-centx)*Circler/(endy-centy);
							 dendy = upy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy>0.0)&&((endx-centx)==-(endy-centy)))               //secend zero  
						 {
							 dendx = upx;
							 dendy = upy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy>0.0)&&(-(endx-centx)>(endy-centy)))
						 {
							 dendx = upx;
							 dendy = centy - (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy>0.0)&&(-(endx-centx)<(endy-centy)))
						 {
							 dendx = centx + (endx-centx)*Circler/(endy-centy);
							 dendy = upy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy<0.0)&&((endx-centx)==(endy-centy)))             //3th zero
						 {
							 dendx = upx;
							 dendy = lowy;
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy<0.0)&&((endx-centx)<(endy-centy)))
						 {
							 dendx = upx;
							 dendy = centy - (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx<0.0)&&(endy-centy<0.0)&&((endx-centx)>(endy-centy)))
						 {
							 dendx = centx - (endx-centx)*Circler/(endy-centy);
							 dendy = lowy;
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy<0.0)&&((endx-centx)==-(endy-centy)))               //4th zero  
						 {
							 dendx = lowx;
							 dendy = lowy;
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy<0.0)&&((endx-centx)>-(endy-centy)))
						 {
							 dendx = lowx;
							 dendy = centy + (endy-centy)*Circler/(endx-centx);
						 }
						 
						 if((endx-centx>0.0)&&(endy-centy<0.0)&&((endx-centx)<-(endy-centy)))
						 {
							 dendx = centx - (endx-centx)*Circler/(endy-centy);
							 dendy = lowy;
						 }
					 } 
				  }
				  
				  if(Gs1.Find("G02")!=-1)
				  {
					  Gg = dendx;
					  Gh = dendy;
					  dendx = dstartx;
					  dendy = dstarty;
					  dstartx = Gg;
					  dstarty = Gh;
				  }

				  memDC1.Arc(upx * NcDrawScale * NCDrawScale + (320 - OffsetX),-upy * NcDrawScale * NCDrawScale + (240 + OffsetY),lowx*NcDrawScale * NCDrawScale + (320 - OffsetX),
					         -lowy*NcDrawScale * NCDrawScale + (240 + OffsetY),dstartx*NcDrawScale * NCDrawScale + (320 - OffsetX),
					         -dstarty*NcDrawScale * NCDrawScale + (240 + OffsetY),dendx*NcDrawScale * NCDrawScale + (320 - OffsetX),-dendy*NcDrawScale * NCDrawScale + (240 + OffsetY));
				  memDC1.MoveTo(endx*NcDrawScale * NCDrawScale + (320 - OffsetX),-endy*NcDrawScale * NCDrawScale + (240 + OffsetY));
				  
				  startx = endx;
				  starty = endy;
                   }
end:              ;
				 }
              memDC1.SelectObject(oldPen);               
              }
}
/*
void CInsertFileDialog::OnButton1() 
{
              UpdateData(1);		
}
*/
void CInsertFileDialog::OnCheck2() 
{
              UpdateData(1);
			  DraftMemDC();
//			  if(m_Detail)
//			  IDC_EDIT1.WS_VISIBLE = TRUE;
}

void CInsertFileDialog::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	          UpdateData(1);
			  DraftMemDC(); 
}
