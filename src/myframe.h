/*
	Name:			myframe.h
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
		~MyFrame();

		wxGridCellChoiceEditor	*ce2, *ce3, *ce5;
		wxString				 cs5[3];
		wxArrayString			 port_list;

		volatile struct M_Grid_Struct
		{
			wxString	c0;
			int			c2;
			int			c3;
			wxString	c4;
			int			c5;
		} m_grid_r1, m_grid_r2;
		M_Grid_Struct	m_grid_r[MAX_GRID_NN];

//		DataIO_Com		*io_com;

		void	Help( char *str, int len );
		int		OnPathInit();
		int		Read_Prj();
		void	Write_Prj();
		int		Read_Cfg();
		void	Write_Cfg();

		// Config
		void	Disable_Config( void );
		void	Enable_Config( void );
		int		Set_Lists( void );
		void	Clear_Project( void );
		bool	Parse_Port( wxString port, unsigned int *port_name, unsigned int *port_nn );
		bool	Check_Port( wxString port, unsigned int row );
		void	Check_Config( void );

		wxBitmap	wxGetBitmapFromMemory( const void *data, size_t length );

		//bool					CheckStartStop;
		//static volatile bool	IsRun;

		//Run_Thread		*CreateThread(), *run_thread_ptr;
		//Data_Thread		*CreateDataThread(), *data_thread_ptr;

//void Set_MDK_prj_stm32f103c8( wxString *buf, wxString prj_name );

		// Event handlers, static
 		void OnTool_New_Prj( wxCommandEvent &event );
		void OnTool_Open_Prj( wxCommandEvent &event );
		void OnTool_Close_Prj( wxCommandEvent &event );
 		void OnTool_Save_Prj( wxCommandEvent &event );
 		void OnExit( wxCommandEvent &event );

		void OnMaximized( wxMaximizeEvent &event );
		void OnSize( wxSizeEvent &event );
		void OnMove( wxMoveEvent &event );

		void OnTool_UART_config( wxCommandEvent &event );
		void OnTool_UART_help( wxCommandEvent &event );
		void OnTool_I2C_help( wxCommandEvent &event );

		void OnCANHelp( wxCommandEvent &event );
		void OnMyAbout( wxCommandEvent &event );
		void OnMyFunctions( wxCommandEvent &event );
		void OnTool_Generate_FW( wxCommandEvent &event );
		void Asc_to_Save( void );

		// Grid handlers
		void OnCellValueChanged( wxGridEvent& );
		void Save_Rows( void );
		void OnDelRow( wxCommandEvent &event );
		void OnInsRow( wxCommandEvent &event );
		//void OnRowUp( wxCommandEvent &event );
		//void OnRowDown( wxCommandEvent &event );

//		void OnConnect( wxCommandEvent &event );
//		void OnRefresh( wxCommandEvent &event );
//		void OnRun( wxCommandEvent &event );
//		void OnStop( wxCommandEvent &event );
//		void OnFile( wxCommandEvent &event );
//		void ActualSize( wxCommandEvent &event );
//		void ZoneSize( wxCommandEvent &event );

		// Virtual event handlers
		void On_check_UART1( wxCommandEvent &event );
		void On_check_USB_VCP( wxCommandEvent &event );
		void On_check_USB_console( wxCommandEvent &event );
		void On_check_CAN_Internal( wxCommandEvent& event );
		void On_check_CAN_MCP2515( wxCommandEvent& event );
		void On_check_W5500( wxCommandEvent& event );
		void On_check_PC13( wxCommandEvent& event );
		void On_check_LCD1602( wxCommandEvent& event );
		void On_check_PCF8574( wxCommandEvent& event );
		void On_check_PCF8574A( wxCommandEvent& event );
		void On_check_SSD1306( wxCommandEvent& event );
		void On_check_BME280( wxCommandEvent& event );
		void On_check_BH1750( wxCommandEvent& event );
		void On_check_WATCHDOG( wxCommandEvent& event );
		void On_check_MCO( wxCommandEvent& event );
		void On_check_TIMER( wxCommandEvent& event );
};
// ===========================================================================

#endif	// __MyFrame__
