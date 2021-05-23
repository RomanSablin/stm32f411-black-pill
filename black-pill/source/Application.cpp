#include <Application.h>

#include <thread.hpp>
#include <ticks.hpp>
#include <string.h>

#include "Board.h"
#include "Uart.h"

using namespace cpp_freertos;

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
		CBoard::mUserLed.Toggle();
//		uart.Send((uint8_t *) "Hello, World\r\n", 14);
		Thread::Delay(Ticks::MsToTicks(1000));
	}
}
