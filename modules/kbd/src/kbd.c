#include "kbd.h"

#include <avr/io.h>


/*
|---------------------------------------------------------------------------------------
|             |  COL7       COL6    COL5    COL4      COL3    COL2        COL1       COL0     
|             | (0x80)     (0x40)  (0x20)  (0x10)    (0x08)  (0x04)      (0x02)     (0x01)
|-------------|-------------------------------------------------------------------------------
|  ROW7 (0x80)|  STOP       Q       C=      SPACE     2       CTRL        <-         1        
|  ROW6 (0x40)|  /          ^       =       RSHIFT    HOME    ;           *          £        
|  ROW5 (0x20)|  ,          @       :       .         -       L           P          +        
|  ROW4 (0x10)|  N          O       K       M         0       J           I          9        
|  ROW3 (0x08)|  V          U       H       B         8       G           Y          7        
|  ROW2 (0x04)|  X          T       F       C         6       D           R          5        
|  ROW1 (0x02)|  LSHIFT     E       S       Z         4       A           W          3        
|  ROW0 (0x01)|  CRSR DN    F5      F3      F1        F7      CRSR RT     RETURN     DELETE   
---------------------------------------------------------------------------------------

COL = HIGH_BYTE
ROW = LOW_BYTE
*/



/*
#define COL0 PB0
#define COL1 PB1
#define COL2 PB2
#define COL3 PB3
#define COL4 PB4
#define COL5 PB5
#define COL6 PC0
#define COL7 PC1
*/
static int read_column(uint8_t col)
{
	switch(col) {
		case 0: return PINB & _BV(PB0);
		case 1: return PINB & _BV(PB1);
		case 2: return PINB & _BV(PB2);
		case 3: return PINB & _BV(PB3);
		case 4: return PINB & _BV(PB4);
		case 5: return PINB & _BV(PB5);
		case 6: return PINC & _BV(PC0);
		case 7: return PINC & _BV(PC1);
		default: return 1;
	}
}

/*
#define ROW0 PC2
#define ROW1 PC3
#define ROW2 PD2
#define ROW3 PD3
#define ROW4 PD4
#define ROW5 PD5
#define ROW6 PD6
#define ROW7 PD7
*/
static void enable_row(uint8_t row)
{
	DDRC &= ~(_BV(PC2) | _BV(PC3));
	DDRD &= ~(_BV(PD2) | _BV(PD3) | _BV(PD4)| _BV(PD5)| _BV(PD6)| _BV(PD7));

	switch(row) {
		case 0: DDRC |= _BV(PC2); break;
		case 1: DDRC |= _BV(PC3); break;
		case 2: DDRD |= _BV(PD2); break;
		case 3: DDRD |= _BV(PD3); break;
		case 4: DDRD |= _BV(PD4); break;
		case 5: DDRD |= _BV(PD5); break;
		case 6: DDRD |= _BV(PD6); break;
		case 7: DDRD |= _BV(PD7); break;
		default: break;
	}
}

static void print_key(const struct kbd_cfg *cfg, uint16_t keycode)
{
	// clang-format off
	switch(keycode) {
		case 0x0402: cfg->print_cb("A"); break;
		case 0x1008: cfg->print_cb("B"); break;
		case 0x1004: cfg->print_cb("C"); break;
		case 0x0404: cfg->print_cb("D"); break;
		case 0x4002: cfg->print_cb("E"); break;
		case 0x2004: cfg->print_cb("F"); break;
		case 0x0408: cfg->print_cb("G"); break;
		case 0x2008: cfg->print_cb("H"); break;
		case 0x0210: cfg->print_cb("I"); break;
		case 0x0410: cfg->print_cb("J"); break;
		case 0x2010: cfg->print_cb("K"); break;
		case 0x0420: cfg->print_cb("L"); break;
		case 0x1010: cfg->print_cb("M"); break;
		case 0x8010: cfg->print_cb("N"); break;
		case 0x4010: cfg->print_cb("O"); break;
		case 0x0220: cfg->print_cb("P"); break;
		case 0x4080: cfg->print_cb("Q"); break;
		case 0x0204: cfg->print_cb("R"); break;
		case 0x2002: cfg->print_cb("S"); break;
		case 0x4004: cfg->print_cb("T"); break;
		case 0x4008: cfg->print_cb("U"); break;
		case 0x8008: cfg->print_cb("V"); break;
		case 0x0202: cfg->print_cb("W"); break;
		case 0x8004: cfg->print_cb("X"); break;
		case 0x0208: cfg->print_cb("Y"); break;
		case 0x1002: cfg->print_cb("Z"); break;

		case 0x0810: cfg->print_cb("0"); break;
		case 0x0180: cfg->print_cb("1"); break;
		case 0x0880: cfg->print_cb("2"); break;
		case 0x0102: cfg->print_cb("3"); break;
		case 0x0802: cfg->print_cb("4"); break;
		case 0x0104: cfg->print_cb("5"); break;
		case 0x0804: cfg->print_cb("6"); break;
		case 0x0108: cfg->print_cb("7"); break;
		case 0x0808: cfg->print_cb("8"); break;
		case 0x0110: cfg->print_cb("9"); break;
 
		case 0x8020: cfg->print_cb(","); break;
		case 0x1020: cfg->print_cb("."); break;

		case 0x8001: cfg->print_cb("\033[1A"); break; // cursor up
		case 0x9041: cfg->print_cb("\033[1B"); break; // cursor down
		case 0x0401: cfg->print_cb("\033[1C"); break; // cursor right
		case 0x1441: cfg->print_cb("\033[1D"); break; // cursor left
		case 0x0201: cfg->print_cb("\r\n"); break; // return 
		case 0x0101: cfg->print_cb("\b"); break; // delete
		case 0x0480: cfg->print_cb("\033[2J"); break; // clear
		
		

		default: return;
	}
	// clang-format on
}

void kbd_init(const struct kbd_cfg *cfg)
{
	// enable pullups for columns
	PORTB |= (_BV(PB0) |_BV(PB1) |_BV(PB2) |_BV(PB3) |_BV(PB4) |_BV(PB5) );
	PORTC |= (_BV(PC0) |_BV(PC1));
}

void kbd_printkeys(const struct kbd_cfg *cfg)
{

	uint16_t result = 0;
	
	for( uint8_t row=0; row < 8; row++)
	{
		enable_row(row);

		for( uint8_t col=0; col < 8; col++)
		{

			if( !read_column(col) )
			{
				result |=  (_BV(row)<<8) | _BV(col);
				
			}
			
		}
	}

	if( result != 0)
		print_key(cfg, result);
}