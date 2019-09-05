/*
	Name:			mioc.cpp
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include "wx/wxprec.h"
#include <wx/txtstrm.h>

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/file.h>
#include <wx/xml/xml.h>
#include <wx/grid.h>
#include <wx/mstream.h>
#include <wx/config.h>
#include <wx/socket.h>
#include <wx/textfile.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include "wx/generic/gridctrl.h"

#include "dataio_com.cpp"
#include "msg.h"
#include "gbl.h"
#include "myframe.cpp"

#ifndef _MY_APP
#define _MY_APP


class my : public wxApp
{
    public:
        bool    OnInit();
        MyFrame *frame;
};

IMPLEMENT_APP( my )

bool my::OnInit()
{
    wxImage::AddHandler( new wxPNGHandler );    // PNG handler
    frame = new MyFrame( ( wxFrame* ) NULL, -1, MSG_000 );
    frame->Show( TRUE );
    return true;
}

#endif _MY_APP
