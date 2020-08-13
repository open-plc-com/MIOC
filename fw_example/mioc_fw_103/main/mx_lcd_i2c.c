// Display TWI LCD1602 / I2C
// ===========================================================================
// last updated on 11/2018
// wiki doc http://www.dfrobot.com/wiki/index.php?title=I2C/TWI_LCD1602_Module_(SKU:_DFR0063)

#ifdef LCD_1602
// ===========================================================================

#ifdef LCD_1602_FAST
#include "mx_lcd_i2c_f.c"
#endif

typedef struct
{
	uint8_t Addr;
	uint8_t displayfunction;
	uint8_t displaycontrol;
	uint8_t displaymode;
	uint8_t numlines;
	uint8_t cols;
	uint8_t rows;
	uint8_t backlightval;
}	LiquidCrystal_I2C_Def;

LiquidCrystal_I2C_Def lcdi2c;

// commands
#define LCD_CLEARDISPLAY			0x01
#define LCD_RETURNHOME				0x02
#define LCD_ENTRYMODESET			0x04
#define LCD_DISPLAYCONTROL			0x08
#define LCD_CURSORSHIFT				0x10
#define LCD_FUNCTIONSET				0x20
#define LCD_SETCGRAMADDR			0x40
#define LCD_SETDDRAMADDR			0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT				0x00
#define LCD_ENTRYLEFT				0x02
#define LCD_ENTRYSHIFTINCREMENT		0x01
#define LCD_ENTRYSHIFTDECREMENT		0x00

// flags for display on/off control
#define LCD_DISPLAYON				0x04
#define LCD_DISPLAYOFF				0x00
#define LCD_CURSORON				0x02
#define LCD_CURSOROFF				0x00
#define LCD_BLINKON					0x01
#define LCD_BLINKOFF				0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE				0x08
#define LCD_CURSORMOVE				0x00
#define LCD_MOVERIGHT				0x04
#define LCD_MOVELEFT				0x00

// flags for function set
#define LCD_8BITMODE				0x10
#define LCD_4BITMODE				0x00
#define LCD_2LINE					0x08
#define LCD_1LINE					0x00
#define LCD_5x10DOTS				0x04
#define LCD_5x8DOTS					0x00

// flags for backlight control
#define LCD_BACKLIGHT				0x08
#define LCD_NOBACKLIGHT				0x00

#define En							0x04	// Enable bit
#define Rw							0x02	// Read/Write bit
#define Rs							0x01	// Register select bit
// ===========================================================================


// ===========================================================================
void LCDI2C_expanderWrite( uint8_t _data )
// ===========================================================================
{
	#ifdef LCD_1602_FAST
		I2C_StartTransmission( I2C1, I2C_Direction_Transmitter, lcdi2c.Addr );	// Wire.beginTransmission(_Addr);
		I2C_WriteData( I2C1, ( int ) (_data) | lcdi2c.backlightval );			// printIIC( ( int ) (_data ) | _backlightval );
		I2C_GenerateSTOP( I2C1, ENABLE );										// Wire.endTransmission();
	#else
		I2C_write_one( I2C1, ( lcdi2c.Addr << 1 ), 0, ( _data  | lcdi2c.backlightval ) );
	#endif
}
// ===========================================================================


// ===========================================================================
void LCDI2C_pulseEnable( uint8_t _data )
// ===========================================================================
{
	LCDI2C_expanderWrite( _data | En );		// En high
	delay_us( 1 );							// enable pulse must be >450ns
	LCDI2C_expanderWrite( _data & ~En );	// En low
	delay_us( 50 );							// commands need > 37us to settle
}
// ===========================================================================


// ===========================================================================
void LCDI2C_write4bits( uint8_t value )
// ===========================================================================
{
	LCDI2C_expanderWrite( value );
	LCDI2C_pulseEnable( value );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_send( uint8_t value, uint8_t mode )		// write either command or data
// ===========================================================================
{
	uint8_t		highnib		= value & 0xf0;
	uint8_t		lownib		= ( value << 4 ) & 0xf0;
	LCDI2C_write4bits( ( highnib ) | mode );
	LCDI2C_write4bits( ( lownib ) | mode );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_write( uint8_t value )
// ===========================================================================
{
	LCDI2C_send( value, Rs );
}
// ===========================================================================

/*
	When the display powers up, it is configured as follows:

	1. Display clear
	2. Function set:
	   DL = 1; 8-bit interface data
	   N = 0; 1-line display
	   F = 0; 5x8 dot character font
	3. Display on/off control:
	   D = 0; Display off
	   C = 0; Cursor off
	   B = 0; Blinking off
	4. Entry mode set:
	   I/D = 1; Increment by 1
	   S = 0; No shift

	Note, however, that resetting the Arduino doesn't reset the LCD, so we
	can't assume that its in that state when a sketch starts (and the
	LiquidCrystal constructor is called).
*/

// ===========================================================================
void LCDI2C_command( uint8_t value )
{
	LCDI2C_send( value, 0 );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_clear()	// high level commands, for the user!
// ===========================================================================
{
	LCDI2C_command( LCD_CLEARDISPLAY );		// clear display, set cursor position to zero
	delay_us( 3000 );						// this command takes a long time!
}
// ===========================================================================


// ===========================================================================
void LCDI2C_home()
// ===========================================================================
{
	LCDI2C_command( LCD_RETURNHOME );	// set cursor position to zero
	delay_us( 3000 );					// this command takes a long time!
}
// ===========================================================================


// ===========================================================================
void LCDI2C_display()
// ===========================================================================
{
	lcdi2c.displaycontrol |= LCD_DISPLAYON;
	LCDI2C_command( LCD_DISPLAYCONTROL | lcdi2c.displaycontrol );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_begin( uint8_t cols, uint8_t lines )
// ===========================================================================
{
	if( lines > 1 )
	{
		lcdi2c.displayfunction |= LCD_2LINE;
	}
	lcdi2c.numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	/*
	if( ( dotsize != 0 ) && ( lines == 1 ) )
	{
		_displayfunction |= LCD_5x10DOTS;
	}
	*/

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay_ms( 50 );

	// Now we pull both RS and R/W low to begin commands
	LCDI2C_expanderWrite( lcdi2c.backlightval );	// reset expanderand turn backlight off (Bit 8 =1)
	delay_ms( 1000 );

	// put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	LCDI2C_write4bits( 0x03 << 4 );
	delay_us( 4500 );	// wait min 4.1ms

	// second try
	LCDI2C_write4bits( 0x03 << 4 );
	delay_us( 4500 );	// wait min 4.1ms

	// third go!
	LCDI2C_write4bits( 0x03 << 4 );
	delay_us( 150 );

	// finally, set to 4-bit interface
	LCDI2C_write4bits( 0x02 << 4 );

	// set # lines, font size, etc.
	LCDI2C_command( LCD_FUNCTIONSET | lcdi2c.displayfunction );

	// turn the display on with no cursor or blinking default
	lcdi2c.displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCDI2C_display();

	// clear it off
	LCDI2C_clear();

	// Initialize to default text direction (for roman languages)
	lcdi2c.displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	LCDI2C_command( LCD_ENTRYMODESET | lcdi2c.displaymode );

	LCDI2C_home();
}
// ===========================================================================


// ===========================================================================
void LCDI2C_init( uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows )
{
	lcdi2c.Addr			= lcd_Addr;
	lcdi2c.cols			= lcd_cols;
	lcdi2c.rows			= lcd_rows;
	lcdi2c.backlightval	= LCD_NOBACKLIGHT;

	init_I2C1();	// Wire.begin();
	lcdi2c.displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	LCDI2C_begin( lcd_cols, lcd_rows );

	I2C1_ERR = 0;
	//init_lcd1();
}
// ===========================================================================


// ===========================================================================
void LCDI2C_setCursor( uint8_t col, uint8_t row )
{
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if( row > lcdi2c.numlines )
	{
		row = lcdi2c.numlines - 1;	// we count rows starting w/0
	}
	LCDI2C_command( LCD_SETDDRAMADDR | ( col + row_offsets[row] ) );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_noDisplay()		// Turn the display on/off (quickly)
// ===========================================================================
{
	lcdi2c.displaycontrol &= ~LCD_DISPLAYON;
	LCDI2C_command( LCD_DISPLAYCONTROL | lcdi2c.displaycontrol );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_noCursor()	// Turns the underline cursor on/off
// ===========================================================================
{
	lcdi2c.displaycontrol &= ~LCD_CURSORON;
	LCDI2C_command( LCD_DISPLAYCONTROL | lcdi2c.displaycontrol );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_cursor()
// ===========================================================================
{
	lcdi2c.displaycontrol |= LCD_CURSORON;
	LCDI2C_command( LCD_DISPLAYCONTROL | lcdi2c.displaycontrol );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_noBlink()	// Turn on and off the blinking cursor
// ===========================================================================
{
	lcdi2c.displaycontrol &= ~LCD_BLINKON;
	LCDI2C_command( LCD_DISPLAYCONTROL | lcdi2c.displaycontrol );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_blink()
// ===========================================================================
{
	lcdi2c.displaycontrol |= LCD_BLINKON;
	LCDI2C_command( LCD_DISPLAYCONTROL | lcdi2c.displaycontrol );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_scrollDisplayLeft( void )	// These commands scroll the display without changing the RAM
// ===========================================================================
{
	LCDI2C_command( LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_scrollDisplayRight( void )
// ===========================================================================
{
	LCDI2C_command( LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_leftToRight( void )		// This is for text that flows Left to Right
// ===========================================================================
{
	lcdi2c.displaymode |= LCD_ENTRYLEFT;
	LCDI2C_command( LCD_ENTRYMODESET | lcdi2c.displaymode );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_rightToLeft( void )		// This is for text that flows Right to Left
// ===========================================================================
{
	lcdi2c.displaymode &= ~LCD_ENTRYLEFT;
	LCDI2C_command( LCD_ENTRYMODESET | lcdi2c.displaymode );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_autoscroll( void )	// This will 'right justify' text from the cursor
// ===========================================================================
{
	lcdi2c.displaymode |= LCD_ENTRYSHIFTINCREMENT;
	LCDI2C_command( LCD_ENTRYMODESET | lcdi2c.displaymode );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_noAutoscroll( void )	// This will 'left justify' text from the cursor
// ===========================================================================
{
	lcdi2c.displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	LCDI2C_command( LCD_ENTRYMODESET | lcdi2c.displaymode );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_createChar( uint8_t location, uint8_t charmap[] )
// Allows us to fill the first 8 CGRAM locations with custom characters
// ===========================================================================
{
	int		i;

	location &= 0x7; // we only have 8 locations 0-7
	LCDI2C_command( LCD_SETCGRAMADDR | ( location << 3 ) );
	for( i = 0; i < 8; i++ )
	{
		LCDI2C_write( charmap[i] );
	}
}
// ===========================================================================


// ===========================================================================
void LCDI2C_noBacklight( void )		// Turn the (optional) backlight off/on
// ===========================================================================
{
	lcdi2c.backlightval = LCD_NOBACKLIGHT;
	LCDI2C_expanderWrite( 0 );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_backlight( void )
{
	lcdi2c.backlightval = LCD_BACKLIGHT;
	LCDI2C_expanderWrite( 0 );
}
// ===========================================================================

// Alias functions

// ===========================================================================
void LCDI2C_cursor_on()
// ===========================================================================
{
	LCDI2C_cursor();
}
// ===========================================================================


// ===========================================================================
void LCDI2C_cursor_off()
// ===========================================================================
{
	LCDI2C_noCursor();
}
// ===========================================================================


// ===========================================================================
void LCDI2C_blink_on()
// ===========================================================================
{
	LCDI2C_blink();
}
// ===========================================================================


// ===========================================================================
void LCDI2C_blink_off()
// ===========================================================================
{
	LCDI2C_noBlink();
}
// ===========================================================================


// ===========================================================================
void LCDI2C_load_custom_character( uint8_t char_num, uint8_t *rows )
// ===========================================================================
{
		LCDI2C_createChar( char_num, rows );
}
// ===========================================================================


// ===========================================================================
void LCDI2C_write_String( char *str )
// ===========================================================================
{
	uint8_t		i = 0;

	while( str[i] )
	{
		LCDI2C_write( str[i] );
		i++;
	}
}
// ===========================================================================


// ===========================================================================
void LCD_write_string( uint16_t n, char *str )
// ===========================================================================
{
	uint16_t	i, len;
	char		s[16];

	for( i = 0; i < 16; i++ )
	{
		s[i] = ' ';
	}
	len = strlen( str );
	if( len > 16 )
	{
		len = 16;
	}
	for( i = 0; i < len; i++ )
	{
		s[i] = str[i];
	}
	n--;
	if( n > 1 )
	{
		return;
	}
	LCDI2C_setCursor( 0, n );
	LCDI2C_write_String( s );

	strcpy( (char*) LCD1[n].data, s );
#endif
}
// ===========================================================================
