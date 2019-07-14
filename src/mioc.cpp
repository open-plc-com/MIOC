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

//#include <wx/bitmap.h>
//#include <wx/image.h>
//#include <wx/icon.h>
//#include <wx/statbmp.h>
//#include <wx/gdicmn.h>
//#include <wx/font.h>
//#include <wx/colour.h>
//#include <wx/settings.h>
//#include <wx/string.h>
//#include <wx/grid.h>
//#include <wx/statline.h>
//#include <wx/sizer.h>
//#include <wx/button.h>
//#include <wx/panel.h>
//#include <wx/dialog.h>


//#include <wx/filename.h>

//#ifdef WIN32
    //#include <windows.h>
//#endif

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
