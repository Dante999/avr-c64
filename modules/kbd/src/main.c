#include <avr/io.h>

#include "kbd.h"
#include "uart.h"

static void print_uart(const char *s)
{
	(void) s;
}

int main(void)
{
	struct kbd_cfg kbd_config = {print_uart};


	kbd_init(&kbd_config);
	uart_init();

	while(1)
	{
		uart_puts("hello world");
	}

	return 0;
}