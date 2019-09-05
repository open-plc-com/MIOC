/*
	Name:			files.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include "tinyxml2.cpp"
namespace XML = tinyxml2;

// ===========================================================================
int MyFrame::OnPathInit( void )
// ===========================================================================
{
	wxString	s;

	wxStandardPathsBase &stdp = wxStandardPaths::Get();
	s = wxStandardPaths().GetExecutablePath();
	wxFileName::SplitPath( s, &WORK_PATH, &S_NAME, &S_EXT );
	PATH_SEP	= wxFileName::DirName( s ).GetPathSeparator();
	EXEC_PATH	= stdp.GetExecutablePath();
	DATA_DIR	= stdp.GetUserLocalDataDir();

	if( S_NAME != wxT( "mioc" ) )
	{
		return 1;
	}

	if( !wxDir::Exists( DATA_DIR ) )
	{
		if( !wxMkdir( DATA_DIR ) )
		{
			s = wxT( "Can't create dir\n\"" );
			s = s + DATA_DIR;
			s = s + wxT( "\"" );
			wxMessageBox( s );
			return 1;
		}
	}
	return 0;
}
// ===========================================================================


// ===========================================================================
int MyFrame::Read_Prj( void )
// ===========================================================================
{
	unsigned int		 i, j, m, n;
	long				 vl;
	const char			*AttributeText = 0;
	wxString			 s;
	XML::XMLDocument	 doc;
	XML::XMLElement		*r1, *e1;

	if( !doc.LoadFile( PRJ_NAME.c_str() ) )
	{
		r1 = doc.FirstChildElement( "PRJ" );
		if( r1 )
		{
			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "MCU" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				s = wxT( e1->GetText() );
				if( ( s == wxT( "STM32F103C8T6" ) ) || ( s == wxT( "STM32F103CBT6" ) ) )
				{
					PRJ_MCU = s;
				}
				else
				{
					PRJ_MCU = wxEmptyString;
					//Disable_Config();
					return 1;
				}

				m_text_mcu->SetValue( PRJ_MCU );

				if( PRJ_MCU != wxEmptyString )
				{
					if( Set_Lists() )
					{
						return 1;
					}
				}
				else
				{
					return 1;
				}

				e1 = r1->FirstChildElement( "PRJ_COMMENT" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					PRJ_COMMENT = s;
					m_text_comment->SetValue( s );
				}

				e1 = r1->FirstChildElement( "SN_FW" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s.ToLong( &vl ) )
					{
						SN_FW = vl;
					}
					else
					{
						SN_FW = 0;
					}
				}

				e1 = r1->FirstChildElement( "UART1" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_UART->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_UART->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "USB_VCP" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_USB_VCP->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_USB_VCP->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "USB_console" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_USB_console->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_USB_console->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "CAN_Internal" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_CAN_Internal->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_CAN_Internal->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "CAN_MCP2515" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_CAN_MCP2515->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_CAN_MCP2515->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "LED_BLINK" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_PC13->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_PC13->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "LCD1602" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_LCD1602->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_LCD1602->Enable( false );
					}
				}

				e1 = r1->FirstChildElement( "C8574" );
				if( e1 )
				{
					m_check_8574->SetValue( true );
				}

				e1 = r1->FirstChildElement( "C8574A" );
				if( e1 )
				{
					m_check_8574A->SetValue( true );
				}

				e1 = r1->FirstChildElement( "SSD1306" );
				if( e1 )
				{
					s = wxT( e1->GetText() );
					if( s == wxT( "C" ) )
					{
						m_check_SSD1306->SetValue( true );
					}
					else
					if( s == wxT( "D" ) )
					{
						m_check_SSD1306->Enable( false );
					}
				}

				//e1 = r1->FirstChildElement( "BME280" );
				//if( e1 )
				//{
					//m_check_BME280->SetValue( true );
				//}

				//e1 = r1->FirstChildElement( "BH1750" );
				//if( e1 )
				//{
					//m_check_BH1750->SetValue( true );
				//}

				//e1 = r1->FirstChildElement( "WatchDog" );
				//if( e1 )
				//{
					//m_check_WatchDog->SetValue( true );
				//}

				//e1 = r1->FirstChildElement( "MCO" );
				//if( e1 )
				//{
					//m_check_MCO->SetValue( true );
				//}

				//e1 = r1->FirstChildElement( "Timer" );
				//if( e1 )
				//{
					//m_check_Timer->SetValue( true );
				//}

				i = 0;
				m_grid->BeginBatch();
				e1 = r1->FirstChildElement( "GRID" );
				while( e1 )
				{
					m_grid->InsertRows( i, 1 );
					m_grid->SetReadOnly( i, 1 );
//					m_grid->SetReadOnly( i, 5 );

					if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
					{
						m = sizeof( VAR_1XX_TYPES ) / sizeof( int );
						ce2 = new wxGridCellChoiceEditor( m, VAR_1XX_TYPES );
						ce3 = new wxGridCellChoiceEditor( PORT_NN, SEL_PORT );
						ce5 = new wxGridCellChoiceEditor( 3, cs5 );
					}

					m_grid->SetCellEditor( i, 2, ce2 );
					m_grid->SetCellEditor( i, 3, ce3 );

					AttributeText = e1->Attribute( "C0" );
					if( AttributeText )
					{
						s = wxT( AttributeText );
						m_grid->SetCellValue( i, 0, s );
					}

					AttributeText = e1->Attribute( "C2" );
					if( AttributeText )
					{
						s = wxT( AttributeText );

						if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
						{
							m = sizeof( VAR_1XX_TYPES ) / sizeof( int );
							if( m )
							{
								n = 0;
								for( j = 0; j < m; j++ )
								{
									if( s == VAR_1XX_TYPES[j] )
									{
										n = j;
										break;
									}
								}

								if( ce2 )
								{
									m_grid->SetCellValue( i, 2, VAR_1XX_TYPES[n] );
								}
							}
						}
					}

					AttributeText = e1->Attribute( "C3" );
					if( AttributeText )
					{
						s = wxT( AttributeText );

						if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
						{
							n = 0;
							for( j = 0; j < (unsigned int) PORT_NN; j++ )
							{
								if( s == SEL_PORT[j] )
								{
									n = j;
									break;
								}
							}

							if( ce3 )
							{
								m_grid->SetCellValue( i, 3, SEL_PORT[n] );
							}

							if( !n )
							{
								m_grid->SetReadOnly( i, 3 );
							}
						}
					}

					AttributeText = e1->Attribute( "C4" );
					if( AttributeText )
					{
						s = wxT( AttributeText );
						m_grid->SetCellValue( i, 4, s );
					}

					AttributeText = e1->Attribute( "C5" );
					if( AttributeText )
					{
						m_grid->SetCellEditor( i, 5, ce5 );
						s = wxT( AttributeText );
						if( s == wxT( "R" ) )
						{
							m_grid->SetCellValue( i, 5, cs5[1] );
						}
						else
						if( s == wxT( "W" ) )
						{
							m_grid->SetCellValue( i, 5, cs5[2] );
						}
						else
						{
							m_grid->SetCellValue( i, 5, cs5[0] );
						}
					}

					e1 = e1->NextSiblingElement( "GRID" );
					i++;
				}
			m_grid->EndBatch();
			m_grid->ForceRefresh();
			return 0;
			}
		}
	}
	return 1;
}
// ===========================================================================


// ===========================================================================
void MyFrame::Write_Prj()
// ===========================================================================
{
	unsigned int		 i, n_rows;
	wxString			 s;
	XML::XMLDocument	 doc;
	XML::XMLElement		*e1;
	XML::XMLNode		*pRoot = doc.NewElement( "PRJ" );

	doc.InsertEndChild( doc.NewDeclaration( "xml version=\"1.0\"" ) );
	//doc.InsertEndChild( doc.NewDeclaration() );
	doc.InsertEndChild( pRoot );

	if( PRJ_MCU != wxEmptyString )
	{
	e1 = doc.NewElement("MCU");
	e1->SetText( PRJ_MCU.c_str() );
	pRoot->InsertEndChild( e1 );

		// ---------------------------------------------------------------------------
		if( PRJ_COMMENT != wxEmptyString )
		{
			e1 = doc.NewElement( "PRJ_COMMENT" );
			e1->SetText( PRJ_COMMENT.c_str() );
			pRoot->InsertEndChild( e1 );
		}

		s.Printf( wxT( "%u" ), SN_FW );
		e1 = doc.NewElement( "SN_FW" );
		e1->SetText( s.c_str() );
		pRoot->InsertEndChild( e1 );

		// --- m_check_UART ----------------------------------------------------------
		e1 = doc.NewElement( "UART1" );
		if( m_check_UART->GetValue() )
		{
			e1->SetText( "C" );
		}
		else
		{
			if( m_check_UART->IsEnabled() )
			{
				e1->SetText( "E" );
			}
			else
			{
				e1->SetText( "D" );
			}
		}
		pRoot->InsertEndChild( e1 );

		// --- m_check_USB_VCP -------------------------------------------------------
		e1 = doc.NewElement( "USB_VCP" );
		if( m_check_USB_VCP->GetValue() )
		{
			e1->SetText( "C" );
		}
		else
		{
			if( m_check_USB_VCP->IsEnabled() )
			{
				e1->SetText( "E" );
			}
			else
			{
				e1->SetText( "D" );
			}
		}
		pRoot->InsertEndChild( e1 );

		// --- m_check_USB_console ---------------------------------------------------
		e1 = doc.NewElement( "USB_console" );
		if( m_check_USB_console->GetValue() )
		{
			e1->SetText( "C" );
		}
		else
		{
			if( m_check_USB_console->IsEnabled() )
			{
				e1->SetText( "E" );
			}
			else
			{
				e1->SetText( "D" );
			}
		}
		pRoot->InsertEndChild( e1 );

//		// --- m_check_CAN_Internal --------------------------------------------------
//		e1 = doc.NewElement( "CAN_Internal" );
//		if( m_check_CAN_Internal->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_CAN_Internal->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

//		// --- m_check_CAN_MCP2515 ---------------------------------------------------
//		e1 = doc.NewElement( "CAN_MCP2515" );
//		if( m_check_CAN_MCP2515->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_CAN_MCP2515->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

		// --- m_check_PC13 ----------------------------------------------------------
		e1 = doc.NewElement( "LED_BLINK" );
		if( m_check_PC13->GetValue() )
		{
			e1->SetText( "C" );
		}
		else
		{
			if( m_check_PC13->IsEnabled() )
			{
				e1->SetText( "E" );
			}
			else
			{
				e1->SetText( "D" );
			}
		}
		pRoot->InsertEndChild( e1 );

		// --- m_check_LCD1602 -------------------------------------------------------
		e1 = doc.NewElement( "LCD1602" );
		if( m_check_LCD1602->GetValue() )
		{
			e1->SetText( "C" );
		}
		else
		{
			if( m_check_LCD1602->IsEnabled() )
			{
				e1->SetText( "E" );
			}
			else
			{
				e1->SetText( "D" );
			}
		}
		pRoot->InsertEndChild( e1 );

		// --- m_check_8574 ----------------------------------------------------------
		if( m_check_8574->GetValue() )
		{
			e1 = doc.NewElement( "C8574" );
			e1->SetText( "C" );
			pRoot->InsertEndChild( e1 );
		}

		// --- m_check_8574A ---------------------------------------------------------
		if( m_check_8574A->GetValue() )
		{
			e1 = doc.NewElement( "C8574A" );
			e1->SetText( "C" );
			pRoot->InsertEndChild( e1 );
		}

//		// --- m_check_SSD1306 -------------------------------------------------------
//		e1 = doc.NewElement( "SSD1306" );
//		if( m_check_SSD1306->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_SSD1306->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

//		// --- m_check_BME280 --------------------------------------------------------
//		e1 = doc.NewElement( "BME280" );
//		if( m_check_BME280->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_BME280->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

//		// --- m_check_BH1750 --------------------------------------------------------
//		e1 = doc.NewElement( "BH1750" );
//		if( m_check_BH1750->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_BH1750->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

//		// --- m_check_WatchDog ------------------------------------------------------
//		e1 = doc.NewElement( "WatchDog" );
//		if( m_check_WatchDog->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_WatchDog->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

//		// --- m_check_MCO -----------------------------------------------------------
//		e1 = doc.NewElement( "MCO" );
//		if( m_check_MCO->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_MCO->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

//		// --- m_check_Timer ---------------------------------------------------------
//		e1 = doc.NewElement( "Timer" );
//		if( m_check_Timer->GetValue() )
//		{
//			e1->SetText( "C" );
//		}
//		else
//		{
//			if( m_check_Timer->IsEnabled() )
//			{
//				e1->SetText( "E" );
//			}
//			else
//			{
//				e1->SetText( "D" );
//			}
//		}
//		pRoot->InsertEndChild( e1 );

		// --- m_grid ----------------------------------------------------------------
		n_rows = m_grid->GetNumberRows();
		if( n_rows > 0 )
		{
			for( i = 0; i < n_rows; i++ )
			{
				e1 = doc.NewElement( "GRID" );
				s = m_grid->GetCellValue( i, 0 );
				e1->SetAttribute( "C0", s.c_str() );
				s = m_grid->GetCellValue( i, 2 );
				e1->SetAttribute( "C2", s.c_str() );
				s = m_grid->GetCellValue( i, 3 );
				e1->SetAttribute( "C3", s.c_str() );
				s = m_grid->GetCellValue( i, 4 );
				e1->SetAttribute( "C4", s.c_str() );
				s = m_grid->GetCellValue( i, 5 );
				e1->SetAttribute( "C5", s.c_str() );
				pRoot->InsertEndChild( e1 );
			}
		}
	}

	doc.SaveFile( PRJ_NAME.c_str() );
	PRJ_CHANGED = false;
	m_statusBar->SetStatusText( wxT( "Project saved" ) );
}
// ===========================================================================


// ===========================================================================
int MyFrame::Read_Cfg()
// ===========================================================================
{
	long				 vl;
	wxString			 s;
	XML::XMLDocument	 doc;
	XML::XMLElement		*r1, *e1;

	//s = DATA_DIR + wxT( PATH_SEP ) + S_NAME + wxT( ".cfg" );
	s = S_NAME + wxT( ".cfg" );

	if( !doc.LoadFile( s.c_str() ) )
	{
		r1 = doc.FirstChildElement( "CFG" );
		if( r1 )
		{
			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Win_MaxSize" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				s = wxT( e1->GetText() );
				if( s == wxT( "T" ) )
				{
					Read_Win_MaxSize = true;
				}
				else
				{
					Read_Win_MaxSize = false;
				}
			}

			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Win_PosX" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				s = wxT( e1->GetText() );
				if( s.ToLong( &vl ) )
				{
					Win_PosX = vl;
				}
			}

			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Win_PosY" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				s = wxT( e1->GetText() );
				if( s.ToLong( &vl ) )
				{
					Win_PosY = vl;
				}
			}

			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Win_SizeX" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				s = wxT( e1->GetText() );
				if( s.ToLong( &vl ) )
				{
					Win_SizeX = vl;
				}
			}

			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Win_SizeY" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				s = wxT( e1->GetText() );
				if( s.ToLong( &vl ) )
				{
					Win_SizeY = vl;
				}
			}

			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Prj_Name" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
				PRJ_NAME = wxT( e1->GetText() );
			}
			//}
		}
		return 0;
	}
	else
	{
		return 1;
	}
	return 0;
}
// ===========================================================================


// ===========================================================================
void MyFrame::Write_Cfg()
// ===========================================================================
{
	wxString			 s;
	XML::XMLDocument	 doc;
	XML::XMLElement		*e1;
	XML::XMLNode		*pRoot = doc.NewElement( "CFG" );

	doc.InsertEndChild( doc.NewDeclaration( "xml version=\"1.0\"" ) );
	//doc.InsertEndChild( doc.NewDeclaration() );
	doc.InsertEndChild( pRoot );

	// ---------------------------------------------------------------------------
	// Win_MaxSize
	// ---------------------------------------------------------------------------
	e1 = doc.NewElement( "Win_MaxSize" );
	if( Win_MaxSize )
	{
		e1->SetText( "T" );
	}
	else
	{
		e1->SetText( "F" );
	}
	pRoot->InsertEndChild( e1 );

	// ---------------------------------------------------------------------------
	// Win_PosX
	// ---------------------------------------------------------------------------
	s.Printf( wxT( "%d" ), Win_PosX );
	e1 = doc.NewElement( "Win_PosX" );
	e1->SetText( s.c_str() );
	pRoot->InsertEndChild( e1 );

	// ---------------------------------------------------------------------------
	// Win_PosY
	// ---------------------------------------------------------------------------
	s.Printf( wxT( "%d" ), Win_PosY );
	e1 = doc.NewElement( "Win_PosY" );
	e1->SetText( s.c_str() );
	pRoot->InsertEndChild( e1 );

	// ---------------------------------------------------------------------------
	// Win_SizeX
	// ---------------------------------------------------------------------------
	s.Printf( wxT( "%d" ), Win_SizeX );
	e1 = doc.NewElement( "Win_SizeX" );
	e1->SetText( s.c_str() );
	pRoot->InsertEndChild( e1 );

	// ---------------------------------------------------------------------------
	// Win_SizeY
	// ---------------------------------------------------------------------------
	s.Printf( wxT( "%d" ), Win_SizeY );
	e1 = doc.NewElement( "Win_SizeY" );
	e1->SetText( s.c_str() );
	pRoot->InsertEndChild( e1 );

	// ---------------------------------------------------------------------------
	// Project Name+Path
	// ---------------------------------------------------------------------------
	if( PRJ_NAME != wxEmptyString )
	{
		e1 = doc.NewElement( "Prj_Name" );
		e1->SetText( PRJ_NAME.c_str() );
		pRoot->InsertEndChild( e1 );
	}

	s = S_NAME + wxT( ".cfg" );
//	s = DATA_DIR + wxT( PATH_SEP ) + S_NAME + wxT( ".cfg" );
	doc.SaveFile( s.c_str() );
}
// ===========================================================================
