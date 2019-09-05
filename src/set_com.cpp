/*
	Name:			set_com.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include "set_com.h"

// ===========================================================================
Set_COM::Set_COM( wxWindow *parent ) : Set_COM_FB( parent )
// ===========================================================================
{
	int				i, com_nn;
	wxString		s;
	wxArrayString	port_list;

	sel_com = false;
	IO_COM->GetPortList( &port_list );
	com_nn = port_list.Count();
	s = wxEmptyString;
	m_com_choice->Clear();
	for( i = 0; i < com_nn; i++ )
	{
		m_com_choice->Append( port_list[i] );
	}
}
// ===========================================================================


// ===========================================================================
Set_COM::~Set_COM(){}
// ===========================================================================


// ===========================================================================
void Set_COM::OnOkButton( wxCommandEvent &event )
// ===========================================================================
{
	if( sel_com )
	{
		event.Skip();
	}
	else
	{
		wxMessageBox( wxT( "Select COM-port" ), wxT( "Error" ), wxICON_HAND );
	}
}
// ===========================================================================


// ===========================================================================
void Set_COM::OnChoiseCOM( wxCommandEvent &event)
// ===========================================================================
{
	int			i;
	long		l;
	wxString	s;

	i = event.GetInt();
	s = m_com_choice->GetString( i );
	s = s.Mid( 3 );
	if( s.ToLong( &l ) )
	{
		COM_NN = l;
		sel_com = true;

		i = m_speed_choice->GetCurrentSelection();
		s = m_speed_choice->GetString( i );
		s.ToLong( &l );
		COM_SPEED = l;
	}
}
// ===========================================================================
