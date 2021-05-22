#include <stdio.h>
#include "Board.h"
#include "Uart.h"

int main(int argc, char **argv)
{
	CBoard::Init();
	CUart uart(USART1);
	uart.Init();

	for (;;)
	{
		uart.Send((uint8_t *) "Hello, World\r\n", 14);
		HAL_Delay(1000);
	}

	return 0;
}
