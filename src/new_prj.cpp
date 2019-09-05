/*
	Name:			new_prj.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include "new_prj.h"

// ===========================================================================
New_Prj::New_Prj( wxWindow *parent ) : New_Project_FB( parent )
// ===========================================================================
{
}
// ===========================================================================


// ===========================================================================
New_Prj::~New_Prj() {}
// ===========================================================================


// ===========================================================================
void New_Prj::OnDirChanged( wxFileDirPickerEvent &WXUNUSED( event ) )
// ===========================================================================
{
	wxString s, s1, s2;

	s = wxEmptyString;
	s1 = m_dir->GetPath();
	if( s1.Len() > 3 )
	{
		s2 = m_project_name->GetValue();
		if( s2 != wxEmptyString )
		{
			prj_dir = s1;
			s = s1 + wxT( PATH_SEP ) + s2 + wxT( ".prj" );
			m_path_project_name->SetValue( s );
		}
	}
}
// ===========================================================================


// ===========================================================================
void New_Prj::OnOkButton( wxCommandEvent &event )
// ===========================================================================
{
	int				i, n;
	wxString		s;
	wxDir			dir;
	wxArrayString	files;

	i = m_choice_MCU->GetSelection();
	s = m_choice_MCU->GetString( i );
	i = 1;
	if( s == wxEmptyString )
	{
		i = 0;
	}

	s = m_path_project_name->GetValue();
	if( s == wxEmptyString )
	{
		i = 0;
	}

	n = dir.GetAllFiles( prj_dir, &files );

//n = 0;	// for test only !!!

	if( n )
	{
		s = wxT( "Directory \"" ) + s + wxT( "\" not empty." );
		wxMessageBox( s, wxT( "Error" ), wxICON_HAND );
		i = 0;
	}

	if( i )
	{
		event.Skip();
	}
}
// ===========================================================================
