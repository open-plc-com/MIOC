/*
	Name:			fw_gen.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/08
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


// ===========================================================================
void MyFrame::OnTool_Generate_FW( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	unsigned int	i, j, k, m, n1, n2, n_rows;
//	bool			grid_err	= false;
	bool			dummy_var	= false;
	wxString		s, s_path, s_name, s_ext;
	wxString		buf, buf_s;
	wxString		s_c;
	wxFile			file;

	m_statusBar->SetStatusText( wxEmptyString );
	if( PRJ_MCU != wxEmptyString )
	{
		SN_FW	= rand();
		buf		= wxEmptyString;
		buf_s	= wxEmptyString;

		wxFileName::SplitPath( PRJ_NAME, &s_path, &s_name, &s_ext );
		s_name = s_path + PATH_SEP + wxT( "main" );
		if( !wxDir::Exists( s_name ) )
		{
			s = wxT( "Directory \"" ) + s_name + wxT( "\" not exist; break." );
			m_statusBar->SetStatusText( s );
			return;
		}
		s_name = s_path + PATH_SEP + wxT( "main" ) + PATH_SEP + wxT( "bsp.h" );

//_log->AppendText( PRJ_NAME ); _log->AppendText( wxT( "\r\n" ) );
//_log->AppendText( s_name ); _log->AppendText( wxT( "\r\n" ) );

		// Check grid
		// ---------------------------------------------------------------------------
		n_rows = m_grid->GetNumberRows();
		for( i = 0; i < n_rows; i++ )
		{
			s = m_grid->GetCellValue( i, 0 );

			for( j = 0; j < i; j++ )
			{
				s_c = m_grid->GetCellValue( j, 0 );
				if( s == s_c )
				{
					m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_data_panel ) );
					m_grid->SetCellBackgroundColour( i, 0, *wxRED );
					m_statusBar->SetStatusText( wxT( "Duplicate name" ) );
					return;
				}
			}

			if( s == wxEmptyString )
			{
				m_grid->SetCellBackgroundColour( i, 0, *wxRED );
				m_grid->Refresh();
				m_statusBar->SetStatusText( wxEmptyString );
				m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_data_panel ) );
				return;
			}

			s = m_grid->GetCellValue( i, 2 );
			if( s == wxEmptyString )
			{
				m_grid->SetCellBackgroundColour( i, 2, *wxRED );
				m_grid->Refresh();
				m_statusBar->SetStatusText( wxEmptyString );
				m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_data_panel ) );
				return;
			}
			else
			if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
			{
				if( ( s == wxT( "GPIO_Mode_AIN" ) ) ||
					( s == wxT( "GPIO_Mode_IN_FLOATING" ) ) ||
					( s == wxT( "GPIO_Mode_IPD" ) ) ||
					( s == wxT( "GPIO_Mode_IPU" ) ) ||
					( s == wxT( "GPIO_Mode_Out_OD" ) ) ||
					( s == wxT( "GPIO_Mode_Out_PP" ) ) ||
					( s == wxT( "DS18B20" ) ) ||
					( s == wxT( "iButton" ) ) )
				{
					s = m_grid->GetCellValue( i, 3 );
					if( s == wxEmptyString )
					{
						m_grid->SetCellBackgroundColour( i, 3, *wxRED );
						m_grid->SetReadOnly( i, 3, false );
						m_grid->Refresh();
						m_statusBar->SetStatusText( wxEmptyString );
						m_auinotebook->SetSelection( m_auinotebook->GetPageIndex( m_data_panel ) );
						return;
					}
				}

/*
    struct Var_Struct
    {
        unsigned int    *name_ptr;
        uint16_t         var_type;      // Variable type:
        uint16_t         gpio_type;     // GPIO type:
        GPIO_TypeDef    *gpio;          // GPIO Port
        uint16_t         gpio_pin;      // GPIO Pin
        uint16_t         err_1w;        // 1-Wire continuous error count
        uint16_t         ibutton_time;  // The rest of the time for remember the value iButton
    } Var[VAR_NN];

                            Var
                            type
                            ----
    bool                    1
    int8                    2
    unsigned int8           3
    int16                   4
    unsigned int16          5
    int32                   6
    unsigned int32          7
    int64                   8
    unsigned int64          9       GPIO
    float                   10      type
    double                  11      ----
    GPIO_Mode_AIN           5       1       ( uint16_t )
    GPIO_Mode_IN_FLOATING   1       2       ( bool     )
    GPIO_Mode_IPD           1       3       ( bool     )
    GPIO_Mode_IPU           1       4       ( bool     )
    GPIO_Mode_Out_OD        1       5       ( bool     )
    GPIO_Mode_Out_PP        1       6       ( bool     )
    DS18B20                 11      7       ( double   )
    iButton                 9       8       ( uint64_t )
    LCD_1602_STR_1          ---             ( char[20] )
    LCD_1602_STR_2          ---             ( char[20] )

    Var[i].gpio = GPIOX
    Var[i].gpio_pin = GPIO_Pin_Nn
*/

			}
		}

		buf.Append( wxT( "#ifndef BSP_DEF\r\n" ) );
		buf.Append( wxT( "#define BSP_DEF\r\n" ) );
		buf.Append( wxT( "/* ======================================================================== */\r\n" ) );
		buf.Append( wxT( "/* Board Support Package File                                               */\r\n" ) );
		buf.Append( wxT( "/* ======================================================================== */\r\n\r\n" ) );

		buf.Append( wxT( "/*\r\n" ) );
		buf.Append( wxT( "                            Var\r\n" ) );
		buf.Append( wxT( "                            type\r\n" ) );
		buf.Append( wxT( "                            ----\r\n" ) );
		buf.Append( wxT( "    bool                    1\r\n" ) );
		buf.Append( wxT( "    int8                    2\r\n" ) );
		buf.Append( wxT( "    unsigned int8           3\r\n" ) );
		buf.Append( wxT( "    int16                   4\r\n" ) );
		buf.Append( wxT( "    unsigned int16          5\r\n" ) );
		buf.Append( wxT( "    int32                   6\r\n" ) );
		buf.Append( wxT( "    unsigned int32          7\r\n" ) );
		buf.Append( wxT( "    int64                   8\r\n" ) );
		buf.Append( wxT( "    unsigned int64          9       GPIO\r\n" ) );
		buf.Append( wxT( "    float                   10      type\r\n" ) );
		buf.Append( wxT( "    double                  11      ----\r\n" ) );
		if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
		{
			buf.Append( wxT( "    GPIO_Mode_AIN           5       1       ( uint16_t )\r\n" ) );
			buf.Append( wxT( "    GPIO_Mode_IN_FLOATING   1       2       ( bool     )\r\n" ) );
			buf.Append( wxT( "    GPIO_Mode_IPD           1       3       ( bool     )\r\n" ) );
			buf.Append( wxT( "    GPIO_Mode_IPU           1       4       ( bool     )\r\n" ) );
			buf.Append( wxT( "    GPIO_Mode_Out_OD        1       5       ( bool     )\r\n" ) );
			buf.Append( wxT( "    GPIO_Mode_Out_PP        1       6       ( bool     )\r\n" ) );
		}
		buf.Append( wxT( "    DS18B20                 11      7       ( double   )\r\n" ) );
		buf.Append( wxT( "    iButton                 9       8       ( int64_t  )\r\n" ) );
		buf.Append( wxT( "    LCD_1602_STR_1          ---             ( char[20] )\r\n" ) );
		buf.Append( wxT( "    LCD_1602_STR_2          ---             ( char[20] )\r\n" ) );
		buf.Append( wxT( "*/\r\n\r\n" ) );

		s.Printf( wxT( "#define SN_FW %d\r\n" ), SN_FW );
		buf.Append(s);
		if( m_check_UART->GetValue() )
		{
			buf.Append( wxT( "#define USE_UART1  // Use UART1\r\n" ) );
		}
		if( m_check_USB_VCP->GetValue() )
		{
			buf.Append( wxT( "#define USB_VCP    // Use USB as VCP\r\n" ) );
		}
		if( m_check_USB_console->GetValue() )
		{
			buf.Append( wxT( "#define VCP_CONS   // USB VCP as Console\r\n" ) );
		}
		if( m_check_PC13->GetValue() )
		{
			buf.Append( wxT( "#define LED_BLINK  // PC13 LED blink\r\n" ) );
		}
		if( m_check_LCD1602->GetValue() )
		{
			buf.Append( wxT( "#define LCD_1602   // Use LCD 1602\r\n" ) );
		}
		if( m_check_8574->GetValue() )
		{
			buf.Append( wxT( "#define PCF8574    // I2C chip of LCD_1602\r\n" ) );
		}
		if( m_check_8574A->GetValue() )
		{
			buf.Append( wxT( "#define PCF8574A   // I2C chip of LCD_1602\r\n" ) );
		}
//		if( m_check_SSD1306->GetValue() )
//		{
//		}
//		if( m_check_CAN_Internal->GetValue() )
//		{
//		}
//		if( m_check_CAN_MCP2515->GetValue() )
//		{
//			buf.Append( wxT( "#define CAN_2515     // Use CAN MCP2515\r\n\r\n" ) );
//		}
//		if( m_check_W5500->GetValue() )
//		{
//		}
//		if( m_check_BME280->GetValue() )
//		{
//		}
//		if( m_check_BH1750->GetValue() )
//		{
//		}
//		if( m_check_WatchDog->GetValue() )
//		{
//		}
//		if( m_check_MCO->GetValue() )
//		{
//		}
//		if( m_check_Timer->GetValue() )
//		{
//		}
//		m_ibt_fix_time->GetValue()

//		buf.Append( wxT( "\r\n" ) );

		buf.Append( wxT( "#define VAR_NN" ) );
		if( n_rows == 0 )
		{
			buf.Append( wxT( " 1\r\n\r\n" ) );
			dummy_var = true;
		}
		else
		{
			s.Printf( wxT( " %d\r\n\r\n" ), n_rows );
			buf.Append( s.c_str() );
		}

		buf.Append( wxT( "struct Var_Struct\r\n" ) );
		buf.Append( wxT( "{\r\n" ) );
		buf.Append( wxT( "    unsigned int  *name_ptr;\r\n" ) );
		buf.Append( wxT( "    uint16_t       var_type;      // Variable type:\r\n" ) );
		buf.Append( wxT( "    uint16_t       gpio_type;     // GPIO type\r\n" ) );
		buf.Append( wxT( "    GPIO_TypeDef  *gpio;          // GPIO Port\r\n" ) );
		buf.Append( wxT( "    uint16_t       gpio_pin;      // GPIO Pin\r\n" ) );
		buf.Append( wxT( "    uint16_t       sync;          // Sync (R/W)\r\n" ) );
		buf.Append( wxT( "    uint16_t       err_1w;        // 1-Wire continuous error count\r\n" ) );
		buf.Append( wxT( "    uint16_t       ibutton_time;  // The rest of the time for remember the value iButton\r\n" ) );
		buf.Append( wxT( "} Var[VAR_NN];\r\n\r\n" ) );

		buf_s.Append( wxT( "\r\nvoid init_bsp( void )\r\n{\r\n" ) );
		buf_s.Append( wxT( "    int i;\r\n\r\n" ) );
		buf_s.Append( wxT( "    for( i = 0; i < VAR_NN; i++ )\r\n" ) );
		buf_s.Append( wxT( "    {\r\n" ) );
		buf_s.Append( wxT( "        Var[i].name_ptr     = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].var_type     = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].gpio_type    = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].gpio         = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].gpio_pin     = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].sync         = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].err_1w       = 0;\r\n" ) );
		buf_s.Append( wxT( "        Var[i].ibutton_time = 0;\r\n" ) );
		buf_s.Append( wxT( "    }\r\n\r\n" ) );

		if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
		{
			for( i = 0; i < n_rows; i++ )
			{
				k = 0;
				m = 0;
				s = m_grid->GetCellValue( i, 2 );
				if( s == wxT( "bool" ) )
				{
					buf.Append( wxT( "bool      " ) );
					k = 1;
				}
				else
				if( s == wxT( "int8" ) )
				{
					buf.Append( wxT( "int8_t    " ) );
					k = 2;
				}
				else
				if( s == wxT( "unsigned int8" ) )
				{
					buf.Append( wxT( "uint8_t   " ) );
					k = 3;
				}
				else
				if( s == wxT( "int16" ) )
				{
					buf.Append( wxT( "int16_t   " ) );
					k = 4;
				}
				else
				if( s == wxT( "unsigned int16" ) )
				{
					buf.Append( wxT( "uint16_t  " ) );
					k = 5;
				}
				else
				if( s == wxT( "int32" ) )
				{
					buf.Append( wxT( "int32_t   " ) );
					k = 6;
				}
				else
				if( s == wxT( "unsigned int32" ) )
				{
					buf.Append( wxT( "uint32_t  " ) );
					k = 7;
				}
				else
				if( s == wxT( "int64" ) )
				{
					buf.Append( wxT( "int64_t   " ) );
					k = 8;
				}
				else
				if( s == wxT( "unsigned int64" ) )
				{
					buf.Append( wxT( "uint64_t  " ) );
					k = 9;
				}
				else
				if( s == wxT( "float" ) )
				{
					buf.Append( wxT( "float     " ) );
					k = 10;
				}
				else
				if( s == wxT( "double" ) )
				{
					buf.Append( wxT( "double    " ) );
					k = 11;
				}
				else
				if( s == wxT( "GPIO_Mode_AIN" ) )
				{
					buf.Append( wxT( "uint16_t  " ) );
					k = 5;
					m = 1;
				}
				else
				if( s == wxT( "GPIO_Mode_IN_FLOATING" ) )
				{
					buf.Append( wxT( "bool      " ) );
					k = 1;
					m = 2;
				}
				else
				if( s == wxT( "GPIO_Mode_IPD" ) )
				{
					buf.Append( wxT( "bool      " ) );
					k = 1;
					m = 3;
				}
				else
				if( s == wxT( "GPIO_Mode_IPU" ) )
				{
					buf.Append( wxT( "bool      " ) );
					k = 1;
					m = 4;
				}
				else
				if( s == wxT( "GPIO_Mode_Out_OD" ) )
				{
					buf.Append( wxT( "bool      " ) );
					k = 1;
					m = 5;
				}
				else
				if( s == wxT( "GPIO_Mode_Out_PP" ) )
				{
					buf.Append( wxT( "bool      " ) );
					k = 1;
					m = 6;
				}
				else
				if( s == wxT( "DS18B20" ) )
				{
					buf.Append( wxT( "double    " ) );
					k = 11;
					m = 7;
				}
				else
				if( s == wxT( "iButton" ) )
				{
					buf.Append( wxT( "uint64_t  " ) );
					k = 9;
					m = 8;
				}

				if( k )
				{
					s = m_grid->GetCellValue( i, 0 );
					buf.Append( s.c_str() );
					buf.Append( wxT( ";\r\n" ) );

					s_c.Printf( wxT( "    Var[%d].name_ptr=(unsigned int*)&%s;" ), i, s.c_str() ); buf_s.Append( s_c );
					s_c.Printf( wxT( " Var[%d].var_type=%d;" ), i, k ); buf_s.Append( s_c );

					if( m )
					{
						s_c.Printf( wxT( " Var[%d].gpio_type=%d;" ), i, m ); buf_s.Append( s_c );
						s_c = m_grid->GetCellValue( i, 3 );

						if( !Parse_Port( s_c, &n1, &n2 ) )
						{
							if( n1 == 0 )
							{
								s_c.Printf( wxT( " Var[%d].gpio=GPIOA;" ), i );
							}
							else
							if( n1 == 1 )
							{
								s_c.Printf( wxT( " Var[%d].gpio=GPIOB;" ), i );
							}
							else
							if( n1 == 2 )
							{
								s_c.Printf( wxT( " Var[%d].gpio=GPIOC;" ), i );
							}
							buf_s.Append( s_c );

							s_c.Printf( wxT( " Var[%d].gpio_pin=GPIO_Pin_%d;" ), i, n2 );
							buf_s.Append( s_c );
						}
					}

					s_c = m_grid->GetCellValue( i, 5 );
					if( s_c == wxT( "R" ) )
					{
						s_c.Printf( wxT( " Var[%d].sync=1;" ), i ); buf_s.Append( s_c );
					}
					else
					if( s_c == wxT( "W" ) )
					{
						s_c.Printf( wxT( " Var[%d].sync=2;" ), i ); buf_s.Append( s_c );
					}

					buf_s.Append( wxT( "\r\n" ) );
				}
			}
		}

		buf_s.Append( "}\r\n\r\n" );
		buf_s.Append( "#endif // BSP_DEF\r\n" );
		buf_s.Append( "/* ======================================================================== */\r\n" );

		if( file.Open( s_name.c_str(), wxFile::write ) )
		{
			file.Write( buf );
			file.Write( buf_s );
			file.Close();
			s_c = wxT( "FW generated by, file \"" ) + s_name + wxT( "\"" );
			m_statusBar->SetStatusText( s_c );
			//m_statusBar->SetStatusText( wxT( "FW generated by " ) );
		}
	}
}
// ===========================================================================
