/*
	Name:			myframe_tools_events.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/

#include "lcd_1602_i2c.h"
#include "create_mdk_prj.h"
#include "create_ebp_prj.h"
#include "stm32f103c8.h"

// ===========================================================================
// Tools event handlers
// ===========================================================================


// ===========================================================================
wxBitmap MyFrame::wxGetBitmapFromMemory( const void *data, size_t length )
// ===========================================================================
{
	wxMemoryInputStream stream( data, length );
	return wxBitmap( stream, wxBITMAP_TYPE_ANY );
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_New_Prj( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	int					i;
	wxString			s, buf, prj_path, prj_name, prj_ext;
	bool				bc;
	wxFile				file;
	PG_Help_OK_Cancel	help( this );

	New_Prj prj( this );
	prj.my_frame = this;

	if( PRJ_CHANGED )
	{
		bc = false;
	}
	else
	{
		bc = true;
	}

	if( !bc )
	{
		help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
		help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE );
		help.m_grid->SetColSize( 0, 200 );
		help.m_grid->SetRowSize( 0, 40 );
		help.m_grid->SetCellValue( 0, 0, _T( "All project data will be lost." ) );
		help.m_grid->SetCellRenderer( 0 , 0, new wxGridCellAutoWrapStringRenderer );
		help.m_grid->SetCellEditor( 0,  0 , new wxGridCellAutoWrapStringEditor );

		help.m_bitmap->SetBitmap( exclamation_xpm );
		help.m_bitmap->Show( true );

		help.Centre();
		help.Fit();

		help.m_sdbSizerOK->SetFocus();

		if( help.ShowModal() == wxID_OK )
		{
			bc = true;
		}
	}

	if( bc )
	{
		if( prj.ShowModal() == wxID_OK )
		{
			s = prj.m_path_project_name->GetValue();
			if( file.Create( s )  )
			{
				Clear_Project();
				Enable_Config();

				i = prj.m_choice_MCU->GetSelection();
				s = prj.m_choice_MCU->GetString( i );
				m_text_mcu->SetValue( s );
				PRJ_MCU = s;

				s = prj.m_text_comment->GetValue();
				m_text_comment->SetValue( s );
				PRJ_COMMENT = s;

				PRJ_NAME = prj.m_path_project_name->GetValue();;
				file.Close();

				Write_Prj();

				wxFileName::SplitPath( PRJ_NAME, &prj_path, &prj_name, &prj_ext );

				if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
				{
					//stm32f103c8.h
					i = sizeof( stm32f103c8 );
					s = prj_path + PATH_SEP + wxT( "read.me" );
					if( file.Open( s.c_str(), wxFile::write ) )
					{
						file.Write( stm32f103c8, i );
						file.Close();
					}
				}
			}
			else
			{
				wxMessageBox( wxT( "Can't create project file." ), wxT( "Error" ), wxICON_HAND );
			}
		}
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_Open_Prj( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	wxString			s;
	bool				bc;
	PG_Help_OK_Cancel	help( this );
	Open_Project_FB		prj_name( this );

	if( PRJ_CHANGED )
	{
		bc = false;
	}
	else
	{
		bc = true;
	}

	if( !bc )
	{
		help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
		help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE );
		help.m_grid->SetColSize( 0, 200 );
		help.m_grid->SetRowSize( 0, 40 );
		help.m_grid->SetCellValue( 0, 0, _T( "All project data will be lost." ) );
		help.m_grid->SetCellRenderer( 0 , 0, new wxGridCellAutoWrapStringRenderer );
		help.m_grid->SetCellEditor( 0,  0 , new wxGridCellAutoWrapStringEditor );

		help.m_bitmap->SetBitmap( exclamation_xpm );
		help.m_bitmap->Show( true );

		help.Centre();
		help.Fit();

		help.m_sdbSizerOK->SetFocus();

		if( help.ShowModal() == wxID_OK )
		{
			bc = true;
		}
	}

	if( bc )
	{
		if( prj_name.ShowModal() == wxID_OK )
		{
			Disable_Config();
			Clear_Project();
			s = prj_name.m_file->GetPath();
			PRJ_NAME = s;
			if( !Read_Prj() )
			{
				Enable_Config();
			}
		}
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_Close_Prj( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	wxString			s;
	bool				bc;
	PG_Help_OK_Cancel	help( this );

	if( PRJ_CHANGED )
	{
		bc = false;
	}
	else
	{
		bc = true;
	}

	if( !bc )
	{
		help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
		help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE );
		help.m_grid->SetColSize( 0, 200 );
		help.m_grid->SetRowSize( 0, 40 );
		help.m_grid->SetCellValue( 0, 0, _T( "All project data will be lost." ) );
		help.m_grid->SetCellRenderer( 0 , 0, new wxGridCellAutoWrapStringRenderer );
		help.m_grid->SetCellEditor( 0,  0 , new wxGridCellAutoWrapStringEditor );

		help.m_bitmap->SetBitmap( exclamation_xpm );
		help.m_bitmap->Show( true );

		help.Centre();
		help.Fit();

		help.m_sdbSizerOK->SetFocus();

		if( help.ShowModal() == wxID_OK )
		{
			bc = true;
		}
	}

	if( bc )
	{
		Disable_Config();
		Clear_Project();
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_Save_Prj( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	Write_Prj();
	PRJ_CHANGED = false;
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnCellValueChanged( wxGridEvent &event )
// ===========================================================================
{
	unsigned int	i, j, m, n, n1, n2, row, col;
	wxString		s, s2, s3;

	PRJ_CHANGED = true;
	row = event.GetRow();
	col = event.GetCol();

	if( col == 0 )
	{
		s = m_grid->GetCellValue( row, 2 );
		if( ( s == wxT( "LCD_1602_STR_1" ) ) || ( s == wxT( "LCD_1602_STR_2" ) ) )
		{
			m_grid->SetCellValue( row, 0, s );
		}

		n = 0;
		s = m_grid->GetCellValue( row, 0 );
		if( s.Len() )
		{
			if( ( s[0] > 47 ) && ( s[0] < 58 ) )
			{
				n = 1;
			}
			for( i = 0; i < s.Len(); i++ )
			{
				if( s[i] < 48 )
				{
					n = 1;
					break;
				}
				else
				if( ( s[i] > 57 ) && ( s[i] < 65 ) )
				{
					n = 1;
					break;
				}
				else
				if( ( s[i] > 90 ) && ( s[i] < 97 )  && ( s[i] != 95 ) )
				{
					n = 1;
					break;
				}
				else
				if( s[i] > 122 )
				{
					n = 1;
					break;
				}
			}
		}

		if( n )
		{
			wxMessageBox( wxT( "Invalid name" ), wxT( "Error" ), wxICON_HAND );
			m_grid->SetCellBackgroundColour( row, 0, *wxRED );
			m_grid->Refresh();
			event.Skip();
		}
		else
		{
			m = 1;
			n = m_grid->GetNumberRows();
			if( n > 1 )
			{
				j = 0;
				s2 = m_grid->GetCellValue( row, 0 );
				for( i = 0; i < n; i++ )
				{
					s = m_grid->GetCellValue( i, 0 );
					if( s != wxEmptyString )
					{
						if( i != row )
						{
							if( s == s2 )
							{
								m = 0;
								wxMessageBox( wxT( "Name already in use." ), wxT( "Error" ), wxICON_HAND );
								m_grid->SetCellBackgroundColour( row, 0, *wxRED );
								m_grid->Refresh();
								event.Skip();
							}
						}
					}
				}
			}

			if( m )
			{
				m_grid->SetCellBackgroundColour( row, 0, *wxWHITE );
				m_grid->Refresh();
				event.Skip();
			}
		}
	}
	else
	if( ( col == 2 ) || ( col == 3 ) )
	{
		s2 = m_grid->GetCellValue( row, 2 );
		s3 = m_grid->GetCellValue( row, 3 );

		if( ( s2 == wxT( "LCD_1602_STR_1" ) ) || ( s2 == wxT( "LCD_1602_STR_2" ) ) )
		{
			m_grid->SetCellValue( row, 0, s2 );
		}

		// Check port for busy
		Parse_Port( s3, &n1, &n2 );

		if( s3 != wxEmptyString )
		{
			if( Check_Port( s3, row ) )
			{
				m_grid->SetCellBackgroundColour( row, 2, *wxRED );
				m_grid->SetCellValue( row, 3, SEL_PORT[0] );
				m_grid->Refresh();
				return;
			}
		}
		m_grid->SetCellBackgroundColour( row, 3, *wxWHITE );

		if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) || ( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
		{
			if( ( s2 == wxT( "GPIO_Mode_AIN" ) ) ||
				( s2 == wxT( "GPIO_Mode_IN_FLOATING" ) ) ||
				( s2 == wxT( "GPIO_Mode_IPD" ) ) ||
				( s2 == wxT( "GPIO_Mode_IPU" ) ) ||
				( s2 == wxT( "GPIO_Mode_Out_OD" ) ) ||
				( s2 == wxT( "GPIO_Mode_Out_PP" ) ) ||
				( s2 == wxT( "DS18B20" ) ) ||
				( s2 == wxT( "iButton" ) ) )
			{
				m_grid->SetReadOnly( row, 3, false );
				if( s3 == wxEmptyString )
				{
					m_grid->SetCellBackgroundColour( row, 2, *wxRED );
					m_grid->Refresh();
				}
				else
				{
					m_grid->SetCellBackgroundColour( row, 2, *wxWHITE );
					m_grid->Refresh();

					if( s2 == wxT( "GPIO_Mode_AIN" ) )
					{
						if( s3 != wxEmptyString )
						{
							Parse_Port( s3, &n1, &n2 );
							if( n1 || ( n2 > 8 ) )
							{
								m_grid->SetCellBackgroundColour( row, 2, *wxRED );
								m_grid->SetCellValue( row, 3, SEL_PORT[0] );
								return;
							}
						}
					}
				}
			}
			else
			{
				m_grid->SetCellBackgroundColour( row, 2, *wxWHITE );
				m_grid->SetReadOnly( row, 3, true );
				m_grid->SetCellValue( row, 3, SEL_PORT[0] );
			}
		}
		Check_Config();
	}
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnInsRow( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	int			m, n;

	n = m_grid->GetNumberRows();
	if( n == MAX_GRID_NN )
	{
		wxMessageBox( wxT( "Unable to add record.\nThe maximum quantity of records is reached." ), wxT( "Error" ), wxICON_HAND );
		return;
	}

	m_grid->InsertRows( n, 1 );
	m_grid->SetGridCursor( n, 0 );

	m = sizeof( VAR_1XX_TYPES ) / sizeof( int );
	ce2 = new wxGridCellChoiceEditor( m, VAR_1XX_TYPES );
	ce3 = new wxGridCellChoiceEditor( PORT_NN, SEL_PORT );
	ce5 = new wxGridCellChoiceEditor( 3, cs5 );

	m_grid->SetCellEditor( n, 2, ce2 );
	m_grid->SetCellValue( n, 2, VAR_1XX_TYPES[0] );

	m_grid->SetCellEditor( n, 3, ce3 );
	m_grid->SetCellValue( n, 3, SEL_PORT[0] );

	m_grid->SetCellEditor( n, 5, ce5 );
	m_grid->SetCellValue( n, 5, cs5[0] );

	m_grid->SetReadOnly( n, 1 );
	m_grid->SetReadOnly( n, 3 );
//	m_grid->SetReadOnly( n, 5 );
	m_grid->Refresh();
	PRJ_CHANGED = true;
}
// ===========================================================================


// ===========================================================================
void MyFrame::Save_Rows( void )
// ===========================================================================
{
	int			i, j, m, n, k;
	wxString	s;

	n = m_grid->GetNumberRows();

	for( i = 0; i < MAX_GRID_NN; i++ )
	{
		m_grid_r[i].c0 = wxEmptyString;
		m_grid_r[i].c2 = 0;
		m_grid_r[i].c3 = 0;
		m_grid_r[i].c4 = wxEmptyString;
		m_grid_r[i].c5 = 0;
	}

	for( i = 0; i < n; i++ )
	{
		s = m_grid->GetCellValue( i, 0 );
		if( s != wxEmptyString )
		{
			m_grid_r[i].c0 = s;
		}

		s = m_grid->GetCellValue( i, 2 );
		if( s != wxEmptyString )
		{
			m = sizeof( VAR_1XX_TYPES ) / sizeof( int );
			if( m )
			{
				k = 0;
				for( j = 0; j < m; j++ )
				{
					if( s == VAR_1XX_TYPES[j] )
					{
						k = j;
						break;
					}
				}
				m_grid_r[i].c2 = k;
			}
		}

		s = m_grid->GetCellValue( i, 3 );
		if( s != wxEmptyString )
		{
			k = 0;
			for( j = 0; j < PORT_NN; j++ )
			{
				if( s == SEL_PORT[j] )
				{
					k = j;
					break;
				}
			}
			m_grid_r[i].c3 = k;
		}

		s = m_grid->GetCellValue( i, 4 );
		if( s != wxEmptyString )
		{
			m_grid_r[i].c4 = s;
		}

		s = m_grid->GetCellValue( i, 5 );
		if( s != wxEmptyString )
		{
			if( s == wxT( "R" ) )
			{
				m_grid_r[i].c5 = 1;
			}
			if( s == wxT( "W" ) )
			{
				m_grid_r[i].c5 = 2;
			}
		}
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnDelRow( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	int			i, j, m, n, k, count;
	wxString	s;
	wxArrayInt	sels;

	n = m_grid->GetNumberRows();
	if( n )
	{
		m_grid->BeginBatch();
		Save_Rows();

		sels = m_grid->GetSelectedRows();
		count = sels.size();
		if( count == 1 )
		{
			i = sels[0];
			m_grid->ClearGrid();
			m_grid->DeleteRows( 0, n );
			m_grid->InsertRows( 0, ( n - 1 ) );
			k = 0;
			for( j = 0; j < n; j++ )
			{
				if( j != i )
				{
					m = sizeof( VAR_1XX_TYPES ) / sizeof( int );
					ce2 = new wxGridCellChoiceEditor( m, VAR_1XX_TYPES );
					ce3 = new wxGridCellChoiceEditor( PORT_NN, SEL_PORT );
					ce5 = new wxGridCellChoiceEditor( 3, cs5 );
					m_grid->SetCellEditor( k, 2, ce2 );
					m_grid->SetCellEditor( k, 3, ce3 );
					m_grid->SetCellEditor( k, 5, ce5 );

					m_grid->SetReadOnly( j, 1 );


					if( m_grid_r[j].c0 != wxEmptyString )
					{
						m_grid->SetCellValue( k, 0, m_grid_r[j].c0 );
					}

					if( m_grid_r[j].c2 != 0 )
					{
						m_grid->SetCellValue( k, 2, VAR_1XX_TYPES[m_grid_r[j].c2] );
					}

					if( m_grid_r[j].c3 != 0 )
					{
						m_grid->SetCellValue( k, 3, SEL_PORT[m_grid_r[j].c3] );
					}
					else
					{
						m_grid->SetReadOnly( k, 3 );
					}

					if( m_grid_r[j].c4 != wxEmptyString )
					{
						m_grid->SetCellValue( k, 4, m_grid_r[j].c4 );
					}

					if( m_grid_r[j].c5 != 0 )
					{
					m_grid->SetCellValue( k, 5, cs5[m_grid_r[j].c5] );
					}
					k++;
				}
			}
			if( i >= ( n - 1 ) )
			{
				i = n - 2;
			}
			if( i >= 0 )
			{
				m_grid->SelectRow( i );
			}
			PRJ_CHANGED = true;
		}
		m_grid->EndBatch();
		m_grid->ForceRefresh();
		Check_Config();
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_UART_config( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	wxString	s;
	Set_COM		set_com( this );

	if( set_com.ShowModal() == wxID_OK )
	{
		m_main_tool->SetToolNormalBitmap( ID_TOOL_CONNECT, disconnect_xpm );
		s.Printf( "COM%d", COM_NN );
		m_tool_com_port->SetValue( s );
		m_bitmap_com_indicator->SetBitmap( pw_r_xpm );
		PRJ_CHANGED = true;
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_UART_help( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	PG_Help_OK help( this );

	help.m_grid->AppendCols(1);
	help.m_grid->AppendRows(3);

	help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	//help.m_grid->EnableGridLines( true );

	help.m_grid->SetColSize( 0, 80 );
	help.m_grid->SetColSize( 1, 80 );
	help.m_grid->SetRowSize( 0, 30 );
	help.m_grid->SetRowSize( 1, 30 );
	help.m_grid->SetRowSize( 2, 25 );
	help.m_grid->SetRowSize( 3, 25 );

	help.m_grid->SetCellSize( 0, 0, 1, 2 );
	help.m_grid->SetCellSize( 1, 0, 1, 2 );

	help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_BOTTOM );
	help.m_grid->SetCellAlignment( 1, 0, wxALIGN_CENTRE, wxALIGN_TOP );
	//help.m_grid->SetCellAlignment( 1, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 2, 0, wxALIGN_RIGHT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 2, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 3, 0, wxALIGN_RIGHT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 3, 1, wxALIGN_LEFT, wxALIGN_CENTRE );

	help.m_grid->SetCellRenderer( 0 , 0, new wxGridCellAutoWrapStringRenderer );
	help.m_grid->SetCellEditor( 0,  0 , new wxGridCellAutoWrapStringEditor );
	help.m_grid->SetCellRenderer( 1 , 0, new wxGridCellAutoWrapStringRenderer );
	help.m_grid->SetCellEditor( 1,  0 , new wxGridCellAutoWrapStringEditor );

	help.m_grid->SetCellValue( 0, 0, wxT( "UART1 connection" ) );
	help.m_grid->SetCellValue( 1, 0, wxT( "________________" ) );

	help.m_grid->SetCellValue( 2, 0, wxT( "Rx" ) );
	help.m_grid->SetCellValue( 2, 1, wxT( "\t - PA9" ) );
	help.m_grid->SetCellValue( 3, 0, wxT( "Tx" ) );
	help.m_grid->SetCellValue( 3, 1, wxT( "\t - PA10" ) );

	help.Centre();
	help.Fit();
	help.m_sdbSizerOK->SetFocus();
	help.ShowModal();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_I2C_help( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	PG_Help_OK help( this );

	help.m_bitmap->SetBitmap( wxGetBitmapFromMemory( lcd_1602_i2c, sizeof( lcd_1602_i2c ) ) );
	help.m_bitmap->Show( true );

	help.m_grid->AppendCols( 1 );
	help.m_grid->AppendRows( 10 );

	help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	//help.m_grid->EnableGridLines( true );

	help.m_grid->SetColSize( 0, 300 );
	help.m_grid->SetColSize( 1, 300 );
	help.m_grid->SetRowSize( 0, 30 );
	help.m_grid->SetRowSize( 1, 30 );
	help.m_grid->SetRowSize( 2, 25 );
	help.m_grid->SetRowSize( 3, 25 );
	help.m_grid->SetRowSize( 4, 25 );
	help.m_grid->SetRowSize( 5, 25 );
	help.m_grid->SetRowSize( 6, 25 );
	help.m_grid->SetRowSize( 7, 30 );
	help.m_grid->SetRowSize( 8, 30 );
	help.m_grid->SetRowSize( 9, 25 );

	help.m_grid->SetCellSize( 0, 0, 1, 2 );
	help.m_grid->SetCellSize( 1, 0, 1, 2 );
	help.m_grid->SetCellSize( 7, 0, 1, 2 );
	help.m_grid->SetCellSize( 8, 0, 1, 2 );

	help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_BOTTOM );
	help.m_grid->SetCellAlignment( 1, 0, wxALIGN_CENTRE, wxALIGN_TOP );
	//help.m_grid->SetCellAlignment( 1, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 2, 0, wxALIGN_RIGHT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 2, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 3, 0, wxALIGN_RIGHT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 3, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 4, 0, wxALIGN_RIGHT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 4, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 5, 0, wxALIGN_RIGHT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 5, 1, wxALIGN_LEFT, wxALIGN_CENTRE );

	help.m_grid->SetCellAlignment( 7, 0, wxALIGN_CENTRE, wxALIGN_BOTTOM );
	help.m_grid->SetCellAlignment( 8, 0, wxALIGN_CENTRE, wxALIGN_TOP );
	help.m_grid->SetCellAlignment( 9, 0, wxALIGN_RIGHT, wxALIGN_TOP );
	help.m_grid->SetCellAlignment( 9, 1, wxALIGN_LEFT, wxALIGN_CENTRE );

//	help.m_grid->SetCellRenderer( 0 , 0, new wxGridCellAutoWrapStringRenderer );
//	help.m_grid->SetCellEditor( 0,  0 , new wxGridCellAutoWrapStringEditor );
//	help.m_grid->SetCellRenderer( 1 , 0, new wxGridCellAutoWrapStringRenderer );
//	help.m_grid->SetCellEditor( 1,  0 , new wxGridCellAutoWrapStringEditor );

	help.m_grid->SetCellValue( 0, 0, wxT( "I2C1 connection" ) );
	help.m_grid->SetCellValue( 1, 0, wxT( "______________" ) );

	help.m_grid->SetCellValue( 2, 0, wxT( "SCL" ) );
	help.m_grid->SetCellValue( 2, 1, wxT( "\t - PB6" ) );
	help.m_grid->SetCellValue( 3, 0, wxT( "SDA" ) );
	help.m_grid->SetCellValue( 3, 1, wxT( "\t - PB7" ) );
	help.m_grid->SetCellValue( 4, 0, wxT( "GND" ) );
	help.m_grid->SetCellValue( 4, 1, wxT( "\t - G" ) );
	help.m_grid->SetCellValue( 5, 0, wxT( "VCC" ) );
	help.m_grid->SetCellValue( 5, 1, wxT( "\t - Power (+5V)" ) );

	help.m_grid->SetCellValue( 7, 0, wxT( "Functions" ) );
	help.m_grid->SetCellValue( 8, 0, wxT( "_________" ) );
	help.m_grid->SetCellValue( 9, 0, wxT( "LCD_write_string( int n_str, char *str )" ) );
	help.m_grid->SetCellValue( 9, 1, wxT( "\t - write str to LCD" ) );

	help.Fit();
	help.Centre();
	help.m_sdbSizerOK->SetFocus();
	help.ShowModal();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnCANHelp( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
wxMessageBox( wxT( "OnCANHelp" ) );
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMyAbout( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	My_Help my_help( this );
	my_help.ShowModal();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMyFunctions( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	PG_Help_OK help( this );

	help.m_grid->AppendCols(1);
	help.m_grid->AppendRows(8);

	help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );

	help.m_grid->SetColSize( 0, 250 );
	help.m_grid->SetColSize( 1, 200 );
	help.m_grid->SetRowSize( 0, 30 );
	help.m_grid->SetRowSize( 1, 30 );
	help.m_grid->SetRowSize( 2, 25 );
	help.m_grid->SetRowSize( 3, 25 );
	help.m_grid->SetRowSize( 4, 25 );
	help.m_grid->SetRowSize( 5, 25 );
	help.m_grid->SetRowSize( 6, 25 );
	help.m_grid->SetRowSize( 7, 25 );

	help.m_grid->SetCellSize( 0, 0, 1, 2 );
	help.m_grid->SetCellSize( 1, 0, 1, 2 );

	help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_BOTTOM );
	help.m_grid->SetCellAlignment( 1, 0, wxALIGN_CENTRE, wxALIGN_TOP );
	//help.m_grid->SetCellAlignment( 1, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 2, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 2, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 3, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 3, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 4, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 4, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 5, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 5, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 6, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 6, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 7, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 7, 1, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 8, 0, wxALIGN_LEFT, wxALIGN_CENTRE );
	help.m_grid->SetCellAlignment( 8, 1, wxALIGN_LEFT, wxALIGN_CENTRE );

	help.m_grid->SetCellRenderer( 0 , 0, new wxGridCellAutoWrapStringRenderer );
	help.m_grid->SetCellEditor( 0,  0 , new wxGridCellAutoWrapStringEditor );
	help.m_grid->SetCellRenderer( 1 , 0, new wxGridCellAutoWrapStringRenderer );
	help.m_grid->SetCellEditor( 1,  0 , new wxGridCellAutoWrapStringEditor );

	help.m_grid->SetCellValue( 0, 0, wxT( "Build in functions" ) );
	help.m_grid->SetCellValue( 1, 0, wxT( "__________________" ) );

	help.m_grid->SetCellValue( 2, 0, wxT( "delay_ms( int ms )" ) );
	help.m_grid->SetCellValue( 2, 1, wxT( "\t - delay in milliseconds" ) );
	help.m_grid->SetCellValue( 3, 0, wxT( "delay_us( int us )" ) );
	help.m_grid->SetCellValue( 3, 1, wxT( "\t - delay in microseconds" ) );
	help.m_grid->SetCellValue( 4, 0, wxT( "print_str( char *str )" ) );
	help.m_grid->SetCellValue( 4, 1, wxT( "\t - print string to console" ) );
	help.m_grid->SetCellValue( 5, 0, wxT( "print" ) );
	help.m_grid->SetCellValue( 5, 1, wxT( "\t - analoque of printf" ) );
	help.m_grid->SetCellValue( 6, 0, wxT( "send_uart1( char *data, int len )" ) );
	help.m_grid->SetCellValue( 6, 1, wxT( "\t - send data to UART1" ) );
	help.m_grid->SetCellValue( 7, 0, wxT( "send_usb( char *data, int len )" ) );
	help.m_grid->SetCellValue( 7, 1, wxT( "\t - send data to USB" ) );
	help.m_grid->SetCellValue( 8, 0, wxT( "set_bit( variable_name, bool set )" ) );
	help.m_grid->SetCellValue( 8, 1, wxT( "\t - set bit as variable" ) );

	help.Centre();
	help.Fit();
	help.m_sdbSizerOK->SetFocus();
	help.ShowModal();
}
// ===========================================================================


// ===========================================================================
void MyFrame::Asc_to_Save()
// ===========================================================================
{
	PG_Help_OK_Cancel help( this );

	if( PRJ_CHANGED )
	{
		help.m_grid->AppendRows(2);
		help.m_grid->SetDefaultCellFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
		help.m_grid->SetColSize( 0, 180 );
		help.m_grid->SetRowSize( 0, 30 );
		help.m_grid->SetRowSize( 1, 30 );
		help.m_grid->SetCellAlignment( 0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE );
		help.m_grid->SetCellAlignment( 1, 0, wxALIGN_CENTRE, wxALIGN_CENTRE );
		help.m_grid->SetCellAlignment( 2, 0, wxALIGN_CENTRE, wxALIGN_CENTRE );
		help.m_grid->SetCellValue( 0, 0, wxT( "Project is changed" ) );
		help.m_grid->SetCellValue( 1, 0, wxT( "Save project?" ) );
		help.m_grid->SetCellValue( 2, 0, wxT( "Ok-Yes; Cancel-No" ) );
		help.Centre();
		help.Fit();
		help.m_sdbSizerOK->SetFocus();

		if( help.ShowModal() == wxID_OK )
		{
			Write_Prj();
			PRJ_CHANGED = false;
		}
	}
}
// ===========================================================================
