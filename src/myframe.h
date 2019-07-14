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


#ifndef __MyFrame__
#define __MyFrame__

#include <wx/msgdlg.h>
#include "myframe_fb.h"

class Run_Thread;
class Data_Thread;


// ===========================================================================
class MyFrame : public MyFrameFB
// ===========================================================================
{
	private:
		DECLARE_EVENT_TABLE()

	public:
		MyFrame( wxWindow		*parent,
				 wxWindowID		 id		= wxID_ANY,
				 const wxString	&title	= wxEmptyString,
				 const wxPoint	&pos	= wxDefaultPosition,
				 const wxSize	&size	= wxSize( 800,600 ),
				 long			 style	= wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL );
//				 long			 style	= wxCAPTION |
//										  wxCLOSE_BOX |
//										  wxICONIZE |
//										  wxMINIMIZE |
//										  wxMINIMIZE_BOX |
//										  wxSYSTEM_MENU |
//										  wxTAB_TRAVERSAL );
		~MyFrame();

		wxGridCellChoiceEditor	*ce2, *ce3, *ce5;
		wxArrayString			 port_list;
		wxString				 cs3[MAX_PORT_NN];
		wxString				 cs5[3];

//		DataIO_Com		*io_com;

		void	Help( char *str, int len );
		int		OnPathInit();
		void	Read_Prj();
		void	Write_Prj();
		int		Read_Cfg();
		void	Write_Cfg();

		//wxBitmap	wxGetBitmapFromMemory( const void *data, size_t length );

		//bool					CheckStartStop;
		//static volatile bool	IsRun;



		//Run_Thread		*CreateThread(), *run_thread_ptr;
		//Data_Thread		*CreateDataThread(), *data_thread_ptr;


		// Event handlers, static
 		void OnTool_New_Prj( wxCommandEvent &event );
 		void OnTool_Save_Prj( wxCommandEvent &event );
 		void OnExit( wxCommandEvent &event );

		void OnMaximized( wxMaximizeEvent &event );
		void OnSize( wxSizeEvent &event );
		void OnMove( wxMoveEvent &event );


//		void OnConnect( wxCommandEvent &event );
//		void OnRefresh( wxCommandEvent &event );
//		void OnRun( wxCommandEvent &event );
//		void OnStop( wxCommandEvent &event );
//		void OnFile( wxCommandEvent &event );
//		void ActualSize( wxCommandEvent &event );
//		void ZoneSize( wxCommandEvent &event );

		// Event handlers, overide them in your derived class
		void OnTool_UART_config( wxCommandEvent &event );


		void OnCANHelp( wxCommandEvent &event );
		void OnMyAbout( wxCommandEvent &event );
//		void OnCheckStart( wxCommandEvent& event );
//		void OnCheckStop( wxCommandEvent& event );

		// Virtual event handlers
		void On_check_UART1( wxCommandEvent &event );
		void On_check_USB_VCP( wxCommandEvent &event );
		void On_check_USB_console( wxCommandEvent &event );
//void OnShowSelection( wxCommandEvent &event );

// Grid handlers
void OnCellValueChanged( wxGridEvent& );
void OnEditorHidden( wxGridEvent &event );
void OnGridEditorHidden( wxGridEvent &event );
void OnGridEditorShown( wxGridEvent &event );
void OnDelRow( wxCommandEvent &event );
void OnInsRow( wxCommandEvent &event );
//void OnDelRow( wxCommandEvent &event );
//void OnRowUp( wxCommandEvent &event );
//void OnRowDown( wxCommandEvent &event );


	//// end generated class members
};
// ===========================================================================


//class MyHelp : public MyHelpFB
//{
	//public:
		//MyHelp( wxWindow *parent );
//};

#endif	// __MyFrame__
