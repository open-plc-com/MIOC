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
// Event handlers
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_UART1( wxCommandEvent &event )
// ===========================================================================
{
	//wxCheckBox *cb;
	//cb = ( wxCheckBox* ) event.GetEventObject();
	if( event.GetInt() )
	{
		//USE_UART1 = true;
//m_statusBar->SetStatusText( _T("USE_UART1 true") );
	}
	else
	{
		//USE_UART1 = false;
//m_statusBar->SetStatusText( _T("USE_UART1 false") );
	}
event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_USB_VCP( wxCommandEvent &event )
// ===========================================================================
{
	//wxCheckBox *cb;
	//cb = ( wxCheckBox* ) event.GetEventObject();
	if( event.GetInt() )
	{
		//USB_VCP = true;
	}
	else
	{
		//USB_VCP = false;
	}
event.Skip();
}
// ===========================================================================


// ===========================================================================
void MyFrame::On_check_USB_console( wxCommandEvent &event )
// ===========================================================================
{
	//wxCheckBox *cb;
	//cb = ( wxCheckBox* ) event.GetEventObject();
	if( event.GetInt() )
	{
		//USB_CONSOLE = true;
	}
	else
	{
		//USB_CONSOLE = false;
	}
event.Skip();
}
// ===========================================================================
