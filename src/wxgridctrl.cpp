#include "wxGridCtrl.h"

IMPLEMENT_DYNAMIC_CLASS( wxGridCtrl, wxGrid );

wxGridCtrl::wxGridCtrl()
{
}

wxGridCtrl::wxGridCtrl( wxWindow* parent, const long& id ):
            wxGrid( parent, id, wxDefaultPosition, wxDefaultSize )
{
}

BEGIN_EVENT_TABLE( wxGridCtrl, wxGrid )
    EVT_GRID_LABEL_LEFT_CLICK( wxGridCtrl::OnLabelLeftClick )
    EVT_GRID_SELECT_CELL( wxGridCtrl::OnSelectCell )
END_EVENT_TABLE();

void wxGridCtrl::DrawRowLabel( wxDC& dc, int row )
{
    if( GetRowHeight( row ) <= 0 || m_rowLabelWidth <= 0 )
        return;
    wxRect rect;
#ifdef __WXGTK20__
    rect.SetX( 1 );
    rect.SetY(GetRowTop( row ) + 1 );
    rect.SetWidth( m_rowLabelWidth - 2 );
    rect.SetHeight( GetRowHeight( row ) - 2 );
    CalcScrolledPosition( 0, rect.y, NULL, &rect.y );
    wxWindowDC *win_dc = ( wxWindowDC* ) &dc;
    wxRendererNative::Get().DrawHeaderButton( win_dc->m_owner, dc, rect, 0 );
#else
    int rowTop = GetRowTop( row ),
        rowBottom = GetRowBottom( row ) - 1;
    dc.SetPen( wxPen( wxSystemSettings::GetColour( wxSYS_COLOUR_3DSHADOW ), 1, wxSOLID ) );
    dc.DrawLine( m_rowLabelWidth - 1, rowTop, m_rowLabelWidth - 1, rowBottom );
    dc.DrawLine( 0, rowTop, 0, rowBottom );
    dc.DrawLine( 0, rowBottom, m_rowLabelWidth, rowBottom );
    dc.SetPen( *wxWHITE_PEN );
    dc.DrawLine( 1, rowTop, 1, rowBottom );
    dc.DrawLine( 1, rowTop, m_rowLabelWidth - 1, rowTop );
#endif
    if( row == GetGridCursorRow() )
    {
        dc.DrawBitmap( wxBitmap( rsn_xpm ), 0, GetRowTop( row ), true );
    }
}

void wxGridCtrl::OnLabelLeftClick( wxGridEvent& event )
{
    if( event.GetRow() != -1 )
    {
        SetGridCursor( event.GetRow(), 0 );
    }
    event.Skip();
}

void wxGridCtrl::OnSelectCell( wxGridEvent& event )
{
    GetGridRowLabelWindow()->Refresh();
    event.Skip();
}

/// Override
bool wxGridCtrl::CreateGrid( int numRows, int numCols, wxGrid::wxGridSelectionModes selmode )
{
    bool bCreate = wxGrid::CreateGrid( numRows, numCols, selmode );
    if( bCreate )
    {
        for( int i = 0; i < numRows; i++ )
        {
            m_mRowData[i] = 0;
        }
    }
    return bCreate;
}

bool wxGridCtrl::AppendRows( int numRows, bool updateLabels )
{
    int nRow = GetNumberRows();
    bool bAdd = wxGrid::AppendRows( numRows,updateLabels );
    if (bAdd)
    {
        while( nRow<GetNumberRows() )
        {
            m_mRowData[nRow] = 0;
            nRow++;
        }
    }
    return bAdd;
}

bool wxGridCtrl::InsertRows( int pos, int numRows, bool updateLabels )
{
    int i;
    std::map<int, int> mRow;
    for( i = 0; i < GetNumberRows(); i++ )
    {
        mRow[i] = GetRowData( i );
    }
    bool bIns=wxGrid::InsertRows( pos, numRows, updateLabels );
    if( bIns )
    {
        for( i = pos + numRows; i < GetNumberRows(); i++ )
        {
            m_mRowData[i] = mRow[i - numRows];
        }
        for( i = pos; i < pos + numRows; i++ )
        {
            m_mRowData[i] = 0;
        }
    }
    return bIns;
}

bool wxGridCtrl::DeleteRows( int pos, int numRows, bool updateLabels )
{
    std::map<int, int> mRow;
    for( int i=0; i < GetNumberRows(); i++)
    {
        mRow[i] = GetRowData( i );
    }
    bool bDel = wxGrid::DeleteRows( pos, numRows, updateLabels );
    if( bDel )
    {
        for( int i = pos; i < GetNumberRows(); i++ )
        {
            m_mRowData[i] = mRow[i + numRows];
        }
    }
    return bDel;
}

/// New
void wxGridCtrl::SetRowData( const int &row, const int &data )
{
    if( row < GetNumberRows() )
    {
        m_mRowData[row] = data;
    }
}

int wxGridCtrl::GetRowData( const int &row )
{
    int data = 0;
    if( row < GetNumberRows() && m_mRowData.find( row ) != m_mRowData.end() )
    {
        data = m_mRowData[row];
    }
    return data;
}
