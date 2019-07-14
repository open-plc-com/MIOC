#include <windows.h>
#include "dataio_com.h"
#include <iostream>
//#include <Winspool.h>

#define COM_BUF_SIZE 128

// ===========================================================================
DataIO_Com::DataIO_Com()
// ===========================================================================
{
	this->state		= false;
	ComBaudRate		= 115200;
	ComByteSize		= 8;
	ComParity		= 0;
	ComStopBits		= 1;
	ComStreamCtrl	= 0;
}
// ===========================================================================


// ===========================================================================
DataIO_Com::~DataIO_Com()
// ===========================================================================
{
	this->Close();
}
// ===========================================================================


// ===========================================================================
void DataIO_Com::State()
// ===========================================================================
{
	if( GetCommState( m_hFile, &dcb ) )
	{
		this->state = false;
	}
}
// ===========================================================================


// ===========================================================================
bool DataIO_Com::Open( int port, int baud )
// ===========================================================================
{
	DCB dcb;
	char COM_string[20];
	sprintf( COM_string,"\\\\.\\COM%d", port );

	m_hFile = CreateFile( COM_string,
						  GENERIC_READ | GENERIC_WRITE,
						  0,
						  NULL,
						  OPEN_EXISTING,
						  FILE_ATTRIBUTE_NORMAL,
						  //FILE_FLAG_OVERLAPPED,
						  NULL );

	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		return false;
	}

	GetCommState( m_hFile, &dcb );

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout			= MAXDWORD;
//	CommTimeOuts.ReadIntervalTimeout			= 0;
	CommTimeOuts.ReadTotalTimeoutMultiplier		= 0;
	CommTimeOuts.ReadTotalTimeoutConstant		= 200;
	CommTimeOuts.WriteTotalTimeoutMultiplier	= 0;
	CommTimeOuts.WriteTotalTimeoutConstant		= 0;

	SetCommTimeouts( m_hFile, &CommTimeOuts );

	// Boilerplate.
	dcb.fBinary				= TRUE;
	dcb.fAbortOnError		= FALSE;
//	dcb.fDtrControl			= DTR_CONTROL_ENABLE;
//	dcb.fDsrSensitivity		= FALSE;
//	dcb.fTXContinueOnXoff	= TRUE;
//	dcb.fOutX				= TRUE;
//	dcb.fInX				= TRUE;
//	dcb.fErrorChar			= FALSE;
//	dcb.fNull				= FALSE;
//	dcb.fRtsControl			= RTS_CONTROL_ENABLE;
//	dcb.fOutxCtsFlow		= FALSE;
//	dcb.fOutxDsrFlow		= FALSE;

	dcb.fOutX				= FALSE;

	dcb.ByteSize			= 8;
	dcb.Parity				= NOPARITY;
	dcb.StopBits			= ONESTOPBIT;
	dcb.BaudRate			= baud;

//	dcb.fDtrControl			= DTR_CONTROL_ENABLE;
//	dcb.fRtsControl			= RTS_CONTROL_ENABLE;

//	dcb.fBinary				= TRUE;
	dcb.DCBlength			= sizeof( DCB );

	SetCommState( m_hFile, &dcb );

	this->state = true;
	return true;
}
// ===========================================================================


// ===========================================================================
void DataIO_Com::Close()
// ===========================================================================
{
	this->state = false;
	CloseHandle( m_hFile );
}
// ===========================================================================


// ===========================================================================
void DataIO_Com::Clean()
// ===========================================================================
{
	if( !state )
	{
		return;
	}

	PurgeComm( m_hFile, PURGE_TXCLEAR | PURGE_RXCLEAR );
}
// ===========================================================================


// ===========================================================================
int DataIO_Com::Send( char *buff, int szBuff )
// ===========================================================================
{
	if( !state )
	{
		return 0;
	}

	if( buff == NULL || szBuff <= 0)
	{
		return 0;
	}

	DWORD lpdwBytesWrittens = 0;
	WriteFile( m_hFile, buff, szBuff, &lpdwBytesWrittens, NULL );

	return lpdwBytesWrittens;
}
// ===========================================================================


// ===========================================================================
int DataIO_Com::Recv( char *buff, int szBuff )
// ===========================================================================
{
	if( !state )
	{
		return 0;
	}

	if( ( buff == NULL ) || ( szBuff <= 0 ) )
	{
		return 0;
	}

	DWORD dwBytesRead = 0;
	ReadFile( m_hFile, buff, szBuff, &dwBytesRead, NULL );

	return dwBytesRead;
}
// ===========================================================================


// ===========================================================================
int DataIO_Com::GetStr( char *buff )
// ===========================================================================
{
	int		j, k, m, n;
	char	c;

	k = COM_BUF_SIZE;

	if( !state )
	{
		return 0;
	}

	if( buff == NULL )
	{
		return 0;
	}

	for( j = 0; j < k; j++ )
	{
		buff[j] = 0;
	}

	m = 1;
	n = 1;
	j = 0;
	while( n && m )
	{
		n = Recv( &c, 1 );
		if( n )
		{
//			if( ( c == 13 ) || ( c == 10 ) )
			if( c == 13 )
			{
				m = 0;
			}
			else
			{
				if( c != 10 )
				{
					buff[j] = c;
					j++;
					if( j == k )
					{
						m = 0;
					}
				}
			}
		}
	}

	return strlen( buff );
}
// ===========================================================================


// ===========================================================================
void DataIO_Com::SetLine( OUT_LINES_NAME ln, bool state )
// ===========================================================================
{
	unsigned char value = 0;

	if( !state )
	{
		return ;
	}

	if( ln == DTR )
	{
		if( state )
		{
			value = 6;
		}
		else
		{
			value = 5;
		}
	}

	if( ln == RTS )
	{
		if( state )
		{
			value = 4;
		}
		else
		{
			value = 3;
		}
	}

	EscapeCommFunction( m_hFile, value );
}
// ===========================================================================


// ===========================================================================
bool DataIO_Com::GetLine( IN_LINES_NAME	ln )
// ===========================================================================
{
	unsigned long ul = 0;

	if( !state )
	{
		return 0;
	}

	GetCommModemStatus( m_hFile, &ul );

	if( ( ul == 0x10 ) && ( ln == CTS ) )
	{
		return true;
	}

	if( ( ul == 0x20 ) && ( ln == DSR ) )
	{
		return true;
	}

	if( ( ul == 0x40 ) && ( ln == RING ) )
	{
		return true;
	}

	if( ( ul == 0x80 ) && ( ln == RLSD ) )
	{
		return true;
	}

	return false;
}
// ===========================================================================


// ===========================================================================
void DataIO_Com::GetPortList( wxArrayString *port_list )
// ===========================================================================
{
	int				i, j, k, l, n;
	int				nLen;
	long			li;
	OSVERSIONINFO	osvi;
	wxString		s, ws;
	wxArrayString	port_l;

	port_list->Clear();
	port_l.Clear();

	osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	BOOL bGetVer = GetVersionEx( &osvi );

	// What system are we working in? ( Only Nt, Xp, Vista, Win7, Win10 )
	// used API QueryDosDevice
	if( bGetVer && ( osvi.dwPlatformId == VER_PLATFORM_WIN32_NT ) )
	{
		// Use QueryDosDevice to view all devices similar to COMx.
		// This is the best solution since ports do not need to be opened.
		TCHAR szDevices[65535];
		DWORD dwChars = QueryDosDevice( NULL, szDevices, 65535 );
		if( dwChars )
		{
			i = 0;
			for( ;; )
			{
				// Get current device name
				TCHAR *pszCurrentDevice = &szDevices[i];

				// If it looks like "COMX" add to the list
				nLen = _tcslen( pszCurrentDevice );

				s = pszCurrentDevice;
				ws = s.Mid( 0, 3 );		// first 3 characters
				if( ( ws.Upper() == "COM" ) && ( s.Length() < 7 ) )
				{
					port_l.Add( s );
				}

				// Go to the next character terminator
				while( szDevices[i] != wxT( '\0' ) )
				{
					i++;
				}

				// Jump to the next line
				i++;

				// The list ends with a double terminator symbol, so if the character is NULL,
				// we have reached the end
				if( szDevices[i] == wxT( '\0' ) )
				{
					break;
				}
			}
		}
	}

	// Sort the list of ports
	n = port_l.Count();
	for( i = 0; i < n - 1; i++ )
	{
		for( j = i + 1; j < n; j++ )
		{
			s = port_l[i].Mid( 3 );
			s.ToLong( &li );
			k = li;
			s = port_l[j].Mid( 3 );
			s.ToLong( &li );
			l = li;
			if( l < k )
			{
				s = port_l[j];
				port_l[j] = port_l[i];
				port_l[i] = s;
			}
		}
	}
	for( i = 0; i < n; i++ )
	{
		port_list->Add( port_l[i] );
	}
}
// ===========================================================================
