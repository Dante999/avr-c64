#include "kbd.h"

#include <avr/io.h>




#define ROW0() (DDRC, PORTC, PC2)

/*
#define ROW0 PC2
#define ROW1 PC3
#define ROW2 PD2
#define ROW3 PD3
#define ROW4 PD4
#define ROW5 PD5
#define ROW6 PD6
#define ROW7 PD7

#define COL0 PB0
#define COL1 PB1
#define COL2 PB2
#define COL3 PB3
#define COL4 PB4
#define COL5 PB5
#define COL6 PC0
#define COL7 PC1
*/

#define SET_COL0() (DDRB |= (1<<COL0))
#define CLEAR_COL0() (DDRB &= ~(1<<COL0))



static void select_column(uint8_t col)
{

}

static void print_key(const struct kbd_cfg *cfg, uint16_t keycode)
{
	// clang-format off
	switch(keycode) {
		case 0x0402: cfg->print_cb("A");
		case 0x1008: cfg->print_cb("B");
		case 0x1004: cfg->print_cb("C");
		case 0x0404: cfg->print_cb("D");
		case 0x4002: cfg->print_cb("E");
		case 0x2004: cfg->print_cb("F");
		case 0x0408: cfg->print_cb("G");
		case 0x2008: cfg->print_cb("H");
		case 0x0210: cfg->print_cb("I");
		case 0x0410: cfg->print_cb("J");
		case 0x2010: cfg->print_cb("K");
		case 0x0420: cfg->print_cb("L");
		case 0x1010: cfg->print_cb("M");
		case 0x8010: cfg->print_cb("N");
		case 0x4010: cfg->print_cb("O");
		case 0x0220: cfg->print_cb("P");
		case 0x4080: cfg->print_cb("Q");
		case 0x0204: cfg->print_cb("R");
		case 0x2002: cfg->print_cb("S");
		case 0x4004: cfg->print_cb("T");
		case 0x4008: cfg->print_cb("U");
		case 0x8008: cfg->print_cb("V");
		case 0x0202: cfg->print_cb("W");
		case 0x8004: cfg->print_cb("X");
		case 0x0208: cfg->print_cb("Y");
		case 0x1002: cfg->print_cb("Z");

		case 0x0810: cfg->print_cb("0");
		case 0x0180: cfg->print_cb("1");
		case 0x0880: cfg->print_cb("2");
		case 0x0102: cfg->print_cb("3");
		case 0x0802: cfg->print_cb("4");
		case 0x0104: cfg->print_cb("5");
		case 0x0804: cfg->print_cb("6");
		case 0x0108: cfg->print_cb("7");
		case 0x0808: cfg->print_cb("8");
		case 0x0110: cfg->print_cb("9");

		case 0x8020: cfg->print_cb(",");
		case 0x1020: cfg->print_cb(".");

		case 0x8001: cfg->print_cb("\033[1A"); // cursor up
		case 0x9001: cfg->print_cb("\033[1B"); // cursor down
		case 0x0401: cfg->print_cb("\033[1C"); // cursor right
		case 0x1401: cfg->print_cb("\033[1D"); // cursor left
		
		

		default: return;
	}
	// clang-format on
}

void kbd_init(const struct kbd_cfg *cfg)
{
	DDRD |= ~( (1<<PD0) | (1<<PD1)); 
}

