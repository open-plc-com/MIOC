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


/*
Config dir (sys):       C:\ProgramData\console
Config dir (user):      C:\Users\root\AppData\Roaming
Data dir (sys):         C:\s\_wx\samples\console\vc_msw
Data dir (sys local):   C:\s\_wx\samples\console\vc_msw
Data dir (user):        C:\Users\root\AppData\Roaming\console
Data dir (user local):  C:\Users\root\AppData\Local\console
Documents dir:          C:\Users\root\Documents
Executable path:        C:\s\_wx\samples\console\vc_msw\console.exe
Plugins dir:            C:\s\_wx\samples\console\vc_msw
Resources dir:          C:\s\_wx\samples\console\vc_msw
Localized res. dir:     C:\s\_wx\samples\console\vc_msw\fr
Message catalogs dir:   C:\s\_wx\samples\console\vc_msw\fr

wxStandardPathsBase& stdp = wxStandardPaths::Get();
wxPrintf(_T("Config dir (sys):\t%s\n"), stdp.GetConfigDir().c_str());
wxPrintf(_T("Config dir (user):\t%s\n"), stdp.GetUserConfigDir().c_str());
wxPrintf(_T("Data dir (sys):\t\t%s\n"), stdp.GetDataDir().c_str());
wxPrintf(_T("Data dir (sys local):\t%s\n"), stdp.GetLocalDataDir().c_str());
wxPrintf(_T("Data dir (user):\t%s\n"), stdp.GetUserDataDir().c_str());
wxPrintf(_T("Data dir (user local):\t%s\n"), stdp.GetUserLocalDataDir().c_str());
wxPrintf(_T("Documents dir:\t\t%s\n"), stdp.GetDocumentsDir().c_str());
wxPrintf(_T("Executable path:\t%s\n"), stdp.GetExecutablePath().c_str());
wxPrintf(_T("Plugins dir:\t\t%s\n"), stdp.GetPluginsDir().c_str());
wxPrintf(_T("Resources dir:\t\t%s\n"), stdp.GetResourcesDir().c_str());
wxPrintf(_T("Localized res. dir:\t%s\n"),
			stdp.GetLocalizedResourcesDir(_T("fr")).c_str());
wxPrintf(_T("Message catalogs dir:\t%s\n"),
			stdp.GetLocalizedResourcesDir
				(
				_T("fr"),
				wxStandardPaths::ResourceCat_Messages
				).c_str());
*/

#include "s1.h"
#include "tinyxml2.cpp"
namespace XML = tinyxml2;

// ===========================================================================
int MyFrame::OnPathInit()
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


//void MyFrame::Fill_Select(){}


// ===========================================================================
void MyFrame::Read_Prj()
// ===========================================================================
{
//_log->AppendText( wxT( "Read_Prj()\n" ) );
//s1();
}
// ===========================================================================


// ===========================================================================
void MyFrame::Write_Prj()
// ===========================================================================
{
	wxString			 s;
	XML::XMLDocument	 doc;
	XML::XMLElement		*e1, *e2;
	XML::XMLNode		*pRoot = doc.NewElement( "PRJ" );

	//doc.InsertEndChild( doc.NewDeclaration( "xml version=\"1.0\"" ) );
	doc.InsertEndChild( doc.NewDeclaration() );
	doc.InsertEndChild( pRoot );

e1 = doc.NewElement("Prj_Name");
e1->SetText( "Path\\Name" );
pRoot->InsertEndChild( e1 );

e1 = doc.NewElement("COM_Port");
e1->SetText( "1" );
pRoot->InsertEndChild( e1 );

e1 = doc.NewElement("COM_Port_speed");
e1->SetText( "2" );
pRoot->InsertEndChild( e1 );

e1 = doc.NewElement("MCU");
e1->SetText( "STM32F103C8T6" );
pRoot->InsertEndChild( e1 );

e1 = doc.NewElement("PA");
e1->SetText( "0000000000000010" );
pRoot->InsertEndChild( e1 );

e1 = doc.NewElement("Comment");
e1->SetText( "Comment" );
pRoot->InsertEndChild( e1 );

e1 = doc.NewElement("Grid");
pRoot->InsertEndChild( e1 );
//e2 = doc.NewElement("Row");
//e2->InsertEndChild( e1 );
e1->SetAttribute("c1", 26);
e1->SetAttribute("c3", "April");
e1->SetAttribute("c4", 2014);
e1->SetAttribute("c5", "Comment");



	doc.SaveFile( "prj.xml" );
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
	//s = wxT( "tst.xml" );

	if( !doc.LoadFile( s.c_str() ) )
	{
		r1 = doc.FirstChildElement( "CFG" );
		if( r1 )
		{
//_log->AppendText( wxT( "CFG\n" ) );
			// ---------------------------------------------------------------------------
			e1 = r1->FirstChildElement( "Win_MaxSize" );
			// ---------------------------------------------------------------------------
			if( e1 )
			{
//_log->AppendText( wxT( "E3\n" ) );
				s = wxT( e1->GetText() );
				if( s == wxT( "T" ) )
				{
					Read_Win_MaxSize = true;
//_log->AppendText( wxT( "Win_MaxSize=T\n" ) );
				}
				else
				{
					Read_Win_MaxSize = false;
//_log->AppendText( wxT( "Win_MaxSize=F\n" ) );
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
//s.Printf( wxT( "Read Win_PosX=%d\n" ), Win_PosX );
//_log->AppendText( s );
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
//s.Printf( wxT( "Read Win_PosY=%d\n" ), Win_PosY );
//_log->AppendText( s );
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
//s.Printf( wxT( "Read Win_SizeX=%d\n" ), Win_SizeX );
//_log->AppendText( s );
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
//s.Printf( wxT( "Read Win_SizeY=%d\n" ), Win_SizeY );
//_log->AppendText( s );
				}
//_log->AppendText( wxT( "E3_val=" ) ); _log->AppendText( s ); _log->AppendText( wxT( "\n" ) );

				// ---------------------------------------------------------------------------
				e1 = r1->FirstChildElement( "Prj_Name" );
				// ---------------------------------------------------------------------------
				if( e1 )
				{
					PRJ_NAME = wxT( e1->GetText() );
				}
			}
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
	XML::XMLElement		*r1, *e1;
	XML::XMLNode		*pRoot = doc.NewElement( "CFG" );

	doc.InsertEndChild( doc.NewDeclaration( "xml version=\"1.0\"" ) );
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
//	doc.SaveFile( "tst.xml" );
//	s = DATA_DIR + wxT( PATH_SEP ) + S_NAME + wxT( ".cfg" );
	doc.SaveFile( s.c_str() );
}
// ===========================================================================
