#ifndef __grig_ctrl__
#define __grig_ctrl__

//#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <map>

class wxGridCtrl: public wxGrid
{
    std::map<int,int> m_mRowData;
    DECLARE_DYNAMIC_CLASS( wxGridCtrl )

protected:
    virtual void DrawRowLabel( wxDC& dc, int row );
    virtual void OnLabelLeftClick( wxGridEvent& event );
    virtual void OnSelectCell( wxGridEvent& event );

    DECLARE_EVENT_TABLE();

public:
    wxGridCtrl();
    wxGridCtrl( wxWindow *parent, const long& id );
//  Override
    bool CreateGrid( int numRows,
                     int numCols,
                     wxGrid::wxGridSelectionModes selmode = wxGrid::wxGridSelectCells );
    bool AppendRows( int numRows = 1, bool updateLabels = true );
    bool InsertRows( int pos = 0, int numRows = 1, bool updateLabels = true );
    bool DeleteRows( int pos = 0, int numRows = 1, bool updateLabels = true );
//  New
    void SetRowData( const int& row, const int& data );
    int GetRowData( const int& row );
};

/* Arrow label: */
/* XPM */
static char *rsn_xpm[] = { "16 16 48 1",
"   c None",   ".  c #4585BA","+  c #4284B9","@  c #4182B8","#  c #C3DDEB",
"$  c #3D80B7","%  c #3F81B8","&  c #B2D3E7","*  c #ABCEE5","=  c #3F81B7",
"-  c #A9CEE6",";  c #368AC2",">  c #AACEE3",",  c #4081B7","'  c #4082B7",
")  c #A3CBE7","!  c #4393CA","~  c #4494CA","{  c #A2C7E0","]  c #4081B8",
"^  c #4182B7","/  c #9AC8E6","(  c #4D9CD1","_  c #4E9DD1",":  c #5FA6D6",
"<  c #9AC0DA","[  c #94C6E8","}  c #56A3D6","|  c #57A4D7","1  c #64ACDC",
"2  c #92BCD7","3  c #8EC5EA","4  c #5EAADD","5  c #5FABDF","6  c #93C4E6",
"7  c #4182B6","8  c #88C4EC","9  c #65B2E4","0  c #8CC3E6","a  c #4181B6",
"b  c #4282B6","c  c #84C6F1","d  c #8BCBF3","e  c #4081B6","f  c #4383B8",
"g  c #87CDFC","h  c #4583B8","i  c #4484B8",
"                ","                ","    .+          ","    @#$         ",
"    %&*=        ","    =-;>,       ","    ')!~{]      ","    ^/(_:<+     ",
"    ^[}|12+     ","    ^3456,      ","    7890a       ","    bcde        ",
"    fga         ","    hi          ","                ","                " };

#endif // __grig_ctrl__