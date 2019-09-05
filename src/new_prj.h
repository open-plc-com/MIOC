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


class New_Prj : public New_Project_FB
{
	public:
		New_Prj( wxWindow *parent );
		~New_Prj();

		wxFrame		*my_frame;
		wxString	 prj_dir;

		void OnDirChanged( wxFileDirPickerEvent &event );
		void OnOkButton( wxCommandEvent &event );
};
