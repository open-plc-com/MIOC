/*
	Name:			set_com.h
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#ifndef __Set_COM__
#define __Set_COM__

#include "myframe_fb.h"

// ===========================================================================
class Set_COM : public Set_COM_FB
// ===========================================================================
{
	private:

	protected:
		bool sel_com;

		// Virtual event handlers, overide them in your derived class
		void OnOkButton( wxCommandEvent &event );
		void OnChoiseCOM( wxCommandEvent &event );

	public:
		Set_COM( wxWindow *parent );
		~Set_COM();
};
// ===========================================================================

#endif // __Set_COM__
