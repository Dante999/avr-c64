#ifndef KBD_KEYMAP_H
#define KBD_KEYMAP_H

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
*/

struct keytoascii = 
{
	uint16_t keycode,
	uint8_t ascii
};

/*
* LOWBYTE  = COLUMN
* HIGHBYTE = ROW
*/
static struct keytoascii keymap[] = 
{
	{0x0402, 'A'},
	{0x1080, 'B'},
	{0x1004, 'C'},
	{0x0404, 'D'},
	{0x1080, 'E'},
	{0x2004, 'F'},
	{0x0408, 'G'},
	{0x2008, 'H'},
	{0x0210, 'I'},
	{0x0410, 'J'},
	{0x2010, 'K'},
	{0x0420, 'L'},
	{0x1010, 'M'},
	{0x8010, 'N'},
	{0x4010, 'O'},
	{0x0220, 'P'},
	{0x4080, 'Q'},
	{0x0204, 'R'},
	{0x2002, 'S'},
	{0x4004, 'T'},
	{0x4008, 'U'},
	{0x8008, 'V'},
	{0x0202, 'W'},
	{0x8004, 'X'},
	{0x0208, 'Y'},
	{0x1002, 'Z'},
};



#endif
