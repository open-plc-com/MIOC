This example of cymometer.

Put symometer.c to main folder

Example of code:

  #include "mx_init_hw.c"
  #include "cymometer.c"

  int main()
  {
  	Init_HW();
	Init_Cymometer();

	// ---------------------------------------------------------------------------
	// The main program loop
	// ---------------------------------------------------------------------------
	while( TRUE )
	{
 		delay_ms( 500 );
 		print( "Freq=%-10d\r", Freq );
	}
  }
