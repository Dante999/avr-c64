#include <avr/io.h>

#include "kbd.h"


static void print_uart(const char *s)
{
	(void) s;
}

int main(void)
{
	struct kbd_cfg kbd_config = {print_uart};


	kbd_init(&kbd_config);

	while(1)
	{
		// do nothing
	}

	return 0;
}