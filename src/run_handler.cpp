// ===========================================================================
class Run_Thread : public wxThread
// ===========================================================================
{
	public:
		Run_Thread( MyFrame *frame );
		MyFrame*		m_frame;
		virtual void	*Entry();
		bool			m_cancel;
};
// ===========================================================================


// ===========================================================================
Run_Thread::Run_Thread( MyFrame *frame ) : wxThread()
// ===========================================================================
{
	m_frame = frame;
}
// ===========================================================================


// ===========================================================================
Run_Thread *MyFrame::CreateThread()
// ===========================================================================
{
	run_thread_ptr = new Run_Thread( this );
	run_thread_ptr->Create();
	return run_thread_ptr;
}
// ===========================================================================


// ===========================================================================
void *Run_Thread::Entry()
// ===========================================================================
{
	int			n;
	float		x, y;
	long		d1, d2;
	char		buf[128];
	wxString	s, s1, s2, s3;

	m_cancel = FALSE;

//try
//{
	while( !m_cancel )
	{
//		if( Data_Show < Data_NN )
//		{
//			s = wxT( ( char* ) DATA_STR[Data_Show] );
//			s[0] = ' ';
//			s[1] = ' ';
//			s.Trim( FALSE );
//			n = s.Find( ';' );
//			if( n )
//			{
//				s1 = s.Mid( 0, n );
//				s2 = s.Mid( n + 1 );
//			}
//			else
//			{
//				s1 = wxT( "0" );
//				s2 = wxT( "0" );
//			}
//			s1.ToLong( &d1 );
//			s2.ToLong( &d2 );
//			x = d1 / 1000.0;
//			y = d2;
//			m_frame->vectorx.push_back( x );
//			m_frame->vectory.push_back( y );
//			m_frame->vectorLayer->SetData( m_frame->vectorx, m_frame->vectory );
//			if( ( Data_Show % 10 ) == 0 )
//			{
//				m_frame->m_plot->Refresh();
//				m_frame->m_plot->Update();
//			}
//		
//			if( m_frame->m_grid->InsertRows( Data_Show ) )
//			{
//				s1.Printf( "%.3f", x );
//				s2.Printf( "%d", ( int ) y );
//				m_frame->m_grid->SetCellValue( Data_Show, 0, s1 );
//				m_frame->m_grid->SetCellValue( Data_Show, 1, s2 );
//			}
//			Data_Show++;
//		}	// if( Data_Show < Data_NN )
//
////wxMilliSleep( 300 );
//		if( ( !IsRun ) && ( !Stop ) )
//		{
//			m_frame->m_grid->EndBatch();
//			//m_frame->m_grid->Update();
//			//m_frame->m_plot->Update();
//			m_frame->Refresh();
//			m_frame->Update();
//			Stop = true;
//
//			strcpy( buf, "S\r" );
//			n = m_frame->io_com->Send( buf, strlen( buf ) );
//
//			m_frame->m_start->SetEditable( true );
//			m_frame->m_stop->SetEditable( true );
//
//			m_frame->m_toolBar->EnableTool( ID_TOOL_STOP, false );
//			m_frame->m_toolBar->EnableTool( ID_TOOL_RUN, true );
//			m_frame->m_toolBar->EnableTool( ID_TOOL_FILE, true );
//		}

		if( !IsRun )
		{
			wxThread::Sleep( 1 );
		}

		if( TestDestroy() )
			m_cancel = true;
	}
	return 0;
//}
//catch(...){}
}
// ===========================================================================
