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


// ===========================================================================
// Tools event handlers
// ===========================================================================


// ===========================================================================
void MyFrame::OnTool_New_Prj( wxCommandEvent &event )
// ===========================================================================
{
	int					i;
	wxString			s;
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
		else
		{
			event.Skip();
		}
	}

	if( bc )
	{
		if( prj.ShowModal() == wxID_OK )
		{
			s = prj.m_path_project_name->GetValue();
			if( file.Create( s )  )
			{
				i = prj.m_choice_MCU->GetSelection();
				s = prj.m_choice_MCU->GetString( i );
				m_text_mcu->SetValue( s );
				PRJ_MCU = s;

				s = prj.m_text_comment->GetValue();
				m_text_comment->SetValue( s );
				PRJ_COMMENT = s;

				PRJ_NAME = prj.m_path_project_name->GetValue();;

//write

				file.Close();
			}
			else
			{
				wxMessageBox( wxT( "Can't create project file." ), wxT( "Error" ), wxICON_HAND );
				event.skip();
			}
		}
	}
	event.skip();
}
// ===========================================================================


void MyFrame::OnTool_Save_Prj( wxCommandEvent &WXUNUSED( event ) )
{
Write_Prj();
PRJ_CHANGED = false;
}


// ===========================================================================
void MyFrame::OnCellValueChanged( wxGridEvent &event )
// ===========================================================================
{
	int			i, j, m, n, row, col;
	wxString	s, s2, s3;

	row = event.GetRow();
	col = event.GetCol();
//s.Printf( wxT("OnCellValueChanged; row %d, col %d\n"), event.GetRow(), event.GetCol()); m_log->AppendText( s );

	if( col == 0 )
	{
		n = 0;
		s = m_grid->GetCellValue( row, 0 );
		if( s.Len() )
		{
//m_log->AppendText( wxT( "---01\n" ) );
			if( ( s[0] > 47 ) && ( s[0] < 58 ) )
			{
//m_log->AppendText( wxT( "---02\n" ) );
				n = 1;
			}
			for( i = 0; i < s.Len(); i++ )
			{
//m_log->AppendText( wxT( "---03\n" ) );
				if( s[i] < 48 )
				{
					n = 1;
				}
				if( ( s[i] > 57 ) && ( s[i] < 65 ) )
				{
					n = 1;
				}
				if( ( s[i] > 90 ) && ( s[i] < 97 )  && ( s[i] != 95 ) )
				{
					n = 1;
				}
				if( s[i] > 122 )
				{
					n = 1;
				}
			}
		}
		if( n )
		{
//s.Printf( wxT( "--- n=%d ---04\n" ), n ); m_log->AppendText( s );
			wxMessageBox( wxT( "Invalid name" ), wxT( "Error" ), wxICON_HAND );
			m_grid->SetCellBackgroundColour( row, 0, *wxRED );
			m_grid->Refresh();
			event.Skip();
		}
		else
		{
//m_log->AppendText( wxT( "---05\n" ) );
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




//else
//if( col == 2 )
//{
s2 = m_grid->GetCellValue( row, 2 );

if( ( PRJ_MCU == wxT( "STM32F103C8T6" ) ) ||
	( PRJ_MCU == wxT( "STM32F103CBT6" ) ) )
{
m_log->AppendText( wxT( "STM32F103\n" ) );
m_log->AppendText( wxT( "if..." ) ); m_log->AppendText( s2 ); m_log->AppendText( wxT( "\n" ) );

if( ( s2 == wxT( "GPIO_Mode_AIN" ) ) ||
	( s2 == wxT( "GPIO_Mode_IN_FLOATING" ) ) ||
	( s2 == wxT( "GPIO_Mode_IPD" ) ) ||
	( s2 == wxT( "GPIO_Mode_IPU" ) ) ||
	( s2 == wxT( "GPIO_Mode_Out_OD" ) ) ||
	( s2 == wxT( "GPIO_Mode_Out_PP" ) ) ||
	( s2 == wxT( "DS18B20" ) ) ||
	( s2 == wxT( "iButton" ) ) )
{
m_log->AppendText( wxT( "STM32F103 - GPIO\n" ) );


////m_grid->SetCellTextColour(0, 2, *wxRED);
////m_grid->SetCellBackgroundColour(0, 2, *wxGREEN);
////m_grid->SetReadOnly( n, 1 );
m_grid->SetReadOnly( row, 3, false );

s3 = m_grid->GetCellValue( row, 3 );

m_log->AppendText( wxT( "s3=" ) ); m_log->AppendText( s3 ); m_log->AppendText( wxT( "\n" ) );


if( s3 == wxEmptyString )
{
m_grid->SetCellBackgroundColour( row, 2, *wxRED );
m_grid->Refresh();
}
else
{
m_grid->SetCellBackgroundColour( row, 2, *wxWHITE );
m_grid->Refresh();

s = m_grid->GetCellValue( row, 3 );
m_log->AppendText( wxT( "Port=" ) ); m_log->AppendText( s ); m_log->AppendText( wxT( "\n" ) );


// Check port for busy
//m_grid->SetCellValue( row, 3, SEL_PORT[1] );


}




//}
}
else
{
m_grid->SetCellBackgroundColour( row, 2, *wxWHITE );
m_grid->SetReadOnly( row, 3, true );
m_grid->SetCellValue( row, 3, cs3[0]);
}





}

}

void MyFrame::OnEditorHidden( wxGridEvent &event )
{
//int row, col;
//wxString s, s2, s3;
//
//row = event.GetRow();
//col = event.GetCol();
//s.Printf(_T("OnEditorHidden; row %d, col %d\n"), event.GetRow(), event.GetCol()); m_log->AppendText( s );
//
//s2 = m_grid->GetCellValue( row, 2 );
//
//if( PRJ_MCU == wxT( "STM32F103" ) )
//{
//m_log->AppendText( wxT( "STM32F103\n" ) );
//m_log->AppendText( wxT( "if..." ) ); m_log->AppendText( s2 ); m_log->AppendText( wxT( "\n" ) );
//}
event.Skip();
}




// ===========================================================================
void MyFrame::OnGridEditorHidden( wxGridEvent &event )
// ===========================================================================
{
//int row, col;
//wxString s, s2, s3;


//row = event.GetRow();
//col = event.GetCol();
//s.Printf(_T("OnGridEditorHidden; row %d, col %d\n"), event.GetRow(), event.GetCol()); m_log->AppendText( s );
//
//s2 = m_grid->GetCellValue( row, 2 );
//
//if( PRJ_MCU == wxT( "STM32F103" ) )
//{
//m_log->AppendText( wxT( "STM32F103\n" ) );
//m_log->AppendText( wxT( "if..." ) ); m_log->AppendText( s2 ); m_log->AppendText( wxT( "\n" ) );
//
//if( ( s2 == wxT( "GPIO_Mode_AIN ") ) ||
//	( s2 == wxT( "GPIO_Mode_IN_FLOATING ") ) ||
//	( s2 == wxT( "GPIO_Mode_IPD ") ) ||
//	( s2 == wxT( "GPIO_Mode_IPU ") ) ||
//	( s2 == wxT( "GPIO_Mode_Out_OD ") ) ||
//	( s2 == wxT( "GPIO_Mode_Out_PP ") ) ||
//	( s2 == wxT( "DS18B20" ) ) ||
//	( s2 == wxT( "iButton" ) ) )
//{
//
//m_log->AppendText( wxT( "STM32F103 - GPIO\n" ) );


////m_grid->SetCellTextColour(0, 2, *wxRED);
////m_grid->SetCellBackgroundColour(0, 2, *wxGREEN);
////m_grid->SetReadOnly( n, 1 );
//m_grid->SetReadOnly( row, 3, false );
//
//s3 = m_grid->GetCellValue( row, 3 );
//if( s3 == wxEmptyString )
//{
//m_grid->SetCellBackgroundColour( row, 2, *wxRED );
//
//
//}
//}
//}

//m_statusBar->SetStatusText( wxT( "OnGridEditorHidden" ), 0 );
//ce2->SetParameters( wxT( "1,2,3" ) );
//m_grid->SetCellValue( 0, 2, wxT( "1" ) );
//m_grid->Refresh();
event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnGridEditorShown( wxGridEvent &event )
// ===========================================================================
{
//uint32_t row, col;
////wxString s, s_sel;
//wxString s, s2, s3;
//
//row = event.GetRow();
//col = event.GetCol();
//s.Printf(_T("-> row %d, col %d\n"), row, col ); m_log->AppendText( s );
//
//s2 = m_grid->GetCellValue( row, 2 );

//if( PRJ_MCU == wxT( "STM32F103" ) )
//{
//m_log->AppendText( wxT( "STM32F103\n" ) );
//m_log->AppendText( wxT( "if..." ) ); m_log->AppendText( s2 ); m_log->AppendText( wxT( "\n" ) );
//
//if( ( s2 == wxT( "GPIO_Mode_AIN ") ) ||
//	( s2 == wxT( "GPIO_Mode_IN_FLOATING ") ) ||
//	( s2 == wxT( "GPIO_Mode_IPD ") ) ||
//	( s2 == wxT( "GPIO_Mode_IPU ") ) ||
//	( s2 == wxT( "GPIO_Mode_Out_OD ") ) ||
//	( s2 == wxT( "GPIO_Mode_Out_PP ") ) ||
//	( s2 == wxT( "DS18B20" ) ) ||
//	( s2 == wxT( "iButton" ) ) )
//{
//
//m_log->AppendText( wxT( "STM32F103 - GPIO\n" ) );
//
//
////m_grid->SetCellTextColour(0, 2, *wxRED);
////m_grid->SetCellBackgroundColour(0, 2, *wxGREEN);
////m_grid->SetReadOnly( n, 1 );
//m_grid->SetReadOnly( row, 3, false );
//
//s3 = m_grid->GetCellValue( row, 3 );
//if( s3 == wxEmptyString )
//{
//m_grid->SetCellBackgroundColour( row, 2, *wxRED );
//
//
//}
//}
//}






//m_statusBar->SetStatusText( s );

//if( s == wxT("GPIO_Mode_AIN") )
//{

//s_sel = wxT( "1,2,3,4,5" );


//}
//else
//{
//s_sel = wxT( " " );
//}
//m_statusBar->SetStatusText( s_sel );
//s_sel = wxT( "1,2,3,4,5" );
//ce3->Reset();
//m_grid->SetCellEditor( row, 3, ce3 );
//ce3->SetParameters( s_sel );
//m_grid->Refresh();

//wxT("GPIO_Mode_IN_FLOATING")
//wxT("GPIO_Mode_IPD")
//wxT("GPIO_Mode_IPU")
//wxT("GPIO_Mode_Out_OD")
//wxT("GPIO_Mode_Out_PP")
//wxT("DS18B20")
//wxT("iButton")





//s = wxT( "1,2,3" );
//s = wxT( "," );
//s = wxEmptyString;
//m_grid->SetCellValue( row, 3, VAR_1XX_TYPES[0] );
//ce3->SetParameters( s_sel );

//{
//	const wxGridCellCoordsArray cells(m_grid->GetSelectedCells());
//	size_t count = cells.size();
//	s.Printf(_T("%lu cells selected:\n"), (unsigned long)count);  _log->AppendText( s );
//	if ( count > 100 )
//	{
//		s.Printf(_T("[too many selected cells, ")
//						_T("showing only the first %lu]\n"),
//						(unsigned long)100); _log->AppendText( s );
//		count = 100;
//	}
//
//	for ( size_t n = 0; n < count; n++ )
//	{
//		const wxGridCellCoords& c = cells[n];
//		s.Printf(_T("  selected cell %lu: (%d, %d)\n"),
//						(unsigned long)n, c.GetCol(), c.GetRow()); _log->AppendText( s );
//	}
//}





//const wxGridCellCoordsArray cells(m_grid->GetSelectedCells());
//size_t count = cells.size();
//s.Printf( wxT( "count = %d\n" ), count ); _log->AppendText( s );
//const wxGridCellCoords& c = cells[0];
//s.Printf(_T("  selected cell (%d, %d)\n"), c.GetCol(), c.GetRow());  _log->AppendText( s );


//wxLogMessage(_T("%lu cells selected:"), (unsigned long)count);
//if ( count > countMax )
//{
//	wxLogMessage(_T("[too many selected cells, ")
//					_T("showing only the first %lu]"),
//					(unsigned long)countMax);
//	count = countMax;
//}
//
//for ( size_t n = 0; n < count; n++ )
//{
//	const wxGridCellCoords& c = cells[n];
//	wxLogMessage(_T("  selected cell %lu: (%d, %d)"),
//					(unsigned long)n, c.GetCol(), c.GetRow());
//}



//m_statusBar->SetStatusText( wxT( "OnGridEditorShown" ), 0 );
//ce2->SetParameters( wxT( "1,2,3" ) );
event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnInsRow( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
int i;
int n;
wxString s;


//m_statusBar->SetStatusText( _T( "OnTool Insert Row" ) );

//wxGrid::InsertRows
//bool InsertRows(int pos = 0, int numRows = 1, bool updateLabels = true)

//wxGrid::GetNumberRows
n = m_grid->GetNumberRows();

//s.Printf( "OnTool Insert Row, n=%d", n );
//m_statusBar->SetStatusText( s );


m_grid->InsertRows( n, 1 );

//s.Printf( "%d", n );
//m_grid->SetCellValue( n, 1, s );
m_grid->SetGridCursor( n, 0 );

m_grid->SetCellEditor( n, 2, ce2 );
m_grid->SetCellValue( n, 2, VAR_1XX_TYPES[0] );
m_grid->SetCellEditor( n, 3, ce3 );
//m_grid->SetCellEditor( n, 5, ce5 );
//m_grid->SetCellValue( n, 5, cs5[1] );
//m_grid->SetCellValue( n, 2, VAR_1XX_TYPES[0] );

//m_grid->SetCellTextColour(0, 2, *wxRED);
//m_grid->SetCellBackgroundColour(0, 2, *wxGREEN);
m_grid->SetReadOnly( n, 1 );
m_grid->SetReadOnly( n, 3 );



//wxString c1[] =
//{
//wxEmptyString,
//_T("---"),
//_T("02"),
//_T("03"),
//_T("04"),
//_T("05"),
//_T("06"),
//_T("07"),
//_T(""),
//_T(""),
//};







//if(!n)
//{
//c1[1] = wxT( "===" );
//}
//else
//{
//c1[1] = wxT( "01" );
//}



//wxGridCellChoiceEditor *ce2 = new wxGridCellChoiceEditor(21, VAR_1XX_TYPES);


//m_grid->SetCellEditor(n, 2, new wxGridCellChoiceEditor(WXSIZEOF(c1), c1));
//m_grid->SetCellEditor(n, 2, new wxGridCellChoiceEditor(5, c1));
//s = m_grid->GetCellValue(n,2);
//_log->AppendText( wxT( "select cell = " ) ); _log->AppendText( s ); _log->AppendText( wxT( "\n" ) );

//delete ce;

//ce2->SetParameters( wxT( "1,2,3" ) );




//s.Printf( "WXSIZEOF(c1)=%d\n", WXSIZEOF(c1) );
//_log->AppendText( s );

//_log->AppendText( wxT( "c1=" ) );

//for( i = 0; i < WXSIZEOF(c1); i++ )
//{
//s.Printf( "%s;", c1[i].c_str() );
//_log->AppendText( s );
//}
//_log->AppendText( wxT( "\n" ) );








//	//m_grid->SetSelectionMode(wxGrid::wxGridSelectCells);
//
//	//Refresh();
//
//	//m_tool_data->EnableTool( ID_TOOL_DEL_ROW, false );
//	//m_tool_data->EnableTool( ID_TOOL_ROW_UP, false );
//	//m_tool_data->EnableTool( ID_TOOL_ROW_DOWN, false );
//	//m_tool_data->EnableTool( ID_TOOL_RUN, false );

//	if( !n )
//	{
//	m_tool_data->EnableTool( ID_TOOL_DEL_ROW, true );
//	m_grid->SetGridCursor( 0, 0 );
//	}


//	else
//	if( n == 1 )
//	{
//	m_tool_data->EnableTool( ID_TOOL_ROW_UP, true );
//	m_tool_data->EnableTool( ID_TOOL_ROW_DOWN, true );
//	m_grid->SetGridCursor( 1, 0 );
//	}
//	else
//	if( n > 1 )
//	{
//	m_grid->SetGridCursor( n, 0 );
//	}
//	//m_grid->SelectCol( 0 );
//
//	const wxString choices[] =
//	{
//	wxEmptyString,
//	_T("01"),
//	_T("02"),
//	_T("03"),
//	};
//
//	m_grid->SetCellEditor(n, 2, new wxGridCellChoiceEditor(WXSIZEOF(choices), choices));
//	m_grid->SetCellValue(n, 2, choices[1]);
//
//	//m_grid->SetCellOverflow(n, 2, false);
//
//
//	//wxGrid::SelectRow
//	//void SelectRow(int row, bool addToSelected = false)
//	//wxGrid::SelectCol
//	//void SelectCol(int col, bool addToSelected = false)
//
//
//	//m_grid->SetCellValue( 0, 1, wxT("-=+") );
//	//m_grid->SetGridCursor(20, 1);
//	//Refresh();
//
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnDelRow( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
wxString s;
const wxArrayInt sels = m_grid->GetSelectedRows();
int count = sels.size();
if( count )
{
s.Printf( "OnDelRow %d %d", sels[0], count );
}
else
s.Printf( "OnDelRow %d", count );

m_statusBar->SetStatusText( s, 0 );

//wxLogMessage(_T("%lu %s selected:"),
//(unsigned long)count, plural);

}
// ===========================================================================









// ===========================================================================
void MyFrame::OnTool_UART_config( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
wxString s;
	Set_COM set_com( this );

	if( set_com.ShowModal() == wxID_OK )
	{
		m_main_tool->SetToolNormalBitmap( ID_TOOL_CONNECT, disconnect_xpm );
		s.Printf( "COM%d", COM_NN );
		m_tool_com_port->SetValue( s );
		m_bitmap_com_indicator->SetBitmap( pw_r_xpm );
//s.Printf( "com=%d speed=%d", COM_NN, COM_SPEED );
//m_statusBar->SetStatusText( s );
	}
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnCANHelp( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
//	Help( (char*) &can, sizeof(can) );
}
// ===========================================================================


// ===========================================================================
void MyFrame::OnMyAbout( wxCommandEvent &WXUNUSED( event ) )
// ===========================================================================
{
	My_Help my_help( this );

	my_help.ShowModal();


//	Help( (char*) &can, sizeof(can) );
}
// ===========================================================================
