#include <Application.h>

#include <thread.hpp>
#include <ticks.hpp>
#include <string.h>

#include "Board.h"

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
		Thread::Delay(Ticks::MsToTicks(1000));
	}
}
