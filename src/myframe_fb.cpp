#include "myframe_fb.h"

#include "disk.xpm"
#include "empty.xpm"
#include "exit.xpm"
#include "help.xpm"
#include "logo.xpm"
#include "make_fw.xpm"
#include "play.xpm"
#include "setting_tools.xpm"
#include "table_row_delete.xpm"
#include "table_row_down.xpm"
#include "table_row_insert.xpm"
#include "table_row_up.xpm"

///////////////////////////////////////////////////////////////////////////

MyFrameFB::MyFrameFB( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	m_menubar = new wxMenuBar( 0 );
	m_menu_file = new wxMenu();
	wxMenuItem* m_menu_new_project;
	m_menu_new_project = new wxMenuItem( m_menu_file, ID_TOOL_NEW_PRJ, wxString( wxT("New Project\tCtrl+N") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menu_new_project );
	
	wxMenuItem* m_menu_open_project;
	m_menu_open_project = new wxMenuItem( m_menu_file, ID_TOOL_OPEN_PRJ, wxString( wxT("Open Project\tCtrl+O") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menu_open_project );
	
	wxMenuItem* m_menu_change_project;
	m_menu_change_project = new wxMenuItem( m_menu_file, ID_TOOL_CHANGE_PRJ, wxString( wxT("Change Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menu_change_project );
	m_menu_change_project->Enable( false );
	
	wxMenuItem* m_menu_save_project;
	m_menu_save_project = new wxMenuItem( m_menu_file, ID_TOOL_SAVE, wxString( wxT("Save project\tCtrl+S") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menu_save_project );
	m_menu_save_project->Enable( false );
	
	wxMenuItem* m_menu_close_project;
	m_menu_close_project = new wxMenuItem( m_menu_file, ID_TOOL_CLOSE_PRJ, wxString( wxT("Close Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menu_close_project );
	m_menu_close_project->Enable( false );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menu_file->AppendSeparator();
	
	wxMenuItem* m_menu_exit;
	m_menu_exit = new wxMenuItem( m_menu_file, ID_TOOL_EXIT, wxString( wxT("Exit\tAlt+X") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menu_exit );
	
	m_menubar->Append( m_menu_file, wxT("&File") ); 
	
	m_menu_tools = new wxMenu();
	wxMenuItem* m_menu_com_connect;
	m_menu_com_connect = new wxMenuItem( m_menu_tools, ID_TOOL_COM_CONNECT, wxString( wxT("Connect/Disconnect COM-port") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_tools->Append( m_menu_com_connect );
	m_menu_com_connect->Enable( false );
	
	wxMenuItem* m_menu_select_com;
	m_menu_select_com = new wxMenuItem( m_menu_tools, ID_TOOL_UART_CONFIG, wxString( wxT("COM-port configure") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_tools->Append( m_menu_select_com );
	m_menu_select_com->Enable( false );
	
	m_menubar->Append( m_menu_tools, wxT("&Tools") ); 
	
	m_help = new wxMenu();
	wxMenuItem* m_menu_about;
	m_menu_about = new wxMenuItem( m_help, ID_TOOL_ABOUT, wxString( wxT("About\tF1") ) , wxEmptyString, wxITEM_NORMAL );
	m_help->Append( m_menu_about );
	
	m_menubar->Append( m_help, wxT("?") ); 
	
	this->SetMenuBar( m_menubar );
	
	m_statusBar = this->CreateStatusBar( 1, 0, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_main_tool = new wxToolBar( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	m_main_tool->AddTool( ID_TOOL_EXIT, wxT("tool"), wxBitmap( exit_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Exit"), wxEmptyString ); 
	m_main_tool->AddTool( ID_TOOL_SAVE, wxT("tool"), wxBitmap( disk_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Save project"), wxEmptyString ); 
	m_main_tool->AddTool( ID_TOOL_GENERATE, wxT("tool"), wxBitmap( make_fw_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Code generation"), wxEmptyString ); 
	m_main_tool->AddSeparator(); 
	m_main_tool->AddTool( ID_TOOL_CONNECT, wxT("tool"), wxBitmap( empty_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("COM connect/disconnect"), wxEmptyString ); 
	m_staticText1 = new wxStaticText( m_main_tool, wxID_ANY, wxT("COM-port : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_main_tool->AddControl( m_staticText1 );
	m_tool_com_port = new wxTextCtrl( m_main_tool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxTE_READONLY );
	m_main_tool->AddControl( m_tool_com_port );
	m_bitmap_com_indicator = new wxStaticBitmap( m_main_tool, wxID_ANY, wxBitmap( empty_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	m_main_tool->AddControl( m_bitmap_com_indicator );
	m_main_tool->AddSeparator(); 
	m_staticText4 = new wxStaticText( m_main_tool, wxID_ANY, wxT("MCU: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_main_tool->AddControl( m_staticText4 );
	m_text_mcu = new wxTextCtrl( m_main_tool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 140,-1 ), wxTE_READONLY );
	m_main_tool->AddControl( m_text_mcu );
	m_main_tool->AddSeparator(); 
	m_text_comment = new wxTextCtrl( m_main_tool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	m_main_tool->AddControl( m_text_comment );
	m_main_tool->AddSeparator(); 
	m_main_tool->Realize();
	
	bSizer2->Add( m_main_tool, 0, wxEXPAND, 5 );
	
	m_auinotebook = new wxAuiNotebook( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_WINDOWLIST_BUTTON );
	m_auinotebook->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	m_data_panel = new wxPanel( m_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_tool_data = new wxToolBar( m_data_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_tool_data->AddTool( ID_TOOL_INS_ROW, wxT("tool"), wxBitmap( table_row_insert_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Insert row"), wxEmptyString ); 
	m_tool_data->AddTool( ID_TOOL_DEL_ROW, wxT("tool"), wxBitmap( table_row_delete_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Delete row"), wxEmptyString ); 
	m_tool_data->AddTool( ID_TOOL_ROW_UP, wxT("tool"), wxBitmap( table_row_up_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Row Up"), wxEmptyString ); 
	m_tool_data->AddTool( ID_TOOL_ROW_DOWN, wxT("tool"), wxBitmap( table_row_down_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Row Down"), wxEmptyString ); 
	m_tool_data->AddSeparator(); 
	m_tool_data->AddTool( ID_TOOL_RUN, wxT("tool"), wxBitmap( play_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Run"), wxEmptyString ); 
	m_tool_data->AddSeparator(); 
	m_tool_data->Realize();
	
	bSizer3->Add( m_tool_data, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( m_data_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_grid = new wxGridCtrl( m_data_panel, wxID_ANY );
	m_grid->CreateGrid( 0, 0 );
	m_grid->SetRowLabelSize( 20 );
	m_grid->SetColLabelSize( 20 );
	m_grid->DisableDragRowSize();
	m_grid->SetDefaultCellBackgroundColour( m_data_panel->GetBackgroundColour() );
	m_grid->EnableDragGridSize( false );
	m_grid->EnableDragColSize( false );
	
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
	m_grid->SetColSize( 1, 100 );
	m_grid->SetColSize( 2, 180 );
	m_grid->SetColSize( 3, 60 );
	m_grid->SetColSize( 4, 400 );
	m_grid->SetColSize( 5, 40 );
	
	wxGridCellAttr *pAttr = new wxGridCellAttr;
	pAttr->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	m_grid->SetColAttr( 0, pAttr );
	m_grid->SetColAttr( 1, pAttr );
	m_grid->SetColAttr( 2, pAttr );
	m_grid->SetColAttr( 3, pAttr );
	m_grid->SetColAttr( 4, pAttr );
	m_grid->SetColAttr( 5, pAttr );
	
	bSizer3->Add( m_grid, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_data_panel->SetSizer( bSizer3 );
	m_data_panel->Layout();
	bSizer3->Fit( m_data_panel );
	m_auinotebook->AddPage( m_data_panel, wxT("Data"), true, wxNullBitmap );
	m_config_window = new wxScrolledWindow( m_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_config_window->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	sbSizerInterfaces = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("Interfaces") ), wxHORIZONTAL );
	
	sbSizerSerial = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("Serial (UART; Virtual COM-port)") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizerUART;
	bSizerUART = new wxBoxSizer( wxHORIZONTAL );
	
	m_tool_UART = new wxToolBar( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_check_UART = new wxCheckBox( m_tool_UART, wxID_ANY, wxT("UART1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tool_UART->AddControl( m_check_UART );
	m_tool_UART->AddTool( ID_TOOL_UART_CONFIG, wxT("tool"), wxBitmap( setting_tools_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("COM-port configure"), wxEmptyString ); 
	m_tool_UART->AddTool( ID_TOOL_SERIAL_HELP, wxT("tool"), wxBitmap( help_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Serial Help"), wxEmptyString ); 
	m_tool_UART->AddSeparator(); 
	m_tool_UART->Realize();
	
	bSizerUART->Add( m_tool_UART, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	sbSizerSerial->Add( bSizerUART, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizerUSB;
	bSizerUSB = new wxBoxSizer( wxVERTICAL );
	
	m_check_USB_VCP = new wxCheckBox( m_config_window, wxID_ANY, wxT("USB VCP"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerUSB->Add( m_check_USB_VCP, 0, wxRIGHT|wxLEFT, 5 );
	
	m_check_USB_console = new wxCheckBox( m_config_window, wxID_ANY, wxT("USB as Console"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerUSB->Add( m_check_USB_console, 0, wxRIGHT|wxLEFT, 5 );
	
	sbSizerSerial->Add( bSizerUSB, 0, wxEXPAND, 5 );
	
	sbSizerInterfaces->Add( sbSizerSerial, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	sbSizerCAN = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("CAN") ), wxHORIZONTAL );
	
	m_tool_CAN = new wxToolBar( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_check_CAN_Internal = new wxCheckBox( m_tool_CAN, wxID_ANY, wxT("Internal"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tool_CAN->AddControl( m_check_CAN_Internal );
	m_tool_CAN->AddSeparator(); 
	m_check_CAN_MCP2515 = new wxCheckBox( m_tool_CAN, wxID_ANY, wxT("MCP2515"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tool_CAN->AddControl( m_check_CAN_MCP2515 );
	m_tool_CAN->AddTool( ID_TOOL_CAN_CFG, wxT("tool"), wxBitmap( setting_tools_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("CAN config"), wxEmptyString ); 
	m_tool_CAN->AddTool( ID_TOOL_CAN_HELP, wxT("tool"), wxBitmap( help_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("CAN Help"), wxEmptyString ); 
	m_tool_CAN->Realize();
	
	sbSizerCAN->Add( m_tool_CAN, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	sbSizerInterfaces->Add( sbSizerCAN, 0, wxRIGHT, 5 );
	
	sbSizerEth = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("Ethernet") ), wxHORIZONTAL );
	
	m_tool_Ethernet = new wxToolBar( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_check_W5500 = new wxCheckBox( m_tool_Ethernet, wxID_ANY, wxT("W5500"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tool_Ethernet->AddControl( m_check_W5500 );
	m_tool_Ethernet->AddTool( ID_TOOL_ETH_CFG, wxT("tool"), wxBitmap( setting_tools_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_tool_Ethernet->AddTool( ID_TOOL_ETH_HELP, wxT("tool"), wxBitmap( help_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_tool_Ethernet->Realize();
	
	sbSizerEth->Add( m_tool_Ethernet, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	sbSizerInterfaces->Add( sbSizerEth, 0, wxRIGHT, 5 );
	
	bSizer4->Add( sbSizerInterfaces, 0, wxALL, 5 );
	
	sbSizerIndicators = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("Indicators") ), wxHORIZONTAL );
	
	sbSizerLED = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("LED") ), wxHORIZONTAL );
	
	m_check_PC13 = new wxCheckBox( m_config_window, wxID_ANY, wxT("LED blink (PC13)"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerLED->Add( m_check_PC13, 0, wxALL, 5 );
	
	sbSizerIndicators->Add( sbSizerLED, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	sbSizerDisplayI2C = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("Display I2C") ), wxHORIZONTAL );
	
	m_staticline8 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	sbSizerDisplayI2C->Add( m_staticline8, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline71 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline71, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_check_LCD1602 = new wxCheckBox( m_config_window, wxID_ANY, wxT("LCD 1602"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_check_LCD1602, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline4 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline4, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_check_8574 = new wxCheckBox( m_config_window, wxID_ANY, wxT("PCF8574(T)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_check_8574, 0, wxALL, 5 );
	
	m_check_8574A = new wxCheckBox( m_config_window, wxID_ANY, wxT("PCF8574A(T)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_check_8574A, 0, wxALL, 5 );
	
	bSizer7->Add( bSizer9, 0, 0, 5 );
	
	m_staticline11 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline11, 0, wxEXPAND|wxTOP, 5 );
	
	sbSizerDisplayI2C->Add( bSizer7, 0, 0, 5 );
	
	m_staticline3 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	sbSizerDisplayI2C->Add( m_staticline3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline9 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline9, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_check_SSD1306 = new wxCheckBox( m_config_window, wxID_ANY, wxT("SSD1306"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_check_SSD1306, 0, wxALL, 5 );
	
	m_staticline10 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline10, 0, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( m_config_window, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer8->Add( m_staticText8, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline14 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline14, 0, wxEXPAND|wxTOP, 5 );
	
	sbSizerDisplayI2C->Add( bSizer8, 0, 0, 5 );
	
	m_staticline5 = new wxStaticLine( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	sbSizerDisplayI2C->Add( m_staticline5, 0, wxEXPAND|wxRIGHT, 5 );
	
	m_tool_Display_I2C = new wxToolBar( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_tool_Display_I2C->AddTool( ID_TOOL_I2C_HELP, wxT("tool"), wxBitmap( help_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("I2C Help"), wxEmptyString ); 
	m_tool_Display_I2C->Realize();
	
	sbSizerDisplayI2C->Add( m_tool_Display_I2C, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizerIndicators->Add( sbSizerDisplayI2C, 0, wxBOTTOM|wxRIGHT, 5 );
	
	bSizer4->Add( sbSizerIndicators, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	sbSizerSensors = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("Sensors") ), wxHORIZONTAL );
	
	m_toolBarSensor = new wxToolBar( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_check_BME280 = new wxCheckBox( m_toolBarSensor, wxID_ANY, wxT("BME280"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBarSensor->AddControl( m_check_BME280 );
	m_toolBarSensor->AddTool( ID_TOOL_BME280_HELP, wxT("tool"), wxBitmap( help_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_toolBarSensor->AddSeparator(); 
	m_check_BH1750 = new wxCheckBox( m_toolBarSensor, wxID_ANY, wxT("BH1750"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBarSensor->AddControl( m_check_BH1750 );
	m_toolBarSensor->AddTool( ID_TOOL_BH1750_HELP, wxT("tool"), wxBitmap( help_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_toolBarSensor->Realize();
	
	sbSizerSensors->Add( m_toolBarSensor, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer4->Add( sbSizerSensors, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	sbSizerSystem = new wxStaticBoxSizer( new wxStaticBox( m_config_window, wxID_ANY, wxT("System") ), wxHORIZONTAL );
	
	m_toolBarSystem = new wxToolBar( m_config_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER ); 
	m_checkBoxWatchDog = new wxCheckBox( m_toolBarSystem, wxID_ANY, wxT("WatchDog"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBarSystem->AddControl( m_checkBoxWatchDog );
	m_toolBarSystem->AddSeparator(); 
	m_checkBoxMCO = new wxCheckBox( m_toolBarSystem, wxID_ANY, wxT("MCO"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBarSystem->AddControl( m_checkBoxMCO );
	m_toolBarSystem->AddSeparator(); 
	m_checkBoxTimer = new wxCheckBox( m_toolBarSystem, wxID_ANY, wxT("Timer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBarSystem->AddControl( m_checkBoxTimer );
	m_toolBarSystem->AddTool( ID_TOOL_TIMER_CONFIG, wxT("tool"), wxBitmap( setting_tools_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_toolBarSystem->Realize();
	
	sbSizerSystem->Add( m_toolBarSystem, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer4->Add( sbSizerSystem, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_config_window->SetSizer( bSizer4 );
	m_config_window->Layout();
	bSizer4->Fit( m_config_window );
	m_auinotebook->AddPage( m_config_window, wxT("Configuration"), false, wxNullBitmap );
	m_panel_log = new wxPanel( m_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	m_log = new wxTextCtrl( m_panel_log, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer19->Add( m_log, 1, wxALL|wxEXPAND, 5 );
	
	m_panel_log->SetSizer( bSizer19 );
	m_panel_log->Layout();
	bSizer19->Fit( m_panel_log );
	m_auinotebook->AddPage( m_panel_log, wxT("log"), false, wxNullBitmap );
	
	bSizer2->Add( m_auinotebook, 1, wxEXPAND, 5 );
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_grid->Connect( wxEVT_CHAR, wxKeyEventHandler( MyFrameFB::OnGridChar ), NULL, this );
	m_check_UART->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_UART1 ), NULL, this );
	m_check_USB_VCP->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_USB_VCP ), NULL, this );
	m_check_USB_console->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_USB_console ), NULL, this );
	m_check_CAN_Internal->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_CAN_Internal ), NULL, this );
	m_check_CAN_MCP2515->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_CAN_MCP2515 ), NULL, this );
	m_check_W5500->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_W5500 ), NULL, this );
	m_check_PC13->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_PC13 ), NULL, this );
}

MyFrameFB::~MyFrameFB()
{
	// Disconnect Events
	m_grid->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyFrameFB::OnGridChar ), NULL, this );
	m_check_UART->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_UART1 ), NULL, this );
	m_check_USB_VCP->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_USB_VCP ), NULL, this );
	m_check_USB_console->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_USB_console ), NULL, this );
	m_check_CAN_Internal->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_CAN_Internal ), NULL, this );
	m_check_CAN_MCP2515->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_CAN_MCP2515 ), NULL, this );
	m_check_W5500->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_W5500 ), NULL, this );
	m_check_PC13->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrameFB::On_check_PC13 ), NULL, this );
	
}

New_Project_FB::New_Project_FB( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( m_panel3, wxID_ANY, wxT("MCU :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxString m_choice_MCUChoices[] = { wxT("STM32F103C8T6") };
	int m_choice_MCUNChoices = sizeof( m_choice_MCUChoices ) / sizeof( wxString );
	m_choice_MCU = new wxChoice( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_MCUNChoices, m_choice_MCUChoices, 0 );
	m_choice_MCU->SetSelection( 0 );
	fgSizer1->Add( m_choice_MCU, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT, 5 );
	
	m_staticText10 = new wxStaticText( m_panel3, wxID_ANY, wxT("Project Name :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_project_name = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	fgSizer1->Add( m_project_name, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT, 5 );
	
	m_staticText3 = new wxStaticText( m_panel3, wxID_ANY, wxT("Project path and Name :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_path_project_name = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	bSizer12->Add( m_path_project_name, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	m_dir = new wxDirPickerCtrl( m_panel3, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	bSizer12->Add( m_dir, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	fgSizer1->Add( bSizer12, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText7 = new wxStaticText( m_panel3, wxID_ANY, wxT("Comment :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_text_comment = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	fgSizer1->Add( m_text_comment, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	bSizer11->Add( fgSizer1, 1, wxALL, 5 );
	
	m_staticline6 = new wxStaticLine( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline6, 0, wxEXPAND, 5 );
	
	m_sdb = new wxStdDialogButtonSizer();
	m_sdbOK = new wxButton( m_panel3, wxID_OK );
	m_sdb->AddButton( m_sdbOK );
	m_sdbCancel = new wxButton( m_panel3, wxID_CANCEL );
	m_sdb->AddButton( m_sdbCancel );
	m_sdb->Realize();
	bSizer11->Add( m_sdb, 0, wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_panel3->SetSizer( bSizer11 );
	m_panel3->Layout();
	bSizer11->Fit( m_panel3 );
	bSizer10->Add( m_panel3, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer10 );
	this->Layout();
	bSizer10->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_dir->Connect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( New_Project_FB::OnDirChanged ), NULL, this );
	m_sdbOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( New_Project_FB::OnOkButton ), NULL, this );
}

New_Project_FB::~New_Project_FB()
{
	// Disconnect Events
	m_dir->Disconnect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( New_Project_FB::OnDirChanged ), NULL, this );
	m_sdbOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( New_Project_FB::OnOkButton ), NULL, this );
	
}

Set_COM_FB::Set_COM_FB( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( m_panel4, wxID_ANY, wxT("COM-port :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer2->Add( m_staticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_com_choiceChoices;
	m_com_choice = new wxChoice( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_com_choiceChoices, 0 );
	m_com_choice->SetSelection( 0 );
	fgSizer2->Add( m_com_choice, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_staticText6 = new wxStaticText( m_panel4, wxID_ANY, wxT("Speed :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer2->Add( m_staticText6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_speed_choiceChoices[] = { wxT("300"), wxT("600"), wxT("1200"), wxT("2400"), wxT("4800"), wxT("9600"), wxT("19200"), wxT("38400"), wxT("57600"), wxT("115200"), wxT("230400"), wxT("460800"), wxT("921600") };
	int m_speed_choiceNChoices = sizeof( m_speed_choiceChoices ) / sizeof( wxString );
	m_speed_choice = new wxChoice( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_speed_choiceNChoices, m_speed_choiceChoices, 0 );
	m_speed_choice->SetSelection( 9 );
	fgSizer2->Add( m_speed_choice, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	bSizer14->Add( fgSizer2, 1, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( m_panel4, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( m_panel4, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	bSizer14->Add( m_sdbSizer2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_panel4->SetSizer( bSizer14 );
	m_panel4->Layout();
	bSizer14->Fit( m_panel4 );
	bSizer13->Add( m_panel4, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_com_choice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( Set_COM_FB::OnChoiseCOM ), NULL, this );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Set_COM_FB::OnOkButton ), NULL, this );
}

Set_COM_FB::~Set_COM_FB()
{
	// Disconnect Events
	m_com_choice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( Set_COM_FB::OnChoiseCOM ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Set_COM_FB::OnOkButton ), NULL, this );
	
}

My_Help::My_Help( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap2 = new wxStaticBitmap( m_panel5, wxID_ANY, wxBitmap( logo_xpm ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer16->Add( m_bitmap2, 0, wxALL, 5 );
	
	m_staticline13 = new wxStaticLine( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer16->Add( m_staticline13, 0, wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( m_panel5, wxID_ANY, wxT("MIOC - Module of Input/Output Configurator v0.2.1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( 18, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer16->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_hyperlink = new wxHyperlinkCtrl( m_panel5, wxID_ANY, wxT("Open-PLC"), wxT("open-plc.com"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer16->Add( m_hyperlink, 0, wxALL, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( m_panel5, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3->Realize();
	bSizer16->Add( m_sdbSizer3, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_panel5->SetSizer( bSizer16 );
	m_panel5->Layout();
	bSizer16->Fit( m_panel5 );
	bSizer15->Add( m_panel5, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer15 );
	this->Layout();
	bSizer15->Fit( this );
	
	this->Centre( wxBOTH );
}

My_Help::~My_Help()
{
}

PG_Help_OK::PG_Help_OK( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap = new wxStaticBitmap( m_panel, wxID_ANY, wxBitmap( empty_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	m_bitmap->Hide();
	
	bSizer2->Add( m_bitmap, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_grid = new wxGrid( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_grid->CreateGrid( 1, 1 );
	m_grid->EnableEditing( false );
	m_grid->EnableGridLines( false );
	m_grid->EnableDragGridSize( false );
	m_grid->SetMargins( 0, 0 );
	
	// Columns
	m_grid->EnableDragColMove( false );
	m_grid->EnableDragColSize( false );
	m_grid->SetColLabelSize( 0 );
	m_grid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_grid->EnableDragRowSize( true );
	m_grid->SetRowLabelSize( 0 );
	m_grid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	m_grid->SetLabelBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	m_grid->SetLabelTextColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	
	// Cell Defaults
	m_grid->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	m_grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer2->Add( m_grid, 0, wxALL, 5 );
	
	m_staticline = new wxStaticLine( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline, 0, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	m_sdbSizer = new wxStdDialogButtonSizer();
	m_sdbSizerOK = new wxButton( m_panel, wxID_OK );
	m_sdbSizer->AddButton( m_sdbSizerOK );
	m_sdbSizer->Realize();
	bSizer2->Add( m_sdbSizer, 1, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );
	
	m_panel->SetSizer( bSizer2 );
	m_panel->Layout();
	bSizer2->Fit( m_panel );
	bSizer1->Add( m_panel, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

PG_Help_OK::~PG_Help_OK()
{
}

PG_Help_OK_Cancel::PG_Help_OK_Cancel( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap = new wxStaticBitmap( m_panel, wxID_ANY, wxBitmap( empty_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	m_bitmap->Hide();
	
	bSizer2->Add( m_bitmap, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_grid = new wxGrid( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_grid->CreateGrid( 1, 1 );
	m_grid->EnableEditing( false );
	m_grid->EnableGridLines( false );
	m_grid->EnableDragGridSize( false );
	m_grid->SetMargins( 0, 0 );
	
	// Columns
	m_grid->EnableDragColMove( false );
	m_grid->EnableDragColSize( false );
	m_grid->SetColLabelSize( 0 );
	m_grid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_grid->EnableDragRowSize( true );
	m_grid->SetRowLabelSize( 0 );
	m_grid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	m_grid->SetLabelBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	m_grid->SetLabelTextColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	
	// Cell Defaults
	m_grid->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	m_grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer2->Add( m_grid, 0, wxALL, 5 );
	
	m_staticline = new wxStaticLine( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline, 0, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	m_sdbSizer = new wxStdDialogButtonSizer();
	m_sdbSizerOK = new wxButton( m_panel, wxID_OK );
	m_sdbSizer->AddButton( m_sdbSizerOK );
	m_sdbSizerCancel = new wxButton( m_panel, wxID_CANCEL );
	m_sdbSizer->AddButton( m_sdbSizerCancel );
	m_sdbSizer->Realize();
	bSizer2->Add( m_sdbSizer, 1, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );
	
	m_panel->SetSizer( bSizer2 );
	m_panel->Layout();
	bSizer2->Fit( m_panel );
	bSizer1->Add( m_panel, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

PG_Help_OK_Cancel::~PG_Help_OK_Cancel()
{
}
