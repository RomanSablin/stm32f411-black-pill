#include <Application.h>

#include <thread.hpp>
#include <ticks.hpp>
#include <string.h>

#include "Board.h"

extern "C"
{
#include "ssd1306_tests.h"
}

using namespace cpp_freertos;

CApplication::CApplication()
	: Thread("App", 1024, 4)
{

}

void CApplication::Run()
{
	ssd1306_TestAll();

	for (;;)
	{
		CBoard::mUserLed.Toggle();
		Thread::Delay(Ticks::MsToTicks(1000));
	}
}
