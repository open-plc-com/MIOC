// ===========================================================================
class Data_Thread : public wxThread
// ===========================================================================
{
	public:
		Data_Thread(	MyFrame *frame );
		MyFrame*		m_frame;
		virtual void	*Entry();
		bool			m_cancel;
};
// ===========================================================================


// ===========================================================================
Data_Thread::Data_Thread( MyFrame *frame ) : wxThread()
// ===========================================================================
{
	m_frame = frame;
}
// ===========================================================================


// ===========================================================================
Data_Thread *MyFrame::CreateDataThread()
// ===========================================================================
{
	data_thread_ptr = new Data_Thread( this );
	data_thread_ptr->Create();
	return data_thread_ptr;
}
// ===========================================================================


// ===========================================================================
void *Data_Thread::Entry()
// ===========================================================================
{
	int		m;
	char	buf[128];

	m_cancel = FALSE;

	while( !m_cancel )
	{
		if( IsRun )
		{
			m = m_frame->io_com->GetStr( buf );
			if( m )
			{
				if( buf[0] == 'D' )
				{
					strcpy( ( char* ) DATA_STR[Data_NN++], buf );
//m_frame->m_msg->AppendText( wxT( buf ) );
//m_frame->m_msg->AppendText( wxT("\n") );
				}
				else
				if( !strcmp( buf, "STOP" ) )
				{
//m_frame->m_msg->AppendText( wxT("STOP\n") );
					IsRun = false;
				}
			}
		}
		else
		//if( !IsRunData )
		{
			wxThread::Sleep( 1 );
		}

		if( TestDestroy() )
			m_cancel = true;
	}
	return 0;
}
// ===========================================================================
