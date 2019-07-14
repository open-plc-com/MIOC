/*
	Name:			
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include "myframe.h"
#include "dev.xpm"
#include "connect.xpm"
#include "disconnect.xpm"
#include "pw_g.xpm"
#include "pw_r.xpm"
#include "empty.xpm"
#include "exclamation.xpm"

#include "set_com.cpp"
#include "files.cpp"
#include "new_prj.cpp"
#include "myframe_tools_events.cpp"
#include "myframe_virtual_events.cpp"
#include "wxgridctrl.cpp"


//#include "tinyxml2.cpp"
//#include "run_handler.cpp"
//#include "data_handler.cpp"


// ===========================================================================
// ===                            MyFrame                                  ===
// ===========================================================================
MyFrame::MyFrame( wxWindow *parent,
// ===========================================================================
				  wxWindowID		 id,
				  const wxString	&title,
				  const wxPoint		&pos,
				  const wxSize		&size,
				  long style )
		: MyFrameFB( parent, id, title, pos, size, style )
{
	//int			i, j, m, n, x, y, com_nn;
	int			i, x, y;
	wxString	s;

	SetIcon( wxIcon( dev_xpm ) );	// Set Icon

	ce2 = new wxGridCellChoiceEditor( 21, VAR_1XX_TYPES );
	for( i = 0; i < MAX_PORT_NN; i++ )
	{
		SEL_PORT[i] = wxEmptyString;
	}
	SEL_PORT[0]		= wxEmptyString;
	SEL_PORT[1]		= "PA0";
	SEL_PORT[2]		= "PA1";
	SEL_PORT[3]		= "PA2";
	SEL_PORT[4]		= "PA3";
	SEL_PORT[5]		= "PA4";
	SEL_PORT[6]		= "PA5";
	SEL_PORT[7]		= "PA6";
	SEL_PORT[8]		= "PA7";
	SEL_PORT[9]		= "PA8";
	SEL_PORT[10]	= "PA9";
	SEL_PORT[11]	= "PA10";
	SEL_PORT[12]	= "PA11";
	SEL_PORT[13]	= "PA12";
	SEL_PORT[14]	= "PA13";
	SEL_PORT[15]	= "PA14";
	SEL_PORT[16]	= "PA15";
	SEL_PORT[17]	= "PB0";
	SEL_PORT[18]	= "PB1";
	SEL_PORT[19]	= "PB2";
	SEL_PORT[20]	= "PB3";
	SEL_PORT[21]	= "PB4";
	SEL_PORT[22]	= "PB5";
	SEL_PORT[23]	= "PB6";
	SEL_PORT[24]	= "PB7";
	SEL_PORT[25]	= "PB8";
	SEL_PORT[26]	= "PB9";
	SEL_PORT[27]	= "PB10";
	SEL_PORT[28]	= "PB11";
	SEL_PORT[29]	= "PB12";
	SEL_PORT[30]	= "PB13";
	SEL_PORT[31]	= "PB14";
	SEL_PORT[32]	= "PB15";
	SEL_PORT[33]	= "PC13";
	PORT_NN			= 34;
	ce3 = new wxGridCellChoiceEditor( PORT_NN, SEL_PORT );
//cs5[0] = wxEmptyString;
//cs5[1] = wxT( "R" );
//cs5[2] = wxT( "W" );
//ce5 = new wxGridCellChoiceEditor( 3, cs5 );

	_log = m_log;

	if( OnPathInit() )
	{
		Close();
	}

	GetSize( &x, &y );
	//m_grid->SetMinSize( wxSize( 400, -1 ) );
	//m_grid->SetSize( wxSize( 400, -1 ) );
	SetMinSize( wxSize( x, y ) );
	SetMaxSize( wxSize( ( x + 20 ), ( y + 20 ) ) );
	Fit();
	SetSize( wxSize( x, y ) );
	SetMaxSize( wxSize( -1, -1 ) );
//	m_config_window->Fit();
//	m_log->Fit();
//	m_log->Refresh();
//	m_log->Show( false );
	//Refresh();

// Can't access to 
if( !Read_Cfg() )
_log->AppendText( wxT( "Read_Cfg main - Ok\n" ) );

s.Printf( wxT( "size VAR_1XX_TYPES=%d\n" ), ( sizeof( VAR_1XX_TYPES ) / sizeof ( int ) - 1 ) ); _log->AppendText( s );

if( Win_SizeX && Win_SizeY  )
{
	// Restore size & position
	if( ( Win_PosX >= 0 ) && ( Win_PosY >= 0 ) )
	{
		Move( Win_PosX, Win_PosY );
	}
	if( Win_SizeX && Win_SizeY )
	{
		SetSize( wxSize( Win_SizeX, Win_SizeY ) );
	}
	if( Read_Win_MaxSize )
	{
//_log->AppendText( wxT( "Set Win_MaxSize=T\n" ) );
		Win_MaxSize = true;
		Maximize();
	}
	else
	{
		Win_MaxSize = false;
//_log->AppendText( wxT( "Set Win_MaxSize=F\n" ) );
	}
}
	// Show/Hide sizers
	// ---------------------------------------------------------------------------
	sbSizerInterfaces->Show( false );
	sbSizerSerial->Show( true );
//	m_tool_UART->Show( true );
//	m_check_UART->Show( false );
//	m_check_USB_VCP->Show( true );
//	m_check_USB_console->Show( true );
//	sbSizerCAN->Show( true );
//	m_check_CAN_MCP2515->Enable( false );
//	m_check_CAN_Internal->Show( false );
//	sbSizerEth->Show( false );

	sbSizerIndicators->Show( false );
//	sbSizerLED->Show( true );
//	m_check_PC13->Show( true );

//	sbSizerDisplayI2C->Show( true );
//	m_check_LCD1602->Show( true );
//	m_check_8574->Show( true );
//	m_check_8574A->Show( true );
//	m_check_SSD1306->Show( false );

//	m_check_LCD1602->Enable( false );
//	m_check_8574->Enable( false );
//	m_check_8574A->Enable( false );
	
//	m_staticline5->Show( false );
//	m_staticline9->Show( false );
//	m_staticline10->Show( false );
//	m_staticline14->Show( false );

	sbSizerSensors->Show( false );
//	m_check_BME280->Show( false );
//	m_check_BH1750->Show( false );

	sbSizerSystem->Show( false );
//	m_checkBoxWatchDog->Show( false );
//	m_checkBoxMCO->Show( false );
//	m_checkBoxTimer->Show( false );
	// ---------------------------------------------------------------------------

//	// ---------------------------------------------------------------------------
//	m_auinotebook->RemovePage( m_auinotebook->GetPageIndex( m_panel_log ) );
//	m_auinotebook->RemovePage( m_auinotebook->GetPageIndex( m_config_window ) );
//	m_auinotebook->Fit();
//	m_auinotebook->Refresh();
//	// ---------------------------------------------------------------------------

//_log->AppendText( wxT( "Start\n" ) );
_log->AppendText( wxT( "WORK_PATH=" ) );	_log->AppendText( WORK_PATH );	_log->AppendText( wxT( "\n" ) );
_log->AppendText( wxT( "EXEC_PATH=" ) );	_log->AppendText( EXEC_PATH );	_log->AppendText( wxT( "\n" ) );
_log->AppendText( wxT( "DATA_DIR=" ) );		_log->AppendText( DATA_DIR );	_log->AppendText( wxT( "\n" ) );
//_log->AppendText( wxT( "S_NAME=" ) );		_log->AppendText( S_NAME );		_log->AppendText( wxT( "\n" ) );
//_log->AppendText( wxT( "S_EXT=" ) );		_log->AppendText( S_EXT );		_log->AppendText( wxT( "\n" ) );

	// --- Tools -----------------------------------------------------------------
//	m_main_tool->EnableTool( ID_TOOL_SAVE, false );
	m_main_tool->EnableTool( ID_TOOL_GENERATE, false );
//	m_main_tool->EnableTool( ID_TOOL_CONNECT, false );

//	m_tool_data->SetToolNormalBitmap( ID_TOOL_INS_ROW, empty_xpm );
//	m_tool_data->EnableTool( ID_TOOL_INS_ROW, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_DEL_ROW, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_DEL_ROW, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_ROW_UP, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_ROW_UP, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_ROW_DOWN, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_ROW_DOWN, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_RUN, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_RUN, false );

//	m_tool_UART->SetToolNormalBitmap( ID_TOOL_UART_CONFIG, empty_xpm );
//	m_tool_UART->EnableTool( ID_TOOL_UART_CONFIG, false );
//	m_tool_UART->SetToolNormalBitmap( ID_TOOL_SERIAL_HELP, empty_xpm );
	m_tool_UART->EnableTool( ID_TOOL_SERIAL_HELP, false );

	m_tool_CAN->SetToolNormalBitmap( ID_TOOL_CAN_CFG, empty_xpm );
	m_tool_CAN->EnableTool( ID_TOOL_CAN_CFG, false );
	m_tool_CAN->SetToolNormalBitmap( ID_TOOL_CAN_HELP, empty_xpm );
	m_tool_CAN->EnableTool( ID_TOOL_CAN_HELP, false );

	m_tool_Ethernet->SetToolNormalBitmap( ID_TOOL_ETH_CFG, empty_xpm );
	m_tool_Ethernet->EnableTool( ID_TOOL_ETH_CFG, false );
	m_tool_Ethernet->SetToolNormalBitmap( ID_TOOL_ETH_HELP, empty_xpm );
	m_tool_Ethernet->EnableTool( ID_TOOL_ETH_HELP, false );

//	m_tool_Display_I2C->SetToolNormalBitmap( ID_TOOL_I2C_HELP, empty_xpm );
	m_tool_Display_I2C->EnableTool( ID_TOOL_I2C_HELP, false );

	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_BH1750_HELP, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_BH1750_HELP, false );
	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_BME280_HELP, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_BME280_HELP, false );

	m_toolBarSystem->EnableTool( ID_TOOL_TIMER_CONFIG, false );
	m_toolBarSystem->SetToolNormalBitmap( ID_TOOL_TIMER_CONFIG, empty_xpm );
	// ---------------------------------------------------------------------------

//	m_log->Enable( false );
//	m_log->Show( false );

	// === Grid handlers  ===
	m_grid->Connect( wxEVT_GRID_EDITOR_HIDDEN,
					 wxGridEventHandler( MyFrame::OnGridEditorHidden ),
					 NULL,
					 this );
	m_grid->Connect( wxEVT_GRID_EDITOR_SHOWN,
					 wxGridEventHandler( MyFrame::OnGridEditorShown ),
					 NULL,
					 this );


//Refresh();

//		OnInit();
//		//IsConnected		= false;
//		//CheckStartStop	= true;
//		//IsRun			= false;
//		//Stop = TRUE;
//	
//		//k = 0;
//		i  = m_grid->GetScrollLineX();
//		m  = i * 2;
//		n = m_grid->GetNumberCols();
//		for( i = 0; i < n; i++ )
//		{
//		j = m_grid->GetColSize( i );
//		m += j;
//		}
//		//i  = m_grid->GetColSize( 0 );
//		//n += i;
//		//i  = m_grid->GetColSize( 1 );
//		//n += i;
//	
//	
//	
//		GetSize( &x, &y );
//		//m_grid->SetMinSize( wxSize( 400, -1 ) );
//		//m_grid->SetSize( wxSize( 400, -1 ) );
//		SetMinSize( wxSize( x, y ) );
//		SetMaxSize( wxSize( ( x + 20 ), ( y + 20 ) ) );
//		//m_grid->Fit();
//		Fit();
//		SetSize( wxSize( x, y ) );
//		SetMaxSize( wxSize( -1, -1 ) );
//		m_grid->Refresh();
//		Refresh();
//	
//	// ???????????????????????????????????????????????????????????????????????????
//	
//	m_auinotebook->RemovePage( m_auinotebook->GetPageIndex( m_panel_config ) );
//	//m_auinotebook->RemovePage( m_auinotebook->GetPageIndex( m_panel_data ) );
//	//m_panel_data->Show( false );
//	////m_panel_config->Show( false );
//	
//	//m_auinotebook->AddPage( m_panel_data, wxT("Config"), false, wxNullBitmap );
//	m_auinotebook->AddPage( m_panel_config, wxT("Configuration"), true, wxNullBitmap );
//	m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_panel_data ) );
//	//m_auinotebook->Fit();
//	m_auinotebook->Refresh();
//	
//	// ???????????????????????????????????????????????????????????????????????????
//	
//	
//	
//	//m_usb_as_console->Hide();
//	//m_panel_config->Fit();
//	//m_panel_config->SetMaxSize( wxSize( -1, -1 ) );
//	
//	m_panel_config->Refresh();
//	
//	
//	m_log->AppendText( WORK_PATH );
//	m_log->AppendText( "\n" );
//	m_log->AppendText( USER_CONFIG_PATH );
//	m_log->AppendText( "\n" );
//	
//	s = USER_CONFIG_PATH + PATH_SEP + wxT( "mcfg" );
//	m_log->AppendText( s );
//	m_log->AppendText( "\n" );
//	
//	if( !wxDir::Exists( s ) )
//	{
//	m_log->AppendText( "dir not Exist\n" );
//	
//	if( !wxFileName::Mkdir(s))
//	{
//	//wxMessageBox( "dir Exist\n" );
//	//Close();
//	m_log->AppendText( "Not Create dir\n" );
//	}
//	else
//	{
//	m_log->AppendText( "Create dir\n" );
//	}
//	}
//	else
//	{
//	//wxFileName::FileExists
//	//bool FileExists() const
//	//static bool FileExists(const wxString& file)
//	//Returns true if the file with this name exists.
//	
//	//wxMessageBox( "dir Exist\n" );
//	//Close();
//	}
//	
//	s.Printf( "size can=%d\n", sizeof(can) );
//	m_log->AppendText( s );
//	
//	//m_configCAN->SetBitmapLabel( wxBitmap( empty_xpm ) );
//	//m_configCAN->Hide();
//	//m_bpButton41->SetBitmapLabel( wxBitmap( empty_xpm ) );
//	//m_bpButton21->SetBitmapLabel( wxBitmap( empty_xpm ) );
//	
//	
//	// ???????????????????????????????????????????????????????????????????????????
//	
//	
//	
//	
//	    //wxGridCellAttr *attr = new wxGridCellAttr;
//	                   //*attrRangeEditor = new wxGridCellAttr,
//	                   //*attrCombo = new wxGridCellAttr;
//	
//	    //attr->SetReadOnly();
//	    //m_grid->SetColAttr(1, attr);
//	m_grid->SetReadOnly(0,1);
//	
//	
//	m_toolBar->EnableTool( ID_TOOL_SAVE, false );
//	m_toolBar->EnableTool( ID_TOOL_CONNECT, false );
//	
//	m_toolBar->EnableTool( ID_CAN_CONFIG, false );
//	
//	
//	
//		//m_toolBar->EnableTool( ID_TOOL_STOP, false );
//		//m_toolBar->EnableTool( ID_TOOL_RUN, false );
//	
//		// Получить список портов Win
//		io_com = new DataIO_Com();
//		io_com->GetPortList( &port_list );
//		com_nn = port_list.Count();
//	
//		s = wxEmptyString;
//	//	m_com_choice->Clear();
//	
//	//	for( i = 0; i < com_nn; i++ )
//	//	{
//	//		m_com_choice->Append( port_list[i] );
//	//	}
//	
//	
//	// ---------------------------------------------------------------------------
//	// Run threads
//	// ---------------------------------------------------------------------------
//	
//	//	run_thread_ptr = CreateThread();
//	//	if( run_thread_ptr->Run() != wxTHREAD_NO_ERROR )
//	//	{
//	//		wxMessageBox( wxT( "Can't start Run thread!" ) );
//	//		Close();
//	//	}
//	//
//	//	//IsRunData = false;
//	//	data_thread_ptr = CreateDataThread();
//	//	data_thread_ptr->SetPriority( 100 );
//	//	if( data_thread_ptr->Run() != wxTHREAD_NO_ERROR )
//	//	{
//	//		wxMessageBox( wxT( "Can't start Data thread!" ) );
//	//		Close();
//	//	}
//	//
//	//	m_grid->Refresh();
//	//	n = m_grid->GetNumberRows();
//	//	if( n )
//	//	{
//	//		m_grid->DeleteRows( 0, n );
//	//	}
//	//	m_grid->Refresh();
//	//
//	//	m_text_x1->Show( FALSE );
//	//	m_text_x2->Show( FALSE );
//	//	m_text_y1->Show( FALSE );
//	//	m_text_y2->Show( FALSE );
//	//	m_x1->Show( FALSE );
//	//	m_x2->Show( FALSE );
//	//	m_y1->Show( FALSE );
//	//	m_y2->Show( FALSE );
}
// === end of MyFrame::MyFrame ===============================================


// ===========================================================================
MyFrame::~MyFrame()
// ===========================================================================
{
	// Disconnect Events
	m_grid->Disconnect( wxEVT_GRID_EDITOR_HIDDEN,
						wxGridEventHandler( MyFrame::OnGridEditorHidden ),
						NULL,
						this );
	m_grid->Disconnect( wxEVT_GRID_EDITOR_SHOWN,
						wxGridEventHandler( MyFrame::OnGridEditorShown ),
						NULL,
						this );
	delete IO_COM;

	Write_Cfg();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnExit( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	Close();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnSize( wxSizeEvent &event )
// ===========================================================================
{
//int max_x, max_y;
wxString s;
wxPoint pos = GetPosition();
wxSize size = event.GetSize();

//s.Printf(wxT("pos=(%d, %d), size x=%d y=%d\n"), pos.x, pos.y, size.x, size.y );
//m_statusBar->SetStatusText( s, 0 );
//_log->AppendText( s );



//if( !Win_MaxSize )
//{
//Win_PosX		= pos.x;
//Win_PosY		= pos.y;

//Win_SizeX		= size.x;
//Win_SizeY		= size.y;

//}


if( ( pos.x >= 0 ) && ( pos.y >= 0 ) )
{
Win_MaxSize		= false;

Win_PosX		= pos.x;
Win_PosY		= pos.y;

Win_SizeX		= size.x;
Win_SizeY		= size.y;

//s.Printf(_("--> pos=(%d, %d), size=(%d, %d)\n"), pos.x, pos.y, size.x, size.y );
//_log->AppendText( s );
}




//	wxString msg;
//	wxSize sizeAll = GetSize(),
//	sizeCl = GetClientSize();
//	msg.Printf(_("pos=(%d, %d), size=%dx%d or %dx%d (client=%dx%d)"),
//	pos.x, pos.y,
//	size.x, size.y,
//	sizeAll.x, sizeAll.y,
//	sizeCl.x, sizeCl.y);


//m_grid->Refresh();

//size = GetMaxSize();
//max_x = size.x;
//max_y = size.y;

//s.Printf(wxT("size max_x=%d max_y=%d\n"), max_x, max_y );
//m_log->AppendText( s );


	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMove( wxMoveEvent &event )
// ===========================================================================
{
wxString s;
wxPoint pos = GetPosition();
//wxSize size = event.GetSize();

//s.Printf(_("move pos=(%d, %d)\n"), pos.x, pos.y );
//m_statusBar->SetStatusText( s, 0 );

if( ( pos.x >= 0 ) && ( pos.y >= 0 ) )
{
Win_PosX	= pos.x;
Win_PosY	= pos.y;
}

//m_log->AppendText( wxT( s ) );

m_grid->Refresh();
//Refresh();
    event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMaximized( wxMaximizeEvent &event )
// ===========================================================================
{
Win_MaxSize		= true;
//wxLogMessage(_T("Frame maximized"));
//m_statusBar->SetStatusText( wxT( "Frame maximized" ), 0 );
//Refresh();
//m_log->AppendText( wxT( "Frame maximized\n" ) );
	event.Skip();
}
// ===========================================================================


//void MyFrame::OnCellLeftClick( wxGridEvent& ev )
//{
//wxString s;
//    s.Printf(_T("Left click at row %d, col %d"), ev.GetRow(), ev.GetCol()); m_log->AppendText( 
//
//    // you must call event skip if you want default grid processing
//    // (cell highlighting etc.)
//    //
//    ev.Skip();
//}


BEGIN_EVENT_TABLE( MyFrame, MyFrameFB )
	EVT_MENU( ID_TOOL_NEW_PRJ,		MyFrame::OnTool_New_Prj )
	EVT_MENU( ID_TOOL_SAVE,			MyFrame::OnTool_Save_Prj )
	EVT_MENU( ID_TOOL_EXIT,			MyFrame::OnExit )
	EVT_MENU( ID_TOOL_UART_CONFIG,	MyFrame::OnTool_UART_config )
	EVT_MENU( ID_TOOL_INS_ROW,		MyFrame::OnInsRow )
	EVT_MENU( ID_TOOL_DEL_ROW,		MyFrame::OnDelRow )
	EVT_MENU( ID_TOOL_ABOUT,		MyFrame::OnMyAbout )

	EVT_MAXIMIZE( MyFrame::OnMaximized )
	EVT_SIZE( MyFrame::OnSize )
	EVT_MOVE( MyFrame::OnMove )

    EVT_GRID_EDITOR_HIDDEN( MyFrame::OnEditorHidden )
    EVT_GRID_CELL_CHANGE( MyFrame::OnCellValueChanged )

//    EVT_GRID_CELL_LEFT_CLICK( MyFrame::OnCellLeftClick )

//	EVT_MENU( ID_TOOL_CONNECT,	MyFrame::OnConnect )
//	EVT_MENU( ID_TOOL_REFRESH,	MyFrame::OnRefresh )
END_EVENT_TABLE()
