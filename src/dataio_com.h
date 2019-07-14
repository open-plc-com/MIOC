#ifndef __dataiocom__
#define __dataiocom__

#include <windows.h>

#define MAX_WIN_PORT 255


// ===========================================================================
class DataIO_Com
// ===========================================================================
{
    protected:
        HANDLE  m_hFile;
        DCB     dcb;
        //dcb.DCBlength = sizeof(DCB);
        enum IN_LINES_NAME{ CTS, DSR, RING, RLSD };
        enum OUT_LINES_NAME{ DTR, RTS };

    public:
        DataIO_Com();
        ~DataIO_Com();
        bool            state;
        int             ComBaudRate;    // Speed
        unsigned char   ComByteSize;    // Bits in byte: 4-8
        unsigned char   ComParity;      // 0-4 = no, odd, even, mark, space
        unsigned char   ComStopBits;    // 0,1,2 = 1, 1.5, 2
        unsigned char   ComStreamCtrl;  // 0,1 = NONE, CTS/RTS

        void            State();
        bool            Open( int port, int baud );
        void            Close();
        void            Clean();
        int             Send( char *buff, int szBuff );
        int             Recv( char *buff, int szBuff );
        int             GetStr( char *buff );
        void            SetLine( OUT_LINES_NAME ln, bool state );
        bool            GetLine( IN_LINES_NAME ln );
        void            GetPortList( wxArrayString *s );
};
// ===========================================================================

#endif // __dataiocom__