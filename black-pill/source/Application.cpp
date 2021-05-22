#include <Application.h>

#include <thread.hpp>
#include <ticks.hpp>
#include <string.h>

#include "Board.h"
#include "Uart.h"

CApplication::CApplication()
	: Thread("App", 1024, 4)
{

}

void CApplication::Run()
{
	CUart uart(USART1);
	uart.Init();

	for (;;)
	{
		uart.Send((uint8_t *) "Hello, World\r\n", 14);
		HAL_Delay(1000);
	}
}
