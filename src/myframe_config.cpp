/*
	Name:			myframe_config.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


// ===========================================================================
void MyFrame::Disable_Config()
// ===========================================================================
{
	// Hide sizers
	// ---------------------------------------------------------------------------
	sbSizerInterfaces->Show( false );
	sbSizerIndicators->Show( false );
	sbSizerSensors->Show( false );
	sbSizerSystem->Show( false );

	// Lines
	m_staticline_indicators->Show( false );
	m_staticline_sensors->Show( false );
	m_staticline_system->Show( false );
	m_staticline_bottom->Show( false );

	// --- Tools -----------------------------------------------------------------
	m_main_tool->EnableTool( ID_TOOL_SAVE, false );
	m_main_tool->EnableTool( ID_TOOL_GENERATE, false );
	m_main_tool->EnableTool( ID_TOOL_CONNECT, false );

//	m_tool_data->SetToolNormalBitmap( ID_TOOL_INS_ROW, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_INS_ROW, false );
//	m_tool_data->SetToolNormalBitmap( ID_TOOL_DEL_ROW, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_DEL_ROW, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_ROW_UP, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_ROW_UP, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_ROW_DOWN, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_ROW_DOWN, false );
	m_tool_data->SetToolNormalBitmap( ID_TOOL_RUN, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_RUN, false );

//	// ---------------------------------------------------------------------------
	m_auinotebook->RemovePage( m_auinotebook->GetPageIndex( m_panel_log ) );
//	m_auinotebook->RemovePage( m_auinotebook->GetPageIndex( m_config_window ) );
}
// ===========================================================================


// ===========================================================================
void MyFrame::Enable_Config()
// ===========================================================================
{
	// Show/Hide sizers
	// ---------------------------------------------------------------------------

	// Interfaces
	// ----------
//	sbSizerInterfaces->Show( true );
	sbSizerSerial->Show( true );
//	m_tool_UART->Show( true );
//	m_check_UART->Show( true );
//	m_check_USB_VCP->Show( true );
//	m_check_USB_console->Show( true );
//	sbSizerCAN->Show( false );
//	m_check_CAN_MCP2515->Enable( false );
//	m_check_CAN_Internal->Show( false );
//	sbSizerEth->Show( false );

	// Indicators
	// ----------
//	sbSizerIndicators->Show( true );
//	sbSizerLED->Show( true );
//	m_check_PC13->Show( true );

//	sbSizerDisplayI2C->Show( true );
//	m_check_LCD1602->Show( true );
//	m_check_8574->Show( true );
//	m_check_8574A->Show( true );
//	m_check_SSD1306->Show( false );

//	m_staticline4->Show( true );
//	m_staticline5->Show( true );
//	m_staticline71->Show( true );
//	m_staticline8->Show( true );
//	m_staticline9->Show( true );
//	m_staticline10->Show( true );
//	m_staticline11->Show( true );
//	m_staticline14->Show( true );

	// Disable lines DS1306
//	m_staticline5->Show( false );
//	m_staticline9->Show( false );
//	m_staticline10->Show( false );
//	m_staticline14->Show( false );

	// Sensors
	// -------
//	sbSizerSensors->Show( true );
//	m_check_BME280->Show( false );
//	m_check_BH1750->Show( false );
//	m_check_CCS811->Show( false );
//	m_check_EC11->Show( false );

	// System
//	sbSizerSystem->Show( true );
//	m_toolBarSystem->Show( true );
//	m_check_WatchDog->Show( false );
//	m_check_MCO->Show( false );
//	m_check_Timer->Show( false );
//	m_text_ibt_fix_time->Show( false );
//	m_ibt_fix_time->Show( false );

	// Screen lines
//	m_staticline_indicators->Show( true );
//	m_staticline_sensors->Show( true );
//	m_staticline_system->Show( true );
//	m_staticline_bottom->Show( true );


	// --- Tools -----------------------------------------------------------------
	m_main_tool->EnableTool( ID_TOOL_SAVE, true );
	m_main_tool->EnableTool( ID_TOOL_GENERATE, true );
//	m_main_tool->EnableTool( ID_TOOL_CONNECT, false );

//	m_tool_data->SetToolNormalBitmap( ID_TOOL_INS_ROW, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_INS_ROW, true );
//	m_tool_data->SetToolNormalBitmap( ID_TOOL_DEL_ROW, empty_xpm );
	m_tool_data->EnableTool( ID_TOOL_DEL_ROW, true );
//	m_tool_data->SetToolNormalBitmap( ID_TOOL_ROW_UP, empty_xpm );
//	m_tool_data->EnableTool( ID_TOOL_ROW_UP, false );
//	m_tool_data->SetToolNormalBitmap( ID_TOOL_ROW_DOWN, empty_xpm );
//	m_tool_data->EnableTool( ID_TOOL_ROW_DOWN, false );
//	m_tool_data->SetToolNormalBitmap( ID_TOOL_RUN, empty_xpm );
//	m_tool_data->EnableTool( ID_TOOL_RUN, false );

	m_tool_UART->SetToolNormalBitmap( ID_TOOL_UART_CONFIG, empty_xpm );
	m_tool_UART->EnableTool( ID_TOOL_UART_CONFIG, false );
//	m_tool_UART->SetToolNormalBitmap( ID_TOOL_SERIAL_HELP, empty_xpm );
//	m_tool_UART->EnableTool( ID_TOOL_SERIAL_HELP, false );

	m_tool_CAN->SetToolNormalBitmap( ID_TOOL_CAN_CFG, empty_xpm );
	m_tool_CAN->EnableTool( ID_TOOL_CAN_CFG, false );
	m_tool_CAN->SetToolNormalBitmap( ID_TOOL_CAN_HELP, empty_xpm );
	m_tool_CAN->EnableTool( ID_TOOL_CAN_HELP, false );

	m_tool_Ethernet->SetToolNormalBitmap( ID_TOOL_ETH_CFG, empty_xpm );
	m_tool_Ethernet->EnableTool( ID_TOOL_ETH_CFG, false );
	m_tool_Ethernet->SetToolNormalBitmap( ID_TOOL_ETH_HELP, empty_xpm );
	m_tool_Ethernet->EnableTool( ID_TOOL_ETH_HELP, false );

//	m_tool_Display_I2C->SetToolNormalBitmap( ID_TOOL_I2C_HELP, empty_xpm );
//	m_tool_Display_I2C->EnableTool( ID_TOOL_I2C_HELP, false );

	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_BME280_HELP, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_BME280_HELP, false );
	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_BH1750_HELP, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_BH1750_HELP, false );
	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_CCS811_HELP, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_CCS811_HELP, false );
	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_EC11_CONFIG, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_EC11_CONFIG, false );
	m_toolBarSensor->SetToolNormalBitmap( ID_TOOL_EC11_HELP, empty_xpm );
	m_toolBarSensor->EnableTool( ID_TOOL_EC11_HELP, false );

	m_toolBarSystem->EnableTool( ID_TOOL_TIMER_CONFIG, false );
	m_toolBarSystem->SetToolNormalBitmap( ID_TOOL_TIMER_CONFIG, empty_xpm );
}
// ===========================================================================


// ===========================================================================
int MyFrame::Set_Lists( void )
// ===========================================================================
{
	int			i, n;
	wxString	s;

	if( ce2 ) { delete ce2; }
	if( ce3 ) { delete ce3; }
	if( ce5 ) { delete ce5; }

	for( i = 0; i < MAX_GRID_NN; i++ )
	{
		m_grid_r[i].c0 = wxEmptyString;
		m_grid_r[i].c2 = 0;
		m_grid_r[i].c3 = 0;
		m_grid_r[i].c4 = wxEmptyString;
		m_grid_r[i].c5 = 0;
	}

	if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
	{
		n = sizeof( VAR_1XX_TYPES ) / sizeof( int );
		ce2 = new wxGridCellChoiceEditor( n, VAR_1XX_TYPES );
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
		//SEL_PORT[]	= "PA13";	// JTAG
		//SEL_PORT[]	= "PA14";	// JTAG
		//SEL_PORT[]	= "PA15";	// JTAG
		SEL_PORT[14]	= "PB0";
		SEL_PORT[15]	= "PB1";
		//SEL_PORT[]	= "PB2";	// boot1
		//SEL_PORT[]	= "PB3";	// JTAG
		//SEL_PORT[]	= "PB4";	// JTAG
		SEL_PORT[16]	= "PB5";
		SEL_PORT[17]	= "PB6";
		SEL_PORT[18]	= "PB7";
		SEL_PORT[19]	= "PB8";
		SEL_PORT[20]	= "PB9";
		SEL_PORT[21]	= "PB10";
		SEL_PORT[22]	= "PB11";
		SEL_PORT[23]	= "PB12";
		SEL_PORT[24]	= "PB13";
		SEL_PORT[25]	= "PB14";
		SEL_PORT[26]	= "PB15";
		SEL_PORT[27]	= "PC13";
		PORT_NN			= 28;
		if( PORT_NN > MAX_PORT_NN )
		{
			PORT_NN = MAX_PORT_NN;
		}
		for( i = 0; i < PORT_NN; i++ )
		{
			//cs3[i] = SEL_PORT[i];
		}
		ce3 = new wxGridCellChoiceEditor( PORT_NN, SEL_PORT );
		cs5[0] = wxEmptyString;
		cs5[1] = wxT( "R" );
		cs5[2] = wxT( "W" );
		ce5 = new wxGridCellChoiceEditor( 3, cs5 );
	}
	else
	{
		return 1;
	}
	return 0;
}
// ===========================================================================


// ===========================================================================
bool MyFrame::Parse_Port( wxString port, unsigned int *port_name, unsigned int *port_nn )
// ===========================================================================
{
	long		l;
	wxString	s;

	if( ( port.Len() < 3 ) || ( port.Len() > 4 ) )
	{
		return true;
	}

	s = port.Mid( 0, 2 );
	if( s == wxT( "PA" ) )
	{
		*port_name = 0;
	}
	else
	if( s == wxT( "PB" ) )
	{
		*port_name = 1;
	}
	else
	if( s == wxT( "PC" ) )
	{
		*port_name = 2;
	}
	else
	{
		return true;
	}

	*port_nn = 0;
	s = port.Mid( 2 );
	if( !s.ToLong( &l ) )
	{
		return true;
	}

	if( ( l < 0 ) && ( l > 15 ) )
	{
		*port_name = 0;
		return true;
	}
	else
	{
		*port_nn = l;
	}
	return false;
}
// ===========================================================================


// ===========================================================================
bool MyFrame::Check_Port( wxString port, unsigned int row = 0 )
// ===========================================================================
{
	unsigned int	i, n_rows;
	bool			check_UART, check_USB_VCP, check_SPI2, check_I2C1;
	bool			check_PC13, check_MCO, check_W5500;
	bool			check_CAN_Internal, check_CAN_MCP2515;
	wxString		s;

	check_UART			= true;
	check_USB_VCP		= true;
	check_SPI2			= true;
	check_CAN_MCP2515	= true;
	check_W5500			= true;
	check_CAN_Internal	= true;
	check_I2C1			= true;
	check_PC13			= true;
	check_MCO			= true;

	n_rows = m_grid->GetNumberRows();
	if( n_rows > 0 )
	{
		for( i = 0; i < n_rows; i++ )
		{
			s = m_grid->GetCellValue( i, 3 );
			if( s != wxEmptyString )
			{
				if( ( s == wxT( "PA9" ) ) || ( s == wxT( "PA10" ) ) )	// UART1
				{
					check_UART = false;
				}

				if( ( s == wxT( "PA11" ) ) || ( s == wxT( "PA12" ) ) )	// USB VCP
				{
					check_USB_VCP = false;
				}

				if( ( s == wxT( "PB6" ) ) || ( s == wxT( "PB7" ) ) )
				{
					check_I2C1 = false;
				}

				if( s == wxT( "PC13" ) )
				{
					check_PC13 = false;
				}

				if( s == wxT( "PA8" ) )
				{
					check_MCO = false;
				}

				if( i != row )
				{
					if( s == port )
					{
						wxMessageBox( wxT( "The port is already use" ), wxT( "Error" ), wxICON_HAND );
						return true;
					}
				}
			}
		}

		if( check_UART )
		{
			m_check_UART->Enable( true );
		}
		else
		{
			if( m_check_UART->GetValue() )
			{
				wxMessageBox( wxT( "The port UART1 is already use" ), wxT( "Error" ), wxICON_HAND );
				return true;
			}
			else
			{
				m_check_UART->Enable( false );
			}
		}

		if( check_USB_VCP )
		{
			m_check_USB_VCP->Enable( true );
		}
		else
		{
			if( m_check_USB_VCP->GetValue() )
			{
				wxMessageBox( wxT( "The port USB is already use" ), wxT( "Error" ), wxICON_HAND );
				return true;
			}
			else
			{
				m_check_USB_VCP->Enable( false );
			}
		}

		if( check_I2C1 )
		{
			m_check_LCD1602->Enable( true );
			m_check_SSD1306->Enable( true );
		}
		else
		{
			if( m_check_LCD1602->GetValue() || m_check_SSD1306->GetValue() )
			{
				wxMessageBox( wxT( "The port I2C1 is already use" ), wxT( "Error" ), wxICON_HAND );
				return true;
			}
			else
			{
			m_check_LCD1602->Enable( false );
			m_check_SSD1306->Enable( false );
			}
		}

		if( check_PC13 )
		{
			m_check_PC13->Enable( true );
		}
		else
		{
			if( m_check_PC13->GetValue() )
			{
				wxMessageBox( wxT( "The port PC13 is already use" ), wxT( "Error" ), wxICON_HAND );
				return true;
			}
			else
			{
				m_check_PC13->Enable( false );
			}
		}
	}
	return false;
}
// ===========================================================================


// ===========================================================================
void MyFrame::Check_Config()
// ===========================================================================
{
	unsigned int	i, n_rows;
	bool			check_UART, check_USB_VCP, check_SPI2, check_I2C1;
	bool			check_PC13, check_MCO, check_W5500;
	bool			check_CAN_Internal, check_CAN_MCP2515;
	wxString		s;

	check_UART			= true;
	check_USB_VCP		= true;
	check_SPI2			= true;
	check_CAN_MCP2515	= true;
	check_W5500			= true;
	check_CAN_Internal	= true;
	check_I2C1			= true;
	check_PC13			= true;
	check_MCO			= true;

	n_rows = m_grid->GetNumberRows();
	if( n_rows > 0 )
	{
		for( i = 0; i < n_rows; i++ )
		{
			s = m_grid->GetCellValue( i, 3 );
			if( s != wxEmptyString )
			{
				if( ( s == wxT( "PA9" ) ) || ( s == wxT( "PA10" ) ) )	// UART1
				{
					check_UART = false;
				}

				if( ( s == wxT( "PA11" ) ) || ( s == wxT( "PA12" ) ) )	// USB VCP
				{
					check_USB_VCP = false;
				}

				if( ( s == wxT( "PB6" ) ) || ( s == wxT( "PB7" ) ) )
				{
					check_I2C1 = false;
				}

				if( s == wxT( "PC13" ) )
				{
					check_PC13 = false;
				}

				if( s == wxT( "PA8" ) )
				{
					check_MCO = false;
				}
			}
		}

		if( check_UART )
		{
			m_check_UART->Enable( true );
		}

		if( check_USB_VCP )
		{
			m_check_USB_VCP->Enable( true );
		}

		if( check_I2C1 )
		{
			m_check_LCD1602->Enable( true );
			m_check_SSD1306->Enable( true );
		}

		if( check_PC13 )
		{
			m_check_PC13->Enable( true );
		}
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::Clear_Project()
// ===========================================================================
{
	int	n;

	n = m_grid->GetNumberRows();
	if( n )
	{
		m_grid->BeginBatch();
		m_grid->ClearGrid();
		m_grid->DeleteRows( 0, n, false );
		m_grid->EndBatch();
	}

	Disable_Config();

	m_text_mcu->SetValue( wxEmptyString );
	m_text_comment->SetValue( wxEmptyString );
	m_tool_com_port->SetValue( wxEmptyString );

	m_check_UART->SetValue( false );
	m_check_USB_VCP->SetValue( false );
	m_check_USB_console->SetValue( false );
	m_check_W5500->SetValue( false );
	m_check_PC13->SetValue( false );
	m_check_LCD1602->SetValue( false );
	m_check_8574->SetValue( false );
	m_check_8574A->SetValue( false );
	m_check_SSD1306->SetValue( false );
	m_check_BME280->SetValue( false );
	m_check_BH1750->SetValue( false );
	m_check_WatchDog->SetValue( false );
	m_check_MCO->SetValue( false );
	m_check_Timer->SetValue( false );

	PRJ_CHANGED		= false;
	PRJ_NAME		= wxEmptyString;
	PRJ_MCU			= wxEmptyString;
	PRJ_COMMENT		= wxEmptyString;

	PORT_NN		= 0;
	SN_FW		= 0;

	COM_NN		= -1;
	COM_SPEED	= -1;
}
// ===========================================================================
