/*
	Name:			myframe.cpp
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
#include "myframe_config.cpp"
#include "files.cpp"
#include "new_prj.cpp"
#include "myframe_tools_events.cpp"
#include "myframe_virtual_events.cpp"
#include "fw_gen.cpp"

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
	int			x, y;
	wxString	s;

	SetIcon( wxIcon( dev_xpm ) );	// Set Icon
	_log = m_log;

	if( OnPathInit() )
	{
		Close();
	}

	GetSize( &x, &y );
	SetMinSize( wxSize( x, y ) );
	SetMaxSize( wxSize( ( x + 20 ), ( y + 20 ) ) );
	Fit();
	SetSize( wxSize( x, y ) );
	SetMaxSize( wxSize( -1, -1 ) );

	Disable_Config();
	Clear_Project();

	// Set grid
	m_grid->SetRowLabelSize( 40 );
	m_grid->SetColLabelSize( 20 );
	m_grid->DisableDragRowSize();
	m_grid->SetDefaultCellBackgroundColour( m_data_panel->GetBackgroundColour() );
	m_grid->EnableDragGridSize( false );
	//m_grid->EnableDragColSize( false );

	m_grid->AppendCols( 6 );

	m_grid->SetColLabelValue( 0, wxT( "Name" ) );
	//m_grid->SetColLabelValue( 1, wxT( "Value" ) );
	m_grid->SetColLabelValue( 1, wxT( "" ) );
	m_grid->SetColLabelValue( 2, wxT( "Type" ) );
	m_grid->SetColLabelValue( 3, wxT( "Port" ) );
	m_grid->SetColLabelValue( 4, wxT( "Comment" ) );
	//m_grid->SetColLabelValue( 5, wxT( "Sync" ) );
	m_grid->SetColLabelValue( 5, wxT( "" ) );

	m_grid->SetColSize( 0, 200 );
	//m_grid->SetColSize( 1, 100 );
	m_grid->SetColSize( 1, 20 );
	m_grid->SetColSize( 2, 180 );
	m_grid->SetColSize( 3, 60 );
	m_grid->SetColSize( 4, 400 );
	m_grid->SetColSize( 5, 20 );
	//m_grid->SetColSize( 5, 40 );

	wxGridCellAttr *pAttr = new wxGridCellAttr;
	pAttr->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	m_grid->SetColAttr( 0, pAttr );
	m_grid->SetColAttr( 1, pAttr );
	m_grid->SetColAttr( 2, pAttr );
	m_grid->SetColAttr( 3, pAttr );
	m_grid->SetColAttr( 4, pAttr );
	m_grid->SetColAttr( 5, pAttr );

	if( !Read_Cfg() )
	{
		if( !Read_Prj() )
		{
			Enable_Config();
		}
	}

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
		Win_MaxSize = true;
		Maximize();
		}
		else
		{
			Win_MaxSize = false;
		}
	}
	m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_data_panel ) );
//	m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_panel_log ) );
	m_config_window->Fit();
	srand( ( unsigned ) time( NULL ) );
}
// === end of MyFrame ========================================================


// ===========================================================================
MyFrame::~MyFrame()
// ===========================================================================
{
	Asc_to_Save();
	Write_Cfg();
	//m_grid->BeginBatch();
	//m_grid->ClearGrid();
	//m_grid->EndBatch();
	delete IO_COM;
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
	wxString	s;
	wxPoint		pos  = GetPosition();
	wxSize		size = event.GetSize();

	if( ( pos.x >= 0 ) && ( pos.y >= 0 ) )
	{
		Win_MaxSize		= false;
		Win_PosX		= pos.x;
		Win_PosY		= pos.y;
		Win_SizeX		= size.x;
		Win_SizeY		= size.y;
	}
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMove( wxMoveEvent &event )
// ===========================================================================
{
	wxString	s;
	wxPoint		pos = GetPosition();

	if( ( pos.x >= 0 ) && ( pos.y >= 0 ) )
	{
		Win_PosX	= pos.x;
		Win_PosY	= pos.y;
	}
	m_grid->Refresh();
    event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMaximized( wxMaximizeEvent &event )
// ===========================================================================
{
	Win_MaxSize = true;
	event.Skip();
}
// ===========================================================================


BEGIN_EVENT_TABLE( MyFrame, MyFrameFB )
	EVT_MENU( ID_TOOL_NEW_PRJ,		MyFrame::OnTool_New_Prj )
	EVT_MENU( ID_TOOL_OPEN_PRJ,		MyFrame::OnTool_Open_Prj )
	EVT_MENU( ID_TOOL_CLOSE_PRJ,	MyFrame::OnTool_Close_Prj )
	EVT_MENU( ID_TOOL_SAVE,			MyFrame::OnTool_Save_Prj )
	EVT_MENU( ID_TOOL_GENERATE,		MyFrame::OnTool_Generate_FW )
	EVT_MENU( ID_TOOL_EXIT,			MyFrame::OnExit )
	EVT_MENU( ID_TOOL_UART_CONFIG,	MyFrame::OnTool_UART_config )
	EVT_MENU( ID_TOOL_SERIAL_HELP,	MyFrame::OnTool_UART_help )
	EVT_MENU( ID_TOOL_I2C_HELP,		MyFrame::OnTool_I2C_help )
	EVT_MENU( ID_TOOL_INS_ROW,		MyFrame::OnInsRow )
	EVT_MENU( ID_TOOL_DEL_ROW,		MyFrame::OnDelRow )
	EVT_MENU( ID_TOOL_ABOUT,		MyFrame::OnMyAbout )
	EVT_MENU( ID_TOOL_FUNCTIONS,	MyFrame::OnMyFunctions )

	EVT_MAXIMIZE( MyFrame::OnMaximized )
	EVT_SIZE( MyFrame::OnSize )
	EVT_MOVE( MyFrame::OnMove )

    //EVT_GRID_EDITOR_HIDDEN( MyFrame::OnEditorHidden )
    EVT_GRID_CELL_CHANGE( MyFrame::OnCellValueChanged )

//    EVT_GRID_CELL_LEFT_CLICK( MyFrame::OnCellLeftClick )

//	EVT_MENU( ID_TOOL_CONNECT,	MyFrame::OnConnect )
//	EVT_MENU( ID_TOOL_REFRESH,	MyFrame::OnRefresh )
END_EVENT_TABLE()
