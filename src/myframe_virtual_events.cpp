/*
	Name:			myframe_virtual_events.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)


   ===========================================================================
   Virtual Events handlers
   ===========================================================================
*/


// ===========================================================================
void MyFrame::On_check_CAN_Internal( wxCommandEvent& event )
// ===========================================================================
{
	if( event.GetInt() )
	{
		m_check_CAN_MCP2515->SetValue( false );
	}
	PRJ_CHANGED = true;
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_CAN_MCP2515( wxCommandEvent& event )
// ===========================================================================
{
	if( event.GetInt() )
	{
		m_check_CAN_Internal->SetValue( false );
	}
	PRJ_CHANGED = true;
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_LCD1602( wxCommandEvent& event )
// ===========================================================================
{
	bool b1, b2;
	if( event.GetInt() )
	{
		b1 = m_check_8574->GetValue();
		b2 = m_check_8574A->GetValue();
		if( !b1 && !b2 )
		{
			m_check_8574A->SetValue( true );
		}
		m_check_SSD1306->SetValue( false );
	}
	PRJ_CHANGED = true;
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_PCF8574( wxCommandEvent& event )
// ===========================================================================
{
	bool b1, b2;
	if( event.GetInt() )
	{
		m_check_8574A->SetValue( false );
	}
	else
	{
		b1 = m_check_8574->GetValue();
		b2 = m_check_8574A->GetValue();
		if( !b1 && !b2 )
		{
			m_check_8574A->SetValue( true );
		}
	}
	PRJ_CHANGED = true;
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_PCF8574A( wxCommandEvent& event )
// ===========================================================================
{
	bool b1, b2;
	if( event.GetInt() )
	{
		m_check_8574->SetValue( false );
	}
	else
	{
		b1 = m_check_8574->GetValue();
		b2 = m_check_8574A->GetValue();
		if( !b1 && !b2 )
		{
			m_check_8574A->SetValue( true );
		}
	}
	PRJ_CHANGED = true;
	event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_SSD1306( wxCommandEvent& event )
// ===========================================================================
{
	if( event.GetInt() )
	{
		m_check_LCD1602->SetValue( false );
	}
	PRJ_CHANGED = true;
	event.Skip();
}
// ===========================================================================


void MyFrame::On_check_UART1( wxCommandEvent &event )       { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_USB_VCP( wxCommandEvent &event )     { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_USB_console( wxCommandEvent &event ) { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_W5500( wxCommandEvent& event )       { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_PC13( wxCommandEvent& event )        { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_BME280( wxCommandEvent& event )      { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_BH1750( wxCommandEvent& event )      { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_WATCHDOG( wxCommandEvent& event )    { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_MCO( wxCommandEvent& event )         { PRJ_CHANGED = true; event.Skip(); }
void MyFrame::On_check_TIMER( wxCommandEvent& event )       { PRJ_CHANGED = true; event.Skip(); }
