#include <avr/io.h>
#include <util/delay.h>

#include "kbd.h"
#include "uart.h"

static void print_uart(const char *s)
{
	(void) s;
}

int main(void)
{
	struct kbd_cfg kbd_config = {uart_puts};

	kbd_init(&kbd_config);
	uart_init();

	while(1)
	{
		_delay_ms(100);
		kbd_printkeys(&kbd_config);
	}

	return 0;
}