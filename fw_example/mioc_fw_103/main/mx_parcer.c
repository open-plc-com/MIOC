/*
	Name:			parcer.c
	Purpose:
	Author:			Alexander Suvorov (www.open-plc.com)
	Created:		2017/12
	Modified by:
	RCS-ID:
	Copyright:		(c) Alexander Suvorov
	Licence:		The MIT License (MIT)
*/


#define S_I_NN 7	// max S_I_NN parameters

// ===========================================================================
int parce_str( char *str, int n_prm )	// return to str parameter # n_prm
// ===========================================================================
{
	int		i, j, n, n1, n2, count_prm;
	int		space_index[S_I_NN];
//	char	s[128];

	n = strlen( ( char* ) usart_rx_data );
	str[0] = 0;
	count_prm = 0;

	if( ( n_prm < 1 ) || ( n_prm > S_I_NN ) )
	{
		return 0;
	}

	if( n )		// Length > 0
	{
		// -----------------------------------------------------------
		// Trim left spaces
		// -----------------------------------------------------------
		j = 0;
		while( usart_rx_data[0] == ' ' )
		{
			n = strlen( ( char* ) usart_rx_data );
			for( j = 0; j < n; j++ )
			{
				usart_rx_data[j] = usart_rx_data[j + 1];
			}
		}
		// -----------------------------------------------------------


		// -----------------------------------------------------------
		// Trim right spaces
		// -----------------------------------------------------------
		n = strlen( ( char* ) usart_rx_data ) - 1;
		if( n > 0 )
		{
			while( usart_rx_data[n] == ' ' )
			{
				if( n >= 0 )
				{
					usart_rx_data[n] = 0;
					if( n )
					{
						n--;
					}
				}
			}
		}
		// -----------------------------------------------------------


		// -----------------------------------------------------------
		// Prepare cmd string
		// -----------------------------------------------------------
		n = strlen( ( char* ) usart_rx_data );
		for( i = 0; i < n; i++ )
		{
			if( ( usart_rx_data[i] < 32 ) || ( usart_rx_data[i] > 126 ) )
			{
				if( usart_rx_data[i] )
				{
					usart_rx_data[i] = '$';
				}
			}
			if( usart_rx_data[i] > 96 )
			{
				usart_rx_data[i] -= 32;		// to upper
			}

			// Remove duplicate spaces
			while( ( usart_rx_data[i] == ' ' ) && ( usart_rx_data[i + 1] == ' ' ) )
			{
				for( j = i; j < n; j++ )
				{
					usart_rx_data[j] = usart_rx_data[j + 1];
				}
			}
		}	// for( i = 0; i < n; i++ )

		// Calculate space indexes
		for( j = 0; j < S_I_NN; j++ )
		{
			space_index[j] = 0;
		}

		j = 0;
		for( i = 0; i <= n; i++ )
		{
			if( ( ( usart_rx_data[i] == ' ' ) || ( usart_rx_data[i] == 0 ) ) && ( j < S_I_NN ) )
			{
				space_index[j++] = i;
				count_prm++;
			}
		}
		// -----------------------------------------------------------


		// -----------------------------------------------------------
		// Get param n_prm
		// -----------------------------------------------------------
		if( space_index[n_prm-1] )
		{
			if( n_prm == 1 )
			{
				n1 = 0;
				n2 = space_index[n_prm-1];
			}
			else
			{
				n1 = space_index[n_prm-2] + 1;
				n2 = space_index[n_prm-1];
			}

			for( i = n1; i < n2; i++ )
			{
				str[i-n1] = usart_rx_data[i];
			}
			str[i-n1] = 0;
		}
		return count_prm;
	}
return 0;
}
// ===========================================================================
