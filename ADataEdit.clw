; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CADataEditView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ADataEdit.h"
LastPage=0

ClassCount=17
Class1=CADataEditApp
Class2=CADataEditDoc
Class3=CADataEditView
Class4=CMainFrame

ResourceCount=15
Resource1=IDD_PROPPAGE1
Class5=CAboutDlg
Class6=CAChartEditView
Resource2=IDD_INSERTFILE
Resource3=IDR_MAINFRAME
Resource4=IDR_MENU3
Resource5=IDD_ConfigDevice
Class7=CInsertFileDialog
Resource6=IDD_PROPPAGE2
Class8=CGoToDLG
Resource7=IDD_PROPPAGE3
Class9=CTextColorDlg
Resource8=IDR_MENU1
Class10=CTransmissiomConfigDlg
Resource9=IDD_PROPPAGE4
Class11=CCommunicationWorking
Resource10=IDD_TextColorDlg
Resource11=IDD_ABOUTBOX
Resource12=IDR_MENU2
Resource13=IDD_GOTODIALOG
Class12=CChartPropertySheet
Class13=CChartPropertyPage1
Class14=CChartPropertyPage2
Class15=CChartPropertyPage3
Class16=CChartPropertyPage4
Resource14=IDD_COMMWORKONG
Class17=CSplashWnd
Resource15=CG_IDD_PAPDIALOGBAR

[CLS:CADataEditApp]
Type=0
HeaderFile=ADataEdit.h
ImplementationFile=ADataEdit.cpp
Filter=N

[CLS:CADataEditDoc]
Type=0
HeaderFile=ADataEditDoc.h
ImplementationFile=ADataEditDoc.cpp
Filter=N

[CLS:CADataEditView]
Type=0
HeaderFile=ADataEditView.h
ImplementationFile=ADataEditView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_EDIT_DELETEALINE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_EDIT_DELETEALINE




[CLS:CAboutDlg]
Type=0
HeaderFile=ADataEdit.cpp
ImplementationFile=ADataEdit.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_SEND_MAIL
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_INSERTAFILE
Command16=ID_EDIT_GOTO
Command17=ID_EDIT_GOTOFILETOP
Command18=ID_EDIT_GOTOFILEBOTTOM
Command19=ID_EDIT_FIND
Command20=ID_EDIT_DELETEALINE
Command21=ID_EDIT_SETFONT
Command22=ID_EDIT_SETCOLOR
Command23=ID_VIEW_TOOLBAR
Command24=ID_VIEW_STATUS_BAR
Command25=ID_WINDOW_SPLIT
Command26=ID_VIEW_SETTINGPASSWORD
Command27=ID_VIEW_LINENO
Command28=ID_VIEW_ATTACHCHART
Command29=ID_VIEW_INCH
Command30=ID_TRANSMISSIOM_SENDOUT
Command31=ID_TRANSMISSIOM_RECEIVEIN
Command32=ID_TRANSMISSIOM_STOP
Command33=ID_TRANSMISSIOM_PAUSE
Command34=ID_TRANSMISSIOM_CONFIGDEVICE
Command35=ID_CHART_DRAWING
Command36=ID_CHART_SAVEAS
Command37=ID_CHART_SETTING
Command38=ID_CHART_EDIT_CUT
Command39=ID_CHART_EDIT_COPY
Command40=ID_CHART_EDIT_PASTE
Command41=ID_APP_ABOUT
CommandCount=41

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_GOTO
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_GOTOFILEBOTTOM
Command11=ID_EDIT_DELETEALINE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_GOTOFILETOP
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_EDIT_CUT
Command19=ID_EDIT_UNDO
Command20=ID_EDIT_GOTO
CommandCount=20

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=IDC_COMBOX
Command10=ID_EDIT_FIND
Command11=ID_BUTTONRedrawView
Command12=ID_BUTTONZoomIn
Command13=ID_BUTTONZoomOut
Command14=ID_BUTTONZoomInW
Command15=ID_BUTTONZoomAll
Command16=ID_BUTTON32820
Command17=ID_BUTTONChartToUp
Command18=ID_BUTTONChartToDown
Command19=ID_BUTTONChartToL
Command20=ID_BUTTONChartToR
Command21=ID_BUTTONQUICKDRAW
Command22=ID_APP_ABOUT
CommandCount=22

[CLS:CAChartEditView]
Type=0
HeaderFile=AChartEditView.h
ImplementationFile=AChartEditView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CAChartEditView

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_INSERTAFILE
Command6=ID_EDIT_INSERTALINE
CommandCount=6

[MNU:IDR_MENU3]
Type=1
Class=?
Command1=ID_TRANSMISSIOM_STOP
Command2=ID_TRANSMISSIOM_PAUSE
CommandCount=2

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=ID_CHART_EDIT_CUT
Command2=ID_CHART_EDIT_COPY
Command3=ID_CHART_EDIT_PASTE
Command4=ID_CHART_SAVEAS
CommandCount=4

[DLG:IDD_INSERTFILE]
Type=1
Class=CInsertFileDialog
ControlCount=5
Control1=stc32,button,1073741831
Control2=IDC_STATIC,static,1342177287
Control3=IDC_STATIC,static,1342308364
Control4=IDC_CHECK2,button,1342242819
Control5=IDC_EDIT1,edit,1350631553

[CLS:CInsertFileDialog]
Type=0
HeaderFile=InsertFileDialog.h
ImplementationFile=InsertFileDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CInsertFileDialog
VirtualFilter=dWC

[CLS:CGoToDLG]
Type=0
HeaderFile=GoToDLG.h
ImplementationFile=GoToDLG.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGoToDLG

[DLG:IDD_GOTODIALOG]
Type=1
Class=CGoToDLG
ControlCount=5
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_OK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342177282
Control5=IDC_STATIC,button,1342177287

[DLG:IDD_TextColorDlg]
Type=1
Class=CTextColorDlg
ControlCount=9
Control1=IDC_OK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_LIST1,SysListView32,1350639616
Control8=IDC_LIST2,SysListView32,1350639616
Control9=IDC_LIST3,SysListView32,1350639616

[CLS:CTextColorDlg]
Type=0
HeaderFile=TextColorDlg.h
ImplementationFile=TextColorDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_ConfigDevice]
Type=1
Class=CTransmissiomConfigDlg
ControlCount=37
Control1=IDC_COMBO1,combobox,1344339970
Control2=IDC_COMBO2,combobox,1344340226
Control3=IDC_COMBO3,combobox,1344340226
Control4=IDC_COMBO4,combobox,1344340226
Control5=IDC_COMBO5,combobox,1344340226
Control6=IDC_COMBO6,combobox,1344340226
Control7=IDC_COMBO7,combobox,1344340226
Control8=IDC_COMBO8,combobox,1344340226
Control9=IDC_EDIT1,edit,1350631552
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_EDIT3,edit,1350631552
Control12=IDC_COMBO9,combobox,1344340226
Control13=IDC_EDIT4,edit,1350631552
Control14=IDC_EDIT5,edit,1350631552
Control15=IDC_EDIT6,edit,1350631552
Control16=IDC_OK,button,1342242816
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC,button,1342178055
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342178055
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,button,1342178055
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352

[CLS:CTransmissiomConfigDlg]
Type=0
HeaderFile=transmissiomconfigdlg.h
ImplementationFile=transmissiomconfigdlg.cpp
BaseClass=CDialog
LastObject=CTransmissiomConfigDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_COMMWORKONG]
Type=1
Class=CCommunicationWorking
ControlCount=3
Control1=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287

[CLS:CCommunicationWorking]
Type=0
HeaderFile=CommunicationWorking.h
ImplementationFile=CommunicationWorking.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCommunicationWorking

[DLG:IDD_PROPPAGE1]
Type=1
Class=CChartPropertyPage1
ControlCount=16
Control1=IDC_CHECK1,button,1342242819
Control2=IDC_STATIC,button,1342178055
Control3=IDC_CHECK2,button,1342242819
Control4=IDC_CHECK3,button,1342242819
Control5=IDC_LIST2,SysListView32,1350639616
Control6=IDC_LIST3,SysListView32,1350639616
Control7=IDC_LIST4,SysListView32,1350639616
Control8=IDC_STATIC,button,1342178055
Control9=IDC_STATIC,button,1342177287
Control10=IDC_EDIT1,edit,1350631552
Control11=IDC_EDIT2,edit,1350631552
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_SCROLLBAR1,scrollbar,1342177281
Control15=IDC_SCROLLBAR2,scrollbar,1342177281
Control16=IDC_STATIC,button,1342177287

[DLG:IDD_PROPPAGE2]
Type=1
Class=CChartPropertyPage2
ControlCount=10
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_STATIC,button,1342177287
Control3=IDC_LIST1,SysListView32,1350639616
Control4=IDC_EDIT7,edit,1350631552
Control5=IDC_EDIT8,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_LIST4,SysListView32,1350639616

[DLG:IDD_PROPPAGE3]
Type=1
Class=CChartPropertyPage3
ControlCount=9
Control1=IDC_LIST1,SysListView32,1350639616
Control2=IDC_LIST2,SysListView32,1350639616
Control3=IDC_RADIO1,button,1342373897
Control4=IDC_RADIO2,button,1342242825
Control5=IDC_RADIO3,button,1342242825
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342178055
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE4]
Type=1
Class=CChartPropertyPage4
ControlCount=0

[CLS:CChartPropertySheet]
Type=0
HeaderFile=ChartPropertySheet.h
ImplementationFile=ChartPropertySheet.cpp
BaseClass=CPropertySheet
LastObject=CChartPropertySheet

[CLS:CChartPropertyPage1]
Type=0
HeaderFile=ChartPropertyPage1.h
ImplementationFile=ChartPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CChartPropertyPage1

[CLS:CChartPropertyPage2]
Type=0
HeaderFile=ChartPropertyPage1.h
ImplementationFile=ChartPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_LIST4

[CLS:CChartPropertyPage3]
Type=0
HeaderFile=ChartPropertyPage1.h
ImplementationFile=ChartPropertyPage1.cpp
BaseClass=CPropertyPage
LastObject=IDC_LIST2
Filter=D
VirtualFilter=idWC

[CLS:CChartPropertyPage4]
Type=0
HeaderFile=ChartPropertyPage1.h
ImplementationFile=ChartPropertyPage1.cpp
BaseClass=CPropertyPage
LastObject=CChartPropertyPage4

[DLG:CG_IDD_PAPDIALOGBAR]
Type=1
Class=?
ControlCount=0

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd

